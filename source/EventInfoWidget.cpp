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
	layout->addRow("Appointment:", &m_appointmentDate);

	setWidget(layoutWidget);
}

void EventInfoWidget::update(QTreeWidgetItem *item) {
	if (item) {
		for (const IntraEvent &event : IntraData::getInstance().getEventList(m_date, m_semesters)) {
			if (item->text(item->columnCount() - 1) == event.activity().name()) {
				m_name.setText(event.activity().name());
				m_moduleName.setText(event.activity().module().name());

				m_appointmentDate.setText(event.appointmentDate().toString(Qt::SystemLocaleShortDate));
			}
		}
	}
}

