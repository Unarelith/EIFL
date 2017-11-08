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
#include <QSqlRecord>
#include <QVariant>

#include "IntraUser.hpp"

#include <iostream>

IntraUser::IntraUser(const QJsonObject &jsonObject) : IntraItem("users") {
	m_id = jsonObject.value("uid").toInt();

	set("login", jsonObject.value("login").toString());
	set("last_name", jsonObject.value("lastname").toString());
	set("first_name", jsonObject.value("firstname").toString());

	const QJsonObject &userInfosObject = jsonObject.value("userinfo").toObject();
	set("birthday", QDate::fromString(userInfosObject.value("birthday").toObject().value("value").toString(), "dd/MM/yyyy"));

	set("picture_link", jsonObject.value("picture").toString());

	set("current_semester", jsonObject.value("semester").toInt());
	set("current_year", jsonObject.value("studentyear").toInt());

	set("credit_count", jsonObject.value("credits").toInt());
	set("spice_count", jsonObject.value("spice").toObject().value("available_spice").toString().toInt());
	set("gpa", jsonObject.value("gpa").toArray().at(0).toObject().value("gpa").toString().toFloat());
}

