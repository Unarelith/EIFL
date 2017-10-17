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
#include <QJsonObject>

#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

void IntraData::update() {
	updateModuleList();
	updateProjectList();
}

void IntraData::updateModuleList() {
	m_moduleList.clear();

	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray projectArray = json.array();
	for (QJsonValue value : projectArray) {
		m_moduleList.emplace_back(value.toObject());
	}

	// std::sort(m_projectList.begin(), m_projectList.end(), [&] (const IntraProject &p1, const IntraProject &p2) {
	// 	return p1.isRegistered() && !p2.isRegistered();
	// });
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QJsonDocument json = IntraSession::getInstance().get("/");
	QJsonArray projectArray = json.object().value("board").toObject().value("projets").toArray();
	for (QJsonValue value : projectArray) {
		m_projectList.emplace_back(value.toObject());
	}

	// std::sort(m_projectList.begin(), m_projectList.end(), [&] (const IntraProject &p1, const IntraProject &p2) {
	// 	return p1.isRegistered() && !p2.isRegistered();
	// });
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

