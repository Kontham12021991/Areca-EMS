#include <stdint.h>
#include <string.h>
#include <stdio.h>
//Annexure – G 
// The NMS message structure from Stationary KAVACH:
#define 	STATIONARY_KAVACH_INFORMATION_MESSAGE_TO_NMS_SERVER     	0x11
#define 	LOCO_KAVACH_POSITION_INFORMATION_MESSAGE	                0x12
#define 	TSR_INFORMATION_MESSAGE_FROM_STATIONARY_KAVACH_TO_NMS	    0x13
#define 	ADJACENT_KAVACH_INFORMATION	                                0x14
#define 	FIELD_INPUT_STATUS_MESSAGE	                                0x15
#define 	FIELD_INPUTS_EVENT_MESSAGE	                                0x16
#define 	STATIONARY_KAVACH_HEALTH_MESSAGE_TO_NMS_SERVER	            0x17
#define 	ONBOARD_KAVACH_HEALTH_PACKET_TO_NMS	                        0x18
#define 	KAVACH_FAULT_MESSAGE_TO_NMS_SERVER	                        0x19
#define 	NMS_ACKNOWLEDGE_MESSAGE_TO_KAVACH_SUBSYSTEM	                0x1F


// Stationary KAVACH information Message to NMS server 
typedef struct {
  uint8_t sof[2];               // Start of Frame (SOF) - {0xAA, 0xAA}
  uint8_t message_type;       // Message Type - e.g., 0x11
  uint8_t message_length[2];    // Message Length (bytes)
  uint8_t message_sequence[2];  // Message Sequence (0-65535)
  uint8_t stationary_kavach_id[2]; // Stationary KAVACH ID (1-65535)
  uint8_t nms_system_id[2];     // NMS System ID (same as stationary KAVACH ID)
  uint8_t system_version;    // System Version (0x00-0x01)
  uint8_t date[3];           // Date (DD/MM/YY)
  uint8_t time[3];           // Time (HH:MM:SS)
  uint8_t station_active_radio; // Station Active Radio (0xF1/F2/E1/E2/other)
  uint8_t sof_tx_byte1;       // SOF Tx byte 1 (0xA5)
  uint8_t sof_tx_byte2;       // SOF Tx byte 2 (0xC3)
  uint32_t crc;             // CRC (CCITT-32 Bit, calculated excluding SOF)
} Skavach_frame_to_NMS_Server_t;


// Loco KAVACH Position Information Message 
typedef struct  {
    unsigned char sof[2];
    unsigned char message_type;
    unsigned char message_length[2];
    unsigned char message_sequence[2];
    unsigned char stationary_kavach_id[2];
    unsigned char nms_system_id[2];
    unsigned char system_version;
    unsigned char date[3];
    unsigned char time[3];
    unsigned char onboard_active_radio;
    unsigned char sof_tx_byte1;
    unsigned char sof_tx_byte2;
    unsigned char no_of_ma_section_count;
    unsigned char route_id[2];
    unsigned char crc[4];
} Lkavach_Position_info_packet_t;

//	TSR Information Message from stationary KAVACH to NMS
typedef struct  {
    uint8_t sof[2];                   // Start of Frame (divided into two bytes)
    uint8_t message_type;           // Message Type (0x11 for All TSR Information)
    uint8_t message_length[2];       // Message Length (divided into two bytes)
    uint8_t message_sequence[2];     // Message Sequence (divided into two bytes)
    uint8_t stationary_kavach_id[2]; // Stationary KAVACH ID (divided into two bytes)
    uint8_t nms_system_id[2];         // NMS System ID (divided into two bytes)
    uint8_t system_version;         // System Version
    uint8_t data[X];                // TSR Information data (length depends on specific sub-message type)
    uint8_t crc[4];                  // CRC (divided into four bytes)
} tsr_info_SKAVCH_NMS_message_t;


//	Adjacent Kavach Information: When handover of Train is in progress.


// write the Framing function 
void framing(Skavach_frame_to_NMS_Server_t *frame, uint8_t *data, uint16_t data_len) {
    frame->sof[0] = 0xAA;
    frame->sof[1] = 0xAA;
    frame->message_type = data[0];
    frame->message_length[0] = (data_len >> 8) & 0xFF;
    frame->message_length[1] = data_len & 0xFF;
    frame->message_sequence[0] = 0x00;
    frame->message_sequence[1] = 0x01;
    frame->stationary_kavach_id[0] = 0x01;
    frame->stationary_kavach_id[1] = 0x00;
    frame->nms_system_id[0] = frame->stationary_kavach_id[0];
    frame->nms_system_id[1] = frame->stationary_kavach_id[1];
    frame->system_version = 0x00;
    frame->date[0] = 0x01;
    frame->date[1] = 0x01;
    frame->date[2] = 0x01;
    frame->time[0] = 0x01;
    frame->time[1] = 0x01;
    frame->time[2] = 0x01;
    frame->station_active_radio = 0xF1;
    frame->sof_tx_byte1 = 0xA5;
    frame->sof_tx_byte2 = 0xC3;
    frame->crc = 0x00000000;
}


// Stationary KAVACH to NMS


//Stationary KAVACH to Stationary KAVACH Communication on E1 Interface