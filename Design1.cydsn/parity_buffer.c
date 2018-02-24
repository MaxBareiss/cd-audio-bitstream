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
#include "parity_buffer.h"


Parity_Buffer par_1_buf;

void Parity_Buffer_Start(){
    memset(par_1_buf.buf,PB_SIZE,42);
    par_1_buf.head = 0;
    par_1_buf.tail = 0;
    par_1_buf.empty = 0;
    par_1_buf.size = PB_SIZE;
}

int pb_add_sample(char* sample){
    // If there is space left?
    if (par_1_buf.tail == par_1_buf.head && !par_1_buf.empty){
        return PB_ERR_FULL;
    }
    int i;
    for (i = 0;i < 4; ++i){
        par_1_buf.buf[(par_1_buf.tail+i)%par_1_buf.size] = sample[i];
    }
    par_1_buf.tail = (par_1_buf.tail+4)%par_1_buf.size;
    
    par_1_buf.empty = 0;
    return PB_SUCCESS;
}

int pb_remove_frame(){
    // A frame is defined as 4 consecutive symbols
    // Are there enough symbols in the frame buffer to make an entire frame?
    if (par_1_buf.head == par_1_buf.tail && par_1_buf.empty){
        return PB_ERR_UNDER_FRAME;
    }
    par_1_buf.head = (par_1_buf.head + 4) % par_1_buf.size;
    if (par_1_buf.head == par_1_buf.tail){
        par_1_buf.empty = 1;
    }
    return PB_SUCCESS;
}

unsigned char pb_get_sample2(unsigned int idx, unsigned int delay){
    int resultant = (par_1_buf.tail + idx - (delay+1)*4 + 1)%par_1_buf.size;
    //unsigned int buf_vol = pb_buffer_volume();
    //int lhs = idx - (delay+1)*4 + par_1_buf.size + 1;
    //if (lhs > buf_vol){
    //    CyHalt(1);
    //}
    return par_1_buf.buf[resultant];
}

unsigned int pb_buffer_volume(){
    if (par_1_buf.head == par_1_buf.tail){
        if (par_1_buf.empty){
            return 0;
        } else {
            return par_1_buf.size;
        }
    }
    return (par_1_buf.tail-par_1_buf.head)%par_1_buf.size;
}