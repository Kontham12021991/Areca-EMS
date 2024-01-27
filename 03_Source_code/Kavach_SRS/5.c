#include <openssl/evp.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <openssl/rand.h>  // For random number generation

#define KEY_SIZE 16
#define BLOCK_SIZE 16

void cbc_mac(unsigned char *message, int message_len, unsigned char *key, unsigned char *mac) {
    EVP_CIPHER_CTX *ctx;
    unsigned char iv[BLOCK_SIZE];
    int out_len;

    // // Generate random IV
    // RAND_bytes(iv, BLOCK_SIZE);

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_192_cbc(), NULL, key, iv);

    for (int i = 0; i < message_len / BLOCK_SIZE; i++) {
        unsigned char block[BLOCK_SIZE];
        memcpy(block, message + i * BLOCK_SIZE, BLOCK_SIZE);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= (i == 0) ? iv[j] : mac[j];
        }
        EVP_EncryptUpdate(ctx, mac, &out_len, block, BLOCK_SIZE);
    }

    EVP_CIPHER_CTX_free(ctx);
}

// void cbc_mac(unsigned char *message, int message_len, unsigned char *key, unsigned char *mac) {
//     EVP_CIPHER_CTX *ctx;
//     unsigned char iv[BLOCK_SIZE];
//     int out_len, final_len;
//    // Generate random IV
//     RAND_bytes(iv, BLOCK_SIZE);

//     EVP_CIPHER_CTX_init(ctx);
//     EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);


//     for (int i = 0; i < message_len / BLOCK_SIZE; i++) {
//         unsigned char block[BLOCK_SIZE];
//         memcpy(block, message + i * BLOCK_SIZE, BLOCK_SIZE);
//         for (int j = 0; j < BLOCK_SIZE; j++) {
//             block[j] ^= (i == 0) ? iv[j] : mac[j];
//         }
//         EVP_EncryptUpdate(ctx, mac, &out_len, block, BLOCK_SIZE);
//         memcpy(mac, mac + out_len, BLOCK_SIZE);
//     }

//         for (int i = 0; i < BLOCK_SIZE; i++) {
//         printf("%02x", mac[i]);
//     }
//     EVP_EncryptFinal_ex(ctx, mac + BLOCK_SIZE - final_len, &final_len);
//     mac[BLOCK_SIZE] = '\0';

//     EVP_CIPHER_CTX_cleanup(ctx);
// }

int main() {
    unsigned char mac[BLOCK_SIZE + 1];
    unsigned char data[] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4,
                            0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B,
                            0x4A, 0x04};
 uint8_t key[] = {0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; 
// uint8_t key[]= {0x75 ,0x46 ,0x20 ,0x67 ,0x6E ,0x75 ,0x4B ,0x20 ,0x79 ,0x6D ,0x20 ,0x73 ,0x74 ,0x61 ,0x68  ,0x54};

   cbc_mac(data, sizeof(data), key, mac);

     // Print MAC in hexadecimal format
    for (int i = 0; i < 16; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");
    return 0;
}

// // Example usage:
// int main() {
//     unsigned char data[] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4,
//                             0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B,
//                             0x4A, 0x04};
//  //uint8_t key[] = {0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; 
//  uint8_t key[]= {0x75 ,0x46 ,0x20 ,0x67 ,0x6E ,0x75 ,0x4B ,0x20 ,0x79 ,0x6D ,0x20 ,0x73 ,0x74 ,0x61 ,0x68  ,0x54};

//     unsigned char mac[AES_BLOCK_SIZE];

//     generate_cbc_mac(data, sizeof(data), key, mac);

//     // Print the generated MAC (replace with appropriate output method)
//     printf("MAC: ");
//     for (int i = 0; i < AES_BLOCK_SIZE; i++) {
//         printf("%02x", mac[i]);
//     }
//     printf("\n");

//     return 0;
// }
