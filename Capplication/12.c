// #include <stdio.h>
// #include <stdint.h>
// #include <string.h>

// int main() {
//     const char* hexString = "01404B409637828096812C6F05012D0258DE0A025A04B1BC81A7";
//     size_t hexStringLength = strlen(hexString);
//     size_t byteArraySize = hexStringLength / 2;

//     uint8_t byteArray[byteArraySize];

//     // Convert hex string to byte array
//     for (size_t i = 0, j = 0; i < hexStringLength; i += 2, ++j) {
//         char hex[3] = {hexString[i], hexString[i + 1], '\0'};
//         byteArray[j] = strtol(hex, NULL, 16);
//     }

//     // Print the resulting byte array
//     printf("Byte Array: ");
//     for (size_t i = 0; i < byteArraySize; ++i) {
//         printf("%02X ", byteArray[i]);
//     }
//     printf("\n");


//     // REVERSE THE ARRAY byteArray
//     for (size_t i = 0, j = byteArraySize - 1; i < j; i++, j--) {
//         uint8_t temp = byteArray[i];   
//         byteArray[i] = byteArray[j];
//         byteArray[j] = temp;
//     }
//         // Print the resulting byte array
//     printf("Byte Array: ");
//     for (size_t i = 0; i < byteArraySize; ++i) {
//         printf("%02X ", byteArray[i]);
//     }
//     printf("\n");
//     return 0;
// }
#include <stdio.h>
#include <string.h>

void reverse_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

int main() {
    char hexString[] = "01404B409637828096812C6F05012D0258DE0A025A04B1BC81A7";
    reverse_string(hexString);
    printf("%s", hexString);
    return 0;
}
