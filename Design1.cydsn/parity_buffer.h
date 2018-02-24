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
#ifndef PARITY_BUFFER_H
#define PARITY_BUFFER_H
#include <stdint.h>

#define PB_SUCCESS 0
#define PB_ERR_FULL -1
#define PB_ERR_UNDER_FRAME -2
#define PB_SIZE (60*4)

/* [] END OF FILE */

typedef struct {
    unsigned char buf[PB_SIZE];
    unsigned int size;
    unsigned int head; // Inclusive
    unsigned int tail; // Exclusive
    uint8_t empty;
} Parity_Buffer;

extern Parity_Buffer par_1_buf;

int pb_add_sample(char* sample);
int pb_remove_frame();
unsigned char* pb_get_sample(unsigned int idx);
unsigned char pb_get_sample2(unsigned int idx, unsigned int delay);
void Parity_Buffer_Start();
unsigned int pb_buffer_volume();
#endif