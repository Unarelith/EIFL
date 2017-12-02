/*
 * =====================================================================================
 *
 *       Filename:  LoginWindow.cpp
 *
 *    Description:
 *
 *        Created:  02/12/2017 02:39:12
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QApplication>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent) {
	setWindowTitle("Login to Epitech Intranet");

	auto *formLayoutWidget = new QWidget;
	auto *formLayout = new QFormLayout(formLayoutWidget);
	formLayout->addRow("Login:", new QLineEdit);
	formLayout->addRow("Password:", new QLineEdit);

	auto *rememberMeCheckBox = new QCheckBox("Remember my password");

	auto *loginButton = new QPushButton("Login");
	connect(loginButton, &QPushButton::clicked, this, &QDialog::accept);

	auto* line = new QFrame();
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);

	auto *offlineButton = new QPushButton("Offline mode");
	connect(offlineButton, &QPushButton::clicked, this, &QDialog::reject);

	auto *quitButton = new QPushButton("Quit");
	connect(quitButton, &QPushButton::clicked, this, &QDialog::reject);
	connect(quitButton, &QPushButton::clicked, this, &LoginWindow::quitButtonPressed);

	auto *verticalLayout = new QVBoxLayout(this);
	verticalLayout->addWidget(formLayoutWidget);
	verticalLayout->addWidget(rememberMeCheckBox);
	verticalLayout->addWidget(loginButton);
	verticalLayout->addWidget(line);
	verticalLayout->addWidget(offlineButton);
	verticalLayout->addWidget(quitButton);
}

