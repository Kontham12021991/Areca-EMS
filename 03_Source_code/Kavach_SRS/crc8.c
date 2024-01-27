#include <stdio.h>

unsigned char calculate_crc(unsigned char* data, int length) {
    unsigned char crc = 0xFF;
    for(int i = 0; i < length; i++) {
        crc ^= data[i];
    }
    return crc;
}



int main() {
    unsigned char data[] = {01, 01, 01, 01, 12,24};
    int length = sizeof(data)/sizeof(data[0]);
    printf("%d ", length );
    unsigned char crc = calculate_crc(data, length);
    printf("The 8-bit CRC of the input data is: 0x%02X\n", crc);
    return 0;
}
