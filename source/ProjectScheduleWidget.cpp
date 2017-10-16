/*
 * =====================================================================================
 *
 *       Filename:  ProjectScheduleWidget.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 21:33:41
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "IntraData.hpp"
#include "ProjectScheduleWidget.hpp"

ProjectScheduleWidget::ProjectScheduleWidget(QWidget *parent) : QGroupBox("Project schedule", parent) {
	QWidget *subLayoutWidget = new QWidget;
	QHBoxLayout *subLayout = new QHBoxLayout(subLayoutWidget);

	QPushButton *clearButton = new QPushButton("Clear highlight");
	QPushButton *todayButton = new QPushButton("Select today");

	connect(clearButton, &QPushButton::clicked, [&] {
		m_calendarWidget.setDateTextFormat(QDate(), QTextCharFormat());
	});

	connect(todayButton, &QPushButton::clicked, [&] {
		m_calendarWidget.setSelectedDate(QDate::currentDate());
	});

	subLayout->addWidget(clearButton);
	subLayout->addWidget(todayButton);

	QVBoxLayout *layout = new QVBoxLayout(this);
	layout->addWidget(&m_calendarWidget);
	layout->addWidget(subLayoutWidget);

	m_currentProjectFormat.setBackground(QBrush(QColor(0, 64, 128)));

	m_registerDateFormat.setBackground(QBrush(QColor(128, 0, 0)));
	m_registerDateFormat.setFontUnderline(QTextCharFormat::SingleUnderline);

	m_beginDateFormat.setBackground(QBrush(QColor(0, 0, 128)));
	m_beginDateFormat.setFontUnderline(QTextCharFormat::SingleUnderline);

	m_endDateFormat.setBackground(QBrush(QColor(0, 0, 128)));
	m_endDateFormat.setFontUnderline(QTextCharFormat::SingleUnderline);
}

void ProjectScheduleWidget::displayProjectDates(QTreeWidgetItem *item, unsigned int) {
	for (const IntraProject &project : IntraData::getInstance().projectList()) {
		if (item->text(0).toStdString() == project.name()) {
			m_calendarWidget.setDateTextFormat(QDate(), QTextCharFormat());

			for (QDateTime i = project.beginDate() ; i < project.endDate() ; i = i.addDays(1)) {
				m_calendarWidget.setDateTextFormat(i.date(), m_currentProjectFormat);
			}

			m_calendarWidget.setDateTextFormat(project.beginDate().date(), m_beginDateFormat);
			m_calendarWidget.setDateTextFormat(project.endDate().date(), m_endDateFormat);

			if (!project.registerDate().isNull())
				m_calendarWidget.setDateTextFormat(project.registerDate().date(), m_registerDateFormat);
		}
	}
}

