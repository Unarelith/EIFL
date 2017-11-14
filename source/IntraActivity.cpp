/*
 * =====================================================================================
 *
 *       Filename:  IntraActivity.cpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 08:19:31
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "IntraActivity.hpp"
#include "IntraSession.hpp"

IntraActivity::IntraActivity(const IntraModule &module, const QJsonObject &jsonObject) : IntraItem("activities"), m_module(module) {
	m_id = jsonObject.value("codeacti").toString().mid(5).toUInt();

	set("module_id", module.id());

	set("name", jsonObject.value("title").toString());

	set("type_code", jsonObject.value("type_code").toString());
	set("type_title", jsonObject.value("type_title").toString());

	// FIXME: Find the difference between 'begin' and 'start' or 'deadline' and 'end'
	set("begin_date", QDateTime::fromString(jsonObject.value("begin").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("end_date", QDateTime::fromString(jsonObject.value("end").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("register_date", QDateTime::fromString(jsonObject.value("end_register").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("appointment_date", {});

	set("is_registrable", m_module.isRegistered() && jsonObject.value("register").toString().toUInt());
	set("is_appointment", jsonObject.value("rdv_status").toString() == "open");
	set("is_appointment_registered", false);

	set("is_project", jsonObject.value("is_projet").toBool());
	set("project_id", jsonObject.value("id_projet").toString().toUInt());
	set("project_name", jsonObject.value("project_title").toString());

	if (isAppointment() && m_module.isRegistered()) {
		QJsonDocument json = IntraSession::getInstance().get(m_module.link() + "/acti-" + QString::number(id()) + "/rdv");

		// FIXME: Find a better way to get this information
		set("is_appointment_registered", json.object().value("student_registered").toBool()
		                              && json.object().value("with_project").toBool());

		// FIXME: Sometimes userId may be used instead of teamId, how to get current user id?
		if (isAppointmentRegistered()) {
			unsigned int teamId = json.object().value("group").toObject().value("id").toInt();
			QJsonArray eventArray = json.object().value("slots").toArray();
			for (QJsonValue eventValue : eventArray) {
				if (eventValue.toObject().value("codeevent").toString() == "event-" + QString::number(m_id)) {
					QJsonArray slotArray = eventValue.toObject().value("slots").toArray();
					for (QJsonValue slotValue : slotArray) {
						if (slotValue.toObject().value("id_team").toString().toUInt() == teamId) {
							set("is_appointment_registered", true);
							set("appointment_date", QDateTime::fromString(slotValue.toObject().value("date").toString(), "yyyy-MM-dd HH:mm:ss"));
						}
					}
				}
			}
		}
	}
}

