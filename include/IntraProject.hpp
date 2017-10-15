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

#include <string>

#include <QDateTime>
#include <QJsonObject>

class IntraProject {
	public:
		IntraProject(const QJsonObject &jsonObject);

		const std::string &name() const { return m_name; }
		const std::string &link() const { return m_link; }

		const QDateTime &beginDate() const { return m_beginDate; }
		const QDateTime &endDate() const { return m_endDate; }
		const QDateTime &registerDate() const { return m_registerDate; }

		unsigned int id() const { return m_id; }

	private:
		std::string m_name;
		std::string m_link;

		QDateTime m_beginDate;
		QDateTime m_endDate;
		QDateTime m_registerDate;

		unsigned int m_id;
};

#endif // INTRAPROJECT_HPP_
