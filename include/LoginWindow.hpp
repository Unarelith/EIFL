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

#include <QDialog>

class LoginWindow : public QDialog {
	Q_OBJECT

	public:
		LoginWindow(QWidget *parent = nullptr);

	signals:
		void quitButtonPressed();
};

#endif // LOGINWINDOW_HPP_
