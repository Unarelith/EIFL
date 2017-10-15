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

IntraSession::IntraSession() {
	login();
}

void IntraSession::login() {
	if (!m_keyring.hasPassword())
		askPassword();

	QString password = m_keyring.getPassword();

	auto r = cpr::Post(cpr::Url{"https://intra.epitech.eu"},
	                    cpr::Payload{{"login",    "quentin.bazin@epitech.eu"},
	                                 {"password", password.toStdString()},
	                                 {"remind",   "on"}});
	if (r.status_code == 200) {
		m_cookies = r.cookies;
	}
	else if (r.status_code == 401) {
		askPassword();
		login();
	}
	else {
		std::cerr << "Failed to login. Code: " << r.status_code << std::endl;
	}
}

QJsonDocument IntraSession::get(const std::string &apiEndpoint) {
	auto r = cpr::Get(cpr::Url{"https://intra.epitech.eu" + apiEndpoint + "?format=json"}, m_cookies);
	return QJsonDocument::fromJson(QByteArray::fromStdString(r.text));
}

void IntraSession::askPassword() {
	bool ok;
	QString text = QInputDialog::getText(nullptr, "Epitech Intra", "Password:", QLineEdit::Password, "", &ok);
	if (ok)
		m_keyring.storePassword(text);
}

