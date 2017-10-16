/*
 * =====================================================================================
 *
 *       Filename:  EventListWidget.cpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 01:28:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "IntraData.hpp"
#include "EventListWidget.hpp"

EventListWidget::EventListWidget(QWidget *parent) : QDockWidget("Event list", parent) {
	m_eventListWidget.setColumnCount(5);
	m_eventListWidget.setHeaderLabels({"Start", "End", "Type", "Module", "Name"});

	setWidget(&m_eventListWidget);
}

void EventListWidget::setDate(const QDate &date) {
	m_eventListWidget.clear();

	auto eventList = IntraData::getInstance().getEventList(date);
	for (const IntraEvent &event : eventList) {
		if (event.isModuleRegistered()) // FIXME: ADD A FCKIN CHECKBOX
			m_eventListWidget.addTopLevelItem(new QTreeWidgetItem({
				event.beginDate().toString("HH:mm"),
				event.endDate().toString("HH:mm"),
				QString::fromStdString(event.typeTitle()),
				QString::fromStdString(event.moduleName()),
				QString::fromStdString(event.name())
			}));
	}
}

