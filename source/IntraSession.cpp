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

#include <QInputDialog>

#include "IntraSession.hpp"

const IntraSession *IntraSession::s_instance = nullptr;

IntraSession::IntraSession() {
	login();
}

void IntraSession::login() {
	if (!m_keyring.has("eifl_login"))
		askLogin();

	if (!m_keyring.has("eifl_password"))
		askPassword();

	auto r = cpr::Post(cpr::Url{baseUrl},
	                   cpr::Payload{{"login",    m_keyring.get("eifl_login").toStdString()},
	                                {"password", m_keyring.get("eifl_password").toStdString()},
	                                {"remind",   "on"}});
	if (r.status_code == 200) {
		m_cookies = r.cookies;
	}
	else if (r.status_code == 401) {
		askLogin();
		askPassword();
		login();
	}
	else {
		std::cerr << "Failed to login. Code: " << r.status_code << std::endl;
	}
}

QJsonDocument IntraSession::get(const QString &apiEndpoint, const ParameterList &parameters) const {
	QString url = baseUrl + apiEndpoint + "?format=json";
	for (auto &parameter : parameters)
		url += "&" + parameter.first + "=" + parameter.second;

	auto r = cpr::Get(cpr::Url{url.toStdString()}, m_cookies);
	return QJsonDocument::fromJson(QByteArray::fromStdString(r.text));
}

void IntraSession::askLogin() {
	bool ok;
	QString text = QInputDialog::getText(nullptr, "Epitech Intra", "Login:", QLineEdit::Normal, "", &ok);
	if (ok)
		m_keyring.store("eifl_login", text);
}

void IntraSession::askPassword() {
	bool ok;
	QString text = QInputDialog::getText(nullptr, "Epitech Intra", "Password:", QLineEdit::Password, "", &ok);
	if (ok)
		m_keyring.store("eifl_password", text);
}

