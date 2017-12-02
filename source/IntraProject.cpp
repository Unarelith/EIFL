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

#include "IntraData.hpp"
#include "IntraProject.hpp"

IntraProject::IntraProject(unsigned int activityId, const QJsonObject &jsonObject) : IntraItem("projects") {
	const IntraActivity *activity = nullptr;
	if (activityId != 0)
		activity = IntraData::getInstance().getActivity(activityId);

	m_id = activityId;

	set("activity_id", activityId);

	set("name", jsonObject.value("title").toString());

	set("register_state", static_cast<int>(RegisterState::Locked));

	if (activity && !jsonObject.value("closed").toBool() && activity->registerDate().isValid())
		set("register_state", static_cast<int>(RegisterState::Registrable));

	if (!jsonObject.value("user_project_title").isNull())
		set("register_state", static_cast<int>(RegisterState::Registered));
}

IntraProject::IntraProject(const QJsonObject &jsonObject) : IntraItem("projects") {
	m_id = jsonObject.value("id_activite").toString().toUInt();

	const IntraActivity *activity = nullptr;
	if (m_id != 0)
		activity = IntraData::getInstance().getActivity(m_id);

	set("activity_id", m_id);

	set("name", jsonObject.value("title").toString());

	set("register_state", static_cast<int>(RegisterState::Unknown));

	if (activity && activity->isRegistrable())
		set("register_state", static_cast<int>(RegisterState::Registrable));
}

