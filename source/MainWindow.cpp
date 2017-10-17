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
#include <QMenuBar>

#include "MainWindow.hpp"

MainWindow::MainWindow() : QMainWindow(nullptr, Qt::Dialog) {
	setWindowTitle("Epitech Intra");
	setFocusPolicy(Qt::ClickFocus);
	resize(width, height);

	IntraData::setInstance(m_intraData);
	IntraSession::setInstance(m_intraSession);

	setupWidgets();
	setupDocks();
	setupMenus();
	connectObjects();
}

void MainWindow::setupWidgets() {
	m_intraData.update();
	m_projectListWidget.update();
	m_userInfoWidget.update();

	m_eventInfoWidget.setDate(QDate::currentDate());
	m_eventListWidget.setDate(QDate::currentDate());

	// FIXME: Find a way to get current semester
	m_eventListWidget.setSemesters({0,5});
	m_eventListWidget.setFilters(true, true, false);
}

void MainWindow::setupDocks() {
	addDockWidget(Qt::RightDockWidgetArea, &m_projectInfoWidget, Qt::Vertical);
	addDockWidget(Qt::RightDockWidgetArea, &m_projectListWidget, Qt::Vertical);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventListWidget, Qt::Horizontal);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventInfoWidget, Qt::Horizontal);
	addDockWidget(Qt::LeftDockWidgetArea, &m_calendarSettingsWidget, Qt::Vertical);

	QTabWidget *tabWidget = new QTabWidget;
	tabWidget->addTab(&m_calendarWidget, "Calendar");
	tabWidget->addTab(&m_userInfoWidget, "User");

	setCentralWidget(tabWidget);

	// tabifyDockWidget(&m_projectListWidget, &m_eventlistWidget);
	// m_projectListWidget.raise();
}

void MainWindow::setupMenus() {
	QAction *exitAction = new QAction(tr("&Exit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);
}

void MainWindow::connectObjects() {
	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::itemClicked, &m_projectInfoWidget, &ProjectInfoWidget::update);
	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::itemClicked, &m_calendarWidget, &CalendarWidget::displayProjectDates);

	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventListWidget, &EventListWidget::setDate);
	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventInfoWidget, &EventInfoWidget::setDate);

	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::filterStateHasChanged, &m_eventListWidget, &EventListWidget::setFilters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::semesterStateHasChanged, &m_eventListWidget, &EventListWidget::setSemesters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::semesterStateHasChanged, &m_eventInfoWidget, &EventInfoWidget::setSemesters);

	connect(&m_calendarSettingsWidget.clearHightlight(), &QPushButton::clicked, &m_calendarWidget, &CalendarWidget::clearAction);
	connect(&m_calendarSettingsWidget.selectToday(), &QPushButton::clicked, &m_calendarWidget, &CalendarWidget::todayAction);

	connect(&m_eventListWidget.eventListWidget(), &QTreeWidget::itemClicked, &m_eventInfoWidget, &EventInfoWidget::update);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape)
		close();
}

