/*
 * =====================================================================================
 *
 *       Filename:  IntraProject.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:47:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAPROJECT_HPP_
#define INTRAPROJECT_HPP_

#include "IntraActivity.hpp"

class IntraProject : public IntraItem {
	public:
		IntraProject(const IntraActivity &activity, const QJsonObject &jsonObject);
		IntraProject(const IntraActivity &activity, const QSqlQuery &sqlQuery)
			: IntraItem("projects", sqlQuery), m_activity(activity) {}

		const IntraActivity &activity() const { return m_activity; }

		QString name() const { return get("name").toString(); }

		bool isRegistrable() const { return get("is_registrable").toBool(); }
		bool isRegistered() const { return get("is_registered").toBool(); }

	private:
		const IntraActivity &m_activity;
};

#endif // INTRAPROJECT_HPP_
