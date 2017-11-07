/*
 * =====================================================================================
 *
 *       Filename:  IntraNotification.hpp
 *
 *    Description:
 *
 *        Created:  29/10/2017 20:56:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRANOTIFICATION_HPP_
#define INTRANOTIFICATION_HPP_

#include <QDateTime>
#include <QJsonObject>
#include <QSqlQuery>

class IntraNotification {
	public:
		IntraNotification(const QJsonObject &jsonObject);
		IntraNotification(const QSqlQuery &sqlQuery);

		unsigned int id() const { return m_id; }

		const QString &title() const { return m_title; }
		const QString &content() const { return m_content; }

		const QDateTime &date() const { return m_date; }

	private:
		unsigned int m_id;

		QString m_title;
		QString m_content;

		QDateTime m_date;
};

#endif // INTRANOTIFICATION_HPP_
