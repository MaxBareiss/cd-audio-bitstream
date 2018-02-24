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

#include "symbol_buffer.h"
#include "START_FRAME.h"

Symbol_Buffer sym_buf;

void Symbol_Buffer_Start(){
    memset(sym_buf.buf,4096,42);
    sym_buf.head = 0;
    sym_buf.tail = 0;
    sym_buf.empty = 0;
    sym_buf.size = 4096;
}

int add_sample(int16_t sample){
    // If there is space left?
    if (sym_buf.tail == sym_buf.head && !sym_buf.empty){
        return ERR_FULL;
    }
    // Banking on Big Endianness
    
    sym_buf.buf[sym_buf.tail] = (unsigned char)((sample & 0xFF00) >> 8);
    
    sym_buf.tail = (sym_buf.tail + 1) % sym_buf.size;
    
    sym_buf.buf[sym_buf.tail] = (unsigned char)(sample & 0x00FF);
    
    sym_buf.tail = (sym_buf.tail + 1) % sym_buf.size;
    
    sym_buf.empty = 0;
    return SUCCESS;
}

int remove_frame(){
    // A frame is defined as 24 consecutive symbols
    // Are there enough symbols in the frame buffer to make an entire frame?
    if ((sym_buf.head + 24) % sym_buf.size > sym_buf.tail){
        return ERR_UNDER_FRAME;
    }
    sym_buf.head = (sym_buf.head + 24) % sym_buf.size;
    if (sym_buf.head == sym_buf.tail){
        sym_buf.empty = 1;
    }
    return SUCCESS;
}

unsigned char* get_sample(unsigned int idx){
    if ((sym_buf.head + idx) % sym_buf.size > sym_buf.tail){
        CyHalt(1);
    }
    return sym_buf.buf + (sym_buf.head + idx) % sym_buf.size;
}

inline unsigned char get_sample2(unsigned int idx, unsigned int delay){
    //if ((sym_buf.head + idx) % sym_buf.size > sym_buf.tail){
    //    CyHalt(1);
    //}
    //START_FRAME_Write(1);
    uint16_t resultant = (sym_buf.tail + idx - (delay+1)*24 + 1)%sym_buf.size;
    //uint16_t buf_vol = buffer_volume();
    //int lhs = idx - (delay+1)*24 + sym_buf.size + 1;
    //if (lhs > buf_vol){
    //    CyHalt(1);
    //}
    //START_FRAME_Write(0);
    return sym_buf.buf[resultant];
}

inline int buffer_volume(){
    if (sym_buf.head == sym_buf.tail){
        if (sym_buf.empty){
            return 0;
        } else {
            return sym_buf.size;
        }
    }
    return (sym_buf.tail-sym_buf.head)%sym_buf.size;
}