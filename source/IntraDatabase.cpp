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
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#include "IntraData.hpp"
#include "IntraEvent.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraSession.hpp"
#include "IntraUser.hpp"

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

void IntraDatabase::clear() const {
	for (QString table : m_database.tables()) {
		removeTable(table);
	}
}

void IntraDatabase::update() const {
	updateUser();
	updateNotifications();
	updateUnits();
}

void IntraDatabase::addTable(const QString &name, const std::map<QString, QVariant> &fields) {
	QString queryString = "create table " + name + "(id INTEGER unique primary key";
	for (auto it : fields) {
		queryString += "," + it.first + " ";

		switch (it.second.type()) {
			case QVariant::Type::Int:
			case QVariant::Type::UInt:      queryString += "INTEGER"; break;
			case QVariant::Type::Bool:      queryString += "BOOLEAN"; break;
			case QVariant::Type::ByteArray:
			case QVariant::Type::Url:
			case QVariant::Type::String:    queryString += "TEXT"; break;
			case QVariant::Type::Date:      queryString += "DATE"; break;
			case QVariant::Type::DateTime:  queryString += "DATETIME"; break;
			default: break;
		}
	}
	queryString += ")";

	QSqlQuery query(queryString);
	if (!query.isActive())
		qWarning() << "Error: Failed to create database table '" << name << "':" << query.lastError().text();
}

void IntraDatabase::removeTable(const QString &name) {
	QSqlDatabase database = QSqlDatabase::database();
	if (!database.tables().contains(name))
		return;

	QSqlQuery query(QString("drop table ") + name);
	if (!query.isActive())
		qWarning() << "Error: Failed to remove table '" << name << "' from database:" << query.lastError().text();
}

void IntraDatabase::updateUser() const {
	QJsonDocument json = IntraSession::getInstance().get("/user");
	IntraUser user(json.object());
	user.updateDatabaseTable();
	user.writeToDatabase();

	emit userUpdateFinished();
}

void IntraDatabase::updateNotifications() const {
	QJsonDocument json = IntraSession::getInstance().get("/");
	QJsonArray notificationArray = json.object().value("history").toArray();
	if (notificationArray.isEmpty())
		return;

	m_database.exec("begin;");

	for (QJsonValue value : notificationArray) {
		IntraNotification notification(value.toObject());
		notification.updateDatabaseTable();
		notification.writeToDatabase();
	}

	m_database.exec("commit;");

	emit notificationUpdateFinished();
}

void IntraDatabase::updateUnits() const {
	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray unitArray = json.array();
	if (unitArray.isEmpty())
		return;

	emit updateStarted();

	m_database.exec("begin;");

	size_t i = 0;
	for (QJsonValue value : unitArray) {
		IntraModule module(value.toObject());
		if (module.semester() == 0 || module.semester() == IntraData::getInstance().userInfo().currentSemester()) {
			module.updateDatabaseTable();
			module.writeToDatabase();

			updateActivities(module);
		}

		emit updateProgressed(i++ * 100 / unitArray.size());

		if (QThread::currentThread()->isInterruptionRequested()) {
			m_database.exec("commit;");
			return;
		}
	}

	m_database.exec("commit;");

	emit updateProgressed(i++ * 100 / unitArray.size());
	emit updateFinished();
}

void IntraDatabase::updateActivities(const IntraModule &unit) const {
	QJsonDocument json = IntraSession::getInstance().get(unit.link());
	QJsonArray activityArray = json.object().value("activites").toArray();
	if (activityArray.isEmpty())
		return;

	size_t i = 0;
	for (QJsonValue value : activityArray) {
		IntraActivity activity(unit, value.toObject());
		activity.updateDatabaseTable();
		activity.writeToDatabase();

		if (activity.isProject())
			updateProjects(activity);

		updateEvents(activity, value.toObject());

		emit unitUpdateProgressed(i++ * 100 / activityArray.size());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}

	emit unitUpdateProgressed(i++ * 100 / activityArray.size());
	emit unitUpdateFinished();
}

void IntraDatabase::updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject) const {
	QJsonArray eventArray = jsonObject.value("events").toArray();
	for (QJsonValue value : eventArray) {
		IntraEvent event(activity, value.toObject());
		event.updateDatabaseTable();
		event.writeToDatabase();

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}
}

void IntraDatabase::updateProjects(const IntraActivity &activity) const {
	QJsonDocument json = IntraSession::getInstance().get(activity.link() + "/project");
	IntraProject project(activity, json.object());
	project.updateDatabaseTable();
	project.writeToDatabase();
}

