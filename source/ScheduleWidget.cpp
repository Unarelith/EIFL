/*
 * =====================================================================================
 *
 *       Filename:  ScheduleWidget.cpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 01:28:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QVBoxLayout>

#include "IntraData.hpp"
#include "ScheduleWidget.hpp"

ScheduleWidget::ScheduleWidget(QWidget *parent) : QDockWidget("Schedule", parent) {
	connect(&m_calendarWidget, &QCalendarWidget::selectionChanged, this, &ScheduleWidget::update);

	m_eventListWidget.setColumnCount(5);
	m_eventListWidget.setHeaderLabels({"Start", "End", "Type", "Module", "Name"});

	QWidget *layoutWidget = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout(layoutWidget);
	layout->addWidget(&m_calendarWidget);
	layout->addWidget(&m_eventListWidget);

	setWidget(layoutWidget);
}

void ScheduleWidget::update() {
	m_eventListWidget.clear();

	auto eventList = IntraData::getInstance().getEventList(m_calendarWidget.selectedDate());
	for (const IntraEvent &event : eventList) {
		if (event.isModuleRegistered()) // FIXME: ADD A FCKIN COMBOBOX
			m_eventListWidget.addTopLevelItem(new QTreeWidgetItem({
				event.beginDate().toString("HH:mm"),
				event.endDate().toString("HH:mm"),
				QString::fromStdString(event.typeTitle()),
				QString::fromStdString(event.moduleName()),
				QString::fromStdString(event.name())
			}));
	}
}

