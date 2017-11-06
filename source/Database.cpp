/*
 * =====================================================================================
 *
 *       Filename:  Database.cpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <deque>

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QSqlError>
#include <QSqlQuery>

#include "Database.hpp"
#include "IntraModule.hpp"
#include "IntraSession.hpp"

Database::Database() {
	if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
		throw std::runtime_error("SQLite required!");

	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName("test_units.sqlite");
	if (!m_database.open())
		qWarning() << "Error: " << m_database.lastError();
}


void Database::updateUnits() {
	if (!m_database.tables().contains("units")) {
		QSqlQuery query("create table units (id             INTEGER unique primary key,"
		                                    "name           TEXT,"
		                                    "semester       INTEGER,"
		                                    "credit_count   INTEGER,"
		                                    "is_registrable INTEGER,"
		                                    "is_registered  INTEGER,"
		                                    "flags          INTEGER)");
		if (!query.isActive())
			qWarning() << "Error: " << query.lastError().text();
	}

	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray unitArray = json.array();
	for (QJsonValue value : unitArray) {
		IntraModule module(value.toObject());

		QSqlQuery insertQuery;
		insertQuery.prepare("insert into units(id, name, semester, credit_count, is_registrable, is_registered, flags) values(?, ?, ?, ?, ?, ?, ?)");
		insertQuery.addBindValue(module.id());
		insertQuery.addBindValue(module.name());
		insertQuery.addBindValue(module.semester());
		insertQuery.addBindValue(module.creditCount());
		insertQuery.addBindValue(module.isRegistrable());
		insertQuery.addBindValue(module.isRegistered());
		insertQuery.addBindValue((int)module.flags());
		if (!insertQuery.exec() && insertQuery.lastError().nativeErrorCode() != "19")
			qWarning() << "Error: " << insertQuery.lastError().text();
	}
}

