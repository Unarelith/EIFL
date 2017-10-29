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
	setupTabs();
	setupMenus();
	connectObjects();
}

void MainWindow::setupWidgets() {
	m_intraData.update();
	m_projectListWidget.update();
	m_userInfoWidget.update();
	m_moduleListWidget.update();
	m_notificationListWidget.update();

	m_eventInfoWidget.setDate(QDate::currentDate());
	m_eventListWidget.setDate(QDate::currentDate());

	unsigned int currentSemester = m_intraData.getUserInfo("").currentSemester();
	m_eventListWidget.setSemesters({0, currentSemester});
	m_eventListWidget.setFilters(true, true, false);

	m_moduleListWidget.setSemesters({0, currentSemester});
	m_moduleListWidget.setFilters(true, true);

	m_calendarSettingsWidget.setSemesters({0, currentSemester});
}

void MainWindow::setupDocks() {
	addDockWidget(Qt::RightDockWidgetArea, &m_projectInfoWidget, Qt::Vertical);
	addDockWidget(Qt::RightDockWidgetArea, &m_projectListWidget, Qt::Vertical);
	addDockWidget(Qt::RightDockWidgetArea, &m_moduleListWidget, Qt::Vertical);

	addDockWidget(Qt::BottomDockWidgetArea, &m_eventListWidget, Qt::Horizontal);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventInfoWidget, Qt::Horizontal);

	addDockWidget(Qt::LeftDockWidgetArea, &m_calendarSettingsWidget, Qt::Vertical);

	tabifyDockWidget(&m_projectListWidget, &m_moduleListWidget);

	m_projectListWidget.raise();
	m_projectInfoWidget.raise();
}

void MainWindow::setupTabs() {
	QTabWidget *tabWidget = new QTabWidget;
	tabWidget->addTab(&m_calendarWidget, "Calendar");
	tabWidget->addTab(&m_userInfoWidget, "User");
	tabWidget->addTab(&m_moduleInfoWidget, "Module");
	tabWidget->addTab(&m_notificationListWidget, "Notifications");

	setCentralWidget(tabWidget);
}

void MainWindow::setupMenus() {
	QAction *exitAction = new QAction(tr("&Exit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(exitAction);
}

void MainWindow::connectObjects() {
	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::currentItemChanged, &m_projectInfoWidget, &ProjectInfoWidget::update);
	connect(&m_projectListWidget.projectListWidget(), &QTreeWidget::currentItemChanged, &m_calendarWidget, &CalendarWidget::displayProjectDates);

	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventListWidget, &EventListWidget::setDate);
	connect(&m_calendarWidget, &CalendarWidget::dateHasChanged, &m_eventInfoWidget, &EventInfoWidget::setDate);

	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::filterStateHasChanged, &m_eventListWidget, &EventListWidget::setFilters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::filterStateHasChanged, &m_moduleListWidget, &ModuleListWidget::setFilters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::semesterStateHasChanged, &m_eventListWidget, &EventListWidget::setSemesters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::semesterStateHasChanged, &m_eventInfoWidget, &EventInfoWidget::setSemesters);
	connect(&m_calendarSettingsWidget, &CalendarSettingsWidget::semesterStateHasChanged, &m_moduleListWidget, &ModuleListWidget::setSemesters);

	connect(&m_calendarSettingsWidget.clearHightlight(), &QPushButton::clicked, &m_calendarWidget, &CalendarWidget::clearAction);
	connect(&m_calendarSettingsWidget.selectToday(), &QPushButton::clicked, &m_calendarWidget, &CalendarWidget::todayAction);

	connect(&m_moduleListWidget.moduleListWidget(), &QTreeWidget::currentItemChanged, &m_moduleInfoWidget, &ModuleInfoWidget::update);
	connect(&m_eventListWidget.eventListWidget(), &QTreeWidget::currentItemChanged, &m_eventInfoWidget, &EventInfoWidget::update);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Escape)
		close();
}

