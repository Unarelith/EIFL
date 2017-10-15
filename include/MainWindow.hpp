/*
 * =====================================================================================
 *
 *       Filename:  MainWindow.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 18:20:45
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef MAINWINDOW_HPP_
#define MAINWINDOW_HPP_

#include <QMainWindow>

#include "IntraData.hpp"
#include "ProjectListWidget.hpp"
#include "ScheduleWidget.hpp"

class MainWindow : public QMainWindow {
	public:
		MainWindow();

		void keyPressEvent(QKeyEvent *event) override;

		static const unsigned int width = 640;
		static const unsigned int height = 480;

	private:
		IntraData m_intraData;

		ProjectListWidget m_projectListWidget;
		ScheduleWidget m_scheduleWidget;
};

#endif // MAINWINDOW_HPP_
