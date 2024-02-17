#include <stdint.h>
#include <stdio.h>
typedef struct {
    uint8_t TSR_ID;
    uint16_t TSR_Distance : 15;
    uint16_t TSR_Length : 15;
    uint8_t TSR_Class : 1;
    uint8_t TSR_Universal_Speed : 6;
    uint8_t TSR_Whistle : 2;
} TSR_Data_t;

typedef struct {
    uint8_t SUB_PKT_TYPE : 4;                      
    uint8_t SUB_PKT_LENGTH_H_TSR : 7;
    uint8_t TSR_STATUS : 2;
    uint8_t TSR_Info_CNT : 5;
    TSR_Data_t TSR_Data[5];  // Assuming MAX_TSR_INFO_CNT is defined
} TSRProfile_t;

#define MAX_TSR_INFO_CNT 5  // Adjust based on requirements

uint8_t extractBits(uint8_t byte, uint8_t startBit, uint8_t numBits) {
    // Create a mask with 1's in the desired bits
    uint8_t mask = (1 << numBits) - 1;
    // Shift the mask to the desired position
    mask <<= startBit;
    // Apply the mask to the byte using bitwise AND
    return (byte & mask) >> startBit;
}

void parseTSRData(const uint8_t* data, TSR_Data_t* tsrData) {
   
    // Parsing TSR_Data_t requires careful bit manipulation. Here's an adjusted approach:

    // Construct the TSR_Distance and TSR_Length from the data
    // Note: This assumes data is in big endian format
    
printf("\n-----------raw parseTSRData %X ",data[0]);
    uint32_t firstPart = (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];
    uint16_t secondPart = (data[5] << 4) | data[5];
    printf("\n firstbyte %X ",firstPart);
    printf("\n secondbyte %X ",secondPart);

    tsrData->TSR_ID = data[0];
    tsrData->TSR_Distance = extractBits(firstPart,0, 15); // Extract bits for TSR_Distance
    tsrData->TSR_Length = ((firstPart & 0x1FFFF) << 4) | (secondPart >> 28);  // Extract bits for TSR_Length
    tsrData->TSR_Class = (secondPart >> 27) & 0x01;
    tsrData->TSR_Universal_Speed = (secondPart >> 21) & 0x3F;
    tsrData->TSR_Whistle = (secondPart >> 19) & 0x03;
}
void reverseBuffer(uint8_t* buffer, size_t size) {
    for (size_t i = 0; i < size / 2; ++i) {

void parseData(const uint8_t* rawData) {
    TSRProfile_t TSRProfile;
     uint32_t index=2 ;

printf("\n-----------raw data %X ",rawData[index]);
    // Parse the header
    // extract the firt four bits from rawData[0]

    TSRProfile.SUB_PKT_TYPE = (rawData[index] & 0x0f);  //4 

    TSRProfile.SUB_PKT_LENGTH_H_TSR = (extractBits(rawData[1],0,3)<<4)|extractBits(rawData[0],4,4); //11
    TSRProfile.TSR_STATUS = extractBits(rawData[1],4,2); //13
 
    // 00 [100 00 (001 ]1010) 0111
    TSRProfile.TSR_Info_CNT = (extractBits(rawData[2],0,3)<<3)|extractBits(rawData[1],5,3); // 5 , 

    // Printing parsed data for verification
    printf("\n SUB_PKT_TYPE: %X\n", TSRProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_H_TSR: %X\n", TSRProfile.SUB_PKT_LENGTH_H_TSR);
    printf("TSR_STATUS: %u\n", TSRProfile.TSR_STATUS);
    printf("TSR_Info_CNT: %u\n", TSRProfile.TSR_Info_CNT);
    for (uint8_t i = 0; i < TSRProfile.TSR_Info_CNT; ++i) {
    uint16_t IDtemp = (rawData[4] << 8) | rawData[3];
  
    // Assuming buffer points to the start of a TSR_Data_t encoded sequence
    TSRProfile.TSR_Data[i].TSR_ID = (extractBits(rawData[3],0,1)<<1)|extractBits(rawData[2],1,7); // 5 , 
    
    uint32_t temp = (rawData[4] << 24) | (rawData[5] << 16) | (rawData[6] << 8) | rawData[7];
    
    // Extract TSR_Distance (15 bits right after TSR_ID)
    TSRProfile.TSR_Data[i].TSR_Distance = (temp >> 17) & 0x7FFF;
    
    // Extract TSR_Length (next 15 bits)
    TSRProfile.TSR_Data[i].TSR_Length = (temp >> 2) & 0x7FFF;
    
    // Extract TSR_Class (1 bit)
    TSRProfile.TSR_Data[i].TSR_Class = (temp >> 1) & 0x01;
    
    // Moving to next byte for TSR_Universal_Speed and TSR_Whistle, use buffer[4] and buffer[5]
    uint8_t nextByte = rawData[8];
    
    // Extract TSR_Universal_Speed (6 bits)
    TSRProfile.TSR_Data[i].TSR_Universal_Speed = nextByte >> 2;
    
    // Extract TSR_Whistle (last 2 bits)
    TSRProfile.TSR_Data[i].TSR_Whistle = nextByte & 0x03;
    printf("TSR_ID: %u\n", TSRProfile.TSR_Data[i].TSR_ID);
    // printf("TSR_Distance: %u\n", TSRProfile.TSR_Data[i].TSR_Distance);
    // printf("TSR_Length: %u\n", TSRProfile.TSR_Data[i].TSR_Length);
    // printf("TSR_Class: %u\n", TSRProfile.TSR_Data[i].TSR_Class);
    // printf("TSR_Universal_Speed: %u\n", TSRProfile.TSR_Data[i].TSR_Universal_Speed);
    // printf("TSR_Whistle: %u\n", TSRProfile.TSR_Data[i].TSR_Whistle);
    }



   
}
        uint8_t temp = buffer[i];
        buffer[i] = buffer[size - 1 - i];
        buffer[size - 1 - i] = temp;
    }
}

int main() {
    uint8_t buffer[] = {0x01, 0x40, 0x4B, 0x40, 0x96, 0x37, 0x82, 0x80, 0x96, 0x81, 0x2C, 0x6F, 0x05, 0x01, 0x2D, 0x02, 0x58, 0xDE, 0x0A, 0x02, 0x5A, 0x04, 0xB1, 0xBC, 0x81, 0xA7};
    reverseBuffer(buffer, 26);
        printf("Byte Array: ");
    for (size_t i = 0; i < 27; ++i) {
        printf("%02X ", buffer[i]);
    }

    uint8_t *ptr = buffer;  // Pointer to traverse the buffer
    TSRProfile_t tsrProfile;
// Assign data to the TSRProfile_t structure
tsrProfile.SUB_PKT_TYPE = *ptr & 0x0f;  // Extract bits 7-4(first_byte & 0xF0) >> 4
tsrProfile.SUB_PKT_LENGTH_H_TSR = *ptr & 0x7F; // Extract bits 3-0
ptr++;
tsrProfile.TSR_STATUS = (*ptr >> 6) & 0x03;   // Extract bits 7-6
tsrProfile.TSR_Info_CNT = (*ptr >> 1) & 0x1F;  // Extract bits 5-1
ptr++;
   // Printing parsed data for verification
    printf("\n SUB_PKT_TYPE: %X\n", tsrProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_H_TSR: %X\n", tsrProfile.SUB_PKT_LENGTH_H_TSR);
    printf("TSR_STATUS: %u\n", tsrProfile.TSR_STATUS);
    printf("TSR_Info_CNT: %u\n", tsrProfile.TSR_Info_CNT);
// Assign data to TSR_Data array
for (int i = 0; i < tsrProfile.TSR_Info_CNT; i++) {
    tsrProfile.TSR_Data[i].TSR_ID = *ptr++;
    // Combine two bytes for 15-bit fields using bit shifting and masking
    tsrProfile.TSR_Data[i].TSR_Distance = (*ptr << 7) | (*(ptr + 1) >> 1);
    ptr += 2;
    tsrProfile.TSR_Data[i].TSR_Length = (*ptr << 7) | (*(ptr + 1) >> 1);
    ptr += 2;
    tsrProfile.TSR_Data[i].TSR_Class = (*ptr >> 7) & 0x01;
    tsrProfile.TSR_Data[i].TSR_Universal_Speed = (*ptr >> 1) & 0x3F;
    tsrProfile.TSR_Data[i].TSR_Whistle = *ptr & 0x03;
    ptr++;
    printf("TSR_ID: %u\n", tsrProfile.TSR_Data[i].TSR_ID);
}
    // Parse the buffer
    // parseData(buffer);

    return 0;
}