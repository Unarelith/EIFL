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
	m_projectListWidget.setColumnCount(2);
	m_projectListWidget.setHeaderLabels({"Name", "Registered"});
	m_projectListWidget.setColumnWidth(0, 300);

	setWidget(&m_projectListWidget);
}

void ProjectListWidget::update() {
	m_projectListWidget.clear();

	auto &projectList = IntraData::getInstance().projectList();
	for (auto &project : projectList) {
		m_projectListWidget.addTopLevelItem(new QTreeWidgetItem({
			QString::fromStdString(project.name()),
			(project.isRegistered() ? "Yes" : "No")
		}));
	}
}

