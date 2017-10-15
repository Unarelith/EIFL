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

ProjectListWidget::ProjectListWidget(QWidget *parent) : QDockWidget("ProjectList", parent) {
	QWidget *layoutWidget = new QWidget;
	QHBoxLayout *layout = new QHBoxLayout(layoutWidget);

	m_projectListWidget.setColumnCount(1);
	m_projectListWidget.setHeaderLabel("Name");

	layout->addWidget(&m_projectListWidget);
	layout->addWidget(&m_projectInfoWidget);
	setWidget(layoutWidget);

	connect(&m_projectListWidget, &QTreeWidget::itemClicked, &m_projectInfoWidget, &ProjectInfoWidget::update);
}

void ProjectListWidget::update() {
	m_projectListWidget.clear();

	auto &projectList = IntraData::getInstance().projectList();
	for (auto &project : projectList) {
		m_projectListWidget.addTopLevelItem(new QTreeWidgetItem(QStringList(QString::fromStdString(project.name()))));
	}
}

