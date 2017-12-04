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
#include <QHeaderView>

#include "HtmlDelegate.hpp"
#include "IntraData.hpp"
#include "NotificationListWidget.hpp"

#include <QLabel>

NotificationListWidget::NotificationListWidget(QWidget *parent) : QWidget(parent) {
	m_model.setHorizontalHeaderLabels({"Date", "Title"});

	m_view.setRootIsDecorated(false);
	m_view.setSortingEnabled(true);
	m_view.sortByColumn(0, Qt::DescendingOrder);
	m_view.setModel(&m_model);
	m_view.setItemDelegate(new HtmlDelegate());
	m_view.setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(&m_view);
}

void NotificationListWidget::update() {
	m_model.clear();
	m_model.setHorizontalHeaderLabels({"Date", "Title"});

	QModelIndex parentItem;
	auto &notificationList = IntraData::getInstance().notificationList();
	for (auto &it : notificationList) {
		QList<QStandardItem *> items = {
			new QStandardItem(it.second.date().toString("yyyy/MM/dd HH:mm:ss")),
			new QStandardItem(it.second.title())
		};

		m_model.appendRow(items);
	}

	m_view.update();
	m_view.header()->resizeSection(0, 160);
	// m_view.header()->setStretchLastSection(false);
	// m_view.header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

