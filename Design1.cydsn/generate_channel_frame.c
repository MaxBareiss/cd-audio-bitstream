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

#include "generate_channel_frame.h"
#include "circ_encoder.h"
#include "q_channel_subcode.h"
#include "START_FRAME.h"
#include "efm.h"

#define STATE_LEAD_IN 0
#define STATE_P_SILENCE 1
#define STATE_FIRST_TRACK 2

unsigned int a_output_frame_count;
unsigned int output_frame_count;
//unsigned int tc_frame_count;
//int tc_frame,tc_second,tc_minute;

unsigned int state;

char out_frame_1[74];
char out_frame_2[74];

char fake_data[147];

uint8_t EDIT_1 = 1;

void generate_channel_frame_Start(){
    // Init type stuff
    a_output_frame_count = 0;
    output_frame_count = 0;
    state = STATE_LEAD_IN;
}

inline static uint8_t check_bit(uint16_t bit){
    if (EDIT_1){
        return out_frame_1[bit >> 3] & (1 << (bit & 0x7));
    }else{
        return out_frame_2[bit >> 3] & (1 << (bit & 0x7));
    }
}

inline static uint8_t check_bit_from_buf(uint16_t bit,const char* buf){
    return buf[bit >> 3] & (1 << (bit & 0x7));
}

inline static void set_bit(uint16_t bit){
    //START_FRAME_Write(1);
    if (EDIT_1){
        out_frame_1[bit >> 3] |= (1 << (bit & 0x7));
    }else{
        out_frame_2[bit >> 3] |= (1 << (bit & 0x7));
    }
    //START_FRAME_Write(0);
}

inline static void clear_bit(const uint16_t bit){
    //START_FRAME_Write(1);
    if (EDIT_1){
        out_frame_1[bit >> 3] &= ~(1 << (bit & 0x7));
    }else{
        out_frame_2[bit >> 3] &= ~(1 << (bit & 0x7));
    }
    //START_FRAME_Write(0);
}

inline static void write_bits(uint16_t loc,const char* data,uint8_t length){
    //START_FRAME_Write(1);
    uint8_t i;
    for (i = 0; i < length;++i){
        if (check_bit_from_buf(i,data)){
            set_bit(loc+i);
        }else{
            clear_bit(loc+i);
        }
    }
    
    //START_FRAME_Write(0);
}

inline static void do_padding(uint16_t start_bit_idx){
    uint16_t left_idx = start_bit_idx;
    while (!check_bit(left_idx--)){}
    uint16_t left_count = start_bit_idx - left_idx;
    
    uint16_t right_idx = start_bit_idx+3;
    while (!check_bit(right_idx++)){}
    uint16_t right_count = right_idx - (start_bit_idx + 3);
    
    if (left_count + right_count + 3 > 10){
        if (left_count < 2){
            set_bit(start_bit_idx+2);
            clear_bit(start_bit_idx+1);
            clear_bit(start_bit_idx);
        }else if (right_count < 2){
            clear_bit(start_bit_idx+2);
            clear_bit(start_bit_idx+1);
            set_bit(start_bit_idx);
        }else{
            clear_bit(start_bit_idx+2);
            set_bit(start_bit_idx+1);
            clear_bit(start_bit_idx);
        }
    }
}

volatile uint8_t COMP_DONE = 0;

int generate_channel_frame(){
    if (COMP_DONE == 1){
        return SUCCESS;
    }
    
    //COMP_DONE = 0;
    START_FRAME_Write(1);
    int retval;
    retval = compute_circ();
    //START_FRAME_Write(0);
    //START_FRAME_Write(1);
    //circ_channel_out();
    //char out_frame[74]; // Really 73.5, 588 bits
    //if (EDIT_1){
        //memset(out_frame_1,0,74);
    //}else{
        //memset(out_frame_2,0,74);
    //}
    // Syncronization Pattern
    const char sync_pattern[3] = {0b10000000,0b00010000,0b00000010};
    
    // This didn't gain much time.
    //write_bits(0,sync_pattern,24);
    if (EDIT_1){
        memcpy(out_frame_1,sync_pattern,3);
    }else{
        memcpy(out_frame_2,sync_pattern,3);
    }
    
    unsigned int tc_frame_count =   output_frame_count/98; // Always floor
    unsigned int a_tc_frame_count = a_output_frame_count/98;
    
    uint8_t p = 0;
    
    if (state == STATE_P_SILENCE){
        p = 0b10000000;
    }
    
    uint8_t tc_frame = tc_frame_count%75;
    uint8_t tc_second = (tc_frame_count-tc_frame)/75%60;
    uint8_t tc_minute = (tc_frame_count-tc_second*60-tc_frame)/(60*75);
        
    uint8_t a_tc_frame = a_tc_frame_count%75;
    uint8_t a_tc_second = (a_tc_frame_count-a_tc_frame)/75%60;
    uint8_t a_tc_minute = (a_tc_frame_count-a_tc_second*60-a_tc_frame)/(60*75);
    //START_FRAME_Write(0);
    //START_FRAME_Write(1);
    // SPECIAL SYNC SEQUENCES
    if (a_output_frame_count % 98 == 0){
        const char special_sync_1[2] = {0b00100000,0b00000100};
        write_bits(24+3,special_sync_1,14);
        //out_frame[3] = 0b00100000;
        //out_frame[4] = 0b00000100; // Last 2 are part of the next thing.
        if (state == STATE_LEAD_IN){
            generate_mode_1_q(0,1,tc_minute,tc_second,tc_frame,0,2,32);
        }else if (state == STATE_P_SILENCE){
            generate_mode_1_q(1,0,tc_minute,tc_second,tc_frame,a_tc_minute,a_tc_second,a_tc_frame);
        }else if (state == STATE_FIRST_TRACK){
            generate_mode_1_q(1,1,tc_minute,tc_second,tc_frame,a_tc_minute,a_tc_second,a_tc_frame);
        }
    }else if (a_output_frame_count % 98 == 1){
        const char special_sync_2[2] = {0b00000000,0b01001000};
        write_bits(24+3,special_sync_2,14);
        //out_frame[3] = 0b00000000;
        //out_frame[4] = 0b01001000; // Last 2 are part of the next thing.
    }else{
        uint8_t subcode_symbol = p;
        uint8_t out_frame_idx = a_output_frame_count % 98 - 2;
        uint8_t q_byte = out_frame_idx/8;
        uint8_t q_bit = out_frame_idx%8;
        uint8_t q_data = (mode_1_q[q_byte] >> q_bit) & 1;
        subcode_symbol |= q_data << 7;
        uint16_t efm_res = eight_fourteen(subcode_symbol) << 2;
        write_bits(24+3,(char*)&efm_res,14);
        //out_frame[3] = (efm_res & 0xFF00) >> 8;
        //out_frame[4] = efm_res & 0x00FF;
    }
    //START_FRAME_Write(0);
    //START_FRAME_Write(1);
    int i;
    for (i = 0;i < 32;++i){
        //START_FRAME_Write(0);
        uint16_t efm = eight_fourteen(output_frame[i]);
        //START_FRAME_Write(1);
        //uint16_t efm = 0;
        write_bits(24+3+(14+3)*(i+1),(char*)&efm,14);
    }
    //START_FRAME_Write(0);
    //START_FRAME_Write(1);
    for (i = 0;i < 33;++i){
        do_padding(24+17*i);
    }
    //START_FRAME_Write(0);
    //START_FRAME_Write(1);
    //uint8_t copy_progress = 0;
    
    switch (state){
        case STATE_LEAD_IN:
            a_output_frame_count++;
            output_frame_count++;
        break;
        case STATE_P_SILENCE:
            a_output_frame_count++;
            output_frame_count--;
        break;
        case STATE_FIRST_TRACK:
            a_output_frame_count++;
            output_frame_count++;
        break;
        default:
            CyHalt(2);
    }
    // State Transition Matrix
    switch (state){
        case STATE_LEAD_IN:
            if (tc_second == 5 && tc_frame == 0){
                state = STATE_P_SILENCE;
                a_output_frame_count = 0;
                output_frame_count = 2*75*98+32*98; // 2s 32f
            }
            break;
        case STATE_P_SILENCE:
            if (output_frame_count == 0){
                state = STATE_FIRST_TRACK;
            }
            break;
        case STATE_FIRST_TRACK:
            break;
        default:
            CyHalt(3);
    }
    COMP_DONE = 1;
    START_FRAME_Write(0);
    return SUCCESS;
}