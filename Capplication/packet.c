#include <stdint.h>
#include <stdio.h>

// TMS5701227CPGEQQ1
// XC7A35T-2FTG256I

// Define the structure with no packing
#pragma pack(push, 1)
struct TurnoutSpeedProfile
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH : 7;
    uint8_t H_TSP : 2;
    uint8_t TO_CNT : 5;
    uint16_t TO_SPEED : 15;
    uint16_t DIFF_DIST_TO : 12;
    uint16_t TO_SPEED_REL_DIST : 15;
    uint16_t PaddingBits : 12;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct TagLinkingInfo
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH : 7;
    uint8_t H_TLI : 4;
    uint16_t DIST_DUP_TAG : 6;
    uint16_t ROUTE_RFID_CNT : 11;
    uint16_t DIST_NXT_RFID : 10;
    uint16_t NXT_RFID_TAG_ID : 11;
    uint8_t DUP_TAG_DIR : 1;
    uint8_t ABS_LOC_RESET : 1;
    uint16_t START_DIST_TO_LOC_RESET : 15;
    uint8_t ADJ_LOCO_DIR : 2;
    uint32_t ABS_LOC_CORRECTION : 23;
    uint16_t ADJ_LINE_CNT : 3;
    uint16_t LINE_TIN : 9;
    uint16_t PaddingBits : 3;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct TrackConditionData
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH : 7;
    uint8_t H_TC : 4;
    uint8_t TRACKCOND_CNT : 4;
    uint16_t TRACKCOND_TYPE : 15;
    uint16_t START_DIST_TRACKCOND : 15;
    uint16_t LENGTH_TRACKCOND : 15;
    uint8_t PaddingBit : 1;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct TSRProfile
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH : 7;
    uint8_t H_TSR : 2;
    uint8_t TSR_STATUS : 5;
    uint8_t TSR_Info_CNT : 8;
    uint16_t TSR_ID : 15;
    uint16_t TSR_Distance : 15;
    uint16_t TSR_Length : 15;
    uint8_t TSR_Class : 1;
    uint8_t TSR_Universal_Speed : 6;
    uint8_t TSR_ClassA_Speed : 6;
    uint8_t TSR_ClassB_Speed : 6;
    uint8_t TSR_ClassC_Speed : 6;
    uint8_t TSR_Whistle : 2;
    uint8_t PaddingBits : 2;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct LCGateProfile
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH_LC : 7;
    uint8_t LM_LC_Info_CNT : 5;
    uint16_t LM_LC_Distance : 15;
    uint16_t LM_LC_ID_Numeric : 10;
    uint8_t LM_LC_ID_Alpha_Suffix : 3;
    uint8_t LM_LC_Manning_Type : 1;
    uint8_t LM_LC_Class : 3;
    uint8_t LM_LC_Auto_Whistling_Enabled : 1;
    uint8_t LM_LC_Auto_Whistling_Type : 2;
    uint8_t PaddingBit : 1;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct GradientProfile
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH_GRAD : 7;
    uint8_t LM_Grad_Info_CNT : 5;
    uint16_t LM_Gradient_Distance : 15;
    uint8_t LM_GDIR : 1;
    uint8_t LM_GRADIENT_VALUE : 5;
    uint8_t PaddingBits :3;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct MovementAuthorityPacket
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH_MA : 7;
    uint8_t FRAME_OFFSET : 4;
    uint8_t DEST_LOCO_SOS : 4;
    uint8_t TRAIN_SECTION_TYPE : 2;
    uint32_t CUR_SIG_INFO : 17;
    uint8_t CUR_SIG_ASPECT : 6;
    uint8_t NEXT_SIG_ASPECT : 6;
    uint16_t APPR_SIG_DIST : 15;
    uint8_t AUTHORITY_TYPE : 2;
    uint16_t AUTHORIZED_SPEED : 6;
    uint16_t MA_W_R_T_SIG : 16;
    uint8_t REQ_SHORTEN_MA : 1;
    uint16_t NEW_MA : 16;
    uint8_t TRN_LEN_INFO_STS : 1;
    uint8_t TRN_LEN_INFO_TYPE : 1;
    uint32_t REF_FRAME_NUM_TLM : 17;
    uint8_t REF_OFFSET_INT_TLM : 8;
    uint16_t NEXT_STN_COMM : 1;
    uint32_t APPR_STN_ILC_IB_S_ID : 17;
    uint16_t PaddingBits : 16;
};
#pragma pack(pop)

// Define the structure with no packing
#pragma pack(push, 1)
struct StaticSpeedProfile
{
    uint8_t SUB_PKT_TYPE : 4;
    uint8_t SUB_PKT_LENGTH_SSP : 7;
    uint8_t LM_Speed_Info_CNT : 5;
    uint16_t LM_Static_Speed_Distance : 15;
    uint8_t LM_Static_Speed_Class : 1;
    uint8_t LM_Static_Speed_Value : 6;
    uint8_t PaddingBit : 2;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct RadioDataPacket
{
    // Common header fields
    uint8_t PACKET_TYPE : 4;                     // 1001
    uint8_t PACKET_LENGTH : 7;                     
    uint32_t FRAME_NUM : 17;
    uint16_t SOURCE_STN_ILC_IBS_ID : 16;
    uint8_t SOURCE_STN_ILC_IBS_VERSION : 3;
    uint32_t DEST_LOCO_ID : 20;
    uint8_t REF_PROF_ID : 4;
    uint16_t LAST_REF_RFID : 10;
    uint16_t DIST_PKT_START : 15;
    uint8_t PKT_DIR : 2;
    uint8_t Padding_Bits : 3;

    struct MovementAuthorityPacket maPacket;
    struct StaticSpeedProfile sspProfile;
    struct GradientProfile gradientProfile;
    struct LCGateProfile lcGateProfile;
    struct TurnoutSpeedProfile mturnonspeedProfile;
    struct TagLinkingInfo tagInfo;
    struct TrackConditionData trackData;
    struct TSRProfile tsrProfile;
    uint32_t LOCO_Specific_MAC_CODE : 32;
    uint32_t PKT_CRC : 32;
};
#pragma pack(pop)
typedef struct RadioDataPacket RadioPacket;

int StaticSpeedProfile_main()
{
    // Example usage
    struct StaticSpeedProfile sspProfile;

    // Set values for the fields
    sspProfile.SUB_PKT_TYPE = 4;
    sspProfile.SUB_PKT_LENGTH_SSP = 7;
    sspProfile.LM_Speed_Info_CNT = 5;
    sspProfile.LM_Static_Speed_Distance = 15;
    sspProfile.LM_Static_Speed_Class = 1;
    sspProfile.LM_Static_Speed_Value = 6;
    sspProfile.PaddingBit = 0;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", sspProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_SSP: %d\n", sspProfile.SUB_PKT_LENGTH_SSP);
    printf("LM_Speed_Info_CNT: %d\n", sspProfile.LM_Speed_Info_CNT);
    printf("LM_Static_Speed_Distance: %d\n", sspProfile.LM_Static_Speed_Distance);
    printf("LM_Static_Speed_Class: %d\n", sspProfile.LM_Static_Speed_Class);
    printf("LM_Static_Speed_Value: %d\n", sspProfile.LM_Static_Speed_Value);
    printf("PaddingBit: %d\n", sspProfile.PaddingBit);

    return 0;
}

int MovementAuthorityPacket_main()
{
    // Example usage
    struct MovementAuthorityPacket maPacket;

    // Set values for the fields
    maPacket.SUB_PKT_TYPE = 4;
    maPacket.SUB_PKT_LENGTH_MA = 7;
    maPacket.FRAME_OFFSET = 4;
    maPacket.DEST_LOCO_SOS = 4;
    maPacket.TRAIN_SECTION_TYPE = 2;
    maPacket.CUR_SIG_INFO = 17;
    maPacket.CUR_SIG_ASPECT = 6;
    maPacket.NEXT_SIG_ASPECT = 6;
    maPacket.APPR_SIG_DIST = 15;
    maPacket.AUTHORITY_TYPE = 2;
    maPacket.AUTHORIZED_SPEED = 6;
    maPacket.MA_W_R_T_SIG = 16;
    maPacket.REQ_SHORTEN_MA = 1;
    maPacket.NEW_MA = 16;
    maPacket.TRN_LEN_INFO_STS = 1;
    maPacket.TRN_LEN_INFO_TYPE = 1;
    maPacket.REF_FRAME_NUM_TLM = 17;
    maPacket.REF_OFFSET_INT_TLM = 8;
    maPacket.NEXT_STN_COMM = 1;
    maPacket.APPR_STN_ILC_IB_S_ID = 17;
    maPacket.PaddingBits = 0;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", maPacket.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_MA: %d\n", maPacket.SUB_PKT_LENGTH_MA);
    printf("FRAME_OFFSET: %d\n", maPacket.FRAME_OFFSET);
    printf("DEST_LOCO_SOS: %d\n", maPacket.DEST_LOCO_SOS);
    printf("TRAIN_SECTION_TYPE: %d\n", maPacket.TRAIN_SECTION_TYPE);
    printf("CUR_SIG_INFO: %d\n", maPacket.CUR_SIG_INFO);
    printf("CUR_SIG_ASPECT: %d\n", maPacket.CUR_SIG_ASPECT);
    printf("NEXT_SIG_ASPECT: %d\n", maPacket.NEXT_SIG_ASPECT);
    printf("APPR_SIG_DIST: %d\n", maPacket.APPR_SIG_DIST);
    printf("AUTHORITY_TYPE: %d\n", maPacket.AUTHORITY_TYPE);
    printf("AUTHORIZED_SPEED: %d\n", maPacket.AUTHORIZED_SPEED);
    printf("MA_W_R_T_SIG: %d\n", maPacket.MA_W_R_T_SIG);
    printf("REQ_SHORTEN_MA: %d\n", maPacket.REQ_SHORTEN_MA);
    printf("NEW_MA: %d\n", maPacket.NEW_MA);
    printf("TRN_LEN_INFO_STS: %d\n", maPacket.TRN_LEN_INFO_STS);
    printf("TRN_LEN_INFO_TYPE: %d\n", maPacket.TRN_LEN_INFO_TYPE);
    printf("REF_FRAME_NUM_TLM: %d\n", maPacket.REF_FRAME_NUM_TLM);
    printf("REF_OFFSET_INT_TLM: %d\n", maPacket.REF_OFFSET_INT_TLM);
    printf("NEXT_STN_COMM: %d\n", maPacket.NEXT_STN_COMM);
    printf("APPR_STN_ILC_IB_S_ID: %d\n", maPacket.APPR_STN_ILC_IB_S_ID);
    printf("PaddingBits: %d\n", maPacket.PaddingBits);

    return 0;
}

int GradientProfile_main()
{
    // Example usage
    struct GradientProfile gradientProfile;

    // Set values for the fields
    gradientProfile.SUB_PKT_TYPE = 4;
    gradientProfile.SUB_PKT_LENGTH_GRAD = 7;
    gradientProfile.LM_Grad_Info_CNT = 5;
    gradientProfile.LM_Gradient_Distance = 15;
    gradientProfile.LM_GDIR = 1;
    gradientProfile.LM_GRADIENT_VALUE = 5;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", gradientProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_GRAD: %d\n", gradientProfile.SUB_PKT_LENGTH_GRAD);
    printf("LM_Grad_Info_CNT: %d\n", gradientProfile.LM_Grad_Info_CNT);
    printf("LM_Gradient_Distance: %d\n", gradientProfile.LM_Gradient_Distance);
    printf("LM_GDIR: %d\n", gradientProfile.LM_GDIR);
    printf("LM_GRADIENT_VALUE: %d\n", gradientProfile.LM_GRADIENT_VALUE);

    return 0;
}

int LCGateProfile_main()
{
    // Example usage
    struct LCGateProfile lcGateProfile;

    // Set values for the fields
    lcGateProfile.SUB_PKT_TYPE = 4;
    lcGateProfile.SUB_PKT_LENGTH_LC = 7;
    lcGateProfile.LM_LC_Info_CNT = 5;
    lcGateProfile.LM_LC_Distance = 15;
    lcGateProfile.LM_LC_ID_Numeric = 10;
    lcGateProfile.LM_LC_ID_Alpha_Suffix = 3;
    lcGateProfile.LM_LC_Manning_Type = 1;
    lcGateProfile.LM_LC_Class = 3;
    lcGateProfile.LM_LC_Auto_Whistling_Enabled = 1;
    lcGateProfile.LM_LC_Auto_Whistling_Type = 2;
    lcGateProfile.PaddingBit = 1;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", lcGateProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH_LC: %d\n", lcGateProfile.SUB_PKT_LENGTH_LC);
    printf("LM_LC_Info_CNT: %d\n", lcGateProfile.LM_LC_Info_CNT);
    printf("LM_LC_Distance: %d\n", lcGateProfile.LM_LC_Distance);
    printf("LM_LC_ID_Numeric: %d\n", lcGateProfile.LM_LC_ID_Numeric);
    printf("LM_LC_ID_Alpha_Suffix: %d\n", lcGateProfile.LM_LC_ID_Alpha_Suffix);
    printf("LM_LC_Manning_Type: %d\n", lcGateProfile.LM_LC_Manning_Type);
    printf("LM_LC_Class: %d\n", lcGateProfile.LM_LC_Class);
    printf("LM_LC_Auto_Whistling_Enabled: %d\n", lcGateProfile.LM_LC_Auto_Whistling_Enabled);
    printf("LM_LC_Auto_Whistling_Type: %d\n", lcGateProfile.LM_LC_Auto_Whistling_Type);
    printf("PaddingBit: %d\n", lcGateProfile.PaddingBit);

    return 0;
}

int TSRProfile_main()
{
    // Example usage
    struct TSRProfile tsrProfile;

    // Set values for the fields
    tsrProfile.SUB_PKT_TYPE = 4;
    tsrProfile.SUB_PKT_LENGTH = 7;
    tsrProfile.H_TSR = 2;
    tsrProfile.TSR_STATUS = 5;
    tsrProfile.TSR_Info_CNT = 8;
    tsrProfile.TSR_ID = 15;
    tsrProfile.TSR_Distance = 15;
    tsrProfile.TSR_Length = 15;
    tsrProfile.TSR_Class = 1;
    tsrProfile.TSR_Universal_Speed = 6;
    tsrProfile.TSR_ClassA_Speed = 6;
    tsrProfile.TSR_ClassB_Speed = 6;
    tsrProfile.TSR_ClassC_Speed = 6;
    tsrProfile.TSR_Whistle = 2;
    tsrProfile.PaddingBits = 2;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", tsrProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH: %d\n", tsrProfile.SUB_PKT_LENGTH);
    printf("H_TSR: %d\n", tsrProfile.H_TSR);
    printf("TSR_STATUS: %d\n", tsrProfile.TSR_STATUS);
    printf("TSR_Info_CNT: %d\n", tsrProfile.TSR_Info_CNT);
    printf("TSR_ID: %d\n", tsrProfile.TSR_ID);
    printf("TSR_Distance: %d\n", tsrProfile.TSR_Distance);
    printf("TSR_Length: %d\n", tsrProfile.TSR_Length);
    printf("TSR_Class: %d\n", tsrProfile.TSR_Class);
    printf("TSR_Universal_Speed: %d\n", tsrProfile.TSR_Universal_Speed);
    printf("TSR_ClassA_Speed: %d\n", tsrProfile.TSR_ClassA_Speed);
    printf("TSR_ClassB_Speed: %d\n", tsrProfile.TSR_ClassB_Speed);
    printf("TSR_ClassC_Speed: %d\n", tsrProfile.TSR_ClassC_Speed);
    printf("TSR_Whistle: %d\n", tsrProfile.TSR_Whistle);
    printf("PaddingBits: %d\n", tsrProfile.PaddingBits);

    return 0;
}

int TrackConditionData_main()
{
    // Example usage
    struct TrackConditionData trackData;

    // Set values for the fields
    trackData.SUB_PKT_TYPE = 4;
    trackData.SUB_PKT_LENGTH = 7;
    trackData.H_TC = 4;
    trackData.TRACKCOND_CNT = 4;
    trackData.TRACKCOND_TYPE = 15;
    trackData.START_DIST_TRACKCOND = 15;
    trackData.LENGTH_TRACKCOND = 15;
    trackData.PaddingBit = 0;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", trackData.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH: %d\n", trackData.SUB_PKT_LENGTH);
    printf("H_TC: %d\n", trackData.H_TC);
    printf("TRACKCOND_CNT: %d\n", trackData.TRACKCOND_CNT);
    printf("TRACKCOND_TYPE: %d\n", trackData.TRACKCOND_TYPE);
    printf("START_DIST_TRACKCOND: %d\n", trackData.START_DIST_TRACKCOND);
    printf("LENGTH_TRACKCOND: %d\n", trackData.LENGTH_TRACKCOND);
    printf("PaddingBit: %d\n", trackData.PaddingBit);

    return 0;
}

int TagLinkingInfo_testmain()
{
    // Example usage
    struct TagLinkingInfo tagInfo;

    // Set values for the fields
    tagInfo.SUB_PKT_TYPE = 4;
    tagInfo.SUB_PKT_LENGTH = 7;
    tagInfo.H_TLI = 4;
    tagInfo.DIST_DUP_TAG = 6;
    tagInfo.ROUTE_RFID_CNT = 11;
    tagInfo.DIST_NXT_RFID = 10;
    tagInfo.NXT_RFID_TAG_ID = 11;
    tagInfo.DUP_TAG_DIR = 1;
    tagInfo.ABS_LOC_RESET = 1;
    tagInfo.START_DIST_TO_LOC_RESET = 15;
    tagInfo.ADJ_LOCO_DIR = 2;
    tagInfo.ABS_LOC_CORRECTION = 23;
    tagInfo.ADJ_LINE_CNT = 3;
    tagInfo.LINE_TIN = 9;
    tagInfo.PaddingBits = 3;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", tagInfo.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH: %d\n", tagInfo.SUB_PKT_LENGTH);
    printf("H_TLI: %d\n", tagInfo.H_TLI);
    printf("DIST_DUP_TAG: %d\n", tagInfo.DIST_DUP_TAG);
    printf("ROUTE_RFID_CNT: %d\n", tagInfo.ROUTE_RFID_CNT);
    printf("DIST_NXT_RFID: %d\n", tagInfo.DIST_NXT_RFID);
    printf("NXT_RFID_TAG_ID: %d\n", tagInfo.NXT_RFID_TAG_ID);
    printf("DUP_TAG_DIR: %d\n", tagInfo.DUP_TAG_DIR);
    printf("ABS_LOC_RESET: %d\n", tagInfo.ABS_LOC_RESET);
    printf("START_DIST_TO_LOC_RESET: %d\n", tagInfo.START_DIST_TO_LOC_RESET);
    printf("ADJ_LOCO_DIR: %d\n", tagInfo.ADJ_LOCO_DIR);
    printf("ABS_LOC_CORRECTION: %d\n", tagInfo.ABS_LOC_CORRECTION);
    printf("ADJ_LINE_CNT: %d\n", tagInfo.ADJ_LINE_CNT);
    printf("LINE_TIN: %d\n", tagInfo.LINE_TIN);
    printf("PaddingBits: %d\n", tagInfo.PaddingBits);

    return 0;
}
void TurnoutSpeedProfile_testmain()
{
    // Example usage
    struct TurnoutSpeedProfile myProfile;

    // Set values for the fields
    myProfile.SUB_PKT_TYPE = 9;
    myProfile.SUB_PKT_LENGTH = 7;
    myProfile.H_TSP = 2;
    myProfile.TO_CNT = 5;
    myProfile.TO_SPEED = 15;
    myProfile.DIFF_DIST_TO = 12;
    myProfile.TO_SPEED_REL_DIST = 15;
    myProfile.PaddingBits = 12;

    // Access the fields
    printf("SUB_PKT_TYPE: %d\n", myProfile.SUB_PKT_TYPE);
    printf("SUB_PKT_LENGTH: %d\n", myProfile.SUB_PKT_LENGTH);
    printf("H_TSP: %d\n", myProfile.H_TSP);
    printf("TO_CNT: %d\n", myProfile.TO_CNT);
    printf("TO_SPEED: %d\n", myProfile.TO_SPEED);
    printf("DIFF_DIST_TO: %d\n", myProfile.DIFF_DIST_TO);
    printf("TO_SPEED_REL_DIST: %d\n", myProfile.TO_SPEED_REL_DIST);
    printf("PaddingBits: %d\n", myProfile.PaddingBits);


}


// int main(void)
// {

//     TurnoutSpeedProfile_testmain();

//     return 0;
// }