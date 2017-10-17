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
#include <vector>

#include "IntraEvent.hpp"
#include "IntraProject.hpp"
#include "IntraUser.hpp"

class IntraData {
	public:
		void update();
		void updateProjectList();

		std::deque<IntraEvent> getEventList(const QDate &date, const std::vector<int> &semesters) const;
		IntraUser getUserInfo(const QString &username) const;

		const std::deque<IntraProject> &projectList() const { return m_projectList; }

		static const IntraData &getInstance() {
			return *s_instance;
		}

		static void setInstance(const IntraData &instance) {
			s_instance = &instance;
		}

	private:
		static const IntraData *s_instance;

		std::deque<IntraProject> m_projectList;
};

#endif // INTRADATA_HPP_
