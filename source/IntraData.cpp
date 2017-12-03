/*
 * =====================================================================================
 *
 *       Filename:  IntraData.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:48:36
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QApplication>
#include <QDebug>
#include <QJsonArray>
#include <QProgressDialog>
#include <QSqlRecord>

#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

IntraData::IntraData() {
	connect(&m_database.loader(), &IntraDatabaseLoader::updateFinished, this, &IntraData::update);
	connect(&m_database.loader(), &IntraDatabaseLoader::userUpdateFinished, this, &IntraData::updateUserList);
	connect(&m_database.loader(), &IntraDatabaseLoader::notificationUpdateFinished, this, &IntraData::updateNotificationList);
	connect(&m_database.loader(), &IntraDatabaseLoader::overviewUpdateFinished, this, &IntraData::windowRefeshRequested);
	connect(&m_database.loader(), &IntraDatabaseLoader::unitUpdateFinished, this, &IntraData::windowRefeshRequested);
}

void IntraData::openDatabase(const QString &path) {
	m_database.open(path);
}

void IntraData::updateDatabase() {
	stopDatabaseUpdate();

	m_databaseThread = new IntraDatabaseThread(&m_database);
	m_databaseThread->start();
}

void IntraData::reloadDatabase() {
	stopDatabaseUpdate();
	m_database.clear();

	updateDatabase();
}

void IntraData::stopDatabaseUpdate() {
	if (m_databaseThread && m_databaseThread->isRunning()) {
		emit stateChanged("Stopping database update...");

		m_databaseThread->requestInterruption();
		m_databaseThread->wait();

		emit stateChanged("Database update stopped.");
	}
}

void IntraData::update() {
	updateUserList();
	updateNotificationList();
	updateModuleList();
	updateActivityList();
	updateEventList();
	updateProjectList();

	emit windowRefeshRequested();
}

void IntraData::updateModuleList() {
	m_moduleList.clear();

	QSqlQuery query("SELECT * FROM units");
	while (query.next()) {
		m_moduleList.emplace(query.value(0).toUInt(), query);
	}
}

void IntraData::updateActivityList() {
	m_activityList.clear();

	QSqlQuery query("SELECT * FROM activities");
	while (query.next()) {
		unsigned int moduleId = query.value(query.record().indexOf("module_id")).toUInt();
		m_activityList.emplace(query.value(0).toUInt(), IntraActivity{moduleId, query});
	}
}

void IntraData::updateEventList() {
	m_eventList.clear();

	QSqlQuery query("SELECT * FROM events");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		m_eventList.emplace(query.value(0).toUInt(), IntraEvent{activityId, query});
	}
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QSqlQuery query("SELECT * FROM projects");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		m_projectList.emplace(query.value(0).toUInt(), IntraProject{activityId, query});
	}
}

void IntraData::updateUserList() {
	// FIXME: Doesn't currently handle multiple users
	QSqlQuery query("SELECT * FROM users");
	while (query.next()) {
		if (query.value(0).toUInt())
			m_userInfo = IntraUser{query};
	}
}

void IntraData::updateNotificationList() {
	m_notificationList.clear();

	QSqlQuery query("SELECT * FROM notifications");
	while (query.next()) {
		IntraNotification notification{query};
		m_notificationList.emplace(notification.id(), std::move(notification));
	}
}

