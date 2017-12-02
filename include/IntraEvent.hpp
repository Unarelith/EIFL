/*
 * =====================================================================================
 *
 *       Filename:  IntraEvent.hpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 02:00:49
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAEVENT_HPP_
#define INTRAEVENT_HPP_

#include "IntraActivity.hpp"

class IntraEvent : public IntraItem {
	public:
		IntraEvent(unsigned int activityId, const QJsonObject &jsonObject);
		IntraEvent(unsigned int activityId, const QSqlQuery &sqlQuery)
			: IntraItem("events", sqlQuery) {}

		unsigned int activityId() const { return get("activity_id").toUInt(); }

		// FIXME: Some sessions require only 1 hour, not 1 day
		bool isValid() const { return QDateTime::currentDateTime().addDays(1) < beginDate(); }
		bool isRegistrable() const { return isValid() && get("is_registrable").toBool(); }
		bool isRegistered() const { return get("is_registered").toBool(); }
		bool isMissed() const { return get("is_missed").toBool(); }
		bool isTokenWritable() const { return get("is_token_writable").toBool(); }

		QString buildingName() const { return get("building_name").toString(); }
		QString roomName() const { return get("room_name").toString(); }

		QDateTime beginDate() const { return get("begin_date").toDateTime(); }
		QDateTime endDate() const { return get("end_date").toDateTime(); }
};

#endif // INTRAEVENT_HPP_
