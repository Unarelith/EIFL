/*
 * =====================================================================================
 *
 *       Filename:  NotificationWidget.hpp
 *
 *    Description:
 *
 *        Created:  04/12/2017 08:48:05
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NOTIFICATIONWIDGET_HPP_
#define NOTIFICATIONWIDGET_HPP_

#include <QLabel>

#include "IntraNotification.hpp"

class NotificationWidget : public QWidget {
	public:
		NotificationWidget(QWidget *parent = nullptr);

		void update(const IntraNotification &notification);

	private:
		QLabel *m_dateWidget;
		QLabel *m_titleWidget;
		QLabel *m_contentWidget;
};

#endif // NOTIFICATIONWIDGET_HPP_
