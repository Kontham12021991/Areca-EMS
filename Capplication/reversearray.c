#include <stdio.h>
 const unsigned char databuf[] = {
    0x08, 0x00, 0x30, 0x3A, 0x14, 0x8D, 0x84, 0x04, 0x04, 0xFE, 0xA2, 0x86, 0x90, 0xEE, 0x07, 0x00,
    0x00, 0x20, 0x00, 0x80, 0xBB, 0xB9, 0x0B, 0x78, 0xEE, 0x42, 0x10, 0x00, 0x01, 0x00, 0x62, 0x32, 0x01,
    0x38, 0x4A, 0x53, 0x20, 0xC5, 0x88, 0x20, 0x5F, 0xE7, 0x3B, 0x01, 0x60, 0x02, 0x00, 0x80, 0x7D, 0x76,
    0x88, 0x7A, 0x0D, 0x7C, 0x54, 0x08, 0x6C, 0x07, 0x13, 0x52, 0x08, 0xF4, 0x31, 0x87, 0x40, 0x1F, 0xA0,
    0x7F, 0x09, 0xC2, 0x1B, 0x4B, 0xA0, 0x25, 0xA0, 0x40, 0xA7, 0x3C, 0xDB, 0xED, 0xE2, 0xF0, 0xC8
};

unsigned char buf[100];
void reverseArray(const unsigned char *data, unsigned char *reversedData, int len) {
    if (data == NULL || reversedData == NULL || len <= 0) {
        // Handle invalid input
        printf("Invalid input.\n");
        return;
    }

    const unsigned char *start = data;
    const unsigned char *end = data + len - 1;

    while (start <= end) {
        // Copy elements from the original array to the reversed array
        *reversedData++ = *end--;
        start++;
    }
}
// int main() {
//     const int dataSize = sizeof(databuf) / sizeof(databuf[0]);
//     printf("datalength of packet is %d\n",dataSize);
//     unsigned char reversedData[dataSize];

//     printf("Original Array:\n");
//     for (int i = 0; i < dataSize; i++) {
//         printf("%02X ", databuf[i]);
//     }

//     // Reverse the array using the reverseArray function
//     reverseArray(databuf, reversedData, dataSize);

//     printf("\n\nReversed Array:\n");
//     for (int i = 0; i < dataSize; i++) {
//         printf("%02X ", reversedData[i]);
//     }

    
//     return 0;
// }

#include <stdio.h>
#include <string.h>

void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - 1 - i];
        str[length - 1 - i] = temp;
    }
}

void printBinaryString(const char *str) {
    while (*str) {
        for (int i = 7; i >= 0; --i) {
            putchar(((*str >> i) & 1) ? '1' : '0');
        }
        putchar(' ');
        ++str;
    }
    putchar('\n');
}

int main() {
    char str[] = "A025A04B1BC2097";

    printf("Original string: %s\n", str);
    printf("Binary of original string: ");
    printBinaryString(str);

    reverseString(str);

    printf("Reversed string: %s\n", str);
    printf("Binary of reversed string: ");
    printBinaryString(str);

    return 0;
}
