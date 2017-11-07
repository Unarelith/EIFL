/*
 * =====================================================================================
 *
 *       Filename:  IntraModule.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 18:34:05
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QSqlRecord>
#include <QVariant>

#include "IntraModule.hpp"

IntraModule::IntraModule(const QJsonObject &jsonObject) {
	m_id = jsonObject.value("id").toInt();

	m_code = jsonObject.value("code").toString();
	m_codeInstance = jsonObject.value("codeinstance").toString();

	m_scholarYear = jsonObject.value("scolaryear").toInt();
	m_semester = jsonObject.value("semester").toInt();
	m_creditCount = jsonObject.value("credits").toString().toInt();

	m_name = jsonObject.value("title").toString();
	m_link = "/module/" + QString::number(m_scholarYear) + "/" + m_code + "/" + m_codeInstance;

	m_isRegistrable = jsonObject.value("open").toString().toInt();
	m_isRegistered = jsonObject.value("status").toString() != "notregistered";

	m_flags = static_cast<Flags>(jsonObject.value("flags").toString().toInt());
}

IntraModule::IntraModule(const QSqlQuery &sqlQuery) {
	m_id = sqlQuery.value(sqlQuery.record().indexOf("id")).toUInt();

	m_name = sqlQuery.value(sqlQuery.record().indexOf("name")).toString();
	m_link = sqlQuery.value(sqlQuery.record().indexOf("link")).toString();

	m_semester = sqlQuery.value(sqlQuery.record().indexOf("semester")).toUInt();
	m_creditCount = sqlQuery.value(sqlQuery.record().indexOf("credit_count")).toUInt();

	m_isRegistrable = sqlQuery.value(sqlQuery.record().indexOf("is_registrable")).toBool();
	m_isRegistered = sqlQuery.value(sqlQuery.record().indexOf("is_registered")).toBool();

	m_flags = (Flags)sqlQuery.value(sqlQuery.record().indexOf("flags")).toUInt();
}

