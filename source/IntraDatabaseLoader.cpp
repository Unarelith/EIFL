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
	updateOverview();
	updateUnits();

	QSqlDatabase::database().exec("begin;");

	updateActivities();

	QSqlDatabase::database().exec("commit;");

	emit updateProgressed(0);
	emit unitUpdateProgressed(0);
}

void IntraDatabaseLoader::updateUser() const {
	QJsonDocument json = IntraSession::getInstance().get("/user");
	IntraUser user(json.object());
	user.updateDatabaseTable();
	user.writeToDatabase();

	emit userUpdateFinished();
	emit unitUpdateProgressed(25);
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
	emit unitUpdateProgressed(50);
}

void IntraDatabaseLoader::updateOverview() const {
	QJsonDocument json = IntraSession::getInstance().get("/");
	QJsonArray projectArray = json.object().value("board").toObject().value("projets").toArray();
	for (const QJsonValue &value : projectArray) {
		if (QThread::currentThread()->isInterruptionRequested())
			return;

		IntraActivity activity(value.toObject());
		if (!IntraData::getInstance().getActivity(activity.id())) {
			activity.updateDatabaseTable();
			activity.writeToDatabase();

			IntraData::getInstance().setActivity(activity.id(), activity);
		}

		IntraProject project(value.toObject());
		if (!IntraData::getInstance().getProject(project.id())) {
			project.updateDatabaseTable();
			project.writeToDatabase();

			IntraData::getInstance().setProject(project.id(), project);
		}
	}

	emit overviewUpdateFinished();
	emit unitUpdateProgressed(75);
}

void IntraDatabaseLoader::updateUnits() const {
	QJsonDocument json = IntraSession::getInstance().get("/course/filter");
	QJsonArray unitArray = json.array();
	if (unitArray.isEmpty())
		return;

	for (const QJsonValue &value : unitArray) {
		if (QThread::currentThread()->isInterruptionRequested())
			return;

		IntraModule module(value.toObject());
		if (module.semester() == 0 || module.semester() == IntraData::getInstance().userInfo().currentSemester()) {
			module.updateDatabaseTable();
			module.writeToDatabase();

			IntraData::getInstance().setModule(module.id(), module);
		}
	}

	emit unitUpdateFinished();
	emit unitUpdateProgressed(100);
}

void IntraDatabaseLoader::updateActivities() const {
	emit updateStarted();

	size_t i = 0;
	auto &unitArray = IntraData::getInstance().moduleList();
	for (auto &it : unitArray) {
		if (QThread::currentThread()->isInterruptionRequested())
			return;

		const IntraModule &unit = it.second;
		QJsonDocument json = IntraSession::getInstance().get(unit.link());
		QJsonArray activityArray = json.object().value("activites").toArray();
		if (!activityArray.isEmpty()) {
			size_t j = 0;
			for (const QJsonValue &value : activityArray) {
				if (QThread::currentThread()->isInterruptionRequested())
					return;

				IntraActivity activity(unit.id(), value.toObject());
				activity.updateDatabaseTable();
				activity.writeToDatabase();

				IntraData::getInstance().setActivity(activity.id(), activity);

				if (QThread::currentThread()->isInterruptionRequested())
					return;

				if (activity.isProject())
					updateProjects(activity);

				updateEvents(activity, value.toObject());

				emit unitUpdateProgressed(j++ * 100 / activityArray.size());
			}

			emit unitUpdateProgressed(j++ * 100 / activityArray.size());
			emit unitUpdateFinished();
		}

		emit updateProgressed(i++ * 100 / unitArray.size());
	}

	emit updateProgressed(i++ * 100 / unitArray.size());
	emit updateFinished();
}

void IntraDatabaseLoader::updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject) const {
	QJsonArray eventArray = jsonObject.value("events").toArray();
	for (const QJsonValue &value : eventArray) {
		if (QThread::currentThread()->isInterruptionRequested())
			return;

		IntraEvent event(activity.id(), value.toObject());
		event.updateDatabaseTable();
		event.writeToDatabase();

		IntraData::getInstance().setEvent(event.id(), event);
	}
}

void IntraDatabaseLoader::updateProjects(const IntraActivity &activity) const {
	QJsonDocument json = IntraSession::getInstance().get(activity.link() + "/project");
	IntraProject project(activity.id(), json.object());
	project.updateDatabaseTable();
	project.writeToDatabase();

	IntraData::getInstance().setProject(project.id(), project);
}

