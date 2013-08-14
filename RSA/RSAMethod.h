/*
 * A flexible rogue-like engine with easy-to-use mouse interface, editor,
 * solo, hotseat, network multiplayer and E-Mail game functionality in mind.
 * Copyright (C) 2013  Ryoga Unryu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RSA_METHOD_H
#define RSA_METHOD_H

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
using namespace CryptoPP;

#include <string>
#include <iostream>
using namespace std;

/** \addtogroup RSA
  * \{
  * \class RSAMethod
  *
  * \brief The RSA Method implemented wrapped around the Crypto++ library. This is written to be completely independent of QT.
  *
  * \author RyogaU
  *
  * \version 0.5
  *
  * Contact: RyogaU@googlemail.com
  * \}
  */
class RSAMethod
{
    AutoSeededRandomPool    randomNumberGenerator;

    RSA::PrivateKey         privateKey;
    string                  privateKeyFilePath;
    size_t                  maxCipherTextLength;

    RSA::PublicKey          publicKey;
    string                  publicKeyFilePath;
    size_t                  maxPlainTextLength;

public:
    /**
      * @brief Loads a key pair from two different files.
      * @param keyDirectory Where to put the keys.
      */
    RSAMethod(const string &privateKeyFilePath, const string &publicKeyFilePath);

    /**
      * @brief Generates a key pair and saves them sperately in two different files.
      * @param keySize The RSA key size in bits.
      * @param keyDirectory Where to get the keys from.
      */
    RSAMethod(unsigned int keySize, const string &privateKeyFilePath, const string &publicKeyFilePath);

private:
    void init();

    /**
      * @brief Generates and loads the private and public keys.
      * @param keySize The size of the key in bits. 1024 Bit Key is currently good enough.
      */
    void generateKeys(unsigned int keySize);

    /**
      * @brief Load keys from the given file paths.
      */
    void loadKeys();

public:
    /**
      * @brief Encrypt a given string with the loaded keys.
      * @param plainText The plaintext to be encrypted.
      * @return The ciphertext.
      */
    string encryptString(const string &plain);

    /**
      * @brief Decrypt a given string with the loaded keys.
      * @param cipherText The ciphertext to be decrypted.
      * @return The recovered plaintext.
      */
    string decryptString(const string &cipher);

    // Get-Methods
    size_t getMaxCipherTextLength();
    size_t getMaxPlainTextLength();

private:
    void load(const string& filename, BufferedTransformation& buffer);
    template<class T>
    void loadKey(const string& filename, T& key)
    {
        ByteQueue queue;

        this->load(filename, queue);
        key.Load(queue);
        return;
    }

    void save(const string& filename, const BufferedTransformation& buffer);
    template<class T>
    void saveKey(const string& filename, const T& key)
    {
        ByteQueue queue;
        key.Save(queue);

        this->save(filename, queue);
        return;
    }
};

#endif // RSA_METHOD_H
