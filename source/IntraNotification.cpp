/*
 * =====================================================================================
 *
 *       Filename:  IntraNotification.cpp
 *
 *    Description:
 *
 *        Created:  29/10/2017 20:56:57
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QSqlRecord>
#include <QVariant>

#include "IntraNotification.hpp"

IntraNotification::IntraNotification(const QJsonObject &jsonObject) {
	m_id = jsonObject.value("id").toString().toUInt();

	m_title = jsonObject.value("title").toString();
	m_content = jsonObject.value("content").toString();

	m_date = QDateTime::fromString(jsonObject.value("date").toString(), "yyyy-MM-dd HH:mm:ss");
}

IntraNotification::IntraNotification(const QSqlQuery &sqlQuery) {
	m_id = sqlQuery.value(sqlQuery.record().indexOf("id")).toUInt();

	m_title = sqlQuery.value(sqlQuery.record().indexOf("title")).toString();
	m_content = sqlQuery.value(sqlQuery.record().indexOf("content")).toString();

	m_date = sqlQuery.value(sqlQuery.record().indexOf("date")).toDateTime();
}

