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
#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

#include "CalendarSettingsWidget.hpp"

CalendarSettingsWidget::CalendarSettingsWidget(QWidget *parent) : QDockWidget("Calendar settings", parent) {
	QWidget *layoutWidget = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout(layoutWidget);

	QGroupBox *filtersGroupBox = new QGroupBox("Filters");
	QVBoxLayout *filtersLayout = new QVBoxLayout(filtersGroupBox);
	filtersLayout->addWidget(new QCheckBox("Current semester only"));
	filtersLayout->addWidget(new QCheckBox("Registered modules only"));
	filtersLayout->addWidget(new QCheckBox("Registered events only"));

	QGroupBox *semesterGroupBox = new QGroupBox("Semester");
	QGridLayout *semesterLayout = new QGridLayout(semesterGroupBox);
	semesterLayout->addWidget(new QCheckBox("Semester 0"), 0, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 1"), 1, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 2"), 1, 1);
	semesterLayout->addWidget(new QCheckBox("Semester 3"), 2, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 4"), 2, 1);
	semesterLayout->addWidget(new QCheckBox("Semester 5"), 3, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 6"), 3, 1);
	semesterLayout->addWidget(new QCheckBox("Semester 7"), 4, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 8"), 4, 1);
	semesterLayout->addWidget(new QCheckBox("Semester 9"), 5, 0);
	semesterLayout->addWidget(new QCheckBox("Semester 10"), 5, 1);

	QGroupBox *actionsGroupBox = new QGroupBox("Actions");
	QVBoxLayout *actionsLayout = new QVBoxLayout(actionsGroupBox);
	actionsLayout->addWidget(new QPushButton("Clear highlight"));
	actionsLayout->addWidget(new QPushButton("Select today"));

	layout->addWidget(filtersGroupBox);
	layout->addWidget(semesterGroupBox);
	layout->addWidget(actionsGroupBox);

	setWidget(layoutWidget);
}

