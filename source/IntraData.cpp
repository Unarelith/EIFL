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

const IntraData *IntraData::s_instance = nullptr;

void IntraData::update() {
	updateProjectList();
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QJsonDocument json = IntraSession::getInstance().get("/");
	QJsonArray projectArray = json.object().value("board").toObject().value("projets").toArray();
	for (QJsonValue value : projectArray) {
		m_projectList.emplace_back(value.toObject());
	}

	std::sort(m_projectList.begin(), m_projectList.end(), [&] (const IntraProject &p1, const IntraProject &p2) {
		return p1.isRegistered() && !p2.isRegistered();
	});
}

std::deque<IntraEvent> IntraData::getEventList(const QDate &date, const std::vector<int> &semesters) const {
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

IntraUser IntraData::getUserInfo(const QString &username) const {
	QJsonDocument json = IntraSession::getInstance().get("/user/" + username);
	return {json.object()};
}

