#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <openssl/rand.h>

#define KEY_SIZE 16
#define BLOCK_SIZE 16

void cbc_mac(unsigned char *message, int message_len, unsigned char *key, unsigned char *mac) {
    EVP_CIPHER_CTX *ctx;
    unsigned char iv[BLOCK_SIZE];
    int out_len;

    // Generate random IV
    RAND_bytes(iv, BLOCK_SIZE);

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    // Padding the message with zero bits
    int padded_len = ((message_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    unsigned char *padded_message = (unsigned char *)malloc(padded_len);
    memcpy(padded_message, message, message_len);
    memset(padded_message + message_len, 0, padded_len - message_len);

    // CBC-MAC calculation
    for (int i = 0; i < padded_len / BLOCK_SIZE; i++) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, padded_message + i * BLOCK_SIZE, BLOCK_SIZE);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= (i == 0) ? iv[j] : mac[j];
        }
        EVP_EncryptUpdate(ctx, mac, &out_len, block, BLOCK_SIZE);
    }

    EVP_CIPHER_CTX_free(ctx);
    free(padded_message);
}

int main() {
    unsigned char data[] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4, 0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B, 0x4A, 0x04};
    unsigned char key[] = {0x18, 0x48, 0x2C, 0x7E, 0x5A, 0xA2, 0x33, 0x05, 0x71, 0x38, 0x68, 0xA5, 0x06, 0xAB, 0x4F, 0x15};
    unsigned char mac[BLOCK_SIZE];
    cbc_mac(data, sizeof(data), key, mac);

    // Print the MAC in hexadecimal format
    printf("MAC: ");
    for (int i = 0; i < 128; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");

    return 0;
}
