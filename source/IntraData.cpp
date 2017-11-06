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
#include <QJsonArray>

#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

void IntraData::update() {
	m_overviewJson = IntraSession::getInstance().get("/");

	updateModuleList();
	updateNotificationList();
	updateProjectList();
}

void IntraData::updateModuleList() {
	m_moduleList.clear();

	m_database.updateUnits();

	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray projectArray = json.array();
	for (QJsonValue value : projectArray) {
		m_moduleList.emplace_back(value.toObject());
	}
}

void IntraData::updateNotificationList() {
	m_notificationList.clear();

	QJsonArray notificationArray = m_overviewJson.object().value("history").toArray();
	for (QJsonValue value : notificationArray) {
		m_notificationList.emplace_back(value.toObject());
	}
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QJsonArray projectArray = m_overviewJson.object().value("board").toObject().value("projets").toArray();
	for (QJsonValue value : projectArray) {
		m_projectList.emplace_back(value.toObject());
	}
}

std::deque<IntraEvent> IntraData::getEventList(const QDate &date, const std::vector<unsigned int> &semesters) const {
	QString semesterString;
	for (int n : semesters)
		semesterString += QString::number(n) + ",";
	semesterString.chop(1);

	QString dateString = date.toString("yyyy-MM-dd");
	QJsonDocument json = IntraSession::getInstance().get("/planning/load", {
		std::make_pair("start", dateString),
		std::make_pair("end", dateString),
		std::make_pair("semester", semesterString)
	});

	std::deque<IntraEvent> eventList;
	for (QJsonValue value : json.array()) {
		eventList.emplace_back(value.toObject());
	}

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

