/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabase.cpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <deque>

#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlRecord>
#include <QStandardPaths>
#include <QThread>

#include "IntraDatabase.hpp"
#include "IntraEvent.hpp"
#include "IntraProject.hpp"
#include "IntraSession.hpp"

void IntraDatabase::open(const QString &path) {
	if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
		throw std::runtime_error("SQLite required!");

	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(path);
	if (!m_database.open()) {
		qWarning() << "Error: " << m_database.lastError();
		throw std::runtime_error("Error: Failed to load database: " + path.toStdString());
	}
}

void IntraDatabase::update() {
	createTables();
	updateUnits();
}

void IntraDatabase::createTables() {
	m_activityFields = {
		{"module_id",      "INTEGER"},
		{"name",           "TEXT"},
		{"type_code",      "TEXT"},
		{"type_title",     "TEXT"},
		{"begin_date",     "DATETIME"},
		{"end_date",       "DATETIME"},
		{"register_date",  "DATETIME"},
		{"is_registrable", "INTEGER"},
		{"is_appointment", "INTEGER"},
		{"is_project",     "INTEGER"},
		{"project_id",     "INTEGER"},
		{"project_name",   "INTEGER"},
	};

	m_eventFields = {
		{"activity_id",      "INTEGER"},
		{"name",             "TEXT"},
		{"building_name",    "TEXT"},
		{"room_name",        "TEXT"},
		{"begin_date",       "DATETIME"},
		{"end_date",         "DATETIME"},
		{"appointment_date", "DATETIME"},
		{"is_registrable",   "INTEGER"},
		{"is_registered",    "INTEGER"},
		{"is_missed",        "INTEGER"},
	};

	m_projectFields = {
		{"activity_id",    "INTEGER"},
		{"name",           "TEXT"},
		{"is_registrable", "INTEGER"},
		{"is_registered",  "INTEGER"},
	};

	m_unitFields = {
		{"name",           "TEXT"},
		{"link",           "TEXT"},
		{"semester",       "INTEGER"},
		{"credit_count",   "INTEGER"},
		{"is_registrable", "INTEGER"},
		{"is_registered",  "INTEGER"},
		{"flags",          "INTEGER"},
	};

	m_tables = {
		{"activities", &m_activityFields},
		{"events",     &m_eventFields},
		{"projects",   &m_projectFields},
		{"units",      &m_unitFields}
	};

	for (auto &it : m_tables) {
		if (m_database.tables().contains(it.first.c_str())) {
			// FIXME: Change record instead of dropping the entire table
			if (m_database.record(it.first.c_str()).count() != it.second->size() + 1) {
				qDebug() << "Removing deprecated table '" << it.first.c_str() << "'...";

				QSqlQuery query(QString("drop table ") + it.first.c_str());
				if (!query.isActive())
					qWarning() << "Error: Failed to remove deprecated table '" << it.first.c_str() << "' from database:" << query.lastError().text();
			}
		}

		if (!m_database.tables().contains(it.first.c_str())) {
			std::string queryString = "create table " + it.first + "(id INTEGER unique primary key,";
			for (auto field = it.second->begin() ; field != it.second->end() ; ++field) {
				queryString += field->first + " " + field->second;
				queryString += (std::next(field) == it.second->end()) ? ")" : ",";
			}

			QSqlQuery query(queryString.c_str());
			if (!query.isActive())
				qWarning() << "Error: Failed to create database table '" << it.first.c_str() << "':" << query.lastError().text();
		}
	}
}

void IntraDatabase::updateUnits() {
	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray unitArray = json.array();
	if (unitArray.isEmpty())
		return;

	emit updateStarted();

	m_database.exec("begin;");

	size_t i = 0;
	for (QJsonValue value : unitArray) {
		IntraModule module(value.toObject());

		updateActivities(module);

		addTableEntry("units", module.id(),
		                       module.name(),
		                       module.link(),
		                       module.semester(),
		                       module.creditCount(),
		                       module.isRegistrable(),
		                       module.isRegistered(),
		                       module.flags());

		emit updateProgressed(i++ * 100 / unitArray.size());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}

	m_database.exec("commit;");

	emit updateProgressed(i++ * 100 / unitArray.size());
	emit updateFinished();
}

void IntraDatabase::updateActivities(const IntraModule &unit) {
	QJsonDocument json = IntraSession::getInstance().get(unit.link());
	QJsonArray activityArray = json.object().value("activites").toArray();
	if (activityArray.isEmpty())
		return;

	size_t i = 0;
	for (QJsonValue value : activityArray) {
		IntraActivity activity(unit, value.toObject());

		if (activity.isProject())
			updateProjects(activity);

		updateEvents(activity, value.toObject());

		addTableEntry("activities", activity.id(),
		                            activity.module().id(),
		                            activity.name(),
		                            activity.typeCode(),
		                            activity.typeTitle(),
		                            activity.beginDate(),
		                            activity.endDate(),
		                            activity.registerDate(),
		                            activity.isRegistrable(),
		                            activity.isAppointment(),
		                            activity.isProject(),
		                            activity.projectId(),
		                            activity.projectName());

		emit unitUpdateProgressed(i++ * 100 / activityArray.size());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}

	emit unitUpdateProgressed(i++ * 100 / activityArray.size());
}

void IntraDatabase::updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject) {
	QJsonArray eventArray = jsonObject.value("events").toArray();
	for (QJsonValue value : eventArray) {
		IntraEvent event(activity, value.toObject());

		addTableEntry("events", event.id(),
		                        event.activity().id(),
		                        event.activity().name(),
		                        event.buildingName(),
		                        event.roomName(),
		                        event.beginDate(),
		                        event.endDate(),
		                        event.appointmentDate(),
		                        event.isRegistrable(),
		                        event.isRegistered(),
		                        event.isMissed());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}
}

void IntraDatabase::updateProjects(const IntraActivity &activity) {
	QJsonDocument json = IntraSession::getInstance().get(activity.link() + "/project");
	IntraProject project(activity, json.object());

	addTableEntry("projects", project.id(),
	                          project.activity().id(),
	                          project.name(),
	                          project.isRegistrable(),
	                          project.isRegistered());
}

