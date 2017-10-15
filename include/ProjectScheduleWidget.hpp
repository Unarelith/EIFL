/*
 * =====================================================================================
 *
 *       Filename:  ProjectScheduleWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:32:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PROJECTSCHEDULEWIDGET_HPP_
#define PROJECTSCHEDULEWIDGET_HPP_

#include <QCalendarWidget>
#include <QGroupBox>
#include <QTextCharFormat>
#include <QTreeWidgetItem>

class ProjectScheduleWidget : public QGroupBox {
	public:
		ProjectScheduleWidget(QWidget *parent = nullptr);

		void displayProjectDates(QTreeWidgetItem *item, unsigned int column);

		const QCalendarWidget &calendarWidget() const { return m_calendarWidget; }

	private:
		QTextCharFormat m_currentProjectFormat;
		QTextCharFormat m_registerDateFormat;
		QTextCharFormat m_beginDateFormat;
		QTextCharFormat m_endDateFormat;

		QCalendarWidget m_calendarWidget;
};

#endif // PROJECTSCHEDULEWIDGET_HPP_
