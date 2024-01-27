#include <stdio.h>
#include <openssl/evp.h>
#include <string.h>

#define AES_BLOCK_SIZE 16

// Function to pad the message with zeros up to a multiple of AES block size
void pad_message(uint8_t *message, size_t message_len, uint8_t *padded_message) {
    size_t padding_len = AES_BLOCK_SIZE - (message_len % AES_BLOCK_SIZE);
    memcpy(padded_message, message, message_len);
    memset(padded_message + message_len, 0, padding_len);
}

// Function to calculate the MAC code using CBC-MAC with AES-128
void calculate_mac(uint8_t *message, size_t message_len, const uint8_t *key, uint8_t *mac) {
    int padding_len;
    uint8_t iv[AES_BLOCK_SIZE];
    uint8_t padded_message[message_len + AES_BLOCK_SIZE];
    int out_len;

    EVP_CIPHER_CTX *aes_cipher = EVP_CIPHER_CTX_new();  // Use EVP_CIPHER_CTX_new for context

    if (!aes_cipher) {
        printf("Error creating AES cipher context\n");
        return;
    }

    // Initialize IV with zeros
    memset(iv, 0, AES_BLOCK_SIZE);
    // Pad the message
    pad_message(message, message_len, padded_message);
    // Initialize AES cipher context for CBC mode
    if (!EVP_CipherInit_ex(aes_cipher, EVP_aes_128_cbc(), NULL, key, iv, 1)) {
        printf("Error initializing AES cipher\n");
        EVP_CIPHER_CTX_free(aes_cipher);
        return;
    }

 // Update the cipher with all message blocks
    for (size_t i = 0; i < (message_len + padding_len) / AES_BLOCK_SIZE; i++) {
        if (!EVP_CipherUpdate(aes_cipher, mac, &out_len, padded_message + i * AES_BLOCK_SIZE, AES_BLOCK_SIZE)) {
            printf("Error during cipher update\n");
            EVP_CIPHER_CTX_free(aes_cipher);
            return;
        }
    }
        // Finalize the cipher and get the MAC code
    if (!EVP_CipherFinal_ex(aes_cipher, mac, &padding_len)) {
        printf("Error during cipher finalization\n");
        EVP_CIPHER_CTX_free(aes_cipher);
        return;
    }
      printf("MAC: %X\n", mac);

    // Clean up
    EVP_CIPHER_CTX_free(aes_cipher);

    // Extract the actual MAC size
     printf("padding_len: %X\n", padding_len);
    if (padding_len > 0) {
        mac[padding_len] = '\0';
    }
}


// int main() {
//     unsigned char message[] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4,
//                                0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B,
//                                0x4A, 0x04};  // Remove trailing zeros
//     size_t message_len = sizeof(message);
//     // ... (key and mac declarations remain the same)
//     uint8_t mac[AES_BLOCK_SIZE];
//     uint8_t key[] = {0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; 
//     calculate_mac(message, message_len, key, mac);

//     printf("The number of times MAC loop was run: %zu\n", message_len / AES_BLOCK_SIZE);
//     printf("MAC Code: %X\n", mac);

//     // Calculate CRC (replace with your actual CRC implementation)
//     uint32_t crc = calculate_crc32(message, message_len);
//     printf("CRC 32 bit: %08X\n", crc);

//     printf("Final data: ");
//     for (size_t i = 0; i < message_len; i++) {
//         printf("%02X", message[i]);
//     }
//     printf("%02X%02X%02X%02X %08X\n", mac[0], mac[1], mac[2], mac[3], crc);

//     return 0;
// }
int main() {
    unsigned char message[] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4,
                               0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B, 
                               0x4A, 0x04};
                               
    size_t message_len = sizeof(message) - 1; // Exclude null terminator


   // uint8_t key[] = {0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; 
    
    uint8_t key[]= {0x75 ,0x46 ,0x20 ,0x67 ,0x6E ,0x75 ,0x4B ,0x20 ,0x79 ,0x6D ,0x20 ,0x73 ,0x74 ,0x61 ,0x68  ,0x54};
    uint8_t mac[AES_BLOCK_SIZE];

    calculate_mac(message, message_len, key, mac);

    printf("Message: %x\n", message);
    printf("MAC: %X\n", mac);

    return 0;
}
