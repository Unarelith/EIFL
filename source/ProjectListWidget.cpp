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

ProjectListWidget::ProjectListWidget(QWidget *parent) : QDockWidget("Projects", parent) {
	m_projectListWidget.setColumnCount(2);
	m_projectListWidget.setHeaderLabels({"Name", "Registered"});
	m_projectListWidget.setColumnWidth(0, 300);

	QWidget *subLayoutWidget = new QWidget;
	subLayoutWidget->setMinimumWidth(m_projectScheduleWidget.calendarWidget().width() / 2);

	QVBoxLayout *subLayout = new QVBoxLayout(subLayoutWidget);
	subLayout->addWidget(&m_projectScheduleWidget);
	subLayout->addWidget(&m_projectInfoWidget);

	QWidget *layoutWidget = new QWidget;
	QHBoxLayout *layout = new QHBoxLayout(layoutWidget);
	layout->addWidget(&m_projectListWidget);
	layout->addWidget(subLayoutWidget);

	setWidget(layoutWidget);

	connect(&m_projectListWidget, &QTreeWidget::itemClicked, &m_projectScheduleWidget, &ProjectScheduleWidget::displayProjectDates);
	connect(&m_projectListWidget, &QTreeWidget::itemClicked, &m_projectInfoWidget, &ProjectInfoWidget::update);
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

