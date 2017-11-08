/*
 * =====================================================================================
 *
 *       Filename:  EventInfoWidget.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:26:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QFormLayout>

#include "IntraData.hpp"
#include "EventInfoWidget.hpp"

EventInfoWidget::EventInfoWidget(QWidget *parent) : QDockWidget("Event details", parent) {
	QWidget *layoutWidget = new QWidget;
	QFormLayout *layout = new QFormLayout(layoutWidget);

	layout->addRow("Name:", &m_name);
	layout->addRow("Module:", &m_moduleName);
	layout->addRow("Is appointment:", &m_isAppointment);
	layout->addRow("Appointment:", &m_appointmentDate);

	setWidget(layoutWidget);
}

void EventInfoWidget::update(QTreeWidgetItem *item) {
	if (item) {
		for (auto &it : IntraData::getInstance().eventList()) {
			if (item->text(item->columnCount() - 1) == it.second.activity().name()) {
				m_name.setText(it.second.activity().name());
				m_moduleName.setText(it.second.activity().module().name());

				m_isAppointment.setText(QString::number(it.second.activity().isAppointment()));
				m_appointmentDate.setText(it.second.activity().appointmentDate().toString(Qt::SystemLocaleShortDate));
			}
		}
	}
}

