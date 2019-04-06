/*
 * =====================================================================================
 *
 *       Filename:  IntraItem.cpp
 *
 *    Description:
 *
 *        Created:  08/11/2017 01:11:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

#include "IntraDatabase.hpp"
#include "IntraItem.hpp"

IntraItem::IntraItem(const QString &sqlTable) {
	m_sqlTable = sqlTable;
}

IntraItem::IntraItem(const QString &sqlTable, const QSqlQuery &sqlQuery) {
	m_sqlTable = sqlTable;

	m_id = sqlQuery.value(0).toUInt();

	for (int i = 1 ; i < sqlQuery.record().count() ; ++i) {
		set(sqlQuery.record().fieldName(i), sqlQuery.value(i));
	};
}

void IntraItem::updateDatabaseTable() const {
	QSqlDatabase database = IntraDatabase::getDatabase();
	if (database.tables().contains(m_sqlTable)) {
		// FIXME: Change record instead of dropping the entire table
		if ((unsigned int)database.record(m_sqlTable).count() != m_data.size() + 1) {
			qDebug() << "Removing deprecated table:" << m_sqlTable;
			IntraDatabase::removeTable(m_sqlTable);
		}
	}

	if (!database.tables().contains(m_sqlTable)) {
		IntraDatabase::addTable(m_sqlTable, m_data);
	}
}

void IntraItem::writeToDatabase() {
	QString insertQueryStringLeft = "insert or replace into " + m_sqlTable + "(id";
	QString insertQueryStringRight = ") values(?";
	for (auto it : m_data) {
		insertQueryStringLeft += "," + it.first;
		insertQueryStringRight += ",?";
	}
	insertQueryStringRight += ")";

	QSqlQuery insertQuery(IntraDatabase::getDatabase());
	insertQuery.prepare(insertQueryStringLeft + insertQueryStringRight);

	unsigned int i = 0;
	insertQuery.bindValue(i++, m_id);
	for (auto it : m_data) {
		insertQuery.bindValue(i++, it.second);
	}

	if (!insertQuery.exec() && insertQuery.lastError().nativeErrorCode() != "19") {
		qWarning() << "Error: Failed to insert an element to table " << m_sqlTable << ":" << insertQuery.lastError().text();
		qWarning() << "       Query:" << insertQuery.lastQuery();
	}
}

void IntraItem::set(const QString &fieldName, const QVariant &value) {
	m_data[fieldName] = value;
}

QVariant IntraItem::get(const QString &fieldName) const {
	auto it = m_data.find(fieldName);
	if (it == m_data.end())
		return {};

	return it->second;
}

