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

class IntraProject {
	public:
		IntraProject(const IntraActivity &activity, const QJsonObject &jsonObject);
		IntraProject(const IntraActivity &activity, const QSqlQuery &sqlQuery);

		const IntraActivity &activity() const { return m_activity; }

		unsigned int id() const { return m_activity.projectId(); }

		const QString &name() const { return m_name; }

	private:
		const IntraActivity &m_activity;

		QString m_name;
};

#endif // INTRAPROJECT_HPP_
