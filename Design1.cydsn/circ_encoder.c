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
#include "circ_encoder.h"
#include "symbol_buffer.h"
#include "parity_buffer.h"
#include "ecc.h"
#include "efm.h"

char output_frame[32];
char old_data_symbol[32];
char output_efm_frame[69];

/* [] END OF FILE */
int compute_circ(){
    // Figure 12
    if (buffer_volume() < 2592){
        return ERR_UNDERFLOW;
    }
    
    char rs_buffer[28];
    rs_buffer[0]  = get_sample2(0,2);
    rs_buffer[1]  = get_sample2(1,2);
    rs_buffer[2]  = get_sample2(8,2);
    rs_buffer[3]  = get_sample2(9,2);
    rs_buffer[4]  = get_sample2(16,2);
    rs_buffer[5]  = get_sample2(17,2);
    rs_buffer[6]  = get_sample2(2,2);
    rs_buffer[7]  = get_sample2(3,2);
    rs_buffer[8]  = get_sample2(10,2);
    rs_buffer[9]  = get_sample2(11,2);
    rs_buffer[10] = get_sample2(18,2);
    rs_buffer[11] = get_sample2(19,2);
    rs_buffer[12] = get_sample2(4,0);
    rs_buffer[13] = get_sample2(5,0);
    rs_buffer[14] = get_sample2(12,0);
    rs_buffer[15] = get_sample2(13,0);
    rs_buffer[16] = get_sample2(20,0);
    rs_buffer[17] = get_sample2(21,0);
    rs_buffer[18] = get_sample2(6,0);
    rs_buffer[19] = get_sample2(7,0);
    rs_buffer[20] = get_sample2(14,0);
    rs_buffer[21] = get_sample2(15,0);
    rs_buffer[22] = get_sample2(22,0);
    rs_buffer[23] = get_sample2(23,0);
    
    char encoded[32];
    
    encode_data(rs_buffer,24,encoded);
    
    char* parity = &encoded[24];
    
    pb_add_sample(parity);
    
    rs_buffer[0]  = get_sample2(0 ,2);
    rs_buffer[1]  = get_sample2(1 ,6);
    rs_buffer[2]  = get_sample2(8 ,10);
    rs_buffer[3]  = get_sample2(9 ,3*4+2);
    rs_buffer[4]  = get_sample2(16,4*4+2);
    rs_buffer[5]  = get_sample2(17,5*4+2);
    rs_buffer[6]  = get_sample2(2 ,6*4+2);
    rs_buffer[7]  = get_sample2(3 ,7*4+2);
    rs_buffer[8]  = get_sample2(10,8*4+2);
    rs_buffer[9]  = get_sample2(11,9*4+2);
    rs_buffer[10] = get_sample2(18,10*4+2);
    rs_buffer[11] = get_sample2(19,11*4+2);
    
    rs_buffer[12] = pb_get_sample2(0,12*4)^0xFF;
    rs_buffer[13] = pb_get_sample2(1,13*4)^0xFF;
    rs_buffer[14] = pb_get_sample2(2,14*4)^0xFF;
    rs_buffer[15] = pb_get_sample2(3,15*4)^0xFF;
    
    rs_buffer[16] = get_sample2(4 ,16*4);
    rs_buffer[17] = get_sample2(5 ,17*4);
    rs_buffer[18] = get_sample2(12,18*4);
    rs_buffer[19] = get_sample2(13,19*4);
    rs_buffer[20] = get_sample2(20,20*4);
    rs_buffer[21] = get_sample2(21,21*4);
    rs_buffer[22] = get_sample2(6 ,22*4);
    rs_buffer[23] = get_sample2(7 ,23*4);
    rs_buffer[24] = get_sample2(14,24*4);
    rs_buffer[25] = get_sample2(15,25*4);
    rs_buffer[26] = get_sample2(22,26*4);
    rs_buffer[27] = get_sample2(23,27*4);
    
    encode_data(rs_buffer,28,encoded);
    
    int i;
    
    for (i = 0; i < 32;i += 2){
        output_frame[i] = old_data_symbol[i];
    }
    for (i = 1; i < 32;i += 2){
        output_frame[i] = encoded[i];
    }
    
    memcpy(old_data_symbol,encoded,32);
    remove_frame();
    pb_remove_frame();
    return SUCCESS;
}

void circ_channel_out(){
     // 68.75
    memset(output_efm_frame,0,69);
    uint8_t byte_start = 0;
    uint8_t bit_start = 0;
    
    int i;
    for(i=0;i<32;i++){
        uint8_t bit_index = 14; // Number of bits you still need to write
        uint16_t efm_value = eight_fourteen(output_frame[i]) << 2;
        
        // Calcualte 8to14 and add it to the bit stream
        while(bit_index != 0) {
            uint8_t n_bits_to_write;
            if (bit_index > 8 - bit_start){
                // You have more bits to write than fit in the byte
                n_bits_to_write = 8 - bit_start;
            } else {
                // You have less bits than fit in the byte
                n_bits_to_write = bit_index;
            }
            uint8_t bits_to_write = efm_value >> (16-n_bits_to_write);
            
            output_efm_frame[byte_start] |= bits_to_write << bit_start;
            
            bit_index -= n_bits_to_write; // Decrement the number of bits to add
            // Update the byte and bit indexes to the stream
            if (n_bits_to_write + bit_start == 8){
                byte_start++;
                bit_start = 0;
            } else {
                bit_start += n_bits_to_write;
            }
            efm_value = efm_value << n_bits_to_write;
        }
        
        // Calculate Padding Bits...later
        bit_start = bit_start + 3;
        if (bit_start >= 8){
            bit_start = bit_start % 8;
            byte_start++;
        }
        
        // Calculate previous padding bits
        if (i > 1){
            int padding_bit_start = bit_start - 14;
            int padding_byte_start = byte_start;
            while (padding_bit_start < 0){
                padding_bit_start += 8;
                padding_byte_start--;
            }
            int before_bit = padding_bit_start;
            int before_byte = padding_byte_start;
            uint8_t before_zeros = 0;
            while (1){
                before_bit--;
                if (before_bit < 0){
                    before_bit += 8;
                    before_byte--;
                }
                if (!(output_efm_frame[before_byte] & (1 << before_bit))){
                    break;
                }else{
                    before_zeros++;
                }
            }
            int after_bit = padding_bit_start;
            int after_byte = padding_byte_start;
            after_bit += 3;
            if (after_bit >= 8){
                after_bit -= 8;
                after_byte++;
            }
            uint8_t after_zeros = 0;
            while (1){
                after_bit++;
                if (after_bit >= 8){
                    after_bit -= 8;
                    after_byte++;
                }
                if (!(output_efm_frame[after_byte] & (1 << after_bit))){
                    break;
                }else{
                    after_zeros++;
                }
            }
            
            if (before_zeros + after_zeros + 3 > 10){
                if (before_zeros < 2){
                    uint8_t set_bit_start = padding_bit_start;
                    uint8_t set_byte_start = padding_byte_start;
                    set_bit_start += 2;
                    if (set_bit_start >= 8){
                        set_bit_start -= 8;
                        set_byte_start++;
                    }
                    output_efm_frame[set_byte_start] |= 1 << set_bit_start;
                }else if (after_zeros < 2){
                    output_efm_frame[padding_byte_start] |= 1 << padding_bit_start;
                }else{
                    uint8_t set_bit_start = padding_bit_start;
                    uint8_t set_byte_start = padding_byte_start;
                    set_bit_start += 1;
                    if (set_bit_start >= 8){
                        set_bit_start -= 8;
                        set_byte_start++;
                    }
                    output_efm_frame[set_byte_start] |= 1 << set_bit_start;
                }
            }
        }
    }
}

void circ_efm(){
    char output[69];
    
    uint8_t byte_start = 0;
    uint8_t bit_start = 0;
    int i;
    for (i = 0; i < 32;++i){
        uint16_t efm_value = eight_fourteen(output_frame[i]) << 2;
        uint8_t startByte = (i*14) / 8;
        uint8_t startBit = i*14 % 8;
        uint8_t endByte = ((i+1)*14) / 8;
        uint8_t endBit = (i+1)*14 % 8;
        if (endByte-startByte == 1){
            uint8_t startData = efm_value >> (8+startBit);
            output[startByte] |= startData;
            uint8_t endData = (efm_value << (8-startBit)) >> endBit;
            output[endByte] = endData;
        }else{ // Three bytes spanned
            uint8_t startData = efm_value >> (8+startBit);
            output[startByte] |= startData;
            uint8_t middleData = (efm_value << (8-startBit)) >> 8;
            output[startByte+1] = middleData;
            uint8_t endData = (efm_value << (16-startBit)) >> 8;
            output[endByte] = endData;
        }
    }
}
