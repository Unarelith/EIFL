/*
 * =====================================================================================
 *
 *       Filename:  IntraProject.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:07:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QSqlRecord>
#include <QVariant>

#include "IntraProject.hpp"

IntraProject::IntraProject(const IntraActivity &activity, const QJsonObject &jsonObject) : m_activity(activity) {
	m_name = jsonObject.value("title").toString();
}

IntraProject::IntraProject(const IntraActivity &activity, const QSqlQuery &sqlQuery) : m_activity(activity) {
	m_name = sqlQuery.value(sqlQuery.record().indexOf("name")).toString();
}

