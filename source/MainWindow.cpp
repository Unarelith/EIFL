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
	IntraSession::setInstance(m_intraSession);

	m_intraData.update();
	m_projectListWidget.update();
	m_eventlistWidget.setDate(QDate::currentDate());
	m_eventInfoWidget.setDate(QDate::currentDate());

	addDockWidget(Qt::LeftDockWidgetArea, &m_projectListWidget, Qt::Vertical);
	addDockWidget(Qt::LeftDockWidgetArea, &m_projectInfoWidget, Qt::Vertical);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventlistWidget, Qt::Horizontal);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventInfoWidget, Qt::Horizontal);

	setCentralWidget(&m_calendarWidget);

	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::itemClicked, &m_projectInfoWidget, &ProjectInfoWidget::update);
	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::itemClicked, &m_calendarWidget, &CalendarWidget::displayProjectDates);
	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventlistWidget, &EventListWidget::setDate);
	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventInfoWidget, &EventInfoWidget::setDate);
	connect(&m_eventlistWidget.eventListWidget(), &QTreeWidget::itemClicked, &m_eventInfoWidget, &EventInfoWidget::update);

	// tabifyDockWidget(&m_projectListWidget, &m_eventlistWidget);
	// m_projectListWidget.raise();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape)
		close();
}

