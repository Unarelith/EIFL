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
		void store(const QString &key, const QString &value);
		void remove(const QString &key);

		bool has(const QString &key);
		QString get(const QString &key);

	private:
		void startJob(QKeychain::Job &job);
};

#endif // KEYRING_HPP_
