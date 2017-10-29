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

#include <QTreeWidget>

class NotificationListWidget : public QWidget {
	public:
		NotificationListWidget(QWidget *parent = nullptr);

		void update();

		const QTreeWidget &notificationListWidget() const { return m_notificationListWidget; }

	private:
		QTreeWidget m_notificationListWidget;
};

#endif // NOTIFICATIONLISTWIDGET_HPP_
