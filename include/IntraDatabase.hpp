/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabase.hpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATABASE_HPP_
#define INTRADATABASE_HPP_

#include <functional>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

#include "IntraDatabaseLoader.hpp"

class IntraDatabase : public QObject {
	Q_OBJECT

	public:
		void open(const QString &path);
		void clear() const;

		static void addTable(const QString &name, const std::map<QString, QVariant> &fields);
		static void removeTable(const QString &name);

		static QSqlDatabase getDatabase();

		const IntraDatabaseLoader &loader() const { return m_loader; }

	private:
		// QSqlDatabase m_database;
		IntraDatabaseLoader m_loader;

		static QString s_path;
};

#endif // INTRADATABASE_HPP_
