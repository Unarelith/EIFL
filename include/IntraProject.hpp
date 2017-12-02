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

#include "IntraItem.hpp"

class IntraProject : public IntraItem {
	public:
		IntraProject(unsigned int activityId, const QJsonObject &jsonObject);
		IntraProject(unsigned int activityId, const QSqlQuery &sqlQuery)
			: IntraItem("projects", sqlQuery) {}
		IntraProject(const QJsonObject &jsonObject);

		unsigned int activityId() const { return get("activity_id").toUInt(); }

		QString name() const { return get("name").toString(); }

		enum class RegisterState {
			Unknown,
			Locked,
			Registered,
			Registrable,
		};

		RegisterState registerState() const { return static_cast<RegisterState>(get("register_state").toInt()); }
};

#endif // INTRAPROJECT_HPP_
