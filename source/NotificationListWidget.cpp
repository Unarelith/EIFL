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
#include <QHBoxLayout>

#include "IntraData.hpp"
#include "NotificationListWidget.hpp"

NotificationListWidget::NotificationListWidget(QWidget *parent) : QWidget(parent) {
	m_notificationListWidget.setHeaderLabels({"Date", "Title"});
	m_notificationListWidget.setRootIsDecorated(false);
	m_notificationListWidget.setSortingEnabled(true);
	m_notificationListWidget.sortItems(0, Qt::DescendingOrder);

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(&m_notificationListWidget);
}

void NotificationListWidget::update() {
	m_notificationListWidget.clear();

	auto &notificationList = IntraData::getInstance().notificationList();
	for (auto &it : notificationList) {
		auto *item = new QTreeWidgetItem(&m_notificationListWidget);
		item->setText(0, it.second.date().toString("yyyy/MM/dd HH:mm:ss"));
		item->setText(1, it.second.title());
	}
}


