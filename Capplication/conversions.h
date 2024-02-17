#ifndef CONVERSIONS_H
#define CONVERSIONS_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
void appendBinaryString(uint8_t *str, unsigned long value, int bits);
void clearDynamicMemory(void *data);
size_t calculateBinaryStringLength(const uint8_t *binaryString);
void add_padding(uint8_t *binary_string, uint8_t count);

uint8_t binaryToHex(uint8_t *binary_char);

void binaryToHexadecimal(const uint8_t *binary_string, uint8_t *hex_string);
#endif 