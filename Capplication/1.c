// #include <stdio.h>
// #include <string.h>
// int paddingbits;
// int i;
// int len;
// int len1;
// int number;


// void  fun(char *binarystring);

// void  fun( char *binarystring)
// {
    
	
//     len = strlen(binarystring);
//     len1 = len % 8;
//     printf("%d\n",len1);
//     paddingbits = 8-len1;
//     number = len+paddingbits;
//     char str2[number];
//     printf("padding_pits %d\r\n",paddingbits);
    
//     for(i=0;i<5;i++)
//     {
//       str2[i]=0x30;
// 	}
	
// 	strcat(str2,binarystring);
// 	 printf("%s",str2);
// }


// int main()
// {
//     char *binarystring ="011010001000010000000010000";
//     printf("%s",&binarystring );
// 	fun(binarystring);
// }
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_padding(char *binary_string) {
    int length = strlen(binary_string);
    int rem = length % 8;

    if (rem > 0) {
        char pad[200]; // Adjust the size accordingly
        memset(pad, '0', 8 - rem);
        pad[8 - rem] = '\0'; // Null-terminate the padding string
        strcat(pad, binary_string);
        strcpy(binary_string, pad);
    }
}
// Function to calculate the length of a binary string passed as input
size_t calculateBinaryStringLength(const char *binaryString) {
    return strlen(binaryString);
}


int main() {
    int len =0 ;
    char *binary_string = (char *)malloc(580 * sizeof(char));

    memset(binary_string, 0, 580 * sizeof(char));
    strcpy(binary_string, "01111001000000101100101100011011010000001010010100100000100111100100000010110010110001101101000000101001010010000010");
    printf("Original binary string: %s\n", binary_string);

    add_padding(binary_string);

    printf("Binary string with padding: %s\n", binary_string);
    len =calculateBinaryStringLength(binary_string);
     printf("The length of the binary string is: %zu bits\n", len);
    free(binary_string); // Free allocated memory

    return 0;
}
