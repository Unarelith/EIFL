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
#include <QJsonObject>

#include "IntraModule.hpp"

class IntraActivity {
	public:
		IntraActivity(const IntraModule &module, const QJsonObject &jsonObject);
		IntraActivity(const IntraModule &module, const QSqlQuery &sqlQuery);

		const IntraModule &module() const { return m_module; }

		unsigned int id() const { return m_id; }

		const QString &name() const { return m_name; }
		const QString link() const { return m_module.link() + "/acti-" + QString::number(m_id); }

		const QString &typeCode() const { return m_typeCode; }
		const QString &typeTitle() const { return m_typeTitle; }

		const QDateTime &beginDate() const { return m_beginDate; }
		const QDateTime &endDate() const { return m_endDate; }
		const QDateTime &registerDate() const { return m_registerDate; }

		bool isCurrentlyActive() const { return m_beginDate <= QDateTime::currentDateTime() && m_endDate > QDateTime::currentDateTime(); }
		bool isRegistrable() const { return m_isRegistrable; }
		bool isAppointment() const { return m_isAppointment; }

		bool isProject() const { return m_isProject; }
		unsigned int projectId() const { return m_projectId; }
		const QString &projectName() const { return m_projectName; }

	private:
		const IntraModule &m_module;

		unsigned int m_id;

		QString m_name;

		QString m_typeCode;
		QString m_typeTitle;

		QDateTime m_beginDate;
		QDateTime m_endDate;
		QDateTime m_registerDate;

		bool m_isRegistrable;
		bool m_isAppointment;

		bool m_isProject;
		unsigned int m_projectId;
		QString m_projectName;
};

#endif // INTRAACTIVITY_HPP_
