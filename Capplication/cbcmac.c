
#include "cbcmac.h"
#include "crc32.h"
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#define AES_KEY_SIZE 16        // 128 bits
#define AES_ROUND_KEY_SIZE 176 // 16 bytes * 11 rounds for AES-128

// Substitute bytes based on the S-box
static const uint8_t sbox[256] = {
0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
			0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
			0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
			0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
			0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
			0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
			0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
			0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
			0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
			0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
			0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
			0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
			0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
			0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
			0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
			0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16,

};

uint8_t globalSessionKey[32];
static void print_hex( const unsigned char *data, size_t len);
static void handleErrors(void);
 
static unsigned char sessionKey[16]; 
static void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}


static void print_hex( const unsigned char *data, size_t len) {

    if (len == 0) return; /* optional */

    for (size_t i = 0; i < len; i++) {
        printf("%02X", data[i]);
        if (i < len - 1) printf(",");
    }
    printf("\n");
}

int encrypt_aes_ecb(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialise the context
    if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

    // Initialise the encryption operation. IMPORTANT - ensure you use a key
    // and IV size appropriate for your cipher
    // In this case we are using 128 bit AES (AES-128)
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, NULL))
        handleErrors();

    // Provide the message to be encrypted, and obtain the encrypted output.
    // EVP_EncryptUpdate can be called multiple times if necessary
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    // Finalise the encryption. Further ciphertext bytes may be written at
    // this stage.
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
    ciphertext_len += len;
    printf("%d",ciphertext_len);

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}



static void storeInGlobalBuffer(const unsigned char *data, size_t len) {
    if (len > sizeof(globalSessionKey)) {
        printf("Data length exceeds global buffer size.\n");
        return;
    }

    for (size_t i = 0; i < len; i++) {
        globalSessionKey[i] = data[i];
    }

    // Optionally, print the stored data
    printf("Stored in global buffer: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X", globalSessionKey[i]);
        if (i < len - 1) printf(",");
    }
    printf("\n");
}

// Function prototype updated to return a pointer to uint8_t
uint8_t *GenerateRData(uint16_t RS, uint16_t RL, int *size)
{

    // Calculate the size of the R array
    *size = 16; // Since the pattern is fixed and always generates 16 bytes

    // Allocate memory for the R buffer
    uint8_t *R = (uint8_t *)malloc(*size * sizeof(uint8_t));
    if (R == NULL)
    {
        // Handle memory allocation failure if needed
        printf("Memory allocation failed\n");
        *size = 0; // No data to return
        return NULL;
    }

    // Break down RS and RL into their bytes
    uint8_t RS_high = RS >> 8;
    uint8_t RS_low = RS & 0xFF;
    uint8_t RL_high = RL >> 8;
    uint8_t RL_low = RL & 0xFF;

    // Constructing R from the pattern described
    uint8_t tempR[] = {
        RS_high, RS_low, RL_low, RL_high,
        RS_high, RS_low, RL_low, RL_high,
        RL_low, RL_high, RS_high, RS_low,
        RL_low, RL_high, RS_high, RS_low};

    // Copy the constructed pattern into the allocated memory
    for (int i = 0; i < *size; i++)
    {
        R[i] = tempR[i];
    }

    // Return the pointer to the allocated memory holding R
    return R;
}
uint8_t sessionkey[16];
uint8_t Rdata[16];
int main()
{
    int size;
    uint16_t RS = 0xA5A5;
    uint16_t RL = 0x7AB9;
    uint8_t *R = GenerateRData(RS, RL, &size);

    unsigned char KA[16] = {0x3C, 0x4F, 0xCF, 0x09, 0x88, 0x15, 0xF7, 0xAB, 0xA6, 0xD2, 0xAE, 0x28, 0x16, 0x15, 0x7E, 0x2B};
    // Check if R was successfully created
    if (R != NULL)
    {
        printf("R: ");
        for (int i = 0; i < size; i++)
        {
            printf("%02X", R[i]);
            Rdata[i] = R[i];
            if (i < size - 1)
            {
                printf(",");
            }
        }
        printf("\n");

        free(R);
    }
    int length = encrypt_aes_ecb(Rdata, sizeof(Rdata), KA, sessionkey);
    storeInGlobalBuffer(sessionkey, sizeof(sessionkey));

    // competed till session key generation 

    return 0;
}
