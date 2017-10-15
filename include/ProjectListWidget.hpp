/*
 * =====================================================================================
 *
 *       Filename:  ProjectListWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:32:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PROJECTLISTWIDGET_HPP_
#define PROJECTLISTWIDGET_HPP_

#include <QDockWidget>
#include <QTreeWidget>

#include "ProjectInfoWidget.hpp"
#include "ProjectScheduleWidget.hpp"

class ProjectListWidget : public QDockWidget {
	public:
		ProjectListWidget(QWidget *parent = nullptr);

		void update();

	private:
		QTreeWidget m_projectListWidget;

		ProjectInfoWidget m_projectInfoWidget;
		ProjectScheduleWidget m_projectScheduleWidget;
};

#endif // PROJECTLISTWIDGET_HPP_
