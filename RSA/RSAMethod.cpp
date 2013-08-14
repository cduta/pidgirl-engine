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

#include "RSAMethod.h"

#include <cryptopp/dsa.h>
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/pssr.h>
#include <cryptopp/sha.h>
#include <cryptopp/oaep.h>
#include <cryptopp/pubkey.h>
#include <cryptopp/queue.h>
using namespace CryptoPP;

#include "Common/FileNameConventions.h"

RSAMethod::RSAMethod(const string &privateKeyFilePath, const string &publicKeyFilePath)
    : privateKeyFilePath(privateKeyFilePath),
      publicKeyFilePath(publicKeyFilePath)
{
    this->loadKeys();
    this->init();
}

RSAMethod::RSAMethod(unsigned int keySize, const string &privateKeyFilePath, const string &publicKeyFilePath)
    : privateKeyFilePath(privateKeyFilePath),
      publicKeyFilePath(publicKeyFilePath)
{
    this->generateKeys(keySize);
    this->init();
}

void RSAMethod::init()
{
    RSAES_OAEP_SHA_Encryptor e(this->publicKey);
    this->maxPlainTextLength = e.FixedMaxPlaintextLength();
    RSAES_OAEP_SHA_Decryptor d(this->privateKey);
    this->maxCipherTextLength = d.FixedMaxPlaintextLength();
    return;
}

void RSAMethod::generateKeys(unsigned int keySize)
{
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(this->randomNumberGenerator, keySize);

    this->privateKey = RSA::PrivateKey(params);
    this->publicKey = RSA::PublicKey(params);

    this->saveKey(this->privateKeyFilePath, this->privateKey);
    this->saveKey(this->publicKeyFilePath, this->publicKey);

    return;
}

void RSAMethod::loadKeys()
{
    this->loadKey(this->privateKeyFilePath, this->privateKey);
    this->loadKey(this->publicKeyFilePath, this->publicKey);
    return;
}

string RSAMethod::encryptString(const string &plain)
{
    std::string cipher;
    RSAES_OAEP_SHA_Encryptor e(this->publicKey);

    StringSource(plain, true,
        new PK_EncryptorFilter(this->randomNumberGenerator, e,
            new StringSink(cipher)
        )
    );

    return cipher;
}

string RSAMethod::decryptString(const string &cipher)
{
    std::string recovered;
    RSAES_OAEP_SHA_Decryptor d(this->privateKey);

    try
    {
        StringSource(cipher, true,
            new PK_DecryptorFilter(this->randomNumberGenerator, d,
                new StringSink(recovered)
            )
        );
    }
    catch(...)
    {
        return string("");
    }

    return recovered;
}

size_t RSAMethod::getMaxCipherTextLength()
{
    return this->maxCipherTextLength;
}

size_t RSAMethod::getMaxPlainTextLength()
{
    return this->maxPlainTextLength;
}

void RSAMethod::load(const string& filename, BufferedTransformation& buffer)
{
    FileSource file(filename.c_str(), true);

    file.TransferTo(buffer);
    buffer.MessageEnd();
    return;
}

void RSAMethod::save(const string& filename, const BufferedTransformation& buffer)
{
    FileSink file(filename.c_str());

    buffer.CopyTo(file);
    file.MessageEnd();
    return;
}
