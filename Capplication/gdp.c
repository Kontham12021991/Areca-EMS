#include "conversions.h"
typedef struct
{
    uint16_t LM_Gradient_Distance;
    uint8_t LM_GDIR;
    uint8_t LM_GRADIENT_VALUE;
} GradietnProfile_cnt;

typedef struct
{
    uint8_t SUB_PKT_TYPE;
    uint8_t SUB_PKT_LENGTH_GRAD;
    uint8_t LM_Grad_Info_CNT;
    GradietnProfile_cnt GDP_CNT[32];
    uint8_t PaddingBits;
} GDP_packet_t;

GDP_packet_t GDP_packet;
// Utility function to append a binary representation of a value to a string.
// void appendBinaryString(char *str, unsigned long value, int bits)
// {
//     for (int i = bits - 1; i >= 0; i--)
//     {
//         strcat(str, ((value >> i) & 1) ? "1" : "0");
//     }
// }

// Create dynamic memory for the given number of elements of GradietnProfile_cnt
void *createDynamicMemory(uint8_t SubPktType, int NoOfElements)
{
    return malloc(NoOfElements * sizeof(GradietnProfile_cnt));
}

// Clear the dynamically allocated memory
void clearDynamicMemory(void *data)
{
    free(data);
}

// // Function to calculate the length of a binary string passed as input
// size_t calculateBinaryStringLength(const char *binaryString) {
//     return strlen(binaryString);
// }

// void add_padding(char *binary_string, char count) {
//     int length = strlen(binary_string);
//     int rem = length % 8;

//     if (rem > 0) {
//         int size = count*40;
//         char pad[size]; // Adjust the size accordingly
//         memset(pad, '0', 8 - rem);
//         pad[8 - rem] = '\0'; // Null-terminate the padding string
//         strcat(pad, binary_string);
//         strcpy(binary_string, pad);
//     }
// }

// // Function to convert a binary character to its hexadecimal equivalent
// char binaryToHex(char *binary_char) {
//     // Convert the binary character to integer
//     int num = strtol(binary_char, NULL, 2);

//     // Convert the integer to hexadecimal character
//     if (num >= 0 && num <= 9) {
//         return num + '0'; // For numbers 0-9
//     } else {
//         return num - 10 + 'A'; // For letters A-F
//     }
// }

// // Function to convert a binary string to a hexadecimal string
// void binaryToHexadecimal(const char *binary_string, char *hex_string) {
//     int binary_length = strlen(binary_string);
//     int hex_length = (binary_length + 3) / 4; // Number of hexadecimal digits needed
//     hex_string[hex_length] = '\0'; // Null-terminate the hexadecimal string

//     int binary_index = 0;
//     int hex_index = 0;

//     while (binary_index < binary_length) {
//         char binary_char[5] = {0}; // Store 4 binary digits and null terminator
//         strncpy(binary_char, binary_string + binary_index, 4); // Get next 4 binary digits

//         hex_string[hex_index++] = binaryToHex(binary_char); // Convert and store in hex string

//         binary_index += 4; // Move to the next group of 4 binary digits
//     }
// }

int main(void)
{
    uint8_t len = 0;
    uint8_t loopvar = 0;

    uint8_t countLoop = 0;
    for (countLoop = 1; countLoop < 32; countLoop++)
    {

        printf("count loop %d\r\n", countLoop);
        char *binaryString = malloc(580 * sizeof(char));

        memset(binaryString, 0, 580 * sizeof(char));

        GDP_packet.LM_Grad_Info_CNT = countLoop;
        for (loopvar = GDP_packet.LM_Grad_Info_CNT; loopvar > 0; loopvar--)
        {
            len = calculateBinaryStringLength(binaryString);

            GDP_packet.GDP_CNT[loopvar - 1].LM_GRADIENT_VALUE = 1;
            appendBinaryString(binaryString, GDP_packet.GDP_CNT[loopvar - 1].LM_GRADIENT_VALUE, 5);
            len = calculateBinaryStringLength(binaryString);

            GDP_packet.GDP_CNT[loopvar - 1].LM_GDIR = 0;
            appendBinaryString(binaryString, GDP_packet.GDP_CNT[loopvar - 1].LM_GDIR, 1);
            len = calculateBinaryStringLength(binaryString);

            GDP_packet.GDP_CNT[loopvar - 1].LM_Gradient_Distance = 1;
            appendBinaryString(binaryString, GDP_packet.GDP_CNT[loopvar - 1].LM_Gradient_Distance, 15);
            len = calculateBinaryStringLength(binaryString);
        }

        uint32_t totalLenbits = len + 5 + 7 + 4;
        printf("totalLenbits %d ", totalLenbits);

        int rem = totalLenbits % 8;
        printf("rem %d ", rem);

        totalLenbits = totalLenbits + 8 - rem;
        printf("totalLenbits %d ", totalLenbits);
        len = totalLenbits / 8;

        // till her we have created the binary string with 21 *2 bits

        appendBinaryString(binaryString, GDP_packet.LM_Grad_Info_CNT, 5);
        GDP_packet.SUB_PKT_LENGTH_GRAD = len;

        appendBinaryString(binaryString, GDP_packet.SUB_PKT_LENGTH_GRAD, 7);

        GDP_packet.SUB_PKT_TYPE = 2;
        appendBinaryString(binaryString, GDP_packet.SUB_PKT_TYPE, 4);
        len = calculateBinaryStringLength(binaryString);
        printf("The length of the binary string is: %zu bits\n", len);

        printf("\r\n GDP packet Binary string %s", binaryString);
        add_padding(binaryString, GDP_packet.LM_Grad_Info_CNT);

        printf("\nBinary string with padding: %s\n", binaryString);

        char hex_string[580 / 4 + 1]; // Maximum possible length of hex string

        binaryToHexadecimal(binaryString, hex_string);
        printf("Hexadecimal string: %s\n", hex_string);
        clearDynamicMemory(binaryString);
    }

    return 0;
}
