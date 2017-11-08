/*
 * =====================================================================================
 *
 *       Filename:  IntraUser.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 14:36:35
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAUSER_HPP_
#define INTRAUSER_HPP_

#include <QDate>
#include <QJsonObject>
#include <QUrl>

#include "IntraItem.hpp"

class IntraUser : public IntraItem {
	public:
		IntraUser() : IntraItem("users") {}
		IntraUser(const QJsonObject &jsonObject);
		IntraUser(const QSqlQuery &sqlQuery) : IntraItem("users", sqlQuery) {}

		QString login() const { return get("login").toString(); }
		QString lastName() const { return get("last_name").toString(); }
		QString firstName() const { return get("first_name").toString(); }

		QDate birthday() const { return get("birthday").toDate(); }

		QUrl pictureLink() const { return get("picture_link").toUrl(); }

		unsigned int currentSemester() const { return get("current_semester").toUInt(); }
		unsigned int currentYear() const { return get("current_year").toUInt(); }

		unsigned int creditCount() const { return get("credit_count").toUInt(); }
		unsigned int spiceCount() const { return get("spice_count").toUInt(); }
		float gpa() const { return get("gpa").toFloat(); }
};

#endif // INTRAUSER_HPP_
