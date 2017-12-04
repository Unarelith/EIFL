/*
 * =====================================================================================
 *
 *       Filename:  NotificationWidget.cpp
 *
 *    Description:
 *
 *        Created:  04/12/2017 08:48:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QVBoxLayout>

#include "NotificationWidget.hpp"

NotificationWidget::NotificationWidget(QWidget *parent) : QWidget(parent) {
	setObjectName("notificationWidget");
	setStyleSheet("QWidget#notificationWidget {"
		"border-style: outset;"
		"border-width: 1px;"
		"border-radius: 6px;"
		"border-color: grey;"
		"padding: 6px;"
	"}");

	m_dateWidget = new QLabel;
	m_dateWidget->setObjectName("dateWidget");

	auto* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	m_titleWidget = new QLabel;
	m_titleWidget->setTextInteractionFlags(Qt::TextBrowserInteraction);
	m_titleWidget->setOpenExternalLinks(true);
	m_titleWidget->setObjectName("titleWidget");

	auto *layout = new QVBoxLayout(this);
	layout->addWidget(m_dateWidget);
	layout->addWidget(line);
	layout->addWidget(m_titleWidget);
}

void NotificationWidget::update(const IntraNotification &notification) {
	// m_dateWidget->setText(notification.date().toString("yyyy/MM/dd HH:mm:ss"));
	m_dateWidget->setText(notification.date().toString("dddd dd MMMM HH:mm:ss"));
	m_titleWidget->setText(notification.title());
}

