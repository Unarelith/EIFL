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

		void setDate(const QDate &date) { m_date = date; update(); }
		void setSemesters(const std::vector<int> &semesters) { m_semesters = semesters; update(); }
		void setFilters(bool isCurrentSemesterEnabled, bool isRegisteredModulesEnabled, bool isRegisteredEventsEnabled);

	private:
		QTreeWidget m_eventListWidget;

		QDate m_date;
		std::vector<int> m_semesters;

		bool m_isCurrentSemesterEnabled;
		bool m_isRegisteredModulesEnabled;
		bool m_isRegisteredEventsEnabled;
};

#endif // EVENTLISTWIDGET_HPP_
