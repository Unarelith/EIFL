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

#include "IntraSession.hpp"
#include "NotificationWidget.hpp"

NotificationWidget::NotificationWidget(QWidget *parent) : QWidget(parent) {
	setObjectName("notificationWidget");

	m_titleWidget = new QLabel;
	m_titleWidget->setTextInteractionFlags(Qt::TextBrowserInteraction);
	m_titleWidget->setOpenExternalLinks(true);
	m_titleWidget->setWordWrap(true);

	auto titleFont = m_titleWidget->font();
	titleFont.setBold(true);
	m_titleWidget->setFont(titleFont);

	auto* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	m_contentWidget = new QLabel;
	m_contentWidget->setTextInteractionFlags(Qt::TextBrowserInteraction);
	m_contentWidget->setOpenExternalLinks(true);
	m_contentWidget->setWordWrap(true);

	auto contentFont = m_contentWidget->font();
	contentFont.setPixelSize(13);
	m_contentWidget->setFont(contentFont);

	auto* line2 = new QFrame;
	line2->setFrameShape(QFrame::HLine);
	line2->setFrameShadow(QFrame::Sunken);

	m_dateWidget = new QLabel;
	m_dateWidget->setAlignment(Qt::AlignRight);

	auto *layout = new QVBoxLayout(this);
	layout->addWidget(m_titleWidget);
	layout->addWidget(line);
	layout->addWidget(m_contentWidget);
	layout->addWidget(line2);
	layout->addWidget(m_dateWidget);
}

void NotificationWidget::update(const IntraNotification &notification) {
	// m_dateWidget->setText(notification.date().toString("yyyy/MM/dd HH:mm:ss"));
	m_dateWidget->setText(notification.date().toString("dddd dd MMMM HH:mm:ss"));

	QString title = notification.title();
	title.replace("href=\"/", QString("href=\"") + IntraSession::baseUrl + "/");
	title.replace("href='/", QString("href='") + IntraSession::baseUrl + "/");
	m_titleWidget->setText(title);

	QString content = notification.content();
	content.replace("href=\"/", QString("href=\"") + IntraSession::baseUrl + "/");
	content.replace("href='/", QString("href='") + IntraSession::baseUrl + "/");
	m_contentWidget->setText(content);
}

