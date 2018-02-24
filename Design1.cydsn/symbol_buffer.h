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

#ifndef SYMBOL_BUFFER_H
#define SYMBOL_BUFFER_H
    
#include <stdint.h>

#define SUCCESS 0
#define ERR_FULL -1
#define ERR_UNDER_FRAME -2

/* [] END OF FILE */
typedef struct {
    unsigned char buf[4096];
    unsigned int size;
    unsigned int head;
    unsigned int tail;
    uint8_t empty;
} Symbol_Buffer;

extern Symbol_Buffer sym_buf;

int add_sample(int16_t sample);
int remove_frame();
unsigned char* get_sample(unsigned int idx);
unsigned char get_sample2(unsigned int idx, unsigned int delay);
void Symbol_Buffer_Start();
int buffer_volume();

#endif