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
#include "NotificationWidget.hpp"

NotificationWidget::NotificationWidget(QWidget *parent) : QWidget(parent) {
	m_textWidget.setReadOnly(true);
	m_textWidget.setAcceptRichText(true);
}

void NotificationWidget::update(const IntraNotification &notification) {
	m_textWidget.setHtml(notification.title());
}

