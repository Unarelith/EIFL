/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabaseLoader.cpp
 *
 *    Description:
 *
 *        Created:  16/11/2017 19:33:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QJsonArray>
#include <QJsonDocument>
#include <QThread>

#include "IntraData.hpp"
#include "IntraDatabaseLoader.hpp"
#include "IntraEvent.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraSession.hpp"
#include "IntraUser.hpp"

void IntraDatabaseLoader::update() const {
	updateUser();
	updateNotifications();

	QSqlDatabase::database().exec("begin;");

	updateUnits();

	QSqlDatabase::database().exec("commit;");
}

void IntraDatabaseLoader::updateUser() const {
	QJsonDocument json = IntraSession::getInstance().get("/user");
	IntraUser user(json.object());
	user.updateDatabaseTable();
	user.writeToDatabase();

	emit userUpdateFinished();
}

void IntraDatabaseLoader::updateNotifications() const {
	QJsonDocument json = IntraSession::getInstance().get("/");
	QJsonArray notificationArray = json.object().value("history").toArray();
	if (notificationArray.isEmpty())
		return;

	for (QJsonValue value : notificationArray) {
		IntraNotification notification(value.toObject());
		notification.updateDatabaseTable();
		notification.writeToDatabase();
	}

	emit notificationUpdateFinished();
}

void IntraDatabaseLoader::updateUnits() const {
	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray unitArray = json.array();
	if (unitArray.isEmpty())
		return;

	emit updateStarted();

	size_t i = 0;
	for (QJsonValue value : unitArray) {
		IntraModule module(value.toObject());
		if (module.semester() == 0 || module.semester() == IntraData::getInstance().userInfo().currentSemester()) {
			module.updateDatabaseTable();
			module.writeToDatabase();

			updateActivities(module);
		}

		emit updateProgressed(i++ * 100 / unitArray.size());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}

	emit updateProgressed(i++ * 100 / unitArray.size());
	emit updateFinished();
}

void IntraDatabaseLoader::updateActivities(const IntraModule &unit) const {
	QJsonDocument json = IntraSession::getInstance().get(unit.link());
	QJsonArray activityArray = json.object().value("activites").toArray();
	if (activityArray.isEmpty())
		return;

	size_t i = 0;
	for (QJsonValue value : activityArray) {
		IntraActivity activity(unit, value.toObject());
		activity.updateDatabaseTable();
		activity.writeToDatabase();

		if (activity.isProject())
			updateProjects(activity);

		updateEvents(activity, value.toObject());

		emit unitUpdateProgressed(i++ * 100 / activityArray.size());

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}

	emit unitUpdateProgressed(i++ * 100 / activityArray.size());
	emit unitUpdateFinished();
}

void IntraDatabaseLoader::updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject) const {
	QJsonArray eventArray = jsonObject.value("events").toArray();
	for (QJsonValue value : eventArray) {
		IntraEvent event(activity, value.toObject());
		event.updateDatabaseTable();
		event.writeToDatabase();

		if (QThread::currentThread()->isInterruptionRequested())
			return;
	}
}

void IntraDatabaseLoader::updateProjects(const IntraActivity &activity) const {
	QJsonDocument json = IntraSession::getInstance().get(activity.link() + "/project");
	IntraProject project(activity, json.object());
	project.updateDatabaseTable();
	project.writeToDatabase();
}

