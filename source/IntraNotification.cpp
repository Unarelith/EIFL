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
#include "IntraNotification.hpp"

IntraNotification::IntraNotification(const QJsonObject &jsonObject) {
	m_title = jsonObject.value("title").toString();
	m_content = jsonObject.value("content").toString();

	m_date = QDateTime::fromString(jsonObject.value("date").toString(), "yyyy-MM-dd HH:mm:ss");
}

