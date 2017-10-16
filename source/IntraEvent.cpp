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
#include "IntraEvent.hpp"

IntraEvent::IntraEvent(const QJsonObject &jsonObject) {
	m_name = jsonObject.value("acti_title").toString().toStdString();

	m_typeCode = jsonObject.value("type_code").toString().toStdString();
	m_typeTitle = jsonObject.value("type_title").toString().toStdString();

	m_semester = jsonObject.value("semester").toInt();

	m_moduleName = jsonObject.value("titlemodule").toString().toStdString();
	m_isModuleRegistered = jsonObject.value("module_registered").toBool();

	m_isAppointment = jsonObject.value("is_rdv").toBool();
	m_appointmentDate = QDateTime::fromString(jsonObject.value("rdv_group_registered").toString().left(19), "yyyy-MM-dd HH:mm:ss");

	m_isRegistrable = jsonObject.value("allow_register").toBool();
	m_isRegistered = jsonObject.value("event_registered").toBool() || !m_appointmentDate.isNull();

	m_beginDate = QDateTime::fromString(jsonObject.value("start").toString(), "yyyy-MM-dd HH:mm:ss");
	m_endDate = QDateTime::fromString(jsonObject.value("end").toString(), "yyyy-MM-dd HH:mm:ss");
}

