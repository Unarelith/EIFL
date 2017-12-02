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
		void store(const QString &key, const QString &value) const;
		void remove(const QString &key) const;

		bool has(const QString &key) const;
		QString get(const QString &key) const;

	private:
		void startJob(QKeychain::Job &job) const;
};

#endif // KEYRING_HPP_
