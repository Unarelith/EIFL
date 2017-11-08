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

#include "IntraItem.hpp"

class IntraModule : public IntraItem {
	public:
		IntraModule(const QJsonObject &jsonObject);
		IntraModule(const QSqlQuery &sqlQuery) : IntraItem("units", sqlQuery) {}

		enum Flags {
			Optional = 1,
			Progressive = 2,
			RoadblockCycle = 4,
			RoadblockYear = 8,
			MultipleRegistration = 32,
			Mandatory = 128
		};

		QString code() const { return get("code").toString(); }
		QString codeInstance() const { return get("code_instance").toString(); }

		unsigned int scholarYear() const { return get("scholar_year").toUInt(); }
		unsigned int semester() const { return get("semester").toUInt(); }
		unsigned int creditCount() const { return get("credit_count").toUInt(); }

		QString name() const { return get("name").toString(); }
		QString link() const { return get("link").toString(); }

		bool isRegistrable() const { return get("is_registrable").toBool(); }
		bool isRegistered() const { return get("is_registered").toBool(); }

		Flags flags() const { return static_cast<Flags>(get("flags").toInt()); }
};

#endif // INTRAMODULE_HPP_
