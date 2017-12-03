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
#include "IntraData.hpp"
#include "IntraModule.hpp"
#include "IntraSession.hpp"

IntraActivity::IntraActivity(unsigned int moduleID, const QJsonObject &jsonObject) : IntraItem("activities") {
	m_id = jsonObject.value("codeacti").toString().mid(5).toUInt();

	const IntraModule *module = nullptr;
	if (moduleID != 0)
		module = IntraData::getInstance().getModule(moduleID);

	set("module_id", moduleID);

	set("name", jsonObject.value("title").toString());
	set("link", (module) ? module->link() + "/acti-" + QString::number(id()) : "");

	set("type_code", jsonObject.value("type_code").toString());
	set("type_title", jsonObject.value("type_title").toString());

	// FIXME: Find the difference between 'begin' and 'start' or 'deadline' and 'end'
	set("begin_date", QDateTime::fromString(jsonObject.value("begin").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("end_date", QDateTime::fromString(jsonObject.value("end").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("register_date", QDateTime::fromString(jsonObject.value("end_register").toString(), "yyyy-MM-dd HH:mm:ss"));
	set("appointment_date", {});

	set("is_registrable", module && module->isRegistered() && jsonObject.value("register").toString().toUInt());
	set("is_appointment", jsonObject.value("rdv_status").toString() == "open");
	set("is_appointment_registered", false);

	set("appointment_event_id", 0);

	set("is_project", jsonObject.value("is_projet").toBool());
	set("project_id", jsonObject.value("id_projet").toString().toUInt());
	set("project_name", jsonObject.value("project_title").toString());

	if (isAppointment() && module && module->isRegistered()) {
		QJsonDocument json = IntraSession::getInstance().get(module->link() + "/acti-" + QString::number(id()) + "/rdv");

		set("is_appointment_registered", json.object().value("group").isObject()
		                              && json.object().value("group").toObject().value("inscrit").toBool());

		// FIXME: Sometimes userId may be used instead of teamId, how to get current user id?
		if (isAppointmentRegistered()) {
			unsigned int teamId = json.object().value("group").toObject().value("id").toInt();
			QJsonArray eventArray = json.object().value("slots").toArray();
			for (QJsonValue eventValue : eventArray) {
				QJsonArray slotArray = eventValue.toObject().value("slots").toArray();
				for (QJsonValue slotValue : slotArray) {
					if (slotValue.toObject().value("id_team").toString().toUInt() == teamId) {
						set("appointment_date", QDateTime::fromString(slotValue.toObject().value("date").toString(), "yyyy-MM-dd HH:mm:ss"));
						set("appointment_event_id", eventValue.toObject().value("codeevent").toString().mid(6).toInt());
					}
				}
			}
		}
	}
}

IntraActivity::IntraActivity(const QJsonObject &jsonObject) : IntraItem("activities") {
	m_id = jsonObject.value("id_activite").toString().toUInt();

	set("module_id", 0);

	set("name", jsonObject.value("title").toString());
	set("link", jsonObject.value("title").toString());

	set("type_code", "PRJ");
	set("type_title", "Project");

	set("begin_date", QDateTime::fromString(jsonObject.value("timeline_start").toString(), "dd/MM/yyyy, HH'h'mm"));
	set("end_date", QDateTime::fromString(jsonObject.value("timeline_end").toString(), "dd/MM/yyyy, HH'h'mm"));
	set("register_date", QDateTime::fromString(jsonObject.value("date_inscription").toString(), "dd/MM/yyyy, HH'h'mm"));
	set("appointment_date", {});

	set("is_registrable", QDateTime::currentDateTime() > get("begin_date").toDateTime() && QDateTime::currentDateTime() < get("register_date").toDateTime());
	set("is_appointment", false);
	set("is_appointment_registered", false);

	set("appointment_event_id", 0);

	set("is_project", true);
	set("project_id", 0);
	set("project_name", jsonObject.value("title").toString());
}

