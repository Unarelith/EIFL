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

const IntraData *IntraData::s_instance = nullptr;

void IntraData::update() {
	m_projectList.clear();

	QJsonDocument json = m_session.get("/");
	updateProjectList(json);
}

void IntraData::updateProjectList(const QJsonDocument &json) {
	QJsonArray projectArray = json.object().value("board").toObject().value("projets").toArray();
	for (QJsonValue value : projectArray) {
		m_projectList.emplace_back(value.toObject());
	}
}

std::deque<IntraEvent> IntraData::getEventList(const QDate &date) const {
	QString dateString = date.toString("yyyy-MM-dd");
	QJsonDocument json = m_session.get("/planning/load", {std::make_pair("start", dateString.toStdString()),
	                                                      std::make_pair("end", dateString.toStdString()),
	                                                      std::make_pair("semester", "5")});
	// FIXME: SEMESTER IS HARDCODED, BUUUUH

	std::deque<IntraEvent> eventList;
	for (QJsonValue value : json.array()) {
		eventList.emplace_back(value.toObject());
	}

	return eventList;
}

