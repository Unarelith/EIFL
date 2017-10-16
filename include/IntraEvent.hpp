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

class IntraEvent {
	public:
		IntraEvent(const QJsonObject &jsonObject);

		const std::string &name() const { return m_name; }

		const std::string &typeCode() const { return m_typeCode; }
		const std::string &typeTitle() const { return m_typeTitle; }

		unsigned int semester() const { return m_semester; }

		const std::string &moduleName() const { return m_moduleName; };
		bool isModuleRegistered() const { return m_isModuleRegistered; }

		const QDateTime &beginDate() const { return m_beginDate; }
		const QDateTime &endDate() const { return m_endDate; }

	private:
		std::string m_name;

		std::string m_typeCode;
		std::string m_typeTitle;

		unsigned int m_semester;

		std::string m_moduleName;
		bool m_isModuleRegistered;

		QDateTime m_beginDate;
		QDateTime m_endDate;
};

#endif // INTRAEVENT_HPP_
