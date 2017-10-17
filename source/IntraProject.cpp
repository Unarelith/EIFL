/*
 * =====================================================================================
 *
 *       Filename:  IntraProject.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:07:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "IntraProject.hpp"
#include "IntraSession.hpp"

IntraProject::IntraProject(const QJsonObject &jsonObject) {
	m_name = jsonObject.value("title").toString();
	m_link = jsonObject.value("title_link").toString();

	// FIXME: project.deadline should be used instead of timeline_end
	m_beginDate = QDateTime::fromString(jsonObject.value("timeline_start").toString(), "dd/MM/yyyy, HH:mm");
	m_endDate = QDateTime::fromString(jsonObject.value("timeline_end").toString(), "dd/MM/yyyy, HH:mm");
	m_registerDate = QDateTime::fromString(jsonObject.value("date_inscription").toString(), "dd/MM/yyyy, HH:mm");

	m_id = jsonObject.value("id_activite").toInt();

	// FIXME: Update should process dates too
	update();
}

void IntraProject::update() {
	QJsonDocument json = IntraSession::getInstance().get(m_link + "project/");

	m_isRegistrable = !json.object().value("closed").toBool();
	m_isRegistered = !json.object().value("user_project_title").isNull();
}

