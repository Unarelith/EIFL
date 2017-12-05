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
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QKeyEvent>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QStandardPaths>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <QTimer>

#include "LoginWindow.hpp"
#include "MainWindow.hpp"

const MainWindow *MainWindow::s_instance = nullptr;

MainWindow::MainWindow() : QMainWindow(nullptr, Qt::Dialog) {
	setWindowTitle("Epitech Intra");
	setFocusPolicy(Qt::ClickFocus);
	resize(width, height);

	MainWindow::setInstance(*this);
	IntraData::setInstance(m_intraData);
	IntraSession::setInstance(m_intraSession);

	setupWidgets();
	setupDocks();
	setupTabs();
	setupMenuBar();
	setupStatusBar();
	setupTrayIcon();

	connectObjects();

	connect(&m_intraSession, &IntraSession::userLoginRequired, this, &MainWindow::login);
	if (m_keyring.has("eifl_login") && m_keyring.has("eifl_password") && m_intraSession.login(m_keyring) == 200) {
		QTimer::singleShot(0, [this] { init(true); });
	}
	else {
		QTimer::singleShot(0, this, &MainWindow::login);
	}
}

void MainWindow::login() {
	m_intraSession.logout();
	m_intraData.stopDatabaseUpdate();

	auto *loginWindow = new LoginWindow(m_keyring);
	connect(loginWindow, &LoginWindow::quitButtonPressed, this, &MainWindow::close);
	connect(loginWindow, &QDialog::finished, this, &MainWindow::init);
	connect(loginWindow, &LoginWindow::databaseReloadRequested, &m_intraData, &IntraData::reloadDatabase);
	loginWindow->exec();
}

void MainWindow::init(bool updateDatabase) {
	QString dirPath = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
	QString path = dirPath + "/intra.sqlite";
	QFileInfo databaseInfo(path);
	if (databaseInfo.exists() && databaseInfo.isFile()) {
		m_intraData.openDatabase(path);
		m_intraData.update();
	}
	else {
		QDir dir(dirPath);
		if (!dir.mkpath(dirPath))
			qWarning() << "Error: Failed to create directory: " + dirPath;

		m_intraData.openDatabase(path);
	}

	show();
	updateWidgets();

	m_userInfoWidget.update();
	m_notificationListWidget.update();

	if (updateDatabase)
		m_intraData.updateDatabase();
}

void MainWindow::setupWidgets() {
	m_eventInfoWidget.setDate(QDate::currentDate());
	m_eventListWidget.setDate(QDate::currentDate());
}

void MainWindow::setupDocks() {
	addDockWidget(Qt::RightDockWidgetArea, &m_projectInfoWidget, Qt::Vertical);
	addDockWidget(Qt::RightDockWidgetArea, &m_projectListWidget, Qt::Vertical);
	addDockWidget(Qt::RightDockWidgetArea, &m_moduleListWidget, Qt::Vertical);

	addDockWidget(Qt::BottomDockWidgetArea, &m_eventListWidget, Qt::Horizontal);
	addDockWidget(Qt::BottomDockWidgetArea, &m_eventInfoWidget, Qt::Horizontal);

	addDockWidget(Qt::LeftDockWidgetArea, &m_calendarSettingsWidget, Qt::Vertical);
	// addDockWidget(Qt::LeftDockWidgetArea, &m_sideBar, Qt::Vertical);

	// tabifyDockWidget(&m_calendarSettingsWidget, &m_sideBar);
	tabifyDockWidget(&m_projectListWidget, &m_moduleListWidget);

	m_projectListWidget.raise();
	// m_sideBar.raise();
}

void MainWindow::setupTabs() {
	QTabWidget *tabWidget = new QTabWidget;
	tabWidget->addTab(&m_calendarWidget, tr("Calendar"));
	tabWidget->addTab(&m_userInfoWidget, tr("User"));
	tabWidget->addTab(&m_moduleInfoWidget, tr("Module"));
	tabWidget->addTab(&m_notificationListWidget, tr("Notifications"));

	setCentralWidget(tabWidget);
}

void MainWindow::setupMenuBar() {
	QAction *loginAction = new QAction(tr("&Login..."), this);
	loginAction->setStatusTip(tr("Login to Epitech Intranet"));
	connect(loginAction, &QAction::triggered, this, &MainWindow::login);
	connect(&m_intraSession, &IntraSession::userLoggedIn, [loginAction] {
		loginAction->setText(tr("&Disconnect..."));
		loginAction->setStatusTip(tr("Disconnect from Epitech Intranet"));
	});
	connect(&m_intraSession, &IntraSession::userLoggedOut, [loginAction] {
		loginAction->setText(tr("&Login..."));
		loginAction->setStatusTip(tr("Login to Epitech Intranet"));
	});

	QAction *exitAction = new QAction(tr("&Exit"), this);
	exitAction->setShortcut(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Exit the program"));
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(loginAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	QAction *updateAction = new QAction(tr("&Update"), this);
	updateAction->setShortcut(QKeySequence::Refresh);
	updateAction->setStatusTip("Update local database with online data");
	connect(updateAction, &QAction::triggered, &m_intraData, &IntraData::updateDatabase);

	QAction *reloadAction = new QAction(tr("&Reload"), this);
	reloadAction->setShortcut(QKeySequence::fromString("Shift+F5"));
	reloadAction->setStatusTip("Performs a full reload of the database");
	connect(reloadAction, &QAction::triggered, &m_intraData, &IntraData::reloadDatabase);

	QAction *stopAction = new QAction(tr("&Stop"), this);
	stopAction->setShortcut(QKeySequence::fromString("Ctrl+C"));
	stopAction->setStatusTip("Stop database update");
	connect(stopAction, &QAction::triggered, &m_intraData, &IntraData::stopDatabaseUpdate);

	QMenu *databaseMenu = menuBar()->addMenu(tr("&Database"));
	databaseMenu->addAction(updateAction);
	databaseMenu->addAction(reloadAction);
	databaseMenu->addAction(stopAction);

	QAction *aboutAction = new QAction(tr("&About"), this);
	aboutAction->setShortcut(QKeySequence::HelpContents);
	aboutAction->setStatusTip("About this program");
	connect(aboutAction, &QAction::triggered, this, &MainWindow::openAboutWindow);

	QAction *aboutQtAction = new QAction(tr("&About Qt"), this);
	aboutQtAction->setStatusTip("About Qt");
	connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);

	QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::setupStatusBar() {
	QProgressBar *dbUpdateBar = new QProgressBar;
	dbUpdateBar->hide();
	dbUpdateBar->setRange(0, 100);
	connect(&m_intraData, &IntraData::databaseUpdateStarted, dbUpdateBar, &QWidget::show);
	connect(&m_intraData, &IntraData::databaseUpdateStopped, dbUpdateBar, &QWidget::hide);

	QProgressBar *unitUpdateBar = new QProgressBar;
	unitUpdateBar->hide();
	unitUpdateBar->setRange(0, 100);
	connect(&m_intraData, &IntraData::databaseUpdateStarted, unitUpdateBar, &QWidget::show);
	connect(&m_intraData, &IntraData::databaseUpdateStopped, unitUpdateBar, &QWidget::hide);

	QLabel *onlineStatusWidget = new QLabel;
	onlineStatusWidget->setPixmap({":/network-offline"});

	connect(&m_intraSession, &IntraSession::userLoggedOut, [onlineStatusWidget] { onlineStatusWidget->setPixmap({":/network-offline"}); });
	connect(&m_intraSession, &IntraSession::userLoggedIn, [onlineStatusWidget] { onlineStatusWidget->setPixmap({":/network-online"}); });
	connect(&m_intraSession, &IntraSession::httpError, [onlineStatusWidget] { onlineStatusWidget->setPixmap({":/network-error"}); });

	QStatusBar *statusBar = QMainWindow::statusBar();
	statusBar->addPermanentWidget(dbUpdateBar);
	statusBar->addPermanentWidget(unitUpdateBar);
	statusBar->addPermanentWidget(onlineStatusWidget);

	connect(&m_intraSession, &IntraSession::stateChanged, statusBar, &QStatusBar::showMessage);
	connect(&m_intraData, &IntraData::stateChanged, statusBar, &QStatusBar::showMessage);
	connect(&m_intraData.database().loader(), &IntraDatabaseLoader::updateProgressed, dbUpdateBar, &QProgressBar::setValue);
	connect(&m_intraData.database().loader(), &IntraDatabaseLoader::unitUpdateProgressed, unitUpdateBar, &QProgressBar::setValue);
}

void MainWindow::setupTrayIcon() {
	auto *trayIconMenu = new QMenu(this);
	QAction *exitAction = trayIconMenu->addAction("Exit");
	connect(exitAction, &QAction::triggered, this, &MainWindow::close);

	auto *trayIcon = new QSystemTrayIcon(QIcon(":/epitech.png"), this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->show();

	connect(trayIcon, &QSystemTrayIcon::activated, [this] (QSystemTrayIcon::ActivationReason reason) {
		if (reason == QSystemTrayIcon::ActivationReason::Trigger) {
			setVisible(!isVisible());
			if (isVisible())
				updateWidgets();
		}
	});
}

void MainWindow::showStatusTip(const QString &statusString) {
	statusBar()->clearMessage();
	statusBar()->showMessage(statusString, 5000);
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

	connect(&m_intraData, &IntraData::windowRefeshRequested, this, &MainWindow::updateWidgets);

	connect(&m_intraData.database().loader(), &IntraDatabaseLoader::userUpdateFinished, &m_userInfoWidget, &UserInfoWidget::update);
	connect(&m_intraData.database().loader(), &IntraDatabaseLoader::notificationUpdateFinished, &m_notificationListWidget, &NotificationListWidget::update);
}

void MainWindow::updateWidgets() {
	if (isVisible()) {
		m_projectListWidget.update();

		const IntraUser &userInfo = IntraData::getInstance().userInfo();
		m_sideBar.update(userInfo);

		unsigned int currentSemester = userInfo.currentSemester();
		if (currentSemester == 0)
			qDebug() << "Failed to get current semester!";

		m_eventListWidget.setSemesters({0, currentSemester});
		m_moduleListWidget.setSemesters({0, currentSemester});
		m_calendarSettingsWidget.setSemesters({0, currentSemester});
	}
}

void MainWindow::closeEvent(QCloseEvent *event) {
	m_intraData.stopDatabaseUpdate();

	QMainWindow::closeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	QMainWindow::keyPressEvent(event);

	if (event->key() == Qt::Key_Escape)
		close();
}

void MainWindow::openAboutWindow() {
	QMessageBox aboutBox(this);
	aboutBox.setWindowTitle("About EIFL");
	aboutBox.setTextFormat(Qt::RichText);
	aboutBox.setText("<h3>Epitech Intra For Linux (EIFL)</h3>"
	                 "Made by Quentin Bazin<br/><br/>"
	                 "Thanks for using this project!<br/><br/>"
	                 "Feel free to create a ticket <a href='https://github.com/Quent42340/EIFL/issues'>here</a> if you find some bugs.");
	aboutBox.setStandardButtons(QMessageBox::Ok);
	aboutBox.exec();
}

