/*
 * =====================================================================================
 *
 *       Filename:  IntraData.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:42:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATA_HPP_
#define INTRADATA_HPP_

#include <deque>
#include <map>
#include <memory>
#include <vector>

#include <QJsonDocument>

#include "IntraDatabase.hpp"
#include "IntraEvent.hpp"
#include "IntraModule.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraUser.hpp"

#include <iostream>

class IntraDatabaseThread : public QThread {
	public:
		IntraDatabaseThread(QObject *parent, std::shared_ptr<IntraDatabase> database) : QThread(parent), m_database(database) {}
		~IntraDatabaseThread() override {
			requestInterruption();
			wait();
		}

		void run() override { m_database->update(); }

	private:
		std::shared_ptr<IntraDatabase> m_database;
};

class IntraData : public QObject {
	Q_OBJECT

	public:
		void openDatabase(const QString &path);
		void updateDatabase();

		void update();
		void updateNotificationList();
		void updateModuleList();
		void updateActivityList();
		void updateEventList();
		void updateProjectList();

		std::deque<IntraEvent> getEventList(const QDate &date, const QList<unsigned int> &semesters) const;
		IntraUser getUserInfo(const QString &login);

		const IntraDatabase &database() const { return *m_database; }

		const std::map<unsigned int, IntraModule> &moduleList() const { return m_moduleList; }
		const std::map<unsigned int, IntraProject> &projectList() const { return m_projectList; }

		const std::deque<IntraNotification> &notificationList() const { return m_notificationList; }

		static IntraData &getInstance() {
			return *s_instance;
		}

		static void setInstance(IntraData &instance) {
			s_instance = &instance;
		}

	signals:
		void databaseUpdateFinished();

	private:
		static IntraData *s_instance;

		std::shared_ptr<IntraDatabase> m_database{std::make_shared<IntraDatabase>()};

		QJsonDocument m_overviewJson;

		std::deque<IntraNotification> m_notificationList;

		std::map<unsigned int, IntraModule> m_moduleList;
		std::map<unsigned int, IntraActivity> m_activityList;
		std::map<unsigned int, IntraEvent> m_eventList;
		std::map<unsigned int, IntraProject> m_projectList;

		std::map<QString, IntraUser> m_userInfoCache;
};

#endif // INTRADATA_HPP_
