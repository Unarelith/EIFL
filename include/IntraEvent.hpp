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

#include <QDateTime>
#include <QJsonObject>

#include "IntraActivity.hpp"

class IntraEvent {
	public:
		IntraEvent(const IntraActivity &activity, const QJsonObject &jsonObject);
		IntraEvent(const IntraActivity &activity, const QSqlQuery &sqlQuery);

		const IntraActivity &activity() const { return m_activity; }

		unsigned int id() const { return m_id; }

		bool isAppointment() const { return m_isAppointment; }
		const QDateTime &appointmentDate() const { return m_appointmentDate; }

		bool isRegistrable() const { return m_isRegistrable; }
		bool isRegistered() const { return m_isRegistered; }
		bool isMissed() const { return m_isMissed; }
		bool isTokenWritable() const { return m_isTokenWritable; }

		const QString &buildingName() const { return m_buildingName; }
		const QString &roomName() const { return m_roomName; }

		const QDateTime &beginDate() const { return m_beginDate; }
		const QDateTime &endDate() const { return m_endDate; }

	private:
		const IntraActivity &m_activity;

		unsigned int m_id;

		bool m_isAppointment;
		QDateTime m_appointmentDate;

		bool m_isRegistered;
		bool m_isRegistrable;
		bool m_isMissed;
		bool m_isTokenWritable;

		QString m_buildingName;
		QString m_roomName;

		QDateTime m_beginDate;
		QDateTime m_endDate;
};

#endif // INTRAEVENT_HPP_
