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

		enum class Flags {
			Optional = 1,
			Progressive = 2,
			RoadblockCycle = 4,
			RoadblockYear = 8,
			MultipleRegistration = 32,
			Mandatory = 128
		};

		const QString &name() const { return m_name; }

		unsigned int semester() const { return m_semester; }
		unsigned int creditCount() const { return m_creditCount; }

		bool isRegistrable() const { return m_isRegistrable; }
		bool isRegistered() const { return m_isRegistered; }

		Flags flags() const { return m_flags; }

	private:
		QString m_name;

		unsigned int m_semester;
		unsigned int m_creditCount;

		bool m_isRegistrable;
		bool m_isRegistered;

		Flags m_flags;
};

#endif // INTRAMODULE_HPP_
