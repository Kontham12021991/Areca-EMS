#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>

void encrypt_data(const char *key_hex, const char *data_hex, const char *iv_hex, unsigned char *result) {
    // Convert hex strings to binary data
    unsigned char key[16];
    unsigned char data[32];
    unsigned char iv[16];

    sscanf(key_hex, "%32s", key);
    sscanf(data_hex, "%32s", data);
    sscanf(iv_hex, "%32s", iv);

    // Pad the data to a multiple of AES block size
    int data_len = strlen(data) / 2;
    int padded_len = (data_len / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    unsigned char *padded_data = malloc(padded_len);
    memset(padded_data, 0, padded_len);
    memcpy(padded_data, data, data_len);

    // Create a cipher object
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    // Encrypt the data
    AES_cbc_encrypt(padded_data, result, padded_len, &aes_key, iv, AES_ENCRYPT);

    free(padded_data);
}

int main() {
    const char *key = "754620676E754B20796D207374616854";
    const char *original_data = "774DB97A774DB97AB97A774DB97A774D";
    const char *iv_hex = "00000000000000000000000000000000";

    // Encrypt the data
    unsigned char ciphertext[32];
    encrypt_data(key, original_data, iv_hex, ciphertext);

    // Print the encrypted data in hex
    printf("encrypted data: ");
    for (int i = 0; i < 32; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

