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

ProjectListWidget::ProjectListWidget(QWidget *parent) : QDockWidget(tr("Projects"), parent) {
	m_projectListWidget.setHeaderLabels({"", tr("Name"), tr("ID")});
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
	for (auto &it : projectList) {
		const IntraActivity *activity = IntraData::getInstance().getActivity(it.second.activityId());
		const IntraModule *module = IntraData::getInstance().getModule(activity ? activity->moduleId() : 0);

		if (activity && (!module || module->isRegistered()) && activity->isCurrentlyActive()) {
			auto *item = new QTreeWidgetItem(&m_projectListWidget);
			item->setText(1, it.second.name());
			item->setText(2, QString::number(it.second.id()));

			if (it.second.registerState() == IntraProject::RegisterState::Locked) {
				item->setIcon(0, QIcon(":/locked.svg"));
				item->setText(0, " 2");
			}
			else if (it.second.registerState() == IntraProject::RegisterState::Registered) {
				item->setIcon(0, QIcon(":/registered.svg"));
				item->setText(0, " 1");
			}
			else if (it.second.registerState() == IntraProject::RegisterState::Registrable) {
				item->setIcon(0, QIcon(":/registrable.svg"));
				item->setText(0, " 3");
			}
			else if (it.second.registerState() == IntraProject::RegisterState::Unknown) {
				item->setIcon(0, QIcon(":/ask.svg"));
				item->setText(0, " 0");
			}
		}
	}

	setWindowTitle(tr("Projects") + " (" + QString::number(m_projectListWidget.topLevelItemCount()) + "/" + QString::number(projectList.size()) + ")");
}

