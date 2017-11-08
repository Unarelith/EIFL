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

#include "IntraEvent.hpp"

IntraEvent::IntraEvent(const IntraActivity &activity, const QJsonObject &jsonObject) : IntraItem("events"), m_activity(activity) {
	m_id = jsonObject.value("code").toString().mid(6).toUInt();

	set("activity_id", m_activity.id());

	// FIXME: Find a better way to get this information
	set("is_registrable", m_activity.isRegistrable());
	set("is_registered", !jsonObject.value("already_register").isNull() || m_activity.isAppointmentRegistered());
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

