/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabase.cpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QDebug>

#include "IntraDatabase.hpp"

void IntraDatabase::open(const QString &path) {
	if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
		throw std::runtime_error("SQLite required!");

	m_database = QSqlDatabase::addDatabase("QSQLITE");
	m_database.setDatabaseName(path);
	if (!m_database.open()) {
		qWarning() << "Error: " << m_database.lastError();
		throw std::runtime_error("Error: Failed to load database: " + path.toStdString());
	}
}

void IntraDatabase::clear() const {
	for (QString table : m_database.tables()) {
		removeTable(table);
	}
}

void IntraDatabase::addTable(const QString &name, const std::map<QString, QVariant> &fields) {
	QString queryString = "create table " + name + "(id INTEGER unique primary key";
	for (auto it : fields) {
		queryString += "," + it.first + " ";

		switch (it.second.type()) {
			case QVariant::Type::Int:
			case QVariant::Type::UInt:      queryString += "INTEGER"; break;
			case QVariant::Type::Bool:      queryString += "BOOLEAN"; break;
			case QVariant::Type::ByteArray:
			case QVariant::Type::Url:
			case QVariant::Type::String:    queryString += "TEXT"; break;
			case QVariant::Type::Date:      queryString += "DATE"; break;
			case QVariant::Type::DateTime:  queryString += "DATETIME"; break;
			default: break;
		}
	}
	queryString += ")";

	QSqlQuery query(queryString);
	if (!query.isActive())
		qWarning() << "Error: Failed to create database table '" << name << "':" << query.lastError().text();
}

void IntraDatabase::removeTable(const QString &name) {
	QSqlDatabase database = QSqlDatabase::database();
	if (!database.tables().contains(name))
		return;

	QSqlQuery query(QString("drop table ") + name);
	if (!query.isActive())
		qWarning() << "Error: Failed to remove table '" << name << "' from database:" << query.lastError().text();
}

