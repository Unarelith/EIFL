/*
 * =====================================================================================
 *
 *       Filename:  IntraEvent.cpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 02:01:18
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QJsonObject>

#include "IntraData.hpp"
#include "IntraEvent.hpp"

IntraEvent::IntraEvent(unsigned int activityId, const QJsonObject &jsonObject) : IntraItem("events") {
	const IntraActivity *activity = nullptr;
	if (activityId != 0)
		activity = IntraData::getInstance().getActivity(activityId);

	m_id = jsonObject.value("code").toString().mid(6).toUInt();

	set("activity_id", activityId);

	// FIXME: Find a better way to get this information
	set("is_registrable", activity && activity->isRegistrable());
	set("is_registered", !jsonObject.value("already_register").isNull() || (activity && activity->isAppointmentRegistered()));
	set("is_missed", jsonObject.value("user_status").toString() == "absent");
	set("is_token_writable", jsonObject.value("allow_token").toString().toInt());

	set("building_name", "");
	set("room_name", "");

	QStringList roomInfos = jsonObject.value("location").toString().split('/');
	if (roomInfos.size() > 2)
		set("building_name", roomInfos.at(2));
	if (roomInfos.size() > 3)
		set("room_name", roomInfos.at(3));

	set("begin_date", QDateTime::fromString(jsonObject.value("begin").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("end_date", QDateTime::fromString(jsonObject.value("end").toString(), "yyyy-MM-dd HH:mm:ss"));
}

