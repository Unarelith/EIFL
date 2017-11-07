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
#include <QHeaderView>
#include <QVBoxLayout>

#include "IntraData.hpp"
#include "EventListWidget.hpp"
#include "IntraData.hpp"

EventListWidget::EventListWidget(QWidget *parent) : QDockWidget("Event list", parent) {
	m_eventListWidget.setColumnCount(7);
	m_eventListWidget.setHeaderLabels({"", "Start", "End", "Room", "Type", "Module", "Name"});
	m_eventListWidget.setRootIsDecorated(false);
	m_eventListWidget.setSortingEnabled(true);
	m_eventListWidget.header()->setSectionResizeMode(QHeaderView::Fixed);
	m_eventListWidget.sortItems(1, Qt::AscendingOrder);
	m_eventListWidget.setColumnWidth(0, 27);
	m_eventListWidget.setColumnWidth(5, 2 * m_eventListWidget.columnWidth(5));

	setWidget(&m_eventListWidget);
}

void EventListWidget::update() {
	m_eventListWidget.clear();

	auto eventList = IntraData::getInstance().getEventList(m_date, m_semesters);
	for (const IntraEvent &event : eventList) {
		if ((!m_isCurrentSemesterEnabled || (event.activity().module().semester() == IntraData::getInstance().getUserInfo("").currentSemester() || event.activity().module().semester() == 0))
		 && (!m_isRegisteredModulesEnabled || event.activity().module().isRegistered())
		 && (!m_isRegisteredEventsEnabled || event.isRegistered())) {
			auto *item = new QTreeWidgetItem(&m_eventListWidget);
			item->setText(1, event.beginDate().toString("HH:mm"));
			item->setText(2, event.endDate().toString("HH:mm"));
			item->setText(3, event.roomName());
			item->setText(4, event.activity().typeTitle());
			item->setText(5, event.activity().module().name());
			item->setText(6, event.activity().name());

			if (event.isMissed()) {
				item->setIcon(0, QIcon(":/missed.svg"));
				item->setText(0, " 0");

				for (int i = 0 ; i < item->columnCount() ; ++i)
					item->setBackgroundColor(i, Qt::darkRed);
			}
			else if (event.isRegistered()) {
				item->setIcon(0, QIcon(":/registered.svg"));
				item->setText(0, " 1");
			}
			else if (event.isRegistrable() && event.isValid()) {
				item->setIcon(0, QIcon(":/registrable.svg"));
				item->setText(0, " 2");
			}
			else {
				item->setIcon(0, QIcon(":/locked.svg"));
				item->setText(0, " 3");
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

