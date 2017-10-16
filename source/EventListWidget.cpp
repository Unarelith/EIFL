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
		if (event.isModuleRegistered()) { // FIXME: ADD A FCKIN CHECKBOX
			auto *item = new QTreeWidgetItem(&m_eventListWidget);
			item->setText(0, event.beginDate().toString("HH:mm"));
			item->setText(1, event.endDate().toString("HH:mm"));
			item->setText(2, QString::fromStdString(event.typeTitle()));
			item->setText(3, QString::fromStdString(event.moduleName()));
			item->setText(4, QString::fromStdString(event.name()));

			if (event.isRegistered()) {
				item->setIcon(0, QIcon("res/icons/registered.svg"));
			}
			else if (event.isRegistrable()) {
				item->setIcon(0, QIcon("res/icons/registrable.svg"));
			}
			else {
				item->setIcon(0, QIcon("res/icons/locked.svg"));
			}
		}
	}
}

