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
#ifndef GENERATE_CHANNEL_FRAME_H
#define GENERATE_CHANNEL_FRAME_H
    
#include <stdint.h>
    
#define SUCCESS 0
    
void generate_channel_frame_Start();
    
int generate_channel_frame();
    
extern char out_frame_1[74];
extern char out_frame_2[74];

extern uint8_t EDIT_1;

extern volatile uint8_t COMP_DONE;

extern char fake_data[147];

#endif