/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 18:20:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QKeyEvent>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow(nullptr, Qt::Dialog) {
	setWindowTitle("Epitech Intra");
	setFocusPolicy(Qt::ClickFocus);
	resize(width, height);

	IntraData::setInstance(m_intraData);
	m_intraData.update();
	m_projectListWidget.update();

	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::itemClicked, &m_scheduleWidget, &ScheduleWidget::displayProjectDates);

	addDockWidget(Qt::BottomDockWidgetArea, &m_projectListWidget, Qt::Horizontal);
	addDockWidget(Qt::TopDockWidgetArea, &m_scheduleWidget, Qt::Horizontal);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape)
		close();
}

