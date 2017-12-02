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
#include "IntraSession.hpp"
#include "ProjectInfoWidget.hpp"

ProjectInfoWidget::ProjectInfoWidget(QWidget *parent) : QDockWidget("Project details", parent) {
	QWidget *layoutWidget = new QWidget;
	QFormLayout *layout = new QFormLayout(layoutWidget);

	m_link.setTextInteractionFlags(Qt::TextBrowserInteraction);
	m_link.setOpenExternalLinks(true);

	layout->addRow("Name:", &m_name);
	layout->addRow("Link:", &m_link);
	layout->addRow("Register date:", &m_registerDate);
	layout->addRow("Begin date:", &m_beginDate);
	layout->addRow("End date:", &m_endDate);

	setWidget(layoutWidget);
}

void ProjectInfoWidget::update(QTreeWidgetItem *item) {
	if (item) {
		for (auto &it : IntraData::getInstance().projectList()) {
			const IntraActivity *activity = IntraData::getInstance().getActivity(it.second.activityId());

			if (activity && item->text(item->columnCount() - 1).toUInt() == it.second.id()) {
				m_name.setText(it.second.name());
				m_link.setText("<a href=\"" + QString(IntraSession::baseUrl) + activity->link() + "/project\">" + "Go to project" + "</a>");

				m_registerDate.setText(activity->registerDate().toString(Qt::SystemLocaleShortDate));
				m_beginDate.setText(activity->beginDate().toString(Qt::SystemLocaleShortDate));
				m_endDate.setText(activity->endDate().toString(Qt::SystemLocaleShortDate));
			}
		}
	}
}

