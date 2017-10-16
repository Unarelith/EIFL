/*
 * =====================================================================================
 *
 *       Filename:  CalendarSettingsWidget.hpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 23:29:19
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef CALENDARSETTINGSWIDGET_HPP_
#define CALENDARSETTINGSWIDGET_HPP_

#include <deque>

#include <QCheckBox>
#include <QDockWidget>
#include <QGroupBox>
#include <QPushButton>

class CalendarSettingsWidget : public QDockWidget {
	public:
		CalendarSettingsWidget(QWidget *parent = nullptr);

		QGroupBox *createFiltersBox();
		QGroupBox *createSemesterBox();
		QGroupBox *createActionsBox();

	private:
		QCheckBox m_currentSemesterOnly{"Current semester only"};
		QCheckBox m_registeredModulesOnly{"Registered modules only"};
		QCheckBox m_registeredEventsOnly{"Registered events only"};

		std::deque<QCheckBox> m_semesters;

		QPushButton m_clearHighlight{"Clear hightlight"};
		QPushButton m_selectToday{"Select today"};
};

#endif // CALENDARSETTINGSWIDGET_HPP_
