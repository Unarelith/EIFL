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

		QJsonDocument get(const std::string &apiEndpoint);

	private:
		void askPassword();

		cpr::Cookies m_cookies;

		Keyring m_keyring;
};

#endif // INTRASESSION_HPP_
