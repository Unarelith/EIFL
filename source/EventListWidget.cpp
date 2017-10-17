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
	m_eventListWidget.setColumnCount(6);
	m_eventListWidget.setHeaderLabels({"Start", "End", "Room", "Type", "Module", "Name"});

	setWidget(&m_eventListWidget);
}

void EventListWidget::update() {
	m_eventListWidget.clear();

	auto eventList = IntraData::getInstance().getEventList(m_date, m_semesters);
	for (const IntraEvent &event : eventList) {
		// FIXME: Find a way to get current semester
		if ((!m_isCurrentSemesterEnabled || (event.semester() == 5 || event.semester() == 0))
		 && (!m_isRegisteredModulesEnabled || event.isModuleRegistered())
		 && (!m_isRegisteredEventsEnabled || event.isRegistered())) {
			auto *item = new QTreeWidgetItem(&m_eventListWidget);
			item->setText(0, event.beginDate().toString("HH:mm"));
			item->setText(1, event.endDate().toString("HH:mm"));
			item->setText(2, event.roomName());
			item->setText(3, event.typeTitle());
			item->setText(4, event.moduleName());
			item->setText(5, event.name());

			if (event.isRegistered()) {
				item->setIcon(0, QIcon(":/registered.svg"));
			}
			else if (event.isRegistrable()) {
				item->setIcon(0, QIcon(":/registrable.svg"));
			}
			else if (event.isMissed()) {
				item->setIcon(0, QIcon(":/missed.svg"));

				for (int i = 0 ; i < item->columnCount() ; ++i)
					item->setBackgroundColor(i, Qt::darkRed);
			}
			else {
				item->setIcon(0, QIcon(":/locked.svg"));
			}
		}
	}
}

void EventListWidget::setFilters(bool isCurrentSemesterEnabled, bool isRegisteredModulesEnabled, bool isRegisteredEventsEnabled) {
	m_isCurrentSemesterEnabled = isCurrentSemesterEnabled;
	m_isRegisteredModulesEnabled = isRegisteredModulesEnabled;
	m_isRegisteredEventsEnabled = isRegisteredEventsEnabled;

	update();
}

