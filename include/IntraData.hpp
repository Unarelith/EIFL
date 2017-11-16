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

#include <map>

#include "IntraDatabase.hpp"
#include "IntraEvent.hpp"
#include "IntraModule.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraUser.hpp"

class IntraData : public QObject {
	Q_OBJECT

	public:
		IntraData();

		void openDatabase(const QString &path);
		void updateDatabase();
		void reloadDatabase();

		void update();
		void updateModuleList();
		void updateActivityList();
		void updateEventList();
		void updateProjectList();
		void updateUserList();
		void updateNotificationList();

		const IntraDatabase &database() const { return m_database; }

		const std::map<unsigned int, IntraModule> &moduleList() const { return m_moduleList; }
		const std::map<unsigned int, IntraEvent> &eventList() const { return m_eventList; }
		const std::map<unsigned int, IntraProject> &projectList() const { return m_projectList; }
		const std::map<unsigned int, IntraNotification> &notificationList() const { return m_notificationList; }

		const IntraUser &userInfo() const { return m_userInfo; }

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

		IntraDatabase m_database;

		std::map<unsigned int, IntraModule> m_moduleList;
		std::map<unsigned int, IntraActivity> m_activityList;
		std::map<unsigned int, IntraEvent> m_eventList;
		std::map<unsigned int, IntraProject> m_projectList;
		std::map<unsigned int, IntraNotification> m_notificationList;
		IntraUser m_userInfo;
};

#endif // INTRADATA_HPP_
