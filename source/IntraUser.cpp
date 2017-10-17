/*
 * =====================================================================================
 *
 *       Filename:  IntraUser.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 14:36:53
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QJsonArray>

#include "IntraUser.hpp"

#include <iostream>

IntraUser::IntraUser(const QJsonObject &jsonObject) {
	m_login = jsonObject.value("login").toString();
	m_lastName = jsonObject.value("lastname").toString();
	m_firstName = jsonObject.value("firstname").toString();

	const QJsonObject &userInfosObject = jsonObject.value("userinfo").toObject();
	m_birthday = QDate::fromString(userInfosObject.value("birthday").toObject().value("value").toString(), "dd/MM/yyyy");

	m_pictureLink = jsonObject.value("picture").toString();

	m_currentSemester = jsonObject.value("semester").toInt();
	m_currentYear = jsonObject.value("studentyear").toInt();

	m_creditCount = jsonObject.value("credits").toInt();
	m_spiceCount = jsonObject.value("spice").toObject().value("available_spice").toString().toInt();
	m_gpa = jsonObject.value("gpa").toArray().at(0).toObject().value("gpa").toString().toFloat();
}

