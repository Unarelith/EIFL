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

	addDockWidget(Qt::TopDockWidgetArea, &m_projectListWidget, Qt::Horizontal);
	addDockWidget(Qt::TopDockWidgetArea, &m_scheduleWidget, Qt::Horizontal);

	tabifyDockWidget(&m_projectListWidget, &m_scheduleWidget);
	m_projectListWidget.raise();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape)
		close();
}

