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

#include <QSqlQuery>
#include <QVariant>

class IntraItem {
	public:
		IntraItem(const QString &sqlTable);
		IntraItem(const QString &sqlTable, const QSqlQuery &sqlQuery);

		void updateDatabaseTable() const;
		void writeToDatabase();

		void set(const QString &fieldName, const QVariant &value);
		QVariant get(const QString &fieldName) const;

		unsigned int id() const { return m_id; }

	protected:
		unsigned int m_id;

	private:
		void prepareQuery();

		QString m_sqlTable;

		std::map<QString, QVariant> m_data;
};

#endif // INTRAITEM_HPP_
