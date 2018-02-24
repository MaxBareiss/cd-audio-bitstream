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
#ifndef Q_CHANNEL_SUBCODE_H
#define Q_CHANNEL_SUBCODE_H
    
void generate_mode_1_q(int track_no,int point_x,int   minute, int   second, int   frame,
                                              int ap_minute, int ap_second, int ap_frame);
char dec_to_bcd(int val);    

extern char mode_1_q[12];

#endif