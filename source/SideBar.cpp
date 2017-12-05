/*
 * =====================================================================================
 *
 *       Filename:  SideBar.cpp
 *
 *    Description:
 *
 *        Created:  05/12/2017 23:16:55
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "IntraSession.hpp"
#include "SideBar.hpp"

SideBar::SideBar(QWidget *parent) : QDockWidget("Side bar (WIP)", parent) {
	setupWidgets();
	setupLayout();
}

void SideBar::setupWidgets() {
	m_profilePicture.setMaximumSize(160 / 2, 190 / 2);
	m_profilePicture.setScaledContents(true);

	auto lastNameFont = m_lastNameLabel.font();
	lastNameFont.setPointSize(16);
	m_lastNameLabel.setFont(lastNameFont);

	auto creditFont = m_creditLabel.font();
	creditFont.setPointSize(18);
	m_creditLabel.setFont(creditFont);
	m_creditLabel.setAlignment(Qt::AlignCenter);

	m_buttonListWidget = new QWidget;
	auto *buttonListLayout = new QVBoxLayout(m_buttonListWidget);
	buttonListLayout->addWidget(new QPushButton(tr("Units")));
	buttonListLayout->addWidget(new QPushButton(tr("Projects")));
	buttonListLayout->addWidget(new QPushButton(tr("Planning")));
}

void SideBar::setupLayout() {
	auto *nameLayoutWidget = new QWidget;
	auto *nameLayout = new QVBoxLayout(nameLayoutWidget);
	nameLayout->addWidget(&m_lastNameLabel, 0);
	nameLayout->addWidget(&m_firstNameLabel, 0);
	nameLayout->addStretch(1);

	auto *pictureLayoutWidget = new QWidget;
	auto *pictureLayout = new QHBoxLayout(pictureLayoutWidget);
	pictureLayout->addWidget(&m_profilePicture);
	pictureLayout->addWidget(nameLayoutWidget);

	auto *subLayoutWidget = new QWidget;
	auto *subLayout = new QHBoxLayout(subLayoutWidget);
	subLayout->addWidget(&m_gpaLabel);
	subLayout->addWidget(&m_creditLabel, 1);
	subLayout->addWidget(&m_spiceLabel);

	auto *mainLayoutWidget = new QWidget;
	auto *mainLayout = new QVBoxLayout(mainLayoutWidget);
	mainLayout->addWidget(pictureLayoutWidget);
	mainLayout->addWidget(subLayoutWidget);
	mainLayout->addWidget(m_buttonListWidget);
	mainLayout->addStretch(1);

	setWidget(mainLayoutWidget);
}

void SideBar::update(const IntraUser &user) {
	m_profilePicture.setPixmap(IntraSession::getInstance().getProfilePicture(user.pictureLink()));

	m_firstNameLabel.setText(user.firstName());
	m_lastNameLabel.setText(user.lastName());

	m_gpaLabel.setNum(user.gpa());
	m_spiceLabel.setNum((int)user.spiceCount());
	m_creditLabel.setNum((int)user.creditCount());
}

