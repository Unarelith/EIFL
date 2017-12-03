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
#include "IntraDatabaseThread.hpp"
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
		void stopDatabaseUpdate();

		void update();
		void updateModuleList();
		void updateActivityList();
		void updateEventList();
		void updateProjectList();
		void updateUserList();
		void updateNotificationList();

		const IntraDatabase &database() const { return m_database; }

		const std::map<unsigned int, IntraModule> &moduleList() const { return m_moduleList; }
		const std::map<unsigned int, IntraActivity> &activityList() const { return m_activityList; }
		const std::map<unsigned int, IntraEvent> &eventList() const { return m_eventList; }
		const std::map<unsigned int, IntraProject> &projectList() const { return m_projectList; }
		const std::map<unsigned int, IntraNotification> &notificationList() const { return m_notificationList; }

		const IntraModule *getModule(unsigned int id) { return getItem(id, m_moduleList); }
		const IntraActivity *getActivity(unsigned int id) { return getItem(id, m_activityList); }
		const IntraEvent *getEvent(unsigned int id) { return getItem(id, m_eventList); }
		const IntraProject *getProject(unsigned int id) { return getItem(id, m_projectList); }
		const IntraNotification *getNotification(unsigned int id) { return getItem(id, m_notificationList); }

		void setModule(unsigned int id, const IntraModule &module) { setItem(id, module, m_moduleList); }
		void setActivity(unsigned int id, const IntraActivity &activity) { setItem(id, activity, m_activityList); }
		void setEvent(unsigned int id, const IntraEvent &event) { setItem(id, event, m_eventList); }
		void setProject(unsigned int id, const IntraProject &project) { setItem(id, project, m_projectList); }
		void setNotification(unsigned int id, const IntraNotification &notification) { setItem(id, notification, m_notificationList); }

		const IntraUser &userInfo() const { return m_userInfo; }

		static IntraData &getInstance() {
			return *s_instance;
		}

		static void setInstance(IntraData &instance) {
			s_instance = &instance;
		}

	signals:
		void stateChanged(const QString &state, int timeout = 0);
		void windowRefeshRequested();

		void databaseUpdateStarted();
		void databaseUpdateStopped();

	private:
		static IntraData *s_instance;

		IntraDatabase m_database;
		IntraDatabaseThread *m_databaseThread = nullptr;

		template<typename T>
		const T *getItem(unsigned int id, const std::map<unsigned int, T> &itemList) {
			auto it = itemList.find(id);
			if (it == itemList.end())
				return nullptr;
			return &it->second;
		}

		template<typename T>
		void setItem(unsigned int id, const T &item, std::map<unsigned int, T> &itemList) {
			auto it = itemList.find(id);
			if (it == itemList.end())
				itemList.emplace(id, item);
			else
				it->second = item;
		}

		std::map<unsigned int, IntraModule> m_moduleList;
		std::map<unsigned int, IntraActivity> m_activityList;
		std::map<unsigned int, IntraEvent> m_eventList;
		std::map<unsigned int, IntraProject> m_projectList;
		std::map<unsigned int, IntraNotification> m_notificationList;
		IntraUser m_userInfo;
};

#endif // INTRADATA_HPP_
