/*
 * =====================================================================================
 *
 *       Filename:  ProjectInfoWidget.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:26:48
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QFormLayout>

#include "IntraData.hpp"
#include "ProjectInfoWidget.hpp"

ProjectInfoWidget::ProjectInfoWidget(QWidget *parent) : QGroupBox("Informations", parent) {
	hide();

	QFormLayout *layout = new QFormLayout(this);

	layout->addRow("Name:", &m_name);
	layout->addRow("Register date:", &m_registerDate);
	layout->addRow("Begin date:", &m_beginDate);
	layout->addRow("End date:", &m_endDate);
}

void ProjectInfoWidget::update(QTreeWidgetItem *item, unsigned int) {
	for (const IntraProject &project : IntraData::getInstance().projectList()) {
		if (item->text(0).toStdString() == project.name()) {
			m_name.setText(QString::fromStdString(project.name()));

			m_registerDate.setText(project.registerDate().toString(Qt::SystemLocaleShortDate));
			m_beginDate.setText(project.beginDate().toString(Qt::SystemLocaleShortDate));
			m_endDate.setText(project.endDate().toString(Qt::SystemLocaleShortDate));
		}
	}

	show();
}

