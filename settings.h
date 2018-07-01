#ifndef SETTINGS_H
#define SETTINGS_H

#include "fdr.h"

#define MEM_TEST false

/* Definição de alguns atributos utilizados na comunicação */
#define VERBOSE true
#define DEFAULT_PORT 8080

#define DONE_MESSAGE "DONE"

#define DONE_ACK "!"
#define DONE_ACK_CHAR '!'

#define ACK true
#define SYN false

/* Maximum time wait for response */
#define TIMEOUT_SEC 5
#define TIMEOUT_MIC 0

typedef struct syn
{
    bool message = SYN;
    char nonce[129];    /* HASH(time | idDestino | idOrigem | seq) */
} structSyn;

typedef struct ack
{
    bool message = ACK;
    char nonceA[129];
    char nonceB[129];
} structAck;

typedef struct DH_ACK 
{
    bool message = ACK;
    char nonce[129];
} DH_ACK;

/* Definição do tipo "byte" utilizado. */
typedef unsigned char byte;

/* Definição da struct de chave RSA. */
typedef struct rsa_key
{
    int d, n;
} RSAKey;

/* Definição da struct que contém o par de chaves RSA. */
typedef struct rsa_key_pair
{
    RSAKey publicKey;
    RSAKey privateKey;
} RSAKeyPair;

/* Definição de todos os possíveis estados da FSM:
    SEND_SYN        :   Envia pedido de início de conexão.
    RECV_SYN        :   Recebe pedido de início de conexão.
    SEND_ACK        :   Envia confirmação do início da conexão.
    RECV_ACK        :   Recebe confirmação do início da conexão.
    SEND_RSA        :   Envia informações RSA.
    RECV_RSA        :   Recebe informações RSA.
    SEND_RSA_ACK    :   Envia confirmação RSA.
    RECV_RSA_ACK    :   Recebe confirmação RSA.
    SEND_DH         :   Envia informações Diffie-Hellman.
    RECV_DH         :   Recebe informações Diffie-Hellman.
    SEND_DH_ACK     :   Envia confirmação Diffie-Hellman.
    RECV_DH_ACK     :   Recebe confirmação Diffie-Hellman.
    SEND_DATA       :   Envia dados cifrados.
    RECV_DATA       :   Recebe dados cifrados.
    DONE    :   Envia pedido de término de conexão.
    RFT     :   Envia confirmação de término de conexão.        :   Request for Termination
    WDC     :   Aguardando confirmação para término de conexão. :   Waiting Done Confirmation
  

*/
typedef enum {
    SEND_SYN, 
    RECV_SYN,
    SEND_ACK,
    RECV_ACK,
    SEND_RSA, 
    RECV_RSA, 
    SEND_RSA_ACK, 
    RECV_RSA_ACK, 
    SEND_DH, 
    RECV_DH,
    SEND_DH_ACK,
    RECV_DH_ACK,
    SEND_DATA, 
    RECV_DATA, 
    FINISH,
    DONE, 
    RFT, 
    WDC
} States;

typedef enum {
    OK,
    DENIED,
    TIMEOUT,
    NO_REPLY,
    NONCE_INVALID,
    FDR_INVALID,
    HASH_INVALID,
    FINISHED,
} Reply;

#endif