#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 24

void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    // AES encryption code
    // write Aes code 
    // return the encrypted data
    //

}

void cbc_mac(unsigned char *message, int message_len, unsigned char *key, unsigned char *mac) {
    int i, j;
    int num_blocks = message_len / BLOCK_SIZE;
    printf("%d",num_blocks);
    unsigned char padded_message[BLOCK_SIZE * (num_blocks + 1)];
    unsigned char iv[BLOCK_SIZE] = {0};

    // Pad the message with zero bits
    memcpy(padded_message, message, message_len);
    memset(padded_message + message_len, 0, BLOCK_SIZE * (num_blocks + 1) - message_len);

    // Encrypt the padded message using AES in CBC mode
    for (i = 0; i < num_blocks; i++) {
        for (j = 0; j < BLOCK_SIZE; j++) {
            padded_message[i * BLOCK_SIZE + j] ^= iv[j];
        }
        aes_encrypt(padded_message + i * BLOCK_SIZE, mac, key);
        memcpy(iv, mac, BLOCK_SIZE);
    }
}

int main() {
    unsigned char message[24] = {0xB3, 0x2A, 0xB7, 0xF0, 0x21, 0x04, 0x09, 0xD4,
                               0x90, 0x41, 0x1A, 0x80, 0xCC, 0x16, 0x08, 0x2B, 
                               0x4A, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    int message_len = 232;
    unsigned char key[] = {
0x18, 0x48,0x2C ,0x7E ,0x5A ,0xA2 ,0x33 ,0x05 ,0x71 ,0x38 ,0x68 ,0xA5 ,0x06 ,0xAB ,0x4F ,0x15}; //{0x71, 0xA3, 0x4F, 0xD9, 0x9E, 0xC2, 0xC4, 0xDD, 0x3E, 0xAB, 0x37, 0x65, 0xB7, 0x11, 0x0F, 0xB6};
    unsigned char mac[BLOCK_SIZE];
    unsigned char final_data[message_len / 8 + BLOCK_SIZE];

    // Calculate the CBC-MAC
    cbc_mac(message, message_len / 8, key, mac);

    // Print the MAC code
    printf("The MAC code is: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X", mac[i]);
    }
    printf("\n");

    // Calculate the CRC-32 bit
    unsigned int crc = 0xFFFFFFFF;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        crc ^= mac[i];
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc >>= 1;
            }
        }
    }
    crc ^= 0xFFFFFFFF;

    // Print the CRC-32 bit
    printf("The CRC-32 bit is: %08X\n", crc);
    // Calculate the correct number of bytes to copy
    size_t bytes_to_copy = message_len < 32 ? message_len : 32;  // Copy at most 32 bytes

    // Copy the message to final_data, ensuring no overread
    memcpy(final_data, message, bytes_to_copy);

    memcpy(final_data + message_len / 8, mac, BLOCK_SIZE);
    memcpy(final_data + message_len / 8 + BLOCK_SIZE, &crc, sizeof(crc));

    // Print the final data
    printf("The final data is: ");
    for (int i = 0; i < message_len / 8 + BLOCK_SIZE + sizeof(crc); i++) {
        printf("%02X", final_data[i]);
    }
    printf("\n");

    return 0;
}
