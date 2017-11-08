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
#include <QJsonObject>

#include "IntraModule.hpp"

IntraModule::IntraModule(const QJsonObject &jsonObject) : IntraItem("units") {
	m_id = jsonObject.value("id").toInt();

	set("code", jsonObject.value("code").toString());
	set("code_instance", jsonObject.value("codeinstance").toString());

	set("scholar_year", jsonObject.value("scolaryear").toInt());
	set("semester", jsonObject.value("semester").toInt());
	set("credit_count", jsonObject.value("credits").toString().toInt());

	set("name", jsonObject.value("title").toString());
	set("link", "/module/" + QString::number(scholarYear()) + "/" + code() + "/" + codeInstance());

	set("is_registrable", jsonObject.value("open").toString().toInt());
	set("is_registered", jsonObject.value("status").toString() != "notregistered");

	set("flags", static_cast<Flags>(jsonObject.value("flags").toString().toInt()));
}

