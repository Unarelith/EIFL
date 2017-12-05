/*
 * =====================================================================================
 *
 *       Filename:  SideBar.hpp
 *
 *    Description:
 *
 *        Created:  05/12/2017 23:16:13
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SIDEBAR_HPP_
#define SIDEBAR_HPP_

#include <QDockWidget>
#include <QLabel>

#include "IntraUser.hpp"

class SideBar : public QDockWidget {
	public:
		SideBar(QWidget *parent = nullptr);

		void setupWidgets();
		void setupLayout();

		void update(const IntraUser &user);

	private:
		QLabel m_profilePicture;

		QLabel m_firstNameLabel;
		QLabel m_lastNameLabel;

		QLabel m_gpaLabel;
		QLabel m_spiceLabel;
		QLabel m_creditLabel;

		QWidget *m_buttonListWidget;
};

#endif // SIDEBAR_HPP_
