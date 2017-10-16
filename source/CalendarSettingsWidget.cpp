/*
 * =====================================================================================
 *
 *       Filename:  CalendarSettingsWidget.cpp
 *
 *    Description:
 *
 *        Created:  16/10/2017 23:29:46
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QGridLayout>
#include <QVBoxLayout>

#include "CalendarSettingsWidget.hpp"

CalendarSettingsWidget::CalendarSettingsWidget(QWidget *parent) : QDockWidget("Calendar settings", parent) {
	QWidget *layoutWidget = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout(layoutWidget);

	layout->addWidget(createFiltersBox());
	layout->addWidget(createSemesterBox());
	layout->addWidget(createActionsBox());

	setWidget(layoutWidget);
}

QGroupBox *CalendarSettingsWidget::createFiltersBox() {
	QGroupBox *filtersGroupBox = new QGroupBox("Filters");
	QVBoxLayout *filtersLayout = new QVBoxLayout(filtersGroupBox);
	filtersLayout->addWidget(&m_currentSemesterOnly);
	filtersLayout->addWidget(&m_registeredModulesOnly);
	filtersLayout->addWidget(&m_registeredEventsOnly);

	connect(&m_currentSemesterOnly, &QCheckBox::stateChanged, this, &CalendarSettingsWidget::filterBoxClicked);
	connect(&m_registeredModulesOnly, &QCheckBox::stateChanged, this, &CalendarSettingsWidget::filterBoxClicked);
	connect(&m_registeredEventsOnly, &QCheckBox::stateChanged, this, &CalendarSettingsWidget::filterBoxClicked);

	m_registeredModulesOnly.setCheckState(Qt::Checked);

	return filtersGroupBox;
}

QGroupBox *CalendarSettingsWidget::createSemesterBox() {
	QGroupBox *semesterGroupBox = new QGroupBox("Semester");
	QGridLayout *semesterLayout = new QGridLayout(semesterGroupBox);
	for (unsigned int i = 0 ; i < 11 ; ++i) {
		m_semesters.emplace_back("Semester " + QString::number(i));
		semesterLayout->addWidget(&m_semesters.back(), i / 2, i % 2);

		// FIXME
		if (i == 0 || i == 5)
			m_semesters.back().setCheckState(Qt::Checked);

		connect(&m_semesters.back(), &QCheckBox::stateChanged, this, &CalendarSettingsWidget::semesterBoxClicked);
	}

	return semesterGroupBox;
}

QGroupBox *CalendarSettingsWidget::createActionsBox() {
	QGroupBox *actionsGroupBox = new QGroupBox("Actions");
	QVBoxLayout *actionsLayout = new QVBoxLayout(actionsGroupBox);
	actionsLayout->addWidget(&m_clearHighlight);
	actionsLayout->addWidget(&m_selectToday);

	return actionsGroupBox;
}

void CalendarSettingsWidget::filterBoxClicked() {
	if (m_registeredEventsOnly.checkState() == Qt::Checked)
		m_registeredModulesOnly.setCheckState(Qt::Checked);

	if (m_registeredModulesOnly.checkState() == Qt::Checked)
		m_currentSemesterOnly.setCheckState(Qt::Checked);

	emit filterStateHasChanged(m_currentSemesterOnly.checkState()   == Qt::Checked,
	                           m_registeredModulesOnly.checkState() == Qt::Checked,
	                           m_registeredEventsOnly.checkState()  == Qt::Checked);
}

void CalendarSettingsWidget::semesterBoxClicked() {
	std::vector<int> semestersEnabled;
	for (unsigned int i = 0 ; i < m_semesters.size() ; ++i) {
		if (m_semesters[i].checkState() == Qt::Checked)
			semestersEnabled.push_back(i);
	}

	emit semesterStateHasChanged(semestersEnabled);
}

