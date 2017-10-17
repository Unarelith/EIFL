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

class IntraUser {
	public:
		IntraUser(const QJsonObject &jsonObject);

		const QString &login() const { return m_login; }
		const QString &lastName() const { return m_lastName; }
		const QString &firstName() const { return m_firstName; }

		const QDate &birthday() const { return m_birthday; }

		const QUrl &pictureLink() const { return m_pictureLink; }

		unsigned int currentSemester() const { return m_currentSemester; }
		unsigned int currentYear() const { return m_currentYear; }

		unsigned int creditCount() const { return m_creditCount; }
		unsigned int spiceCount() const { return m_spiceCount; }
		float gpa() const { return m_gpa; }

	private:
		QString m_login;
		QString m_lastName;
		QString m_firstName;

		QDate m_birthday;

		QUrl m_pictureLink;

		unsigned int m_currentSemester;
		unsigned int m_currentYear;

		unsigned int m_creditCount;
		unsigned int m_spiceCount;
		float m_gpa;
};

#endif // INTRAUSER_HPP_
