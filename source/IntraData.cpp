/*
 * =====================================================================================
 *
 *       Filename:  IntraData.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:48:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QApplication>
#include <QJsonArray>
#include <QProgressDialog>
#include <QSqlRecord>

#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

void IntraData::openDatabase(const QString &path) {
	m_database->open(path);
}

void IntraData::updateDatabase() {
	IntraDatabaseThread *thread = new IntraDatabaseThread(this, m_database);
	connect(m_database.get(), &IntraDatabase::updateFinished, this, &IntraData::update);
	connect(thread, &QThread::finished, thread, &QObject::deleteLater);
	thread->start();
}

void IntraData::update() {
	m_overviewJson = IntraSession::getInstance().get("/");
	updateNotificationList();

	updateModuleList();
	updateActivityList();
	updateEventList();
	updateProjectList();

	emit databaseUpdateFinished();
}

void IntraData::updateNotificationList() {
	m_notificationList.clear();

	QJsonArray notificationArray = m_overviewJson.object().value("history").toArray();
	for (QJsonValue value : notificationArray) {
		m_notificationList.emplace_back(value.toObject());
	}
}

void IntraData::updateModuleList() {
	m_moduleList.clear();

	QSqlQuery query("SELECT * FROM units");
	while (query.next()) {
		IntraModule module{query};
		m_moduleList.emplace(module.id(), std::move(module));
	}
}

void IntraData::updateActivityList() {
	m_activityList.clear();

	QSqlQuery query("SELECT * FROM activities");
	while (query.next()) {
		unsigned int moduleId = query.value(query.record().indexOf("module_id")).toUInt();
		auto it = m_moduleList.find(moduleId);
		if (it == m_moduleList.end()) {
			throw std::runtime_error("Error: Unable to find module with id " + std::to_string(moduleId));
		}

		IntraActivity activity{it->second, query};
		m_activityList.emplace(activity.id(), std::move(activity));
	}
}

void IntraData::updateEventList() {
	m_eventList.clear();

	QSqlQuery query("SELECT * FROM events");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		auto it = m_activityList.find(activityId);
		if (it == m_activityList.end()) {
			throw std::runtime_error("Error: Unable to find activity with id " + std::to_string(activityId));
		}

		IntraEvent event{it->second, query};
		m_eventList.emplace(event.id(), std::move(event));
	}
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QSqlQuery query("SELECT * FROM projects");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		auto it = m_activityList.find(activityId);
		if (it == m_activityList.end()) {
			throw std::runtime_error("Error: Unable to find activity with id " + std::to_string(activityId));
		}

		IntraProject project{it->second, query};
		m_projectList.emplace(project.id(), std::move(project));
	}
}

std::deque<IntraEvent> IntraData::getEventList(const QDate &date, const QList<unsigned int> &semesters) const {
	// QString semesterString;
	// for (int n : semesters)
	// 	semesterString += QString::number(n) + ",";
	// semesterString.chop(1);
	//
	// QString dateString = date.toString("yyyy-MM-dd");
	// QJsonDocument json = IntraSession::getInstance().get("/planning/load", {
	// 	std::make_pair("start", dateString),
	// 	std::make_pair("end", dateString),
	// 	std::make_pair("semester", semesterString)
	// });

	std::deque<IntraEvent> eventList;
	for (auto it : m_eventList) {
		if (semesters.contains(it.second.activity().module().semester()) && (it.second.beginDate().date() == date || it.second.endDate().date() == date)) {
			eventList.emplace_back(it.second);
		}
	}
	// for (QJsonValue value : json.array()) {
	// 	eventList.emplace_back(value.toObject());
	// }

	return eventList;
}

IntraUser IntraData::getUserInfo(const QString &login) {
	auto it = m_userInfoCache.find(login);
	if (it == m_userInfoCache.end()) {
		QJsonDocument json = IntraSession::getInstance().get("/user/" + login);
		auto r = m_userInfoCache.emplace(login, json.object());
		return r.first->second;
	}

	return it->second;
}

