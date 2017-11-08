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
#include "IntraItem.hpp"

IntraItem::IntraItem(const QString &sqlTable, IntraItem *parent) {
	m_parent = parent;
	m_sqlTable = sqlTable;
}

IntraItem::IntraItem(const QString &sqlTable, const QSqlQuery &sqlQuery, IntraItem *parent) {
	m_parent = parent;
	m_sqlTable = sqlTable;

	m_id = sqlQuery.value(0).toUInt();

	for (size_t i = 1 ; i < sqlQuery.record().count() ; ++i) {
		set(sqlQuery.record().fieldName(i), sqlQuery.value(i));
	};
}

void IntraItem::removeDatabaseTable() const {
	QSqlDatabase database = QSqlDatabase::database();
	if (!database.tables().contains(m_sqlTable))
		return;

	QSqlQuery query(QString("drop table ") + m_sqlTable);
	if (!query.isActive())
		qWarning() << "Error: Failed to remove table '" << m_sqlTable << "' from database:" << query.lastError().text();
}

void IntraItem::createDatabaseTable() const {
	QSqlDatabase database = QSqlDatabase::database();
	if (database.tables().contains(m_sqlTable)) {
		// FIXME: Change record instead of dropping the entire table
		if (database.record(m_sqlTable).count() != m_data.size()) {
			removeDatabaseTable();
		}
	}

	if (!database.tables().contains(m_sqlTable)) {
		QString queryString = "create table " + m_sqlTable + "(id INTEGER unique primary key,";
		for (auto field = m_data.begin() ; field != m_data.end() ; ++field) {
			queryString += field->first + " ";

			switch (field->second.type()) {
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

			queryString += (std::next(field) == m_data.end()) ? ")" : ",";
		}

		QSqlQuery query(queryString);
		if (!query.isActive())
			qWarning() << "Error: Failed to create database table '" << m_sqlTable << "':" << query.lastError().text();
	}
}

void IntraItem::writeToDatabase() const {
	QString insertQueryString = "insert or replace into " + m_sqlTable + "(id,";
	for (auto field = m_data.begin(); field != m_data.end(); ++field)
		insertQueryString += field->first + (std::next(field) == m_data.end() ? ")" : ",");
	insertQueryString += " values(?,";
	for (auto field = m_data.begin(); field != m_data.end(); ++field)
		insertQueryString += QString("?") + (std::next(field) == m_data.end() ? ")" : ",");

	QSqlQuery insertQuery;
	insertQuery.prepare(insertQueryString);

	insertQuery.addBindValue(m_id);
	for (auto it : m_data) {
		insertQuery.addBindValue(it.second);
	}

	if (!insertQuery.exec() && insertQuery.lastError().nativeErrorCode() != "19")
		qWarning() << "Error: Failed to insert an element to the database:" << insertQuery.lastError().text();
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

