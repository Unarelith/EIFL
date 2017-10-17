/*
 * =====================================================================================
 *
 *       Filename:  IntraSession.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 18:24:46
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRASESSION_HPP_
#define INTRASESSION_HPP_

#include <QJsonDocument>

#include <cpr/cpr.h>

#include "Keyring.hpp"

class IntraSession {
	public:
		IntraSession();

		void login();

		using ParameterList = std::map<QString, QString>;
		QJsonDocument get(const QString &apiEndpoint, const ParameterList &parameters = {}) const;

		static const IntraSession &getInstance() {
			return *s_instance;
		}

		static void setInstance(const IntraSession &instance) {
			s_instance = &instance;
		}

		static constexpr const char *baseUrl = "https://intra.epitech.eu";

	private:
		static const IntraSession *s_instance;

		void askLogin();
		void askPassword();

		cpr::Cookies m_cookies;

		Keyring m_keyring;
};

#endif // INTRASESSION_HPP_
