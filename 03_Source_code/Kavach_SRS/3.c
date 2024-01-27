#include <stdint.h>
#include <string.h>
#include <stdio.h>
// Assume AES encryption function is available in a separate library
void AES_encrypt(uint8_t *ciphertext, const uint8_t *plaintext, const uint8_t *key);

// Calculate CBC-MAC using AES
void cbc_mac(uint8_t *mac, const uint8_t *message, size_t message_len, const uint8_t *key) {
    uint8_t block[16];  // Temporary block for encryption
    uint8_t iv[16] = {0};  // Initialization vector (all zeros)
    size_t num_blocks = (message_len + 15) / 16;  // Number of blocks

    // Padding: Add zero bytes to make message length a multiple of 16
    memset(block, 0, 16);  // Clear block for padding
    memcpy(block, message + (num_blocks - 1) * 16, message_len % 16);  // Copy last partial block

    // CBC-MAC calculation
    for (size_t i = 0; i < num_blocks; i++) {
        for (size_t j = 0; j < 16; j++) {
            block[j] ^= iv[j];  // XOR with previous ciphertext or IV
        }
        AES_encrypt(iv, block, key);  // Encrypt the block
    }

    // The MAC is the last ciphertext block
    memcpy(mac, iv, 16);
}

int main() {
    uint8_t message[] = {
        0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4, 0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B,
        0x4A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    size_t message_len = sizeof(message);
    uint8_t key[] = {
0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; //{0
    uint8_t mac[16];

    cbc_mac(mac, message, message_len, key);

    // Print the MAC in hex notation
    for (int i = 0; i < 16; i++) {
        printf("%02X", mac[i]);
    }
    printf("\n");

    return 0;
}
