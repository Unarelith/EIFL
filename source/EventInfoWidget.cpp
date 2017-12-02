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
			const IntraActivity *activity = IntraData::getInstance().getActivity(it.second.activityId());
			const IntraModule *module = IntraData::getInstance().getModule(activity ? activity->moduleId() : 0);

			if (activity && item->text(item->columnCount() - 1) == activity->name()) {
				m_name.setText(activity->name());
				m_moduleName.setText(module ? module->name() : "");

				m_isAppointment.setText(QString::number(activity->isAppointment()));
				m_appointmentDate.setText(activity->appointmentDate().toString(Qt::SystemLocaleShortDate));
			}
		}
	}
}

