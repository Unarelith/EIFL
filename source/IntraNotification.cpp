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

IntraNotification::IntraNotification(const QJsonObject &jsonObject) : IntraItem("notifications") {
	m_id = jsonObject.value("id").toString().toUInt();

	set("title", jsonObject.value("title").toString());
	set("content", jsonObject.value("content").toString());

	set("date", QDateTime::fromString(jsonObject.value("date").toString(), "yyyy-MM-dd HH:mm:ss"));
}

