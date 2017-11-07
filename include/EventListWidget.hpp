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

#include <QDate>
#include <QDockWidget>
#include <QTreeWidget>

class EventListWidget : public QDockWidget {
	public:
		EventListWidget(QWidget *parent = nullptr);

		void update();

		const QTreeWidget &eventListWidget() const { return m_eventListWidget; }

		bool hasSemester(unsigned int semester) { for (unsigned int s : m_semesters) if (s == semester) return true; return false; }

		void setDate(const QDate &date) { m_date = date; update(); }
		void setSemesters(const QList<unsigned int> &semesters) { m_semesters = semesters; update(); }
		void setFilters(bool isCurrentSemesterEnabled, bool isRegisteredModulesEnabled, bool isRegisteredEventsEnabled);

	private:
		QTreeWidget m_eventListWidget;

		QDate m_date;
		QList<unsigned int> m_semesters;

		bool m_isCurrentSemesterEnabled = false;
		bool m_isRegisteredModulesEnabled = true;
		bool m_isRegisteredEventsEnabled = false;
};

#endif // EVENTLISTWIDGET_HPP_
