/*
 * =====================================================================================
 *
 *       Filename:  IntraModule.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 18:33:23
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRAMODULE_HPP_
#define INTRAMODULE_HPP_

#include <QJsonObject>

class IntraModule {
	public:
		IntraModule(const QJsonObject &jsonObject);

		const QString &name() const { return m_name; }

		unsigned int semester() const { return m_semester; }

		bool isRegistrable() const { return m_isRegistrable; }
		bool isRegistered() const { return m_isRegistered; }

	private:
		QString m_name;

		unsigned int m_semester;

		bool m_isRegistrable;
		bool m_isRegistered;
};

#endif // INTRAMODULE_HPP_
