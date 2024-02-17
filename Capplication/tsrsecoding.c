#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define TSR_INFO_CNT 32

typedef struct
{
    uint8_t TSR_ID;
    uint16_t TSR_Distance : 15;
    uint16_t TSR_Length : 15;
    uint8_t TSR_Class : 1;
    uint8_t TSR_Universal_Speed : 6;
    uint8_t TSR_Whistle : 2;
} TSR_Data_t;

typedef struct
{
    uint8_t SUB_PKT_TYPE : 4;                      // 7
    uint8_t SUB_PKT_LENGTH_H_TSR : 7;
    uint8_t TSR_STATUS : 2;
    uint8_t TSR_Info_CNT : 5;
    TSR_Data_t TSR_Data[TSR_INFO_CNT];
} TSRProfile_t;

static TSRProfile_t TSRProfile;

// Function to convert a hexadecimal character to its integer equivalent
uint8_t hexToDecimal(char hexChar) {
    if (hexChar >= '0' && hexChar <= '9') {
        return hexChar - '0';
    } else if (hexChar >= 'A' && hexChar <= 'F') {
        return hexChar - 'A' + 10;
    } else if (hexChar >= 'a' && hexChar <= 'f') {
        return hexChar - 'a' + 10;
    }
    return 0; // Invalid character
}

// Function to convert a hexadecimal string to a byte array
void hexStringToByteArray(const char* hexString, uint8_t* byteArray, size_t length) {
    size_t len = length;
    if (len % 2 != 0) {
        printf("Hex string length must be even\n");
        return;
    }

    for (size_t i = 0, j = len - 1; i < len; i += 2, --j) {
        byteArray[j] = (hexToDecimal(hexString[i]) << 4) | hexToDecimal(hexString[i + 1]);
    }
}
uint8_t extractBits(uint8_t byte, uint8_t startBit, uint8_t numBits) {
    // Create a mask with 1's in the desired bits
    uint8_t mask = (1 << numBits) - 1;
    // Shift the mask to the desired position
    mask <<= startBit;
    // Apply the mask to the byte using bitwise AND
    return (byte & mask) >> startBit;
}

void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
     char* hexString = "01404B409637828096812C6F05012D0258DE0A025A04B1BC81A7";
    reverse_string(hexString);
    printf("%s\n", hexString);
    
    char* mutableString = strdup(hexString); // Create a mutable copy
    if (mutableString == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }
  //  reverse_string(mutableString);
    printf("%s\n", mutableString);


    size_t hexStringLength = strlen(mutableString);
    size_t byteArraySize = hexStringLength / 2;
    uint8_t byteArray[byteArraySize];
    // Convert hex string to byte array
    for (size_t i = 0, j = 0; i < hexStringLength; i += 2, ++j) {
        char hex[3] = {mutableString[i], mutableString[i + 1], '\0'};
        byteArray[j] = strtol(hex, NULL, 16);
    }
    printf("\n");
    // for (size_t i = 0, j = byteArraySize - 1; i < j; i++, j--) {
    //     uint8_t temp = byteArray[i];   
    //     byteArray[i] = byteArray[j];
    //     byteArray[j] = temp;
    // }
            // Print the resulting byte array
    printf("Byte Array: ");
    for (size_t i = 0; i < byteArraySize; ++i) {
        printf("%02X ", byteArray[i]);
    }

// assign the byte array to structure dont use memcpy 

    TSRProfile.SUB_PKT_TYPE =extractBits(byteArray[byteArraySize-1],0, 4);;  //4 BITS 
     printf("\n SUB_PKT_TYPE: %02X\n", TSRProfile.SUB_PKT_TYPE);
    // assign data TSRProfile.SUB_PKT_LENGTH_H_TSR from byte array 0 and 1 take 7 bits 
    uint8_t lowernibble =0;
    uint8_t highernibble =0;
    lowernibble  =  extractBits(byteArray[byteArraySize-1],4, 4); // 4 BITS 
    highernibble = extractBits(byteArray[byteArraySize-2],0, 3); // 1 3 BITS

    printf("\n lowernibble %d , %d", lowernibble, highernibble);

    TSRProfile.SUB_PKT_LENGTH_H_TSR = (highernibble << 4) | lowernibble;
    // assign data TSRProfile.TSR_STATUS from byte array 1 and 2 take 2 bits 
    TSRProfile.TSR_STATUS =extractBits(byteArray[byteArraySize-2],3, 2); // 1 3 BITS5, 2); // 2
      printf("TSR_STATUS: %02X\n", TSRProfile.TSR_STATUS);
    
  
    // assign data TSRProfile.TSR_Info_CNT from byte array 1 and 2 take 5 bits 
    TSRProfile.TSR_Info_CNT = extractBits(byteArray[byteArraySize-3],0, 3)<<4|extractBits(byteArray[byteArraySize-2],6, 2);

   // 01404B409637828096812C6F05012D0258DE0A025A04B1BC81A7
    // Print the resulting structure
  
    printf("TSR_Info_CNT: %02X\n", TSRProfile.TSR_Info_CNT);
    // sim

    for ( size_t i = 0; i < TSRProfile.TSR_Info_CNT; ++i) {
        TSRProfile.TSR_Data[i].TSR_Distance = extractBits(byteArray[i],0, 15);
        TSRProfile.TSR_Data[i].TSR_Length = extractBits(byteArray[i],15, 15);
        TSRProfile.TSR_Data[i].TSR_ID = extractBits(byteArray[i],30, 8);
        TSRProfile.TSR_Data[i].TSR_Class = extractBits(byteArray[i],38, 1);
        TSRProfile.TSR_Data[i].TSR_Universal_Speed = extractBits(byteArray[i],39, 6);
        TSRProfile.TSR_Data[i].TSR_Whistle = extractBits(byteArray[i],45, 2);
        printf("TSR_Data[%d]: %02X\n", i, TSRProfile.TSR_Data[i].TSR_Distance);
    }

    free(mutableString); // Free the allocated memor
    return 0;
}
