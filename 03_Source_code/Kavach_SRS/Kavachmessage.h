
// include file header

// Packet structure between KAVACH entities and KMS
/*Field Descriptor of bytes Remarks
Start of Frame 2 OxAS, OxC3
Message Type I 0x90
Message length in terms of bytes from Date
Message Length 2 field to CRC field (inclusive of both)
Date 3 DD:MM:YY in Hex
Time 3 HH:MM:SS in Hex
OxII — Stationary KAVACH
Type of KAVACH unit | | 0x22 — Onboard KAVACH
0x33 ~TSRMS
Stationary KAVACH ID.in Hex, \?
KAVACH Unit ID 3 OnboardKAVACH ID in
TSRMS ID in Hex
0x01 — Primary
SIM ID 0x02 ~ Secand
32 Bit CCITT CRE 4 Packet CRC. from tnessage to t to SIM ID*/

// cretae the structure 

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

//Identification Acknowledge Message, bys (RMS.t6 KAVACH)
/*Field Descriptor of bytes Remarks
Start of Frame 2 oA. OxC3
Message Type |» ]
Message Length 3 ssage length in terms of bytes from Date
~~ __}field to CRC field (inclusive of both)
Date A 3 X / | DD:MM°YY in Hex
| Time *& 8 “WT HE:MM&SS in Hex
a» YY Ox11 — Stationary KAVACH
Type of KAWA rit Me" 0x22 ~ Onboard KAVACH
, . i= 0X33 TSRMS ID
WS : Stationary KAVACH ID in Hex,
KAMACH Unit ip 3 OnboardKAVACH ID in Hex,
re . TSRMS ID in Hex
| 0x01 —OTP sent
“Aeknowledge Status I 0x02 -KAVACH ID not registered
¥ 0x03 ~ Message delivery failed
32.Bit CCITT CRC 4 Packet CRC from message to type to Ack Status*/

// create the Structure
typedef struct{
    unsigned char start_of_frame[2];
    unsigned char message_type;
    unsigned char message_length[3];
    unsigned char date[3];
    unsigned char time[3];
    unsigned char kavach_type;
    unsigned char kavach_id[3];
    unsigned char ack_status;
    unsigned char crc[4];
}kavach_Identify_ack_t;
//Authentication Key Request Message, 24 bytes (KAVACH to KMS)
/*Field Descriptor of bytes Remarks
Start of Frame 2 OxAS, OxC3
Message Type | 0x92
Message length in terms of bytes from Date field
Message Length 2 to CRC field (inclusive of both)
Date 3 DD:MM-:Y'Y (in Hex)
Time 3 HH:MM&SS (in Hex)
Ox1 1 — Stationary KAVACH
Type of KAVACH unit | ] 0x22 —- Onboard KAVACH
0x33- TSRMS ID
Stationary KAVACH ID in Hex,
KAVACH Unit [D 3 OnboardKAVACH ID in Hex,
TSRMS ID in Hex
0x01 — Primary
SIM ID : 0x02 — Secondary
OTP j oe in SMS, 4 charactef Alpha Numer-
| 32 Bit CCITT CRC 4 Packet CRC from messaged type to*/
// create the Structure
typedef struct{
    unsigned char start_of_frame[2];
    unsigned char message_type;
    unsigned char message_length[2];
    unsigned char date[3];
    unsigned char time[3];
    unsigned char kavach_type;
    unsigned char kavach_id[3];
    unsigned char sim_id;
    unsigned char otp[4];
    unsigned char crc[4];
}kavach_Auth_keyreq_t;


//Authentication Key Response Message, 24 bytes (KMS to KAVACH)

/*Field Descriptor the oa Remarks . .
Start of Frame 2 OxAS, Ox y
Message Type | Ox93 ae “Qu ,
Message length.in terms of bytes from Date field
Message Length 2 to So of both)
Date 3 DD:MM:¥¥(in Hex)
Time 3 :MM&SS (in Hex)
Ox} — Stationary KAVACH
Type of KAVACH unit 1 0x22 — OnboardKAVACH
_ | '0k33 TSRMS ID
fr Stationary KAVACH ID in Hex,
OnboardKAVACH ID in Hex,
TSRMS ID in Hex
KAVACH Unit ID 2
Key set Unique ID. ae Unique ID of Key Set
Number of Key Sets (p) “) OxlE
Key set =x validity start time | 4 HH DD MM YY (in Hex) ———— a
Key set—x validityend time | 4 HH DD MM YY (in Hex) : =
Key set=-x 16*2 2 keys, Each key size of 16 bytes
32 Bit CCIPPORE 4 Packet CRC from message to type to Key set —x*/

// create the structure 
typedef struct{
    unsigned char start_of_frame[2];
    unsigned char message_type;
    unsigned char message_length[2];
    unsigned char date[3];
    unsigned char time[3];
    unsigned char kavach_type;
    unsigned char kavach_id[3];
    unsigned char key_set_id;
    unsigned char key_set_validity_start_time[4];
    unsigned char key_set_validity_end_time[4];
    unsigned char key_set[32];
    unsigned char crc[4];
}kavach_Auth_keyMessage_t;