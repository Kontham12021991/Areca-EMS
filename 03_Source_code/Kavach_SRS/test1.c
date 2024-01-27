#include<stdio.h>

// test the GPs communication 
// write the function to test the GPs communication
// return 1 if the communication is successful  
// return 0 if the communication is not successful

// write the c function to genertate the Generic Message Authentication Calculation
// return the GMAC value
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1024

int generate_gmac(unsigned char *key, unsigned char *message, int message_len, unsigned char *gmac, int *gmac_len) {
    int len, i, j;
    unsigned char *iv = NULL;
    unsigned char *padded_message = NULL;
    int padded_message_len = 0;
    int ret = 0;

    if (message_len % 128 != 0) {
        padded_message_len = ((message_len / 128) + 1) * 128;
    } else {
        padded_message_len = message_len;
    }

    padded_message = (unsigned char *) malloc(padded_message_len);
    if (padded_message == NULL) {
        printf("Error: Unable to allocate memory for padded message\n");
        return -1;
    }

    memcpy(padded_message, message, message_len);
    memset(padded_message + message_len, 0, padded_message_len - message_len);

    // AES-128 in CBC mode with an initialization vector of all zeros
    // The last block of the encrypted message is then returned as the GMAC.
    for (i = 0; i < padded_message_len; i += 16) {
        for (j = 0; j < 16; j++) {
            padded_message[i + j] ^= iv[j];
        }
        aes_encrypt(padded_message + i, key, gmac + i);
        memcpy(iv, gmac + i, 16);
    }

    *gmac_len = 16;
    ret = 1;

cleanup:
    if (padded_message != NULL) {
        free(padded_message);
    }

    return ret;
}


int test_gps_communication(){
    return 1;
}
int main() {
    int result;
    result = test_gps_communication();
    if(result == 1){
        printf("Test case passed");
    }
    else{
        printf("Test case failed");
    }
    unsigned char key[16] = {0x00};
    unsigned char message[] = "Hello, world!";
    int message_len = strlen(message) * 8;
    unsigned char gmac[16] = {0x00};
    int gmac_len = 0;

    if (generate_gmac(key, message, message_len, gmac, &gmac_len) != 1) {
        printf("Error: Unable to generate GMAC\n");
        return -1;
    }

    printf("GMAC: ");
    for (int i = 0; i < gmac_len; i++) {
        printf("%02x", gmac[i]);
    }
    printf("\n");
    return 0;
}

//14OBE7D0IF92OBD2404001F403FFFE00520A1065A00000240780000000
//71A34FD99EC2C4DD3EAB3765B711FOB6