/*
 * =====================================================================================
 *
 *       Filename:  ModuleListWidget.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 18:41:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MODULELISTWIDGET_HPP_
#define MODULELISTWIDGET_HPP_

#include <QDockWidget>
#include <QTreeWidget>

#include "ProjectInfoWidget.hpp"

class ModuleListWidget : public QDockWidget {
	public:
		ModuleListWidget(QWidget *parent = nullptr);

		void update();

		const QTreeWidget &moduleListWidget() const { return m_moduleListWidget; }

		void setSemesters(const std::vector<unsigned int> &semesters) { m_semesters = semesters; update(); }
		void setFilters(bool isCurrentSemesterEnabled, bool isRegisteredModulesEnabled);

	private:
		QTreeWidget m_moduleListWidget;

		std::vector<unsigned int> m_semesters;

		bool m_isCurrentSemesterEnabled;
		bool m_isRegisteredModulesEnabled;
};

#endif // MODULELISTWIDGET_HPP_
