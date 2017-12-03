/*
 * =====================================================================================
 *
 *       Filename:  IntraActivity.hpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 08:18:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAACTIVITY_HPP_
#define INTRAACTIVITY_HPP_

#include <QDateTime>

#include "IntraItem.hpp"

class IntraActivity : public IntraItem {
	public:
		IntraActivity(unsigned int moduleId, const QJsonObject &jsonObject);
		IntraActivity(unsigned int moduleId, const QSqlQuery &sqlQuery)
			: IntraItem("activities", sqlQuery) {}
		IntraActivity(const QJsonObject &jsonObject);

		unsigned int moduleId() const { return get("module_id").toInt(); }

		QString name() const { return get("name").toString(); }
		QString link() const { return get("link").toString(); }

		QString typeCode() const { return get("type_code").toString(); }
		QString typeTitle() const { return get("type_title").toString(); }

		QDateTime beginDate() const { return get("begin_date").toDateTime(); }
		QDateTime endDate() const { return get("end_date").toDateTime(); }
		QDateTime registerDate() const { return get("register_date").toDateTime(); }
		QDateTime appointmentDate() const { return get("appointment_date").toDateTime(); }

		bool isCurrentlyActive() const { return beginDate() <= QDateTime::currentDateTime() && endDate() > QDateTime::currentDateTime(); }
		bool isRegistrable() const { return get("is_registrable").toBool(); }
		bool isAppointment() const { return get("is_appointment").toBool(); }
		bool isAppointmentRegistered() const { return get("is_appointment_registered").toBool(); }

		unsigned int appointmentEventId() const { return get("appointment_event_id").toUInt(); }

		bool isProject() const { return get("is_project").toBool(); }
		unsigned int projectId() const { return get("project_id").toUInt(); }
		QString projectName() const { return get("project_name").toString(); }

};

#endif // INTRAACTIVITY_HPP_
