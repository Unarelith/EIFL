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
#include <QJsonObject>

#include "IntraProject.hpp"

IntraProject::IntraProject(const IntraActivity &activity, const QJsonObject &jsonObject) : IntraItem("projects"), m_activity(activity) {
	m_id = activity.id();

	set("activity_id", m_activity.id());

	set("name", jsonObject.value("title").toString());

	set("is_registrable", !jsonObject.value("closed").toBool() && m_activity.registerDate().isValid());
	set("is_registered", !jsonObject.value("user_project_title").isNull());
}

