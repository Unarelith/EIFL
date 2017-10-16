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

EventInfoWidget::EventInfoWidget(QWidget *parent) : QGroupBox("Informations", parent) {
	QFormLayout *layout = new QFormLayout(this);

	layout->addRow("Name:", &m_name);
	layout->addRow("Module:", &m_moduleName);
	layout->addRow("Registrable:", &m_isRegistrable);
	layout->addRow("Registered:", &m_isRegistered);
	layout->addRow("Appointment:", &m_appointmentDate);
}

void EventInfoWidget::update(QTreeWidgetItem *item, unsigned int) {
	for (const IntraEvent &event : IntraData::getInstance().getEventList(m_date)) {
		if (item->text(4).toStdString() == event.name()) {
			m_name.setText(QString::fromStdString(event.name()));
			m_moduleName.setText(QString::fromStdString(event.moduleName()));

			m_isRegistrable.setText(event.isRegistrable() ? "Yes" : "No");
			m_isRegistered.setText(event.isRegistered() ? "Yes" : "No");

			m_appointmentDate.setText(event.appointmentDate().toString(Qt::SystemLocaleShortDate));
		}
	}
}

