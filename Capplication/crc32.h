#ifndef CRC32_H
#define CRC32_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

uint32_t crc32(const uint8_t *data, size_t length);
bool verifyCrc32(uint8_t *data, size_t length);
void Crc_testSampletest (void);

#endif