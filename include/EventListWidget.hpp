/*
 * =====================================================================================
 *
 *       Filename:  EventListWidget.hpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 01:28:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef EVENTLISTWIDGET_HPP_
#define EVENTLISTWIDGET_HPP_

#include <QDockWidget>
#include <QTreeWidget>

class EventListWidget : public QDockWidget {
	public:
		EventListWidget(QWidget *parent = nullptr);

		void setDate(const QDate &date);

		const QTreeWidget &eventListWidget() const { return m_eventListWidget; }

	private:
		QTreeWidget m_eventListWidget;
};

#endif // EVENTLISTWIDGET_HPP_
