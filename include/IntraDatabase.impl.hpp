/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabase.impl.hpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 07:48:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATABASE_IMPL_HPP_
#define INTRADATABASE_IMPL_HPP_

#include <QDebug>

#include "IntraDatabase.hpp"

template<typename T>
void addBindValue(QSqlQuery &query, T value) {
	query.addBindValue(value);
}

template<typename T, typename... Args>
void addBindValue(QSqlQuery &query, T value, Args &&...args) {
	query.addBindValue(value);
	addBindValue(query, std::forward<Args>(args)...);
}

template<typename... Args>
void IntraDatabase::addTableEntry(const std::string &table, unsigned int id, Args &&...args) const {
	std::string insertQueryString = "insert into " + table + "(id,";
	for (auto field = m_tables.at(table)->begin(); field != m_tables.at(table)->end(); ++field)
		insertQueryString += field->first + (std::next(field) == m_tables.at(table)->end() ? ")" : ",");
	insertQueryString += " values(?,";
	for (auto field = m_tables.at(table)->begin(); field != m_tables.at(table)->end(); ++field)
		insertQueryString += std::string("?") + (std::next(field) == m_tables.at(table)->end() ? ")" : ",");

	QSqlQuery insertQuery;
	insertQuery.prepare(insertQueryString.c_str());

	addBindValue(insertQuery, id, std::forward<Args>(args)...);

	if (!insertQuery.exec() && insertQuery.lastError().nativeErrorCode() != "19")
		qWarning() << "Error: Failed to insert an element to the database:" << insertQuery.lastError().text();
}

#endif // INTRADATABASE_IMPL_HPP_
