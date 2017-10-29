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
#include <QDebug>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "IntraData.hpp"
#include "IntraSession.hpp"

IntraData *IntraData::s_instance = nullptr;

void IntraData::update() {
	m_overviewJson = IntraSession::getInstance().get("/");

	updateModuleList();
	updateNotificationList();
	updateProjectList();
}

void IntraData::updateModuleList() {
	m_moduleList.clear();

	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray projectArray = json.array();
	for (QJsonValue value : projectArray) {
		m_moduleList.emplace_back(value.toObject());
	}

	if (QSqlDatabase::isDriverAvailable("QSQLITE")) {
		QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
		db.setDatabaseName("test_units.sqlite");
		if (!db.open())
			qWarning() << "Error: " << db.lastError();

		if (!db.tables().contains("units")) {
			QSqlQuery query("create table units (id INTEGER unique primary key,"
			                "name TEXT,"
			                "semester INTEGER,"
			                "credit_count INTEGER,"
			                "is_registrable INTEGER,"
			                "is_registered INTEGER,"
			                "flags INTEGER)");
			if (!query.isActive())
				qWarning() << "Error: " << query.lastError().text();
		}

		for (const IntraModule &module : m_moduleList) {
			QSqlQuery insertQuery;
			insertQuery.prepare("insert into units(id, name, semester, credit_count, is_registrable, is_registered, flags) values(?, ?, ?, ?, ?, ?, ?)");
			insertQuery.addBindValue(module.id());
			insertQuery.addBindValue(module.name());
			insertQuery.addBindValue(module.semester());
			insertQuery.addBindValue(module.creditCount());
			insertQuery.addBindValue(module.isRegistrable());
			insertQuery.addBindValue(module.isRegistered());
			insertQuery.addBindValue((int)module.flags());
			if (!insertQuery.exec() && insertQuery.lastError().nativeErrorCode() != "19")
				qWarning() << "Error: " << insertQuery.lastError().text();
		}
	}
}

void IntraData::updateNotificationList() {
	m_notificationList.clear();

	QJsonArray notificationArray = m_overviewJson.object().value("history").toArray();
	for (QJsonValue value : notificationArray) {
		m_notificationList.emplace_back(value.toObject());
	}
}

void IntraData::updateProjectList() {
	m_projectList.clear();

	QJsonArray projectArray = m_overviewJson.object().value("board").toObject().value("projets").toArray();
	for (QJsonValue value : projectArray) {
		m_projectList.emplace_back(value.toObject());
	}
}

std::deque<IntraEvent> IntraData::getEventList(const QDate &date, const std::vector<unsigned int> &semesters) const {
	QString semesterString;
	for (int n : semesters)
		semesterString += QString::number(n) + ",";
	semesterString.chop(1);

	QString dateString = date.toString("yyyy-MM-dd");
	QJsonDocument json = IntraSession::getInstance().get("/planning/load", {
		std::make_pair("start", dateString),
		std::make_pair("end", dateString),
		std::make_pair("semester", semesterString)
	});

	std::deque<IntraEvent> eventList;
	for (QJsonValue value : json.array()) {
		eventList.emplace_back(value.toObject());
	}

	return eventList;
}

IntraUser IntraData::getUserInfo(const QString &login) {
	auto it = m_userInfoCache.find(login);
	if (it == m_userInfoCache.end()) {
		QJsonDocument json = IntraSession::getInstance().get("/user/" + login);
		auto r = m_userInfoCache.emplace(login, json.object());
		return r.first->second;
	}

	return it->second;
}

