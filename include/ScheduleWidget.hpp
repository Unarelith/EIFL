/*
 * =====================================================================================
 *
 *       Filename:  ScheduleWidget.hpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 01:28:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SCHEDULEWIDGET_HPP_
#define SCHEDULEWIDGET_HPP_

#include <QCalendarWidget>
#include <QDockWidget>
#include <QTreeWidget>

#include "EventInfoWidget.hpp"

class ScheduleWidget : public QDockWidget {
	public:
		ScheduleWidget(QWidget *parent = nullptr);

		void update();

	private:
		QCalendarWidget m_calendarWidget;

		EventInfoWidget m_eventInfoWidget;
		QTreeWidget m_eventListWidget;
};

#endif // SCHEDULEWIDGET_HPP_
