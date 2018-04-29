#include "iotAuth.h"

/*  encryptAES()
    Função interna.
    Realiza a cifragem de plain com o algoritmo AES, onde o resultado é
    armazenado no array cipher.
*/
void iotAuth::encryptAES(int bits, int cipher_size, byte *key, byte plain[], unsigned long long int my_iv, byte cipher[])
{
    aes.iv_inc();
    byte iv[N_BLOCK];

    aes.set_IV(my_iv);
    aes.get_IV(iv);

    aes.do_aes_encrypt(plain, cipher_size, cipher, key, bits, iv);
}

/*  decryptAES()
    Função interna.
    Realiza decrifragem de cipher com o algoritmo AES, onde o resultado é
    armazenado no array plain.
*/
void iotAuth::decryptAES(int bits, int cipher_size, byte *key, byte plain[], unsigned long long int my_iv, byte cipher[])
{
    byte iv[N_BLOCK];

    aes.set_IV(my_iv);
    aes.get_IV(iv);

    int total = 16;
    if(cipher_size > 16 && cipher_size <= 32){
        total = 32;
    }else if(cipher_size > 32 && cipher_size <= 48){
        total = 48;
    }else if(cipher_size > 48 && cipher_size <= 64){
        total = 64;
    }
    aes.do_aes_decrypt(cipher, total, plain, key, bits, iv);
}

/*  encrypt()
    Função utilizada na comunicação entre cliente e servidor, onde é realizada
    a cifragem do texto plano (plain, em bytes), e o resultado é armazenado
    em um array de char cipherHex, com o valor em hexadecimal.
*/
void iotAuth::encrypt(byte plain[], int plain_size, char cipherHex[], int cipherHex_size)
{
    byte *key = (unsigned char*)"1234567891234567";
    unsigned long long int iv = 11111111;
    byte cipher[64];

    memset(cipher, 0, sizeof(cipher));
    memset(cipherHex, 0, cipherHex_size);

    encryptAES(256, 64, key, plain, iv, cipher);
    utils.ByteArrayToHexString(cipher, sizeof(cipher), cipherHex, cipherHex_size);
    cout << "Cifrado em HEXA (iotAuth): " << cipherHex << endl;
}

/*  decrypt()
    Função utilizada na comunicação entre cliente e servidor, onde é realizada
    a decifragem do texto cifrado (cipher, em hexadecimal) e o resultado é
    armazenado em um array de bytes, plain.
*/
void iotAuth::decrypt(byte plain[], int plain_size, char cipherHex[], int cipherHex_size)
{
    byte *key = (unsigned char*)"1234567891234567";
    unsigned long long int iv = 11111111;

    byte cipher[64];

    memset(cipher, 0, sizeof(cipher));
    memset(plain, 0, plain_size);

    utils.HexStringToByteArray(cipherHex, cipherHex_size, cipher, sizeof(cipher));

    decryptAES(256, 64, key, plain, iv, cipher);
    cout << "Decifrado em CHAR (iotAuth): " << plain << endl;
}
