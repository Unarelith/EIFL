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

#include "CalendarWidget.hpp"
#include "EventInfoWidget.hpp"
#include "EventListWidget.hpp"
#include "IntraData.hpp"
#include "IntraSession.hpp"
#include "ProjectInfoWidget.hpp"
#include "ProjectListWidget.hpp"

class MainWindow : public QMainWindow {
	public:
		MainWindow();

		void keyPressEvent(QKeyEvent *event) override;

		static const unsigned int width = 1280;
		static const unsigned int height = 720;

	private:
		IntraData m_intraData;
		IntraSession m_intraSession;

		CalendarWidget m_calendarWidget;

		ProjectInfoWidget m_projectInfoWidget;
		ProjectListWidget m_projectListWidget;

		EventInfoWidget m_eventInfoWidget;
		EventListWidget m_eventlistWidget;
};

#endif // MAINWINDOW_HPP_
