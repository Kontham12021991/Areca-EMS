// #include <stdio.h>
// #include <openssl/aes.h>
// #include <string.h>

// // Function to print bytes in hex
// void print_hex(const char *label, unsigned char *data, size_t len) {
//     printf("%s: ", label);
//     for (size_t i = 0; i < len; ++i) {
//         printf("%02X", data[i]);
//         if (i < len - 1) printf(",");
//     }
//     printf("\n");
// }

// // Function to compare generated session key against expected value
// int verify_session_key(unsigned char *sessionKey, unsigned char *expectedKey, size_t len) {
//     return memcmp(sessionKey, expectedKey, len) == 0;
// }

// int main(void) {
//     unsigned char KA[16] = {0x3C,0x4F,0xCF,0x09,0x88,0x15,0xF7,0xAB,0xA6,0xD2,0xAE,0x28,0x16,0x15,0x7E,0x2B};
//     unsigned char R[16] = {0xA5,0xA5,0xB9,0x7A,0xA5,0xA5,0xB9,0x7A,0xB9,0x7A,0xA5,0xA5,0xB9,0x7A,0xA5,0xA5};
//     unsigned char expectedKey[16] = {0x62,0x41,0x39,0x86,0xDA,0xDD,0xA1,0xCE,0xF0,0x88,0x58,0x2C,0xE1,0xC9,0x44,0x52};
//     unsigned char sessionKey[16]; // To store the encryption result

//     // Initializing AES key structure
//     AES_KEY enc_key;
//     AES_set_encrypt_key(KA, 128, &enc_key);

//     // Encrypting R using KA
//     AES_encrypt(R, sessionKey, &enc_key);

//     // Print the generated session key
//     print_hex("Generated Session Key", sessionKey, sizeof(sessionKey));

//     // Verify the generated session key against the expected key
//     if (verify_session_key(sessionKey, expectedKey, sizeof(sessionKey))) {
//         printf("Verification Success: The generated session key matches the expected value.\n");
//     } else {
//         printf("Verification Failed: The generated session key does not match the expected value.\n");
//     }

//     return 0;
// }

#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

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

// int Test_main(void) {
//     unsigned char KA[16] = {0x3C,0x4F,0xCF,0x09,0x88,0x15,0xF7,0xAB,0xA6,0xD2,0xAE,0x28,0x16,0x15,0x7E,0x2B};
//     unsigned char R[16] = {0xA5,0xA5,0xB9,0x7A,0xA5,0xA5,0xB9,0x7A,0xB9,0x7A,0xA5,0xA5,0xB9,0x7A,0xA5,0xA5};
  

//     // Encrypt R using KA
//     int encrypted_length = encrypt_aes_ecb(R, sizeof(R), KA, sessionKey);

//     storeInGlobalBuffer(sessionKey, sizeof(sessionKey));


//     return 0;
// }


