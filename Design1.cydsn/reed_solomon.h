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

#include "stdint.h"

void reed_solomon_Start();

void reed_solomon_encode();

extern int16_t rs_data[28];

void encode_rs();
void decode_rs();

extern int16_t bb[4];
extern int16_t recd[32];