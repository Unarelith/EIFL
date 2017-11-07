/*
 * =====================================================================================
 *
 *       Filename:  UserInfoWidget.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 14:25:59
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef USERINFOWIDGET_HPP_
#define USERINFOWIDGET_HPP_

#include <QLabel>

class UserInfoWidget : public QWidget {
	public:
		UserInfoWidget(QWidget *parent = nullptr);

		void update();

	private:
		QLabel m_login;
		QLabel m_name;

		QLabel m_birthday;

		QLabel m_creditCount;
		QLabel m_spiceCount;
		QLabel m_gpa;
};

#endif // USERINFOWIDGET_HPP_
