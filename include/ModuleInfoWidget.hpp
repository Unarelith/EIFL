/*
 * =====================================================================================
 *
 *       Filename:  ModuleInfoWidget.hpp
 *
 *    Description:
 *
 *        Created:  17/10/2017 20:16:52
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MODULEINFOWIDGET_HPP_
#define MODULEINFOWIDGET_HPP_

#include <QDockWidget>
#include <QLabel>
#include <QTreeWidgetItem>

class ModuleInfoWidget : public QDockWidget {
	public:
		ModuleInfoWidget(QWidget *parent = nullptr);

		void update(QTreeWidgetItem *item);

	private:
		QLabel m_name;

		QLabel m_creditCount;
};

#endif // MODULEINFOWIDGET_HPP_
