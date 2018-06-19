#ifndef IOT_AUTH_H
#define IOT_AUTH_H

#include "settings.h"
#include "utils.h"
#include "RSA/RSA.h"
#include "SHA/sha512.h"
#include "fdr.h"
#include <string>
#include <iostream>
#include <sstream>
#include "AES/AES.h"
#include <unistd.h>

using namespace std;

class IotAuth
{
    protected:

    public:

        uint8_t* encryptAES(uint8_t* plaintext, uint8_t* key, uint8_t* iv, int size);
        uint8_t* decryptAES(uint8_t* ciphertext, uint8_t* key, uint8_t* iv, int size);

        RSAKeyPair generateRSAKeyPair();
        int generateIV();
        FDR generateFDR();

        int randomNumber(int upperBound);

        string hash(string *message);
        bool isHashValid(string *message, string *hash);

        int* encryptRSA(string *plain, RSAKey *rsaKey, int size);
        int* encryptRSA(byte *plain, RSAKey *rsaKey, int size);
        byte* decryptRSA(int *cipher, RSAKey *rsaKey, int size);

        char* getNounce(string *source, string *receiver, int sequence);

    private:

        AES aes;
        RSA rsa;
};
#endif
