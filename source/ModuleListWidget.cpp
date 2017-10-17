/*
 * =====================================================================================
 *
 *       Filename:  ModuleListWidget.cpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 18:42:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHBoxLayout>
#include <QHeaderView>

#include "IntraData.hpp"
#include "ModuleListWidget.hpp"

ModuleListWidget::ModuleListWidget(QWidget *parent) : QDockWidget("Modules", parent) {
	m_moduleListWidget.setColumnCount(2);
	m_moduleListWidget.setHeaderLabels({"", "Name"});
	m_moduleListWidget.setRootIsDecorated(false);
	m_moduleListWidget.setSortingEnabled(true);
	m_moduleListWidget.header()->setSectionResizeMode(QHeaderView::Fixed);
	m_moduleListWidget.setColumnWidth(0, 27);
	m_moduleListWidget.sortItems(0, Qt::DescendingOrder);

	setWidget(&m_moduleListWidget);
}

void ModuleListWidget::update() {
	m_moduleListWidget.clear();

	auto &moduleList = IntraData::getInstance().moduleList();
	for (auto &module : moduleList) {
		if ((!m_isCurrentSemesterEnabled || (module.semester() == IntraData::getInstance().getUserInfo("").currentSemester() || module.semester() == 0))
		 && (!m_isRegisteredModulesEnabled || module.isRegistered())
		 && std::find(m_semesters.begin(), m_semesters.end(), module.semester()) != m_semesters.end()) {
			auto *item = new QTreeWidgetItem(&m_moduleListWidget);
			item->setText(1, module.name());

			if (module.isRegistered()) {
				item->setIcon(0, QIcon(":/registered.svg"));
				item->setText(0, " 0");
			}
			else if (module.isRegistrable()) {
				item->setIcon(0, QIcon(":/registrable.svg"));
				item->setText(0, " 2");
			}
			else {
				item->setIcon(0, QIcon(":/locked.svg"));
				item->setText(0, " 1");
			}
		}
	}
}

void ModuleListWidget::setFilters(bool isCurrentSemesterEnabled, bool isRegisteredModulesEnabled) {
	m_isCurrentSemesterEnabled = isCurrentSemesterEnabled;
	m_isRegisteredModulesEnabled = isRegisteredModulesEnabled;

	update();
}

