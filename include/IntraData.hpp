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
#include <vector>

#include <QJsonDocument>

#include "Database.hpp"
#include "IntraEvent.hpp"
#include "IntraModule.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraUser.hpp"

class IntraData {
	public:
		void update();
		void updateModuleList();
		void updateNotificationList();
		void updateProjectList();

		std::deque<IntraEvent> getEventList(const QDate &date, const std::vector<unsigned int> &semesters) const;
		IntraUser getUserInfo(const QString &login);

		const std::deque<IntraModule> &moduleList() const { return m_moduleList; }
		const std::deque<IntraNotification> &notificationList() const { return m_notificationList; }
		const std::deque<IntraProject> &projectList() const { return m_projectList; }

		static IntraData &getInstance() {
			return *s_instance;
		}

		static void setInstance(IntraData &instance) {
			s_instance = &instance;
		}

	private:
		static IntraData *s_instance;

		Database m_database;

		QJsonDocument m_overviewJson;

		std::deque<IntraModule> m_moduleList;
		std::deque<IntraNotification> m_notificationList;
		std::deque<IntraProject> m_projectList;

		std::map<QString, IntraUser> m_userInfoCache;
};

#endif // INTRADATA_HPP_
