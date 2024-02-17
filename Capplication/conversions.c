// Utility function to append a binary representation of a value to a string.

#include "conversions.h"
void appendBinaryString(uint8_t *str, unsigned long value, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        strcat(str, ((value >> i) & 1) ? "1" : "0");
    }
}

// Clear the dynamically allocated memory
void clearDynamicMemory(void *data)
{
    free(data);
}


// Function to calculate the length of a binary string passed as input
size_t calculateBinaryStringLength(const uint8_t *binaryString) {
    return strlen(binaryString);
}


void add_padding(uint8_t *binary_string, uint8_t count) {
    int length = strlen(binary_string);
    int rem = length % 8;

    if (rem > 0) {
        int size = count*40;
        uint8_t pad[size]; // Adjust the size accordingly
        memset(pad, '0', 8 - rem);
        pad[8 - rem] = '\0'; // Null-terminate the padding string
        strcat(pad, binary_string);
        strcpy(binary_string, pad);
    }
}

// Function to convert a binary uint8_tacter to its hexadecimal equivalent
uint8_t binaryToHex(uint8_t *binary_char) {
    // Convert the binary character to integer
    int num = strtol(binary_char, NULL, 2);

    // Convert the integer to hexadecimal character
    if (num >= 0 && num <= 9) {
        return num + '0'; // For numbers 0-9
    } else {
        return num - 10 + 'A'; // For letters A-F
    }
}

// Function to convert a binary string to a hexadecimal string
void binaryToHexadecimal(const uint8_t *binary_string, uint8_t *hex_string) {
    int binary_length = strlen(binary_string);
    int hex_length = (binary_length + 3) / 4; // Number of hexadecimal digits needed
    hex_string[hex_length] = '\0'; // Null-terminate the hexadecimal string

    int binary_index = 0;
    int hex_index = 0;

    while (binary_index < binary_length) {
        uint8_t binary_char[5] = {0}; // Store 4 binary digits and null terminator
        strncpy(binary_char, binary_string + binary_index, 4); // Get next 4 binary digits

        hex_string[hex_index++] = binaryToHex(binary_char); // Convert and store in hex string

        binary_index += 4; // Move to the next group of 4 binary digits
    }
}
