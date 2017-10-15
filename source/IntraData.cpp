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

