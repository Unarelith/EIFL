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

class IntraSession : public QObject {
	Q_OBJECT

	public:
		int login(const Keyring &keyring);

		using ParameterList = std::map<QString, QString>;
		QJsonDocument get(const QString &apiEndpoint, const ParameterList &parameters = {}) const;

		bool isLoggedIn() const { return m_isLoggedIn; }

		static IntraSession &getInstance() { return *s_instance; }
		static void setInstance(IntraSession &instance) { s_instance = &instance; }

		static constexpr const char *baseUrl = "https://intra.epitech.eu";

	signals:
		void stateChanged(const QString &state, int timeout = 0) const;

	private:
		static IntraSession *s_instance;

		bool m_isLoggedIn = false;

		cpr::Cookies m_cookies;
};

#endif // INTRASESSION_HPP_
