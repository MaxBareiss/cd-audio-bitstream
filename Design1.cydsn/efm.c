/* ========================================
 *
 * Copyright YOUR COMPANY00, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED00, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/* [] END OF FILE */
#include "efm.h"

uint16_t EFM_TABLE[256] = {0b0100100010000000,
0b1000010000000000,
0b1001000010000000,
0b1000100010000000,
0b0100010000000000,
0b0000010001000000,
0b0001000010000000,
0b0010010000000000,
0b0100100100000000,
0b1000000100000000,
0b1001000100000000,
0b1000100100000000,
0b0100000100000000,
0b0000000100000000,
0b0001000100000000,
0b0010000100000000,
0b1000000010000000,
0b1000001000000000,
0b1001001000000000,
0b0010000010000000,
0b0100001000000000,
0b0000001000000000,
0b0001001000000000,
0b0010001000000000,
0b0100100001000000,
0b1000000001000000,
0b1001000001000000,
0b1000100001000000,
0b0100000001000000,
0b0000100001000000,
0b0001000001000000,
0b0010000001000000,
0b0000000010000000,
0b1000010000100000,
0b0000100010000000,
0b0010010010000000,
0b0100010000100000,
0b0000010000100000,
0b0100000010000000,
0b0010010000100000,
0b0100100100100000,
0b1000000100100000,
0b1001000100100000,
0b1000100100100000,
0b0100000100100000,
0b0000000100100000,
0b0001000100100000,
0b0010000100100000,
0b0000010000000000,
0b1000001000100000,
0b1001001000100000,
0b1000010001000000,
0b0100001000100000,
0b0000001000100000,
0b0001001000100000,
0b0010001000100000,
0b0100100000100000,
0b1000000000100000,
0b1001000000100000,
0b1000100000100000,
0b0100000000100000,
0b0000100000100000,
0b0001000000100000,
0b0010000000100000,
0b0100100010010000,
0b1000010010010000,
0b1001000010010000,
0b1000100010010000,
0b0100010010010000,
0b0000000010010000,
0b0001000010010000,
0b0010010010010000,
0b0100100100010000,
0b1000000100010000,
0b1001000100010000,
0b1000100100010000,
0b0100000100010000,
0b0000000100010000,
0b0001000100010000,
0b0010000100010000,
0b1000000010010000,
0b1000001000010000,
0b1001001000010000,
0b0010000010010000,
0b0100001000010000,
0b0000001000010000,
0b0001001000010000,
0b0010001000010000,
0b0100100000010000,
0b1000000000010000,
0b1001000000010000,
0b1000100000010000,
0b0100000000010000,
0b0000100000010000,
0b0001000000010000,
0b0010000000010000,
0b0100100010001000,
0b1000010010001000,
0b1001000010001000,
0b1000100010001000,
0b0100010010001000,
0b0000000010001000,
0b0100000010010000,
0b0010010010001000,
0b0100100100001000,
0b1000000100001000,
0b1001000100001000,
0b1000100100001000,
0b0100000100001000,
0b0000000100001000,
0b0001000100001000,
0b0010000100001000,
0b1000000010001000,
0b1000001000001000,
0b1001001000001000,
0b0010000010001000,
0b0100001000001000,
0b0000001000001000,
0b0001001000001000,
0b0010001000001000,
0b0100100000001000,
0b0000100100100000,
0b1001000000001000,
0b1000100000001000,
0b0100000000001000,
0b0000100000001000,
0b0001000000001000,
0b0010000000001000,
0b0100100010000100,
0b1000010010000100,
0b1001000010000100,
0b1000100010000100,
0b0100010010000100,
0b0000000010000100,
0b0001000010000100,
0b0010010010000100,
0b0100100100000100,
0b1000000100000100,
0b1001000100000100,
0b1000100100000100,
0b0100000100000100,
0b0000000100000100,
0b0001000100000100,
0b0010000100000100,
0b1000000010000100,
0b1000001000000100,
0b1001001000000100,
0b0010000010000100,
0b0100001000000100,
0b0000001000000100,
0b0001001000000100,
0b0010001000000100,
0b0100100000000100,
0b1000001001000000,
0b1001000000000100,
0b1000100000000100,
0b0100001001000000,
0b0000100000000100,
0b0001000000000100,
0b0010001001000000,
0b0000100010000100,
0b1000010000100100,
0b0100010001000000,
0b0000010010000100,
0b0100010000100100,
0b0000010000100100,
0b0100000010000100,
0b0010010000100100,
0b0100100100100100,
0b1000000100100100,
0b1001000100100100,
0b1000100100100100,
0b0100000100100100,
0b0000000100100100,
0b0001000100100100,
0b0010000100100100,
0b0000010010000000,
0b1000001000100100,
0b1001001000100100,
0b0010010001000000,
0b0100001000100100,
0b0000001000100100,
0b0001001000100100,
0b0010001000100100,
0b0100100000100100,
0b1000000000100100,
0b1001000000100100,
0b1000100000100100,
0b0100000000100100,
0b0000100000100100,
0b0001000000100100,
0b0010000000100100,
0b0100010010000000,
0b1000010001000100,
0b1001001001000000,
0b0000100010010000,
0b0100010001000100,
0b0000010001000100,
0b0001001001000000,
0b0010010001000100,
0b0000100100000100,
0b1000010000000100,
0b0000100100010000,
0b0000100100000000,
0b0100010000000100,
0b0000010000000100,
0b0000001001000000,
0b0010010000000100,
0b0000010010010000,
0b1000001001000100,
0b1001001001000100,
0b1000010010000000,
0b0100001001000100,
0b0000001001000100,
0b0001001001000100,
0b0010001001000100,
0b0100100001000100,
0b1000000001000100,
0b1001000001000100,
0b1000100001000100,
0b0100000001000100,
0b0000100001000100,
0b0001000001000100,
0b0010000001000100,
0b0100010000001000,
0b0000010000001000,
0b1000010001001000,
0b0010010000001000,
0b0100010001001000,
0b0000010001001000,
0b0100000010001000,
0b0010010001001000,
0b1000010000001000,
0b1000010000010000,
0b0000100100100100,
0b0000100100001000,
0b0100010000010000,
0b0000010000010000,
0b0001000010001000,
0b0010010000010000,
0b0000010010001000,
0b1000001001001000,
0b1001001001001000,
0b0000100010001000,
0b0100001001001000,
0b0000001001001000,
0b0001001001001000,
0b0010001001001000,
0b0100100001001000,
0b1000000001001000,
0b1001000001001000,
0b1000100001001000,
0b0100000001001000,
0b0000100001001000,
0b0001000001001000,
0b00100000010010};

inline uint16_t eight_fourteen(uint8_t val){
    return EFM_TABLE[val];
}