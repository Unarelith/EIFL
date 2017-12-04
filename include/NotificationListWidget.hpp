/*
 * =====================================================================================
 *
 *       Filename:  NotificationListWidget.hpp
 *
 *    Description:
 *
 *        Created:  29/10/2017 21:05:09
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef NOTIFICATIONLISTWIDGET_HPP_
#define NOTIFICATIONLISTWIDGET_HPP_

#include <QVBoxLayout>

#include "NotificationWidget.hpp"

class NotificationListWidget : public QWidget {
	public:
		NotificationListWidget(QWidget *parent = nullptr);

		void update();

	private:
		QVBoxLayout *m_layout = nullptr;
		QList<NotificationWidget *> m_widgetList;
};

#endif // NOTIFICATIONLISTWIDGET_HPP_
