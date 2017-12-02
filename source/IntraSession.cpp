/*
 * =====================================================================================
 *
 *       Filename:  IntraSession.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 18:25:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>

#include <QStatusBar>

#include "IntraSession.hpp"
#include "MainWindow.hpp"

IntraSession *IntraSession::s_instance = nullptr;

int IntraSession::login(const Keyring &keyring) {
	auto r = cpr::Post(cpr::Url{baseUrl},
	                   cpr::Payload{{"login",    keyring.get("eifl_login").toStdString()},
	                                {"password", keyring.get("eifl_password").toStdString()},
	                                {"remind",   "on"}});
	if (r.status_code == 200) {
		m_cookies = r.cookies;
		m_cookies["language"] = "fr";

		m_isLoggedIn = true;
	}

	return r.status_code;
}

QJsonDocument IntraSession::get(const QString &apiEndpoint, const ParameterList &parameters) const {
	QString url = baseUrl + apiEndpoint + "?format=json";
	for (auto &parameter : parameters)
		url += "&" + parameter.first + "=" + parameter.second;

	// std::cout << "GET " << apiEndpoint.toStdString() << std::endl;

	emit stateChanged("Downloading intra data, this may take a while...");

	// QTime before = QTime::currentTime();

	auto r = cpr::Get(cpr::Url{url.toStdString()}, m_cookies);
	if (r.status_code != 200) {
		std::cerr << "Error: Http request failed. Code: " << r.status_code << std::endl;
		emit stateChanged("Request failed. (" + QString::number(r.status_code) + ")");
	}
	// else {
	// 	emit stateChanged("Downloading intra data... Done. (" + QString::number(r.status_code) + ")");
	// }

	// std::cout << "GET request finished in " << before.msecsTo(QTime::currentTime()) << " ms" << std::endl;

	return QJsonDocument::fromJson(QByteArray::fromStdString(r.text));
}

