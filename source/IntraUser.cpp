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

// IntraUser::IntraUser(const QJsonObject &jsonObject) {
// 	m_id = jsonObject.value("uid").toInt();
//
// 	m_login = jsonObject.value("login").toString();
// 	m_lastName = jsonObject.value("lastname").toString();
// 	m_firstName = jsonObject.value("firstname").toString();
//
// 	const QJsonObject &userInfosObject = jsonObject.value("userinfo").toObject();
// 	m_birthday = QDate::fromString(userInfosObject.value("birthday").toObject().value("value").toString(), "dd/MM/yyyy");
//
// 	m_pictureLink = jsonObject.value("picture").toString();
//
// 	m_currentSemester = jsonObject.value("semester").toInt();
// 	m_currentYear = jsonObject.value("studentyear").toInt();
//
// 	m_creditCount = jsonObject.value("credits").toInt();
// 	m_spiceCount = jsonObject.value("spice").toObject().value("available_spice").toString().toInt();
// 	m_gpa = jsonObject.value("gpa").toArray().at(0).toObject().value("gpa").toString().toFloat();
// }

// IntraUser::IntraUser(const QSqlQuery &sqlQuery) {
// 	m_id = sqlQuery.value(sqlQuery.record().indexOf("id")).toUInt();
//
// 	m_login = sqlQuery.value(sqlQuery.record().indexOf("login")).toString();
// 	m_lastName = sqlQuery.value(sqlQuery.record().indexOf("last_name")).toString();
// 	m_firstName = sqlQuery.value(sqlQuery.record().indexOf("first_name")).toString();
//
// 	m_birthday = sqlQuery.value(sqlQuery.record().indexOf("birthday")).toDate();
//
// 	m_currentSemester = sqlQuery.value(sqlQuery.record().indexOf("current_semester")).toUInt();
//
// 	m_creditCount = sqlQuery.value(sqlQuery.record().indexOf("credit_count")).toUInt();
// 	m_spiceCount = sqlQuery.value(sqlQuery.record().indexOf("spice_count")).toUInt();
// 	m_gpa = sqlQuery.value(sqlQuery.record().indexOf("gpa")).toFloat();
// }

