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

#include <QStandardItemModel>
#include <QTreeView>

class NotificationListWidget : public QWidget {
	public:
		NotificationListWidget(QWidget *parent = nullptr);

		void update();

		const QTreeView &view() const { return m_view; }

	private:
		QStandardItemModel m_model;
		QTreeView m_view;
};

#endif // NOTIFICATIONLISTWIDGET_HPP_
