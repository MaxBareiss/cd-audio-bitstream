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

#ifndef CIRC_ENCODER_H
#define CIRC_ENCODER_H
    

#define ERR_UNDERFLOW -1
    
    
int compute_circ();
void circ_channel_out();

extern char output_efm_frame[69];
extern char output_frame[32];
    
#endif