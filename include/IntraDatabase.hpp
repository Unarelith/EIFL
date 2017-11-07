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

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

#include "IntraActivity.hpp"
#include "IntraModule.hpp"

class IntraDatabase : public QObject {
	Q_OBJECT

	public:
		void open(const QString &path);
		void update();

		template<typename... Args>
		void addTableEntry(const std::string &table, unsigned int id, Args &&...args) const;

	signals:
		void updateStarted() const;
		void updateProgressed(int value) const;
		void updateFinished() const;

		void unitUpdateProgressed(int value) const;

	private:
		void createTables();

		void updateUnits();
		void updateActivities(const IntraModule &unit);
		void updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject);
		void updateProjects(const IntraActivity &activity);

		QSqlDatabase m_database;

		std::vector<std::pair<std::string, std::string>> m_activityFields;
		std::vector<std::pair<std::string, std::string>> m_eventFields;
		std::vector<std::pair<std::string, std::string>> m_projectFields;
		std::vector<std::pair<std::string, std::string>> m_unitFields;
		std::map<std::string, std::vector<std::pair<std::string, std::string>> *> m_tables;

		std::map<std::string, QSqlQuery> m_insertQueryMap;
};

#include "include/IntraDatabase.impl.hpp"

#endif // INTRADATABASE_HPP_
