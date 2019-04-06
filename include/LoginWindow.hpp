/*
 * =====================================================================================
 *
 *       Filename:  LoginWindow.hpp
 *
 *    Description:
 *
 *        Created:  02/12/2017 02:36:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef LOGINWINDOW_HPP_
#define LOGINWINDOW_HPP_

#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>

#include "Keyring.hpp"

class LoginWindow : public QDialog {
	Q_OBJECT

	public:
		LoginWindow(const Keyring &keyring, QWidget *parent = nullptr);

		void login();

		void setupWidgets();

	signals:
		void databaseReloadRequested();
		void quitButtonPressed();

	private:
		const Keyring &m_keyring;

		QLabel m_errorLabel;

		QLineEdit m_autologinWidget;
		// QLineEdit m_loginWidget;
		// QLineEdit m_passwordWidget;

		QCheckBox m_rememberMeWidget{"Remember my password"};
};

#endif // LOGINWINDOW_HPP_
