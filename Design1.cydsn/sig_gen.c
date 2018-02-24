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
#include "sig_gen.h"
#include <math.h>

const int SAMPLE_RATE = 44100;
const float FREQ = 1000.0f;

float phase;

void Sig_Gen_Start(){
    phase = 0.0f;
}

int16_t generate_sample(){
    //phase += 2*3.14159*FREQ/SAMPLE_RATE;
    //return (int16_t)(sin(phase)*16384);
    return 0;
}

