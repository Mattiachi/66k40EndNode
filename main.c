/* Author:  Chiappalone Mattia
 * Date:    March 2023
 * Version: v1.0. 
 * 
 * MPLAB X IDE v3.40
 * XC8 v.138 PRO
 * Microcontroller: PIC18LF66K40 (sleep current 20nA @1.8V)
 * 
 * Description:
 * The LED is on while the radio module is not configured 
 * to send a packet. Once it turns off it means that is ready
 * to send a packet. 
 * Once every 10 seconds the led flashes and a payload is queued 
 * to be sent with spreading factor 12 to the Chirpstack 
 * application matching the Network Session Key
 * and App Session Key. 
 * 
 * 
 * Tested:
 * 1) Join LoRaWAN Network sending a string 
 * 2) 1) Blink LED on PortRC7 (1)
 * 
 * To test:
 *  
 * 1) Tx pin for EUSART on pin RC6 (31)
 * 2) Sleeping Mode
 * 3) Add ADC capability
 * 
 *  PIC connection respect to Olimex Radio Module:
 *  RB0 (48) -> DIO5
 *  RB1 (47) -> DIO0
 *  RB2 (46) -> DIO1
 *  RB4 (44) -> DIO2
 *  RC2 (33) -> NRESET
 *  RD3 (53) -> NSS
 *  
 *  RC3 (50) -> SCK
 *  RC5 (49) -> SDI or MISO
 *  RC4 (51) -> SDO or MOSI
*/
#include "mcc_generated_files/mcc.h"
//#include <stdio.h>      // To use printf in EUSART1

// my functions
void sendPacket(void);
void flash(void);

// Variables
int portNumber = 2;
uint16_t payload[1];
uint8_t JoinedServer = 0;
int count = 1;          // Number of packets sent

// Premade functions for LoRaWAN & variables
uint8_t nwkSKey[16] = {0x6A, 0xC2, 0xD7, 0x90, 0x05, 0x62, 0x34, 0x76, 0xD0, 0x8D, 0x5F, 0x9C, 0x57, 0x07, 0xA3, 0xFF};
uint8_t appSKey[16] = {0x3F, 0x1F, 0x99, 0x58, 0xDF, 0xCB, 0x63, 0x7F, 0xAD, 0xC0, 0x60, 0x8E, 0x16, 0x4B, 0x22, 0xB7};
uint32_t devAddr = 0x00006640;
void RxDataDone(uint8_t* pData, uint8_t dataLength, OpStatus_t status);
void RxJoinResponse(bool status);

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();
    
    //printf("System Initialized");   // Baud Rate 300
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    myLED_SetHigh();                // Custom function written by MCC
    
    LORAWAN_Init(RxDataDone, RxJoinResponse);
    LORAWAN_SetNetworkSessionKey(nwkSKey);
    LORAWAN_SetApplicationSessionKey(appSKey);
    LORAWAN_SetDeviceAddress(devAddr);
    LORAWAN_Join(ABP);
    
       while(JoinedServer == 0){   // While the network isnt joined do nothing...
        LORAWAN_Mainloop();
        myLED_SetLow();
    }
    
    int flag = 5;   // When flag reaches 10 it can send a message

    while (1)
    {   
        LORAWAN_Mainloop();
        flag++;
        
        if(flag > 10){
            flag = 0;
            flash();
            sendPacket();
        }
     for(int x = 0; x < 1000; x++) __delay_ms(1);   // delay of one second
     
    } // End of while
} // End of main

void sendPacket(void){
    //myLED_SetHigh();
    payload[0] = 0xFF00;
    LORAWAN_Send(UNCNF, portNumber, &payload, sizeof(payload)); 
    //printf("Packet #%d sent: temperature value: %d\n\r", count, payload[0]);
    count++;
    //myLED_SetLow();
}

void RxDataDone(uint8_t* pData, uint8_t dataLength, OpStatus_t status)
{
}

void RxJoinResponse(bool status)
{    
    JoinedServer = 1;
}

void flash(void){
    for(uint8_t x = 0; x < 10; x++){
        myLED_Toggle();
        __delay_ms(25);
        __delay_ms(25);
    }
    myLED_SetLow();
}
