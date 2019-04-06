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
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>

#include "IntraSession.hpp"
#include "SideBar.hpp"

SideBar::SideBar(QWidget *parent) : QDockWidget("Side bar (WIP)", parent) {
	setupWidgets();
	setupLayout();
}

void SideBar::setupWidgets() {
	m_profilePicture.setObjectName("profilePicture");
	m_profilePicture.setMaximumSize(80, 80);
	m_profilePicture.setScaledContents(true);

	auto lastNameFont = m_lastNameLabel.font();
	lastNameFont.setPointSize(16);
	m_lastNameLabel.setFont(lastNameFont);
	// m_lastNameLabel.setObjectName("lastNameLabel");
	// m_firstNameLabel.setObjectName("firstNameLabel");

	auto creditFont = m_creditLabel.font();
	creditFont.setPointSize(18);
	m_creditLabel.setFont(creditFont);
	m_creditLabel.setAlignment(Qt::AlignCenter);
	// m_creditLabel.setObjectName("creditLabel");
	// m_gpaLabel.setObjectName("gpaLabel");
	// m_spiceLabel.setObjectName("spiceLabel");

	QList<QPushButton *> buttonList;
	QStringList nameList = {"Units", "Projects", "Planning"};
	for (auto &name : nameList) {
		buttonList.push_back(new QPushButton(name));
		buttonList.back()->setObjectName("sideBarButton");
	}

	m_buttonListWidget = new QWidget;
	auto *buttonListLayout = new QVBoxLayout(m_buttonListWidget);
	buttonListLayout->setSpacing(0);
	buttonListLayout->setMargin(0);
	buttonListLayout->setContentsMargins(0, 0, 0, 0);
	for (auto &button : buttonList)
		buttonListLayout->addWidget(button);
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

	auto* line = new QFrame();
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	auto *profileLayoutWidget = new QWidget;
	auto *profileLayout = new QVBoxLayout(profileLayoutWidget);
	profileLayout->addWidget(pictureLayoutWidget);
	profileLayout->addWidget(subLayoutWidget);
	profileLayout->addWidget(line);

	auto *mainLayoutWidget = new QWidget;
	mainLayoutWidget->setObjectName("sideBar");
	auto *mainLayout = new QVBoxLayout(mainLayoutWidget);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setMargin(0);
	mainLayout->addWidget(profileLayoutWidget);
	mainLayout->addWidget(m_buttonListWidget);
	mainLayout->addStretch(1);

	setWidget(mainLayoutWidget);

}

void SideBar::update(const IntraUser &user) {
	QPixmap picturePixmap = IntraSession::getInstance().getProfilePicture(user.pictureLink());
	unsigned int minSize = std::min(picturePixmap.width(), picturePixmap.height());
	unsigned int rX = picturePixmap.width() - minSize;
	unsigned int rY = picturePixmap.height() - minSize;

	QPixmap targetPixmap(minSize, minSize);
	targetPixmap.fill(QColor(0, 0, 0, 0));

	QPainter painter(&targetPixmap);
	QRegion region(QRect(0, 0, picturePixmap.width() - rX, picturePixmap.height() - rY), QRegion::Ellipse);
	painter.setClipRegion(region);
	painter.drawPixmap(0, 0, picturePixmap);

	m_profilePicture.setPixmap(targetPixmap);

	m_firstNameLabel.setText(user.firstName());
	m_lastNameLabel.setText(user.lastName());

	m_gpaLabel.setNum(user.gpa());
	m_spiceLabel.setNum((int)user.spiceCount());
	m_creditLabel.setNum((int)user.creditCount());
}

