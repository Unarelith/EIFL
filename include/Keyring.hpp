/*
 * =====================================================================================
 *
 *       Filename:  Keyring.hpp
 *
 *    Description:
 *
 *        Created:  15/10/2017 20:57:33
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef KEYRING_HPP_
#define KEYRING_HPP_

#include <qt5keychain/keychain.h>

class Keyring {
	public:
		void storePassword(const QString &password);
		void deletePassword();

		bool hasPassword();
		QString getPassword();

	private:
		void startJob(QKeychain::Job &job);
};

#endif // KEYRING_HPP_
