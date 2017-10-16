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
#include <QGroupBox>
#include <QLabel>
#include <QTreeWidgetItem>

class EventInfoWidget : public QGroupBox {
	public:
		EventInfoWidget(QWidget *parent = nullptr);

		void update(QTreeWidgetItem *item, unsigned int column);

		void setDate(const QDate &date) { m_date = date; }

	private:
		QLabel m_name;
		QLabel m_moduleName;

		QLabel m_isRegistrable;
		QLabel m_isRegistered;

		QLabel m_appointmentDate;

		QDate m_date;
};

#endif // EVENTINFOWIDGET_HPP_