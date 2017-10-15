/*
 * =====================================================================================
 *
 *       Filename:  ScheduleWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:32:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef SCHEDULEWIDGET_HPP_
#define SCHEDULEWIDGET_HPP_

#include <QCalendarWidget>
#include <QDockWidget>
#include <QTextCharFormat>
#include <QTreeWidgetItem>

class ScheduleWidget : public QDockWidget {
	public:
		ScheduleWidget(QWidget *parent = nullptr);

		void displayProjectDates(QTreeWidgetItem *item, unsigned int column);

	private:
		QTextCharFormat m_currentProjectFormat;
		QTextCharFormat m_registerDateFormat;
		QTextCharFormat m_beginDateFormat;
		QTextCharFormat m_endDateFormat;

		QCalendarWidget m_calendarWidget;
};

#endif // SCHEDULEWIDGET_HPP_
