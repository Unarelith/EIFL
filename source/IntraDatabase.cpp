/*
 * =====================================================================================
 *
 *       Filename:  IntraDatabase.cpp
 *
 *    Description:
 *
 *        Created:  06/11/2017 01:38:28
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <QDebug>

#include "IntraDatabase.hpp"

QString IntraDatabase::s_path;

void IntraDatabase::open(const QString &path) {
	s_path = path;

	if (!QSqlDatabase::isDriverAvailable("QSQLITE"))
		throw std::runtime_error("SQLite required!");

	// m_database = QSqlDatabase::database();
	// if (!m_database.isValid()) {
	// 	m_database = QSqlDatabase::addDatabase("QSQLITE");
	// 	m_database.setDatabaseName(path);
	// 	if (!m_database.open()) {
	// 		qWarning() << "Error: " << m_database.lastError();
	// 		throw std::runtime_error("Error: Failed to load database: " + path.toStdString());
	// 	}
	// }
}

void IntraDatabase::clear() const {
	for (QString table : getDatabase().tables()) {
		removeTable(table);
	}
}

void IntraDatabase::addTable(const QString &name, const std::map<QString, QVariant> &fields) {
	QString queryString = "create table " + name + "(id INTEGER unique primary key";
	for (auto it : fields) {
		queryString += "," + it.first + " ";

		switch (it.second.type()) {
			case QVariant::Type::Int:
			case QVariant::Type::UInt:      queryString += "INTEGER"; break;
			case QVariant::Type::Bool:      queryString += "BOOLEAN"; break;
			case QVariant::Type::ByteArray:
			case QVariant::Type::Url:
			case QVariant::Type::String:    queryString += "TEXT"; break;
			case QVariant::Type::Date:      queryString += "DATE"; break;
			case QVariant::Type::DateTime:  queryString += "DATETIME"; break;
			default: break;
		}
	}
	queryString += ")";

	QSqlQuery query(queryString, getDatabase());
	if (!query.isActive())
		qWarning() << "Error: Failed to create database table " << name << ":" << query.lastError().text();
}

void IntraDatabase::removeTable(const QString &name) {
	QSqlDatabase database = getDatabase();
	if (!database.tables().contains(name))
		return;

	QSqlQuery query(QString("drop table ") + name);
	if (!query.isActive())
		qWarning() << "Error: Failed to remove table " << name << " from database:" << query.lastError().text();
}

QSqlDatabase IntraDatabase::getDatabase() {
	// Starting with Qt 5.11, sharing the same connection between threads is not allowed.
	// We use a dedicated connection for each thread requiring access to the database,
	// using the thread address as connection name.
	const QString thread_address = QString("0x") + QString::number((quintptr)QThread::currentThreadId(), 16);

 	// Check if there's already an open and valid connection to the database.
	QSqlDatabase db = QSqlDatabase::database(thread_address);
	if (db.isOpen() && db.isValid()) {
		return db;
	} else {
		qDebug() << "Creating new database connection for thread" << thread_address;
		db = QSqlDatabase::addDatabase(QString("QSQLITE"), thread_address);
		db.setDatabaseName(s_path);
		if (!db.open() || !db.isValid()) {
			qWarning() << "Error: " << db.lastError();
			throw std::runtime_error("Error: Failed to load database: " + s_path.toStdString());
		}
	}

	return db;
}

