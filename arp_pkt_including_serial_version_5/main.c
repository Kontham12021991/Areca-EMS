#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "crc.h"
#include "serial.h"

#define ARP_ERROR 1
#define NO_ARP_ERROR 0

struct ARP_DATA
{
    uint32_t pkt_type;
    uint32_t pkt_length;
    uint32_t frame_num;
    uint32_t source_loco_id;
    uint32_t source_loco_version;
    uint32_t abs_loco_loc;
    uint32_t train_length;
    uint32_t train_speed;
    uint32_t movement_dir;
    uint32_t emergency_status;
    uint32_t loco_mode;
    uint32_t approaching_station_id;
    uint32_t last_rfid_tag;
    uint32_t tin;
    uint32_t longitude_degree;
    uint32_t longitude_minutes;
    uint32_t longitude_sec;
    uint32_t latitude_degree;
    uint32_t latitude_minutes;
    uint32_t latitude_sec;
    uint32_t loco_rnd_numrl;
    uint32_t padding_bits;
    uint32_t pkt_crc;
};

struct ARP_ELEMENT_SIZE
{
    uint32_t pkt_type;
    uint32_t pkt_length;
    uint32_t frame_num;
    uint32_t source_loco_id;
    uint32_t source_loco_version;
    uint32_t abs_loco_loc;
    uint32_t train_length;
    uint32_t train_speed;
    uint32_t movement_dir;
    uint32_t emergency_status;
    uint32_t loco_mode;
    uint32_t approaching_station_id;
    uint32_t last_rfid_tag;
    uint32_t tin;
    uint32_t longitude_degree;
    uint32_t longitude_minutes;
    uint32_t longitude_sec;
    uint32_t latitude_degree;
    uint32_t latitude_minutes;
    uint32_t latitude_sec;
    uint32_t loco_rnd_numrl;
    uint32_t padding_bits;
    uint32_t pkt_crc;
};

struct ARP_VALID_RANGE
{
    uint32_t pkt_type_min;
    uint32_t pkt_type_max;
    uint32_t pkt_length_min;
    uint32_t pkt_length_max;
    uint32_t frame_num_min;
    uint32_t frame_num_max;
    uint32_t source_loco_id_min;
    uint32_t source_loco_id_max;
    uint32_t source_loco_version_min;
    uint32_t source_loco_version_max;
    uint32_t abs_loco_loc_min;
    uint32_t abs_loco_loc_max;
    uint32_t train_length_min;
    uint32_t train_length_max;
    uint32_t train_speed_min;
    uint32_t train_speed_max;
    uint32_t movement_dir_min;
    uint32_t movement_dir_max;
    uint32_t emergency_status_min;
    uint32_t emergency_status_max;
    uint32_t loco_mode_min;
    uint32_t loco_mode_max;
    uint32_t approaching_station_id_min;
    uint32_t approaching_station_id_max;
    uint32_t last_rfid_tag_min;
    uint32_t last_rfid_tag_max;
    uint32_t tin_min;
    uint32_t tin_max;
    uint32_t longitude_degree_min;
    uint32_t longitude_degree_max;
    uint32_t longitude_minutes_min;
    uint32_t longitude_minutes_max;
    uint32_t longitude_sec_min;
    uint32_t longitude_sec_max;
    uint32_t latitude_degree_min;
    uint32_t latitude_degree_max;
    uint32_t latitude_minutes_min;
    uint32_t latitude_minutes_max;
    uint32_t latitude_sec_min;
    uint32_t latitude_sec_max;
    uint32_t loco_rnd_numrl_min;
    uint32_t loco_rnd_numrl_max;
    uint32_t padding_bits_len;
};

uint32_t ARP_valid_check(struct ARP_DATA data, struct ARP_VALID_RANGE range)
{
    // Validation logic
    if (data.pkt_type > range.pkt_type_max || data.pkt_type < range.pkt_type_min)
    {
        printf("DATA NOT VALID pkt_type ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.pkt_length > range.pkt_length_max || data.pkt_length < range.pkt_length_min)
    {
        printf("DATA NOT VALID pkt_length ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.frame_num > range.frame_num_max || data.frame_num < range.frame_num_min)
    {
        printf("DATA NOT VALID frame_num ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.source_loco_id > range.source_loco_id_max || data.source_loco_id < range.source_loco_id_min)
    {
        printf("DATA NOT VALID source_loco_id ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.source_loco_version > range.source_loco_version_max || data.source_loco_version < range.source_loco_version_min)
    {
        printf("DATA NOT VALID source_loco_version ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.abs_loco_loc > range.abs_loco_loc_max || data.abs_loco_loc < range.abs_loco_loc_min)
    {
        printf("DATA NOT VALID abs_loco_loc ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.train_length > range.train_length_max || data.train_length < range.train_length_min)
    {
        printf("DATA NOT VALID train_length ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.train_speed > range.train_speed_max || data.train_speed < range.train_speed_min)
    {
        printf("DATA NOT VALID train_speed ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.movement_dir > range.movement_dir_max || data.movement_dir < range.movement_dir_min)
    {
        printf("DATA NOT VALID movement_dir ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.emergency_status > range.emergency_status_max || data.emergency_status < range.emergency_status_min)
    {
        printf("DATA NOT VALID emergency_status ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.loco_mode > range.loco_mode_max || data.loco_mode < range.loco_mode_min)
    {
        printf("DATA NOT VALID loco_mode ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.approaching_station_id > range.approaching_station_id_max || data.approaching_station_id < range.approaching_station_id_min)
    {
        printf("DATA NOT VALID approaching_station_id ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.last_rfid_tag > range.last_rfid_tag_max || data.last_rfid_tag < range.last_rfid_tag_min)
    {
        printf("DATA NOT VALID last_rfid_tag ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.tin > range.tin_max || data.tin < range.tin_min)
    {
        printf("DATA NOT VALID tin ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.longitude_degree > range.longitude_degree_max || data.longitude_degree < range.longitude_degree_min)
    {
        printf("DATA NOT VALID longitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.latitude_degree > range.latitude_degree_max || data.latitude_degree < range.latitude_degree_min)
    {
        printf("DATA NOT VALID latitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.longitude_minutes > range.longitude_minutes_max || data.longitude_minutes < range.longitude_minutes_min)
    {
        printf("DATA NOT VALID longitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.latitude_minutes > range.latitude_minutes_max || data.latitude_minutes < range.latitude_minutes_min)
    {
        printf("DATA NOT VALID latitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.longitude_sec > range.longitude_sec_max || data.longitude_sec < range.longitude_sec_min)
    {
        printf("DATA NOT VALID longitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.latitude_sec > range.latitude_sec_max || data.latitude_sec < range.latitude_sec_min)
    {
        printf("DATA NOT VALID latitude ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.loco_rnd_numrl > range.loco_rnd_numrl_max || data.loco_rnd_numrl < range.loco_rnd_numrl_min)
    {
        printf("DATA NOT VALID loco_rnd_numrl ARP_ERROR\n");
        return ARP_ERROR;
    }
    else if (data.padding_bits != range.padding_bits_len)
    {
        printf("DATA NOT VALID padding_bits ARP_ERROR\n");
        return ARP_ERROR;
    }
    else
    {
        return NO_ARP_ERROR;
    }
}

void int_to_bin(int num, unsigned char *binary_array, int size)
{
    // Conversion logic
    for (int i = size - 1; i >= 0; i--)
    {
        binary_array[i] = num % 2;
        num = num / 2;
    }
}

int hex_char_to_int(char c)
{
    // Conversion logic
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return 10 + c - 'a';
    else if (c >= 'A' && c <= 'F')
        return 10 + c - 'A';
    else
        return -1; // Invalid character
}

void hex_string_to_bytes(const char *hex_string, unsigned char *bytes)
{
    // Conversion logic
    size_t len = strlen(hex_string);
    size_t i;
    for (i = 0; i < len / 2; i++)
    {
        int high_nibble = hex_char_to_int(hex_string[i * 2]);
        int low_nibble = hex_char_to_int(hex_string[i * 2 + 1]);
        if (high_nibble == -1 || low_nibble == -1)
        {
            printf("Invalid hex string\n");
            return;
        }
        bytes[i] = (unsigned char)((high_nibble << 4) | low_nibble);
    }
}

//---------------------------------------------------------------------------------------------------------------------

int prepare_binarray(struct ARP_DATA *dptr, struct ARP_ELEMENT_SIZE *sptr, unsigned char *finptr)

{
    unsigned char aar[100];
    int zerofill, rsize = 0;

    int_to_bin(dptr->pkt_type, aar, sptr->pkt_type);
    memcpy(finptr, aar, sptr->pkt_type);
    finptr += sptr->pkt_type;
    rsize += sptr->pkt_type;

    int_to_bin(dptr->pkt_length, aar, sptr->pkt_length);
    memcpy(finptr, aar, sptr->pkt_length);
    finptr += sptr->pkt_length;
    rsize += sptr->pkt_length;

    int_to_bin(dptr->frame_num, aar, sptr->frame_num);
    memcpy(finptr, aar, sptr->frame_num);
    finptr += sptr->frame_num;
    rsize += sptr->frame_num;

    int_to_bin(dptr->source_loco_id, aar, sptr->source_loco_id);
    memcpy(finptr, aar, sptr->source_loco_id);
    finptr += sptr->source_loco_id;
    rsize += sptr->source_loco_id;

    int_to_bin(dptr->source_loco_version, aar, sptr->source_loco_version);
    memcpy(finptr, aar, sptr->source_loco_version);
    finptr += sptr->source_loco_version;
    rsize += sptr->source_loco_version;

    int_to_bin(dptr->abs_loco_loc, aar, sptr->abs_loco_loc);
    memcpy(finptr, aar, sptr->abs_loco_loc);
    finptr += sptr->abs_loco_loc;
    rsize += sptr->abs_loco_loc;

    int_to_bin(dptr->train_length, aar, sptr->train_length);
    memcpy(finptr, aar, sptr->train_length);
    finptr += sptr->train_length;
    rsize += sptr->train_length;

    int_to_bin(dptr->train_speed, aar, sptr->train_speed);
    memcpy(finptr, aar, sptr->train_speed);
    finptr += sptr->train_speed;
    rsize += sptr->train_speed;

    int_to_bin(dptr->movement_dir, aar, sptr->movement_dir);
    memcpy(finptr, aar, sptr->movement_dir);
    finptr += sptr->movement_dir;
    rsize += sptr->movement_dir;

    int_to_bin(dptr->emergency_status, aar, sptr->emergency_status);
    memcpy(finptr, aar, sptr->emergency_status);
    finptr += sptr->emergency_status;
    rsize += sptr->emergency_status;

    int_to_bin(dptr->loco_mode, aar, sptr->loco_mode);
    memcpy(finptr, aar, sptr->loco_mode);
    finptr += sptr->loco_mode;
    rsize += sptr->loco_mode;

    int_to_bin(dptr->approaching_station_id, aar, sptr->approaching_station_id);
    memcpy(finptr, aar, sptr->approaching_station_id);
    finptr += sptr->approaching_station_id;
    rsize += sptr->approaching_station_id;

    int_to_bin(dptr->last_rfid_tag, aar, sptr->last_rfid_tag);
    memcpy(finptr, aar, sptr->last_rfid_tag);
    finptr += sptr->last_rfid_tag;
    rsize += sptr->last_rfid_tag;

    int_to_bin(dptr->tin, aar, sptr->tin);
    memcpy(finptr, aar, sptr->tin);
    finptr += sptr->tin;
    rsize += sptr->tin;

    int_to_bin(dptr->longitude_degree, aar, sptr->longitude_degree);
    memcpy(finptr, aar, sptr->longitude_degree);
    finptr += sptr->longitude_degree;
    rsize += sptr->longitude_degree;

    int_to_bin(dptr->longitude_minutes, aar, sptr->longitude_minutes);
    memcpy(finptr, aar, sptr->longitude_minutes);
    finptr += sptr->longitude_minutes;
    rsize += sptr->longitude_minutes;

    int_to_bin(dptr->longitude_sec, aar, sptr->longitude_sec);
    memcpy(finptr, aar, sptr->longitude_sec);
    finptr += sptr->longitude_sec;
    rsize += sptr->longitude_sec;

    int_to_bin(dptr->latitude_degree, aar, sptr->latitude_degree);
    memcpy(finptr, aar, sptr->latitude_degree);
    finptr += sptr->latitude_degree;
    rsize += sptr->latitude_degree;

    int_to_bin(dptr->latitude_minutes, aar, sptr->latitude_minutes);
    memcpy(finptr, aar, sptr->latitude_minutes);
    finptr += sptr->latitude_minutes;
    rsize += sptr->latitude_minutes;

    int_to_bin(dptr->latitude_sec, aar, sptr->latitude_sec);
    memcpy(finptr, aar, sptr->latitude_sec);
    finptr += sptr->latitude_sec;
    rsize += sptr->latitude_sec;

    int_to_bin(dptr->loco_rnd_numrl, aar, sptr->loco_rnd_numrl);
    memcpy(finptr, aar, sptr->loco_rnd_numrl);
    finptr += sptr->loco_rnd_numrl;
    rsize += sptr->loco_rnd_numrl;

    if ((rsize % 8) != 0)
        zerofill = 8 - (rsize % 8);
    else
        zerofill = 0;
    memset(finptr, 0, zerofill);
    finptr += zerofill;
    rsize += zerofill;

    return (rsize);
}

int bin_hex(unsigned char *result, unsigned char *bin, int size)

{
    int hexsize = 0;
    unsigned char i, tmp;

    printf("\nsize: %d ", size);
    while (size != 0)
    {
        tmp = 0;
        for (i = 0; i < 8; ++i)
        {
            tmp <<= 1;
            if (*bin == 1)
                tmp |= 0x01;
            ++bin;
            // printf("%x-", tmp);
        }

        // printf("\ntest :%x", tmp);
        *result = tmp;
        printf("\n byte:%02x", tmp);
        ++result;
        ++hexsize;
        size = size - 8;
    }
    return (hexsize);
}

//___________________________________________________________________________________________________

char *hexArrayToString(unsigned char hexArray[], int arrSize)
{
    // Assuming each byte can be represented by 2 characters (including null terminator)
    int stringLength = arrSize * 2 + 1; // +1 for the null terminator
    char *str = (char *)malloc(stringLength * sizeof(char));
    if (str == NULL)
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    str[0] = '\0'; // Ensure the string is empty initially
    for (int i = 0; i < arrSize; i++)
    {
        sprintf(str + strlen(str), "%02x", hexArray[i]); // Convert each byte to its hexadecimal string representation
    }

    return str;
}

//____________________________________________________________________________________________________

int main(void)
{
    struct ARP_ELEMENT_SIZE size = {4, 7, 17, 20, 3, 23, 11, 9, 2, 3, 4, 16, 10, 9, 9, 6, 6, 8, 6, 6, 16, 5, 32};
    struct ARP_VALID_RANGE range = {0, 15, 0, 127, 1, 86400, 1, 999999, 1, 7, 0, 8388608, 1, 2047, 0, 400, 0, 3, 0, 7, 0, 7, 0, 65535, 0, 1023, 1, 511, 0, 180, 0, 60, 0, 60, 0, 90, 0, 60, 0, 60, 0, 65535, 5};
    struct ARP_DATA data = {13, 28, 40401, 37461, 2, 155514, 370, 120, 1, 0, 2, 503, 931, 82, 79, 24, 14, 17, 27, 26, 9232, 5};
    HANDLE hSerial;
    char send_Data[100];
    char receive_Data[100];

    printf("\r\n *************************************************************");

    printf("\r\n  **************LOCO KAVACH **********************************");

    printf("\r\n *************************************************************");

    uint32_t status = ARP_valid_check(data, range);

    // Print validity status
    if (status == NO_ARP_ERROR)
    {
        printf("DATA VALID\n");
    }
    else
    {
        printf("DATA NOT VALID\n");
        return 1; // Exit program if data is not valid
    }

    unsigned char result[500];
    unsigned char hexary[500];
    int rsize = prepare_binarray(&data, &size, result);

    printf("Binary Array: ");
    for (int i = 0; i < rsize; i++)
        printf("%d", result[i]);
    printf("\n");

    int hsize = bin_hex(hexary, result, rsize);

    printf("hexaraay size : %d", hsize);

    printf("hex Array: ");
    for (int i = 0; i < hsize; i++)
        printf("%02x", hexary[i]);
    printf("\n");

    int crc = crc_calc(hsize, hexary);
    printf("crc calc:%2x", crc);

    // sprintf(&hexary[hsize], "%d", crc);
    hexary[hsize++] = (unsigned char)(crc >> 24);
    hexary[hsize++] = (unsigned char)(crc >> 16) & (0x000000ff);
    hexary[hsize++] = (unsigned char)(crc >> 8) & (0x000000ff);
    hexary[hsize++] = (unsigned char)crc;

    printf("hex crc Array: ");

    for (int i = 0; i < hsize; i++)
        printf("%02x", hexary[i]);
    printf("\n");
    printf("\r\n *************************************************************");

    printf("\r\n *************************LOCO KAVACH ************************");

    printf("\r\n *************************************************************\n");
    char *hex_str = hexArrayToString(hexary, hsize);
    // Open serial port
    hSerial = openSerialPort("COM1");
    if (hSerial == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "ARP_ERROR opening serial port\n");
        return 1;
    }

    // Configure serial port
    if (!configureSerialPort(hSerial))
    {
        closeSerialPort(hSerial);
        return 1;
    }
    uint8_t radio_modem1[] = "f1a5c3";
    uint8_t radio_modem2[] = "f2a5c3";
    uint8_t final_str[256];

    while (1)
    {
        Sleep(2000);
        sprintf(final_str, "%s%s", radio_modem1, hex_str);
        // Send data
        if (!sendData(hSerial, final_str))
        {
            closeSerialPort(hSerial);
            return 1;
        }

        // Read data
        if (!receiveData(hSerial, receive_Data, BUFFER_SIZE))
        {
            closeSerialPort(hSerial);
            return 1;
        }

        Sleep(2000);
        sprintf(final_str, "%s%s", radio_modem2, hex_str);
        // Send data
        if (!sendData(hSerial, final_str))
        {
            closeSerialPort(hSerial);
            return 1;
        }

        // Read data
        if (!receiveData(hSerial, receive_Data, BUFFER_SIZE))
        {
            closeSerialPort(hSerial);
            return 1;
        }
    }

    // Close serial port
    closeSerialPort(hSerial);

    return 0;
}
