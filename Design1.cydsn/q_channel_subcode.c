/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#include "q_channel_subcode.h"
#include <stdint.h>

char mode_1_q[12];

char dec_to_bcd(int val){
    char res = 0;
    int LSD = val % 10;
    res = LSD;
    int MSD = (val-LSD)/10;
    res |= MSD << 4;
    return res;
}

uint16_t Compute_CRC16_Simple(char* data, unsigned int length){
    uint16_t generator = 0x1021;	/* divisor is 16bit */
    uint16_t crc = 0; /* CRC value is 16bit */

    unsigned int i;
    for (i = 0; i < length;++i)
    {
        crc ^= (uint16_t)(data[i] << 8); /* move byte into MSB of 16bit CRC */
        int j;
        for (j = 0; j < 8; j++)
        {
            if ((crc & 0x8000) != 0) /* test for MSB = bit 15 */
            {
                crc = (uint16_t)((crc << 1) ^ generator);
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}

void generate_mode_1_q(int track_no,int point_x,int   minute, int   second, int   frame,
                                              int ap_minute, int ap_second, int ap_frame){
    // CONTROL, ADR
    mode_1_q[0] = 0b00100001;
    // TNO (Track No)
    if (track_no == -1){
        // Lead out
        mode_1_q[1] = 0xAA;
    }else{
        mode_1_q[1] = dec_to_bcd(track_no);
    }
    
    // X (idx to track no)
    mode_1_q[2] = dec_to_bcd(point_x);
    
    // MIN, SEC, FRAME
    mode_1_q[3] = dec_to_bcd(minute);
    mode_1_q[4] = dec_to_bcd(second);
    mode_1_q[5] = dec_to_bcd(frame);
    
    // ZERO
    mode_1_q[6] = 0;
    
    // AMIN, ASEC, AFRAME
    mode_1_q[7] = dec_to_bcd(ap_minute);
    mode_1_q[8] = dec_to_bcd(ap_second);
    mode_1_q[9] = dec_to_bcd(ap_frame);
    
    // REDUNDANCY CHECKING
    
    uint16_t crc_val = Compute_CRC16_Simple(mode_1_q,10);
    
    mode_1_q[10] = (crc_val & 0xFF00) >> 8;
    mode_1_q[11] = (crc_val & 0x00FF);
}