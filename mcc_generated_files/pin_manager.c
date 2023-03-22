/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.0
        Device            :  PIC18LF66K40
        Driver Version    :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/

#include <xc.h>
#include "pin_manager.h"
#include "stdbool.h"

void (*IOCBF4_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */   
    LATE = 0x00;    
    LATD = 0x00;    
    LATA = 0x00;    
    LATF = 0x00;    
    LATB = 0x00;    
    LATG = 0x00;    
    LATC = 0x00;    
    LATH = 0x00;    

    /**
    TRISx registers
    */    
    TRISE = 0xFF;
    TRISF = 0xFF;
    TRISA = 0xFE;
    TRISG = 0xDF;
    TRISB = 0xFF;
    TRISH = 0x0F;
    TRISC = 0xBF;
    TRISD = 0x97;

    /**
    ANSELx registers
    */   
    ANSELB = 0xE0;
    ANSELD = 0x77;
    ANSELE = 0xFF;
    ANSELG = 0xFF;
    ANSELF = 0xFF;
    ANSELA = 0xFF;

    /**
    WPUx registers
    */ 
    WPUD = 0xFF;
    WPUF = 0xFF;
    WPUE = 0xFF;
    WPUB = 0xFF;
    WPUG = 0xFF;
    WPUA = 0xFF;
    WPUC = 0xFF;
    WPUH = 0x0F;

    /**
    ODx registers
    */   
    ODCONE = 0x00;
    ODCONF = 0x00;
    ODCONA = 0x00;
    ODCONG = 0x00;
    ODCONB = 0x00;
    ODCONH = 0x00;
    ODCONC = 0x00;
    ODCOND = 0x00;
    

    /**
    IOCx registers
    */
    // interrupt on change for group IOCBF - flag
    IOCBFbits.IOCBF4 = 0;
    // interrupt on change for group IOCBN - negative
    IOCBNbits.IOCBN4 = 1;
    // interrupt on change for group IOCBP - positive
    IOCBPbits.IOCBP4 = 1;

    // register default IOC callback functions at runtime; use these methods to register a custom function
    IOCBF4_SetInterruptHandler(IOCBF4_DefaultInterruptHandler);
   
    // Enable IOCI interrupt 
    PIE0bits.IOCIE = 1; 
    
    
    bool state = GIE;
    GIE = 0;
    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

    INT1PPSbits.INT1PPS = 0x09;   //RB1->EXT_INT:INT1;
    INT3PPSbits.INT3PPS = 0x0B;   //RB3->EXT_INT:INT3;
    RD5PPS = 0x1C;   //RD5->MSSP2:SDO2;
    INT0PPSbits.INT0PPS = 0x08;   //RB0->EXT_INT:INT0;
    INT2PPSbits.INT2PPS = 0x0A;   //RB2->EXT_INT:INT2;
    RC6PPS = 0x0C;   //RC6->EUSART1:TX1;
    RD6PPS = 0x1B;   //RD6->MSSP2:SCK2;
    SSP2DATPPSbits.SSP2DATPPS = 0x1F;   //RD7->MSSP2:SDI2;

    PPSLOCK = 0x55;
    PPSLOCK = 0xAA;
    PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS

    GIE = state;
}       

void PIN_MANAGER_IOC(void)
{   
    // interrupt on change for pin IOCBF4
    if(IOCBFbits.IOCBF4 == 1)
    {
        IOCBF4_ISR();  
    }                          


}

/**
   IOCBF4 Interrupt Service Routine
*/
void IOCBF4_ISR(void) {

    // Add custom IOCBF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(IOCBF4_InterruptHandler)
    {
        IOCBF4_InterruptHandler();
    }
    IOCBFbits.IOCBF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF4 at application runtime
*/
void IOCBF4_SetInterruptHandler(void* InterruptHandler){
    IOCBF4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF4
*/
void IOCBF4_DefaultInterruptHandler(void){
    // add your IOCBF4 interrupt custom code
    // or set custom function using IOCBF4_SetInterruptHandler()
}

/**
 End of File
*/