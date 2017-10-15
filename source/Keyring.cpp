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

void Keyring::storePassword(const QString &password) {
	QKeychain::WritePasswordJob job(QString("EIFL"));
	job.setBinaryData(password.toUtf8());
	startJob(job);

	if (job.error())
		std::cerr << "Failed to write password to keyring: " << qPrintable(job.errorString()) << std::endl;
}

void Keyring::deletePassword() {
	QKeychain::DeletePasswordJob job(QString("EIFL"));
	startJob(job);

	if (job.error())
		std::cerr << "Failed to delete password from keyring: " << qPrintable(job.errorString()) << std::endl;
}

bool Keyring::hasPassword() {
	QKeychain::ReadPasswordJob job(QString("EIFL"));
	startJob(job);

	return !job.error();
}

QString Keyring::getPassword() {
	QKeychain::ReadPasswordJob job(QString("EIFL"));
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

