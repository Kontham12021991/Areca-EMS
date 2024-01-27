#include "Kavachmessage.h"


// create the function Following tables shows the packet structure to be used for communication
//between KMS and KAVACH units for the purpose of transmission
//of Authentication Keys. The packet transmission protocol shall be in
//UDP.
// write the function to recive the Kavach packet from buffer 
// and store it in the structure
// return the structure
// if the packet is not in the correct format return NULL
// if the packet is in the correct format return the structure

typedef struct {
    unsigned char start_of_frame[2];
    unsigned char message_type;
    unsigned char message_length[2];
    unsigned char date[3];
    unsigned char time[3];
    unsigned char kavach_type;
    unsigned char kavach_id[3];
    unsigned char sim_id;
    unsigned char crc[4];
}kavach_packet_t;
// write functo to extract data from above structure
// and store it in the structure

kavach_packet_t *kavach_packet;
int flag=0,i;
kavach_packet_t *ExtractKavachpacket(const unsigned char *buf){
    kavach_packet = (kavach_packet_t *)malloc(sizeof(kavach_packet_t));
    for(i=0;i<2;i++){
        kavach_packet->start_of_frame[i]=buf[i];
    }
    kavach_packet->message_type=buf[2];
    for(i=0;i<2;i++){
        kavach_packet->message_length[i]=buf[i+3];
    }
    for(i=0;i<3;i++){
        kavach_packet->date[i]=buf[i+5];
    }
    for(i=0;i<3;i++){
        kavach_packet->time[i]=buf[i+8];
    }
    kavach_packet->kavach_type=buf[11];
    for(i=0;i<3;i++){
        kavach_packet->kavach_id[i]=buf[i+12];
    }
    kavach_packet->sim_id=buf[15];
    for(i=0;i<4;i++){
        kavach_packet->crc[i]=buf[i+16];
    }
    return kavach_packet;
}