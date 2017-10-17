/*
 * =====================================================================================
 *
 *       Filename:  UserInfoWidget.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 14:26:34
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QFormLayout>

#include "IntraData.hpp"
#include "IntraUser.hpp"
#include "UserInfoWidget.hpp"

UserInfoWidget::UserInfoWidget(QWidget *parent) : QWidget(parent) {
	QFormLayout *layout = new QFormLayout(this);
	layout->addRow("Login:", &m_login);
	layout->addRow("Name:", &m_name);
	layout->addRow("Birthday:", &m_birthday);
	layout->addRow("Credits:", &m_creditCount);
	layout->addRow("Spices:", &m_spiceCount);
	layout->addRow("GPA:", &m_gpa);
}

void UserInfoWidget::update(const QString &login) {
	IntraUser userInfo = IntraData::getInstance().getUserInfo(login);

	m_login.setText(userInfo.login());
	m_name.setText(userInfo.firstName() + " " + userInfo.lastName());

	m_birthday.setText(userInfo.birthday().toString(Qt::SystemLocaleShortDate));

	m_creditCount.setNum((int)userInfo.creditCount());
	m_spiceCount.setNum((int)userInfo.spiceCount());
	m_gpa.setNum(userInfo.gpa());
}

