/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 18:20:20
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QApplication>

#include "MainWindow.hpp"

std::ostream &operator<<(std::ostream &stream, const QString &str) {
	return stream << str.toStdString();
}

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainWindow win;

	return app.exec();
}

