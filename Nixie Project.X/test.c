/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.80.0
        Device            :  PIC18F57Q43
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define O_A0 PORTAbits.RA0
#define O_A2 PORTAbits.RA2
#define O_A3 PORTAbits.RA3
#define O_A4 PORTAbits.RA4
#define O_A5 PORTAbits.RA5
#define O_A6 PORTAbits.RA6
#define O_A7 PORTAbits.RA7

//
//#define O_B0  PORTBbits.RB0
//#define O_B1  PORTBbits.RB1
//#define O_B2  PORTBbits.RB2
//#define O_B3  PORTBbits.RB3
//#define O_B4  PORTBbits.RB4
//#define O_B5  PORTBbits.RB5
//#define O_B6  PORTBbits.RB6
//#define O_B7  PORTBbits.RB7
//
//#define O_C0  PORTCbits.RC0
//#define O_C1  PORTCbits.RC1
//#define O_C2  PORTCbits.RC2
//#define O_C3  PORTCbits.RC3
//#define O_C4  PORTCbits.RC4
//#define O_C5  PORTCbits.RC5
//#define O_C6  PORTCbits.RC6
//#define O_C7  PORTCbits.RC7
//
//#define O_D0  PORTDbits.RD0
//#define O_D1  PORTDbits.RD1
//#define O_D2  PORTDbits.RD2
//#define O_D3  PORTDbits.RD3
//#define O_D4  PORTDbits.RD4
//#define O_D5  PORTDbits.RD5
//#define O_D6  PORTDbits.RD6
//#define O_D7  PORTDbits.RD7
//
//#define O_F0  PORTFbits.RF0
//#define O_F1  PORTFbits.RF1
//#define O_F2  PORTFbits.RF2
//#define O_F3  PORTFbits.RF3
//#define O_F4  PORTFbits.RF4
//#define O_F5  PORTFbits.RF5
//#define O_F6  PORTFbits.RF6
//#define O_F7  PORTFbits.RF7

void Flip_Pins();
void Count_To();

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();
    int counter = 0;
    int MS_Nib;
    int LS_Nib;
    while (1)
    {
        //        Flip_Pins();

        //        TRISA = 0x00;

        Count_To(counter);

        counter += 1;
        
        // Add your application code
    }
}

void Count_To(int count_to)
{
    int counter = 0;
    int MS_Nib = 0, LS_Nib = 0;
    while (counter < count_to)
    {
        MS_Nib = 0;
        PORTA = 0x00;

        MS_Nib = counter << 4;
        LS_Nib = counter;
        //        PORTA = MS_Nib | LS_Nib;
        PORTA = counter;
        __delay_ms(1000);

        counter += 1;   
    }
}

void Flip_Pins()
{
    PORTA = 0xFF;
    PORTB = 0xFF;
    PORTC = 0xFF;
    PORTD = 0xFF;
    PORTF = 0xFF;

    __delay_ms(2000);

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTF = 0x00;
}

/**
 End of File
*/