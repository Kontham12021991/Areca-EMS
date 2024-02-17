#include <stdio.h>
#include <stdint.h>

// Structure to represent the Access Authority Packet Version 2.0
typedef struct {
    uint8_t pkt_type; // 4 bits
    uint8_t pkt_length; // 7 bits
    uint32_t frame_num; // 17 bits
    uint16_t source_stn_ilc_ibs_id; // 16 bits
    uint8_t source_stn_ilc_ibs_version; // 3 bits
    uint32_t stn_ilc_ibs_loc; // 22 bits
    uint16_t dest_loco_id; // 17 bits
    uint8_t allotted_fdma_freq; // 4 bits
} AccessAuthorityPacket;

// Function to create an Access Authority Packet Version 2.0
AccessAuthorityPacket createAccessAuthorityPacket(uint8_t pkt_type, uint8_t pkt_length, uint32_t frame_num, uint16_t source_stn_ilc_ibs_id, 
                                                  uint8_t source_stn_ilc_ibs_version, uint32_t stn_ilc_ibs_loc, uint16_t dest_loco_id, 
                                                  uint8_t allotted_fdma_freq) {
    AccessAuthorityPacket packet;
    packet.pkt_type = pkt_type;
    packet.pkt_length = pkt_length;
    packet.frame_num = frame_num;
    packet.source_stn_ilc_ibs_id = source_stn_ilc_ibs_id;
    packet.source_stn_ilc_ibs_version = source_stn_ilc_ibs_version;
    packet.stn_ilc_ibs_loc = stn_ilc_ibs_loc;
    packet.dest_loco_id = dest_loco_id;
    packet.allotted_fdma_freq = allotted_fdma_freq;

    return packet;
}

int main() {
    // Example of creating an Access Authority Packet Version 2.0
    AccessAuthorityPacket packet = createAccessAuthorityPacket(0b0011, 0b0000001, 1, 1234, 2, 56789, 9999, 0b0001);

    // Display the created Access Authority Packet Version 2.0
    printf("Created Access Authority Packet Version 2.0:\n");
    printf("Packet Type: %d\n", packet.pkt_type);
    printf("Packet Length: %d\n", packet.pkt_length);
    printf("Frame Number: %d\n", packet.frame_num);
    printf("Source Station ILC IBS ID: %d\n", packet.source_stn_ilc_ibs_id);
    printf("Source Station ILC IBS Version: %d\n", packet.source_stn_ilc_ibs_version);
    printf("Station ILC IBS Location: %d\n", packet.stn_ilc_ibs_loc);
    printf("Destination Loco ID: %d\n", packet.dest_loco_id);
    printf("Allotted FDMA Frequency: %d\n", packet.allotted_fdma_freq);

    return 0;
}