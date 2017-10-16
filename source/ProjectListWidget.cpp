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

#include "IntraData.hpp"
#include "ProjectListWidget.hpp"

ProjectListWidget::ProjectListWidget(QWidget *parent) : QDockWidget("Project list", parent) {
	m_projectListWidget.setColumnCount(1);
	m_projectListWidget.setHeaderLabel("Name");

	setWidget(&m_projectListWidget);
}

void ProjectListWidget::update() {
	m_projectListWidget.clear();

	auto &projectList = IntraData::getInstance().projectList();
	for (auto &project : projectList) {
		auto *item = new QTreeWidgetItem(&m_projectListWidget);
		item->setText(0, QString::fromStdString(project.name()));

		if (project.isRegistered()) {
			item->setIcon(0, QIcon("res/icons/registered.svg"));
		}
		else if (project.isRegistrable()) {
			item->setIcon(0, QIcon("res/icons/registrable.svg"));
		}
		else {
			item->setIcon(0, QIcon("res/icons/locked.svg"));
		}
	}
}

