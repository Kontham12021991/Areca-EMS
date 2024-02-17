#ifndef SESSIONKEY_H
#define SESSIONKEY_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>


int encrypt_aes_ecb(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *ciphertext);
void storeInGlobalBuffer(const unsigned char *data, size_t len);
#endif