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
#include "IntraModule.hpp"

IntraModule::IntraModule(const QJsonObject &jsonObject) {
	m_name = jsonObject.value("title").toString();

	m_semester = jsonObject.value("semester").toInt();
	m_creditCount = jsonObject.value("credits").toString().toInt();

	m_isRegistrable = jsonObject.value("open").toString().toInt();
	m_isRegistered = jsonObject.value("status").toString() != "notregistered";
}

