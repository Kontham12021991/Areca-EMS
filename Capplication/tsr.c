#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define TSR_INFO_CNT 32
#define TSR_PACKET 0x07
#define TSR_N 5
typedef struct
{
    uint8_t TSR_ID;
    uint16_t TSR_Distance:15;
    uint16_t TSR_Length:15;
    uint8_t TSR_Class:1;
    uint8_t TSR_Universal_Speed:6;
    uint8_t TSR_Whistle : 2;
} TSR_Data_t;
typedef struct
{
    uint8_t SUB_PKT_TYPE :4;
    uint8_t SUB_PKT_LENGTH_H_TSR :7;
    uint8_t TSR_STATUS:2;
    uint8_t TSR_Info_CNT:5;
    TSR_Data_t TSR_Data[TSR_INFO_CNT];
} TSRProfile_t;

static TSRProfile_t TSRProfile;
void appendBinaryString(uint8_t *str, unsigned long value, int bits)
{
    for (int i = bits - 1; i >= 0; i--)
    {
        strcat(str, ((value >> i) & 1) ? "1" : "0");
    }
    // printf("\r\n TSR packet Binary string %s", str);
}

// Clear the dynamically allocated memory
void clearDynamicMemory(void *data)
{
    free(data);
}

// Function to calculate the length of a binary string passed as input
size_t calculateBinaryStringLength(const uint8_t *binaryString)
{
    return strlen(binaryString);
}

void add_padding(uint8_t *binary_string, uint32_t count)
{
    uint32_t length = strlen(binary_string);
    printf("\n add_padding length= %d", length);
    uint32_t rem = length % 8;
    printf("\n add_padding = %d", rem);

    if (rem > 0)
    {
        int size = count * 2;
        uint8_t pad[size]; // Adjust the size accordingly
        memset(pad, '0', size * sizeof(char));
        pad[8 - rem] = '\0'; // Null-terminate the padding string
        printf("\n Binary string after loop: in addpadding function  %s\n", binary_string);

        strcat(pad, binary_string);
        strcpy(binary_string, pad);
        printf("\n Binary string after loop: in addpadding function  %s\n", binary_string);
    }
}
// Function to convert a binary uint8_tacter to its hexadecimal equivalent
uint8_t binaryToHex(uint8_t *binary_char)
{
    // Convert the binary character to integer
    int num = strtol(binary_char, NULL, 2);

    // Convert the integer to hexadecimal character
    if (num >= 0 && num <= 9)
    {
        return num + '0'; // For numbers 0-9
    }
    else
    {
        return num - 10 + 'A'; // For letters A-F
    }
}

// Function to convert a binary string to a hexadecimal string
void binaryToHexadecimal(const uint8_t *binary_string, uint8_t *hex_string)
{
    int binary_length = strlen(binary_string);
    int hex_length = (binary_length + 3) / 4; // Number of hexadecimal digits needed
    hex_string[hex_length] = '\0';            // Null-terminate the hexadecimal string

    int binary_index = 0;
    int hex_index = 0;

    while (binary_index < binary_length)
    {
        uint8_t binary_char[5] = {0};                          // Store 4 binary digits and null terminator
        strncpy(binary_char, binary_string + binary_index, 4); // Get next 4 binary digits

        hex_string[hex_index++] = binaryToHex(binary_char); // Convert and store in hex string

        binary_index += 4; // Move to the next group of 4 binary digits
    }
}

int main(void)
{
    uint32_t len = 0;
    uint8_t loopvar = 0;
    uint8_t cnt = 2;
    uint8_t countLoop = 0;
    uint32_t totalbits = 0;

    printf("count loop %d\r\n", countLoop);
    uint8_t *binaryString = malloc(1000 * sizeof(uint8_t));

    memset(binaryString, 0, 1000 * sizeof(uint8_t));
    if (binaryString == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    TSRProfile.TSR_Info_CNT = 4;

    for (loopvar = TSRProfile.TSR_Info_CNT; loopvar > 0; loopvar--)
    {
        len = calculateBinaryStringLength(binaryString);
        printf("\nBinary string after loop: %s\n", binaryString);
        // printf("\r\n Length %d ",len);
        TSRProfile.TSR_Data[loopvar - 1].TSR_Whistle = 0;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_Whistle, 2);
        printf("\nBinary string after loopTSR_Whistle : %s\n", binaryString);
        
        len =calculateBinaryStringLength(binaryString);   
        
        TSRProfile.TSR_Data[loopvar - 1].TSR_Universal_Speed = 5;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_Universal_Speed, 6);
        printf("\nBinary string after loop: TSR_Universal_Speed %s\n", binaryString);
         len =calculateBinaryStringLength(binaryString);
        TSRProfile.TSR_Data[loopvar - 1].TSR_Class = 0;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_Class, 1);
        printf("\nBinary string after loop:TSR_Class  %s\n", binaryString);
         len =calculateBinaryStringLength(binaryString);
        TSRProfile.TSR_Data[loopvar - 1].TSR_Length = 301;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_Length, 15);
        printf("\nBinary string after loop: TSR_Length %s\n", binaryString);
        
         len =calculateBinaryStringLength(binaryString);
        TSRProfile.TSR_Data[loopvar - 1].TSR_Distance = 300;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_Distance, 15);
        printf("\nBinary string after loop: TSR_Distance %s\n", binaryString);
        len =calculateBinaryStringLength(binaryString);
        TSRProfile.TSR_Data[loopvar - 1].TSR_ID = 111;
        appendBinaryString(binaryString, TSRProfile.TSR_Data[loopvar - 1].TSR_ID, 8);
        printf("\nBinary string after loop: TSR_ID %s\n", binaryString);
         len =calculateBinaryStringLength(binaryString);
    }

    printf("\r\n Length %d ", len);
    uint32_t totalLenbits = len + 5 + 2 + 7 + 4;
    printf("\n For calculating tem totalLenbits %d ", totalLenbits);

    int rem = totalLenbits % 8;
    printf("\n rem %d ", rem);

    if (rem != 0)
    {
        totalLenbits = totalLenbits + 8 - rem;
        len = totalLenbits / 8;
    }
    else
    {
        totalLenbits = totalLenbits;
        len = totalLenbits / 8;
    }
    // till her we have created the binary string with 21 *2 bits
    TSRProfile.TSR_STATUS = cnt;
    appendBinaryString(binaryString, TSRProfile.TSR_Info_CNT, 5);
    TSRProfile.TSR_STATUS = 0;
    appendBinaryString(binaryString, TSRProfile.TSR_STATUS, 2);
    TSRProfile.SUB_PKT_LENGTH_H_TSR = len;
    printf("TSRProfile.SUB_PKT_LENGTH_H_TSR == %d\n ", TSRProfile.SUB_PKT_LENGTH_H_TSR);
    appendBinaryString(binaryString, TSRProfile.SUB_PKT_LENGTH_H_TSR, 7);
    TSRProfile.SUB_PKT_TYPE = TSR_PACKET;
    appendBinaryString(binaryString, TSRProfile.SUB_PKT_TYPE, 4);

    len = calculateBinaryStringLength(binaryString);
    printf("\nThe length of the binary string is: %zu bits\n", len);

    printf("\r\n GDP packet Binary string %s", binaryString);
    add_padding(binaryString, totalLenbits);
    len = calculateBinaryStringLength(binaryString);
    printf("\r\n Length %d ", len);

    printf("\nBinary string with padding: %s\n", binaryString);

    char hex_string[1000 / 4 + 1]; // Maximum possible length of hex string

    binaryToHexadecimal(binaryString, hex_string);
    printf("Hexadecimal string: %s\n", hex_string);
    clearDynamicMemory(binaryString);

    return 0;
}
