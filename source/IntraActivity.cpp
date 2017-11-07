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
#include <QSqlRecord>
#include <QVariant>

#include "IntraActivity.hpp"

#include <QDebug>

IntraActivity::IntraActivity(const IntraModule &module, const QJsonObject &jsonObject) : m_module(module) {
	m_id = jsonObject.value("codeacti").toString().mid(5).toUInt();

	m_name = jsonObject.value("title").toString();

	m_typeCode = jsonObject.value("type_code").toString();
	m_typeTitle = jsonObject.value("type_title").toString();

	// FIXME: Find the difference between 'begin' and 'start' or 'deadline' and 'end'
	m_beginDate = QDateTime::fromString(jsonObject.value("begin").toString(), "yyyy-MM-dd HH:mm:ss");
	m_endDate = QDateTime::fromString(jsonObject.value("end").toString(), "yyyy-MM-dd HH:mm:ss");
	m_registerDate = QDateTime::fromString(jsonObject.value("end_register").toString(), "yyyy-MM-dd HH:mm:ss");

	m_isRegistrable = m_module.isRegistered() && jsonObject.value("register").toString().toUInt();
	m_isAppointment = jsonObject.value("rdv_status").toString() == "open";

	m_isProject = jsonObject.value("is_projet").toBool();
	m_projectId = jsonObject.value("id_projet").toString().toUInt();
	m_projectName = jsonObject.value("project_title").toString();
}

IntraActivity::IntraActivity(const IntraModule &module, const QSqlQuery &sqlQuery) : m_module(module) {
	m_id = sqlQuery.value(sqlQuery.record().indexOf("id")).toUInt();

	m_name = sqlQuery.value(sqlQuery.record().indexOf("name")).toString();

	m_typeCode = sqlQuery.value(sqlQuery.record().indexOf("type_code")).toString();
	m_typeTitle = sqlQuery.value(sqlQuery.record().indexOf("type_title")).toString();

	m_beginDate = sqlQuery.value(sqlQuery.record().indexOf("begin_date")).toDateTime();
	m_endDate = sqlQuery.value(sqlQuery.record().indexOf("end_date")).toDateTime();
	m_registerDate = sqlQuery.value(sqlQuery.record().indexOf("register_date")).toDateTime();

	m_isRegistrable = sqlQuery.value(sqlQuery.record().indexOf("is_registrable")).toBool();
	m_isAppointment = sqlQuery.value(sqlQuery.record().indexOf("is_appointment")).toBool();

	m_projectName = sqlQuery.value(sqlQuery.record().indexOf("project_name")).toString();
	m_projectId = sqlQuery.value(sqlQuery.record().indexOf("project_id")).toUInt();
}

