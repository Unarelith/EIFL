#!/usr/bin/env python3

# requires:
# - python-keyring
# - python-requests

from datetime import date, datetime, timedelta
from PyQt5.Qt import *
import getpass
import json
import keyring
import requests
import signal
import sys

def daterange(start_date, end_date):
    for n in range(int ((end_date - start_date).days)):
        yield start_date + timedelta(n)

class Project:
    def __init__(self, data):
        self.title = data["title"]
        self.titleLink = data["title_link"]

        self.timelineStart = datetime.strptime(data["timeline_start"], "%d/%m/%Y, %H:%M")
        self.timelineEnd = datetime.strptime(data["timeline_end"], "%d/%m/%Y, %H:%M")

        self.registerDate = datetime.strptime(data["date_inscription"], "%d/%m/%Y, %H:%M") if data["date_inscription"] else False

        self.activityId = data["id_activite"]

    def __repr__(self):
        return ' '.join((self.title, str(self.timelineStart), str(self.timelineEnd), str(self.registerDate)))

class IntraSession:
    def __init__(self):
        password = keyring.get_password("login", "EpitechIntra");
        if not password:
            keyring.set_password("login", "EpitechIntra", getpass.getpass())
            password = keyring.get_password("login", "EpitechIntra");

        self.session = requests.Session()

        self.url = 'https://intra.epitech.eu/'
        values = {'login'    : "quentin.bazin@epitech.eu",
                  'password' : password,
                  'remind'   : 'on'}

        r = self.session.post(self.url, data=values)
        if r.status_code != 200:
            print("Error: Bad username or password")
            exit(1)

    def getProjects(self):
        r = self.session.get("https://intra.epitech.eu/?format=json")

        projects = []
        projects_data = json.loads(r.content)["board"]["projets"]
        for data in projects_data:
            projects.append(Project(data))

        return projects

class ProjectInfoWidget(QGroupBox):
    def __init__(self, projectList, parent=None):
        QGroupBox.__init__(self, "Informations", parent)
        self.projectList = projectList

        self.name = QLabel("name")
        self.timelineEnd = QLabel("timeline_end")
        self.registerState = QLabel("register_state")

        self.layout = QFormLayout(self)
        self.layout.addRow("Name:", self.name)
        self.layout.addRow("Deadline:", self.timelineEnd)
        self.layout.addRow("Register state: ", self.registerState)

        self.hide()

    def update(self, treeWidgetItem, column):
        project = [p for p in self.projectList if p.title == treeWidgetItem.text(0)][0]

        self.name.setText(project.title)
        self.timelineEnd.setText(str(project.timelineEnd))
        self.registerState.setText(str(project.registerDate))
        self.show()

class ProjectWidget(QDockWidget):
    def __init__(self, session, parent=None):
        QDockWidget.__init__(self, "Projects", parent)

        self.layoutWidget = QWidget()
        self.layout = QHBoxLayout(self.layoutWidget)

        self.projectListWidget = QTreeWidget()
        self.projectListWidget.setColumnCount(1)
        self.projectListWidget.setHeaderLabels(["Name"])

        projectList = session.getProjects()
        for project in projectList:
            self.projectListWidget.addTopLevelItem(QTreeWidgetItem(None, [project.title]))

        self.projectInfoWidget = ProjectInfoWidget(projectList)
        self.projectListWidget.itemClicked.connect(self.projectInfoWidget.update)

        self.layout.addWidget(self.projectListWidget)
        self.layout.addWidget(self.projectInfoWidget)
        self.setWidget(self.layoutWidget)

class CalendarWidget(QDockWidget):
    def __init__(self, session, parent=None):
        QDockWidget.__init__(self, "Planning", parent)
        self.projectList = session.getProjects()

        self.calendarWidget = QCalendarWidget()

        self.currentProjectFormat = QTextCharFormat()
        self.currentProjectFormat.setBackground(QBrush(QColor(0, 64, 128)))

        self.registerDateFormat = QTextCharFormat()
        self.registerDateFormat.setBackground(QBrush(QColor(128, 0, 0)))
        self.registerDateFormat.setFontUnderline(QTextCharFormat.SingleUnderline)

        self.timelineStartFormat = QTextCharFormat()
        self.timelineStartFormat.setBackground(QBrush(QColor(0, 0, 128)))
        self.timelineStartFormat.setFontUnderline(QTextCharFormat.SingleUnderline)

        self.timelineEndFormat = QTextCharFormat()
        self.timelineEndFormat.setBackground(QBrush(QColor(0, 0, 128)))
        self.timelineEndFormat.setFontUnderline(QTextCharFormat.SingleUnderline)

        self.setWidget(self.calendarWidget)

    def displayProjectDates(self, treeWidgetItem, column):
        project = [p for p in self.projectList if p.title == treeWidgetItem.text(0)][0]

        self.calendarWidget.setDateTextFormat(QDate(), QTextCharFormat())

        for date in daterange(project.timelineStart, project.timelineEnd):
            self.calendarWidget.setDateTextFormat(date, self.currentProjectFormat)

        self.calendarWidget.setDateTextFormat(project.timelineStart, self.timelineStartFormat)
        self.calendarWidget.setDateTextFormat(project.timelineEnd, self.timelineEndFormat)

        if project.registerDate:
            self.calendarWidget.setDateTextFormat(project.registerDate, self.registerDateFormat)

class NotificationWidget(QDockWidget):
    def __init__(self, session, parent=None):
        QDockWidget.__init__(self, "Notifications", parent)

class SystemTrayIcon(QSystemTrayIcon):
    def __init__(self, icon, parent=None):
        QSystemTrayIcon.__init__(self, icon, parent)

        self.menu = QMenu(parent)
        self.menu.addAction("Exit")

        self.setContextMenu(self.menu)

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self, None, Qt.Dialog)
        self.setWindowTitle("Epitech Intra")
        self.resize(640, 480)

        icon = QIcon('epitech_logo.png')
        trayIcon = SystemTrayIcon(icon, self)
        trayIcon.show()
        trayIcon.activated.connect(self.trayIconActivated)

        self.session = IntraSession()

        calendarWidget = CalendarWidget(self.session)
        notificationWidget = NotificationWidget(self.session)
        projectWidget = ProjectWidget(self.session)
        projectWidget.projectListWidget.itemClicked.connect(calendarWidget.displayProjectDates)

        self.addDockWidget(Qt.TopDockWidgetArea, calendarWidget, Qt.Horizontal)
        self.addDockWidget(Qt.TopDockWidgetArea, notificationWidget, Qt.Horizontal)
        self.addDockWidget(Qt.BottomDockWidgetArea, projectWidget, Qt.Horizontal)

    def trayIconActivated(self, reason):
        self.setVisible(not self.isVisible())

def main():
    signal.signal(signal.SIGINT, signal.SIG_DFL)

    app = QApplication(sys.argv)
    win = MainWindow()
    win.show()

    sys.exit(app.exec_())

if __name__ == '__main__':
    main()

