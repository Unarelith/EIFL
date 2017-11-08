/*
 * =====================================================================================
 *
 *       Filename:  IntraItem.hpp
 *
 *    Description:
 *
 *        Created:  08/11/2017 00:12:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAITEM_HPP_
#define INTRAITEM_HPP_

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class IntraItem {
	public:
		IntraItem(const QString &sqlTable, IntraItem *parent = nullptr);
		IntraItem(const QString &sqlTable, const QSqlQuery &sqlQuery, IntraItem *parent = nullptr);

		void removeDatabaseTable() const;
		void createDatabaseTable() const;
		void writeToDatabase() const;

		void set(const QString &fieldName, const QVariant &value);
		QVariant get(const QString &fieldName) const;

		unsigned int id() const { return m_id; }

	protected:
		unsigned int m_id;

	private:
		IntraItem *m_parent = nullptr;

		QString m_sqlTable;

		std::map<QString, QVariant> m_data;
};

#endif // INTRAITEM_HPP_
