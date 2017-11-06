/*
 * =====================================================================================
 *
 *       Filename:  Database.hpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:10
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <QSqlDatabase>

class Database {
	public:
		Database();

		void updateUnits();

	private:
		QSqlDatabase m_database;
};

#endif // DATABASE_HPP_
