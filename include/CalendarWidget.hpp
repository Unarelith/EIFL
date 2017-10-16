/*
 * =====================================================================================
 *
 *       Filename:  CalendarWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:32:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CALENDARWIDGET_HPP_
#define CALENDARWIDGET_HPP_

#include <QCalendarWidget>
#include <QDockWidget>
#include <QTextCharFormat>
#include <QTreeWidgetItem>

class CalendarWidget : public QWidget {
	Q_OBJECT

	public:
		CalendarWidget(QWidget *parent = nullptr);

		void loadFormats();

		void displayProjectDates(QTreeWidgetItem *item, unsigned int column);

		const QCalendarWidget &calendarWidget() const { return m_calendarWidget; }

	public slots:
		void clearAction() { m_calendarWidget.setDateTextFormat(QDate(), QTextCharFormat()); }
		void todayAction() { m_calendarWidget.setSelectedDate(QDate::currentDate()); }

	signals:
		void dateHasChanged(const QDate &date);

	private:
		QTextCharFormat m_currentProjectFormat;
		QTextCharFormat m_registerDateFormat;
		QTextCharFormat m_beginDateFormat;
		QTextCharFormat m_endDateFormat;

		QCalendarWidget m_calendarWidget;
};

#endif // CALENDARWIDGET_HPP_
