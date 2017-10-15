/*
 * =====================================================================================
 *
 *       Filename:  ProjectInfoWidget.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 22:26:27
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef PROJECTINFOWIDGET_HPP_
#define PROJECTINFOWIDGET_HPP_

#include <QGroupBox>
#include <QLabel>
#include <QTreeWidgetItem>

class ProjectInfoWidget : public QGroupBox {
	public:
		ProjectInfoWidget(QWidget *parent = nullptr);

		void update(QTreeWidgetItem *item, unsigned int column);

	private:
		QLabel m_name;

		QLabel m_registerDate;
		QLabel m_beginDate;
		QLabel m_endDate;
};

#endif // PROJECTINFOWIDGET_HPP_
