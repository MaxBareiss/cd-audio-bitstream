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
#include "project.h"
#include "symbol_buffer.h"
#include "parity_buffer.h"
#include "sig_gen.h"
#include "circ_encoder.h"
#include "ecc.h"
#include "generate_channel_frame.h"

#define DMA_DST_BASE (CYDEV_PERIPH_BASE)  /* Destination base address */

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    Sig_Gen_Start();
    Symbol_Buffer_Start();
    Parity_Buffer_Start();
    initialize_ecc();
    generate_channel_frame_Start();
    ShiftReg_Start();
    
    unsigned long count = 0;
    //assert(1);
    //CyHalt(1);
    
    //memset(fake_data,0b10101010,147);
    int i;
    for (i = 0; i < 147;++i){
        fake_data[i] = i;
    }
    memset(fake_data,127,10);
    isr_fifo_Start();
    //uint8 DMA_Chan;               /* The DMA Channel */
    //uint8 DMA_TD[1];	          /* The DMA Transaction Descriptor (TD) */  	
    
    //DMA_Chan = DMA_DmaInitialize(1, 1, HI16(fake_data), HI16(CYDEV_PERIPH_BASE) );
    
    //DMA_TD[0] = CyDmaTdAllocate();
    
    //CyDmaTdSetConfiguration(DMA_TD[0], 147, DMA_TD[0], TD_INC_SRC_ADR);
    
    //CyDmaTdSetAddress(DMA_TD[0], LO16((uint32)fake_data), LO16((uint32)ShiftReg_SHIFT_REG_LSB_PTR) );
    
    //CyDmaChSetInitialTd(DMA_Chan, DMA_TD[0]);
    
    
    //CyDmaChEnable(DMA_Chan, 1);
    
    //while (1){
        
        //for (i = 0; i < 147;++i){
        //    START_FRAME_Write(1);
        //    while (ShiftReg_GetFIFOStatus(ShiftReg_IN_FIFO) == ShiftReg_RET_FIFO_FULL){}
        //    ShiftReg_WriteData(fake_data[i]);
        //    START_FRAME_Write(0);
        //}
        
    //}
    for(;;)
    {
        int16_t sample = generate_sample();
        int retval = add_sample(sample);
        //START_FRAME_Write(1);
        retval = generate_channel_frame();
        //if (retval == SUCCESS){
        //    while (1) {}
        //}
        //START_FRAME_Write(0);
        //for (i = 0; i < 74;++i){
            //while (ShiftReg_GetFIFOStatus(ShiftReg_OUT_FIFO) == ShiftReg_RET_FIFO_FULL){}
            //ShiftReg_WriteData(out_frame[i]);
            //ShiftReg_WriteData(0b10101010);
        //}
        ++count;
    }
}

/* [] END OF FILE */
