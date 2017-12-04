/*
 * =====================================================================================
 *
 *       Filename:  NotificationListWidget.cpp
 *
 *    Description:
 *
 *        Created:  29/10/2017 21:05:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHeaderView>
#include <QHBoxLayout>
#include <QScrollArea>

#include "IntraData.hpp"
#include "NotificationListWidget.hpp"

NotificationListWidget::NotificationListWidget(QWidget *parent) : QWidget(parent) {
	auto *layoutWidget = new QWidget;
	m_layout = new QVBoxLayout(layoutWidget);

	auto *scrollArea = new QScrollArea;
	scrollArea->setWidget(layoutWidget);
	scrollArea->setWidgetResizable(true);

	auto *globalLayout = new QHBoxLayout(this);
	globalLayout->addWidget(scrollArea);
}

void NotificationListWidget::update() {
	QLayoutItem *item;
	while ((item = m_layout->takeAt(0)) != NULL) {
		delete item->widget();
		delete item;
	}

	m_widgetList.clear();

	QModelIndex parentItem;
	auto &notificationList = IntraData::getInstance().notificationList();
	for (auto it = notificationList.rbegin() ; it != notificationList.rend() ; ++it) {
		auto *widget = new NotificationWidget;
		widget->update(it->second);
		m_layout->addWidget(widget);
		m_widgetList.append(widget);
	}
}

