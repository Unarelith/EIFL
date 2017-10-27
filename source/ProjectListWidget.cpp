/*
 * =====================================================================================
 *
 *       Filename:  ProjectListWidget.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:33:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHBoxLayout>
#include <QHeaderView>

#include "IntraData.hpp"
#include "ProjectListWidget.hpp"

ProjectListWidget::ProjectListWidget(QWidget *parent) : QDockWidget("Projects", parent) {
	m_projectListWidget.setHeaderLabels({"", "Name", "ID"});
	m_projectListWidget.setRootIsDecorated(false);
	m_projectListWidget.setSortingEnabled(true);
	m_projectListWidget.header()->setSectionResizeMode(QHeaderView::Fixed);
	m_projectListWidget.setColumnWidth(0, 27);
	m_projectListWidget.sortItems(0, Qt::AscendingOrder);
	m_projectListWidget.hideColumn(2);

	setWidget(&m_projectListWidget);
}

void ProjectListWidget::update() {
	m_projectListWidget.clear();

	auto &projectList = IntraData::getInstance().projectList();
	for (auto &project : projectList) {
		auto *item = new QTreeWidgetItem(&m_projectListWidget);
		item->setText(1, project.name());
		item->setText(2, QString::number(project.id()));

		if (project.isRegistered()) {
			item->setIcon(0, QIcon(":/registered.svg"));
			item->setText(0, " 0");
		}
		else if (project.isRegistrable()) {
			item->setIcon(0, QIcon(":/registrable.svg"));
			item->setText(0, " 2");
		}
		else {
			item->setIcon(0, QIcon(":/locked.svg"));
			item->setText(0, " 1");
		}
	}
}

