/*
 * =====================================================================================
 *
 *       Filename:  Keyring.cpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 20:57:47
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <iostream>

#include <QEventLoop>

#include "Keyring.hpp"

void Keyring::store(const QString &key, const QString &value) {
	QKeychain::WritePasswordJob job(key);
	job.setBinaryData(value.toUtf8());
	startJob(job);

	if (job.error())
		std::cerr << "Failed to write password to keyring: " << qPrintable(job.errorString()) << std::endl;
}

void Keyring::remove(const QString &key) {
	QKeychain::DeletePasswordJob job(key);
	startJob(job);

	if (job.error())
		std::cerr << "Failed to delete password from keyring: " << qPrintable(job.errorString()) << std::endl;
}

bool Keyring::has(const QString &key) {
	QKeychain::ReadPasswordJob job(key);
	startJob(job);

	return !job.error();
}

QString Keyring::get(const QString &key) {
	QKeychain::ReadPasswordJob job(key);
	startJob(job);

	if (job.error())
		std::cerr << "Failed to read password from keyring: " << qPrintable(job.errorString()) << std::endl;

	return job.textData();
}

void Keyring::startJob(QKeychain::Job &job) {
	QEventLoop loop;
	job.setAutoDelete(false);
	job.setKey("EpitechIntra");
	job.connect(&job, SIGNAL(finished(QKeychain::Job*)), &loop, SLOT(quit()));
	job.start();
	loop.exec();
}

