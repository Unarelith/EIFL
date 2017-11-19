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

#include "IntraDatabaseThread.hpp"
#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

IntraData::IntraData() {
	connect(&m_database.loader(), &IntraDatabaseLoader::updateFinished, this, &IntraData::update);
	connect(&m_database.loader(), &IntraDatabaseLoader::userUpdateFinished, this, &IntraData::updateUserList);
	connect(&m_database.loader(), &IntraDatabaseLoader::notificationUpdateFinished, this, &IntraData::updateNotificationList);
	connect(&m_database.loader(), &IntraDatabaseLoader::unitUpdateFinished, this, &IntraData::update);
}

void IntraData::openDatabase(const QString &path) {
	m_database.open(path);
}

void IntraData::updateDatabase() {
	IntraDatabaseThread *thread = new IntraDatabaseThread(&m_database);
	thread->start();
}

void IntraData::reloadDatabase() {
	m_database.clear();
	updateDatabase();
}

void IntraData::update() {
	updateUserList();
	updateNotificationList();
	updateModuleList();
	updateActivityList();
	updateEventList();
	updateProjectList();

	emit databaseUpdateFinished();
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
		auto it = m_moduleList.find(moduleId);
		if (it == m_moduleList.end()) {
			qWarning() << "Error: Unable to find module with id" << moduleId << "for activity with id" << query.value(0).toUInt();
			continue;
		}

		m_activityList.emplace(query.value(0).toUInt(), IntraActivity{it->second, query});
	}
}

void IntraData::updateEventList() {
	m_eventList.clear();

	QSqlQuery query("SELECT * FROM events");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		auto it = m_activityList.find(activityId);
		if (it == m_activityList.end()) {
			qWarning() << "Error: Unable to find activity with id" << activityId << "for event with id" << query.value(0).toUInt();
			continue;
		}

		m_eventList.emplace(query.value(0).toUInt(), IntraEvent{it->second, query});
	}
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QSqlQuery query("SELECT * FROM projects");
	while (query.next()) {
		unsigned int activityId = query.value(query.record().indexOf("activity_id")).toUInt();
		auto it = m_activityList.find(activityId);
		if (it == m_activityList.end()) {
			qWarning() << "Error: Unable to find activity with id" << activityId << "for event with id" << query.value(0).toUInt();
			continue;
		}

		m_projectList.emplace(query.value(0).toUInt(), IntraProject{it->second, query});
	}
}

void IntraData::updateUserList() {
	// FIXME: Doesn't currently handle multiple users
	QSqlQuery query("SELECT * FROM users");
	if (query.next()) {
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

