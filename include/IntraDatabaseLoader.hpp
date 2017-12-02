/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabaseLoader.hpp
 *
 *    Description:
 *
 *        Created:  16/11/2017 19:33:07
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATABASELOADER_HPP_
#define INTRADATABASELOADER_HPP_

#include "IntraActivity.hpp"
#include "IntraModule.hpp"

class IntraDatabaseLoader : public QObject {
	Q_OBJECT

	public:
		void update() const;

	signals:
		void updateStarted() const;
		void updateProgressed(int value) const;
		void updateFinished() const;

		void userUpdateFinished() const;
		void notificationUpdateFinished() const;
		void overviewUpdateFinished() const;

		void unitUpdateProgressed(int value) const;
		void unitUpdateFinished() const;

	private:
		void updateUser() const;
		void updateNotifications() const;
		void updateOverview() const;
		void updateUnits() const;
		void updateActivities() const;
		void updateEvents(const IntraActivity &activity, const QJsonObject &jsonObject) const;
		void updateProjects(const IntraActivity &activity) const;
};

#endif // INTRADATABASELOADER_HPP_
