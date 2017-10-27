/*
 * =====================================================================================
 *
 *       Filename:  EventInfoWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:26:27
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef EVENTINFOWIDGET_HPP_
#define EVENTINFOWIDGET_HPP_

#include <QDate>
#include <QDockWidget>
#include <QLabel>
#include <QTreeWidgetItem>

class EventInfoWidget : public QDockWidget {
	public:
		EventInfoWidget(QWidget *parent = nullptr);

		void update(QTreeWidgetItem *item);

		void setDate(const QDate &date) { m_date = date; }
		void setSemesters(const std::vector<unsigned int> &semesters) { m_semesters = semesters; }

	private:
		QLabel m_name;
		QLabel m_moduleName;

		QLabel m_appointmentDate;

		QDate m_date;
		std::vector<unsigned int> m_semesters;
};

#endif // EVENTINFOWIDGET_HPP_
