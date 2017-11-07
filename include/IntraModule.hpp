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
#include <QSqlQuery>

class IntraModule {
	public:
		IntraModule(const QJsonObject &jsonObject);
		IntraModule(const QSqlQuery &sqlQuery);

		enum Flags {
			Optional = 1,
			Progressive = 2,
			RoadblockCycle = 4,
			RoadblockYear = 8,
			MultipleRegistration = 32,
			Mandatory = 128
		};

		unsigned int id() const { return m_id; }

		const QString &code() const { return m_code; }
		const QString &codeInstance() const { return m_codeInstance; }

		unsigned int scholarYear() const { return m_scholarYear; }
		unsigned int semester() const { return m_semester; }
		unsigned int creditCount() const { return m_creditCount; }

		const QString &name() const { return m_name; }
		const QString &link() const { return m_link; }

		bool isRegistrable() const { return m_isRegistrable; }
		bool isRegistered() const { return m_isRegistered; }

		Flags flags() const { return m_flags; }

	private:
		unsigned int m_id;

		QString m_code;
		QString m_codeInstance;

		unsigned int m_scholarYear;
		unsigned int m_semester;
		unsigned int m_creditCount;

		QString m_name;
		QString m_link;

		bool m_isRegistrable;
		bool m_isRegistered;

		Flags m_flags;
};

#endif // INTRAMODULE_HPP_
