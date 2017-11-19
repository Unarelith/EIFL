/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabaseThread.hpp
 *
 *    Description:
 *
 *        Created:  16/11/2017 18:29:54
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef INTRADATABASETHREAD_HPP_
#define INTRADATABASETHREAD_HPP_

#include "IntraDatabase.hpp"

class IntraDatabaseThread : public QThread {
	public:
		IntraDatabaseThread(IntraDatabase *database) : QThread(database), m_database(database) {}
		~IntraDatabaseThread() override {
			requestInterruption();
			wait();
		}

		void run() override { m_database->loader().update(); }

	private:
		IntraDatabase *m_database;
};

#endif // INTRADATABASETHREAD_HPP_
