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

#include "IntraItem.hpp"

class IntraNotification : public IntraItem {
	public:
		IntraNotification(const QJsonObject &jsonObject);
		IntraNotification(const QSqlQuery &sqlQuery) : IntraItem("notifications", sqlQuery) {}

		QString title() const { return get("title").toString(); }
		QString content() const { return get("content").toString(); }

		QDateTime date() const { return get("date").toDateTime(); }
};

#endif // INTRANOTIFICATION_HPP_
