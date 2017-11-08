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

#include "IntraActivity.hpp"
#include "IntraModule.hpp"

#include <QDebug>

// class Thread : public QThread {
// 	public:
// 		Thread(QObject *parent, std::function<void(void)> func) : QThread(parent), m_func(func) {}
// 		~Thread() override {
// 			requestInterruption();
// 			wait();
// 		}
//
// 		void run() override { m_func(); }
//
// 	private:
// 		std::function<void(void)> m_func;
// };

class IntraDatabase : public QObject {
	Q_OBJECT

	public:
		IntraDatabase();

		void open(const QString &path);
		void clear();
		void update();

		template<typename... Args>
		void addTableEntry(const std::string &table, unsigned int id, Args &&...args) const;

	signals:
		void updateStarted() const;
		void updateProgressed(int value) const;
		void updateFinished() const;

		void unitUpdateProgressed(int value) const;

	private:
		void updateUser();
		void updateNotifications();
		void updateUnits();
		void updateActivities(const IntraModule &unit);
		void updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject);
		void updateProjects(const IntraActivity &activity);

		void removeTable(const QString &name);
		void createTables();

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
