/*
 * =====================================================================================
 *
 *       Filename:  IntraData.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:42:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATA_HPP_
#define INTRADATA_HPP_

#include <deque>
#include <map>
#include <memory>
#include <vector>

#include "IntraDatabase.hpp"
#include "IntraEvent.hpp"
#include "IntraModule.hpp"
#include "IntraNotification.hpp"
#include "IntraProject.hpp"
#include "IntraUser.hpp"

template<typename... Args>
class IntraDatabaseThread : public QThread {
	using FuncType = void(IntraDatabase::*)(Args...) const;

	public:
		IntraDatabaseThread(QObject *parent, IntraDatabase *database, FuncType func, Args &&...args)
			: QThread(parent), m_func(func), m_database(database), m_args(std::forward<Args>(args)...) {}

		// ~IntraDatabaseThread() override {
		// 	requestInterruption();
		// 	wait();
		// }

		void run() override { call(m_database, m_func, m_args); }

	private:
		template<typename Instance, typename Function, typename Tuple, size_t... I>
		auto call(Instance i, Function f, Tuple t, std::index_sequence<I...>) {
			return (i->*f)(std::get<I>(t)...);
		}

		template<typename Instance, typename Function, typename Tuple>
		auto call(Instance i, Function f, Tuple t) {
			static constexpr auto size = std::tuple_size<Tuple>::value;
			return call(i, f, t, std::make_index_sequence<size>{});
		}

		FuncType m_func;
		IntraDatabase *m_database;
		std::tuple<Args...> m_args;
};

class IntraDatabaseThreadPool : public QObject {
	public:
		IntraDatabaseThreadPool(std::shared_ptr<IntraDatabase> database) : m_database(database) {
			m_database->setThreadPool(this);
		}

		~IntraDatabaseThreadPool() override {
			for (QThread *thread : m_pool) {
				thread->requestInterruption();
				thread->wait();
			}
		}

		void addThread(QThread *thread) {
			m_pool.emplace_back(thread);
		}

		template<typename... Args>
		void addTask(void (IntraDatabase::*func)(Args...) const, Args &&...args) {
			m_pool.emplace_back(new IntraDatabaseThread<Args...>(nullptr, m_database.get(), func, std::forward<Args>(args)...));
		}

		template<typename... Args>
		void runTask(void (IntraDatabase::*func)(Args...) const, Args &&...args) {
			addTask(func, std::forward<Args>(args)...);
			m_pool.back()->start();
		}

		void start() {
			for (QThread *thread : m_pool)
				if (!thread->isRunning() && !thread->isFinished())
					thread->start();
		}

	private:
		std::deque<QThread *> m_pool;
		std::shared_ptr<IntraDatabase> m_database;
};

class IntraData : public QObject {
	Q_OBJECT

	public:
		IntraData();

		void openDatabase(const QString &path);
		void updateDatabase();
		void reloadDatabase();

		void update();
		void updateModuleList();
		void updateActivityList();
		void updateEventList();
		void updateProjectList();
		void updateUserList();
		void updateNotificationList();

		const IntraDatabase &database() const { return *m_database; }

		const std::map<unsigned int, IntraModule> &moduleList() const { return m_moduleList; }
		const std::map<unsigned int, IntraEvent> &eventList() const { return m_eventList; }
		const std::map<unsigned int, IntraProject> &projectList() const { return m_projectList; }
		const std::map<unsigned int, IntraNotification> &notificationList() const { return m_notificationList; }

		const IntraUser &userInfo() const { return m_userInfo; }

		static IntraData &getInstance() {
			return *s_instance;
		}

		static void setInstance(IntraData &instance) {
			s_instance = &instance;
		}

	signals:
		void databaseUpdateFinished();

	private:
		static IntraData *s_instance;

		std::shared_ptr<IntraDatabase> m_database{std::make_shared<IntraDatabase>()};

		std::map<unsigned int, IntraModule> m_moduleList;
		std::map<unsigned int, IntraActivity> m_activityList;
		std::map<unsigned int, IntraEvent> m_eventList;
		std::map<unsigned int, IntraProject> m_projectList;
		std::map<unsigned int, IntraNotification> m_notificationList;
		IntraUser m_userInfo;

		IntraDatabaseThreadPool m_threadPool{m_database};
};

#endif // INTRADATA_HPP_
