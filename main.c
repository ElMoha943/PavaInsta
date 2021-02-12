// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = ON        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include "pava.h"
#include <string.h>
void main(){
    //Configura entradas y salidas
    ANSEL=0b00000010; //1=entrada analogica 0=entrada digital
    ADCON0=0b10000111;
    ADCON1=10000000;
    TRISA=0b00000011;
    TRISB=0b00000000;
    TRISD=0x00;
    TRISE=0x00;
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
    PORTE=0x00;
    //Configura UART a 9600 baudios
    TXSTAbits.TXEN=1;
    TXSTAbits.BRGH=1;
    RCSTAbits.SPEN=1;
    RCSTAbits.CREN=1;
    BAUDCTLbits.BRG16=0;
    SPBRG=25;
    SPBRGH=0;
    
    while(1)
    {
        if (RCIF == 1){ //Recibe comandos del dispositivo maestro
            RX_Byte();
        }
        switch(modo) //control de relees a R calefactora
        {
            case 1: //apagado, 0°
                RA2=0;
                RA3=0;
                RA5=0;
                break;
            case 2: // 80°
                RA2=1;
                RA3=0;
                RA5=0;
                break;
            case 3: // 90°
                RA2=0;
                RA3=0;
                RA5=1;
                break;
            case 4: // 100°
                RA2=0;
                RA3=1;
                RA5=0;
                break;
        }
        //MIDE TEMPERATURA
        GO_DONE=1; // empieza la conversión
        __delay_ms(1); // espera el fin de la conversión
        resultado=ADRESH<<8;
        resultado=resultado+ADRESL;
        //ENCIENDE LEDS DEPENDIENDO DE LA TEMPERATURA
        if(resultado<163) // 0°
        {
            PORTB=0b00000000; 
            PORTA=0b00000000;
        } 
        else if(resultado<184) //  80°
        {
            PORTB=0b11110000; 
            PORTA=0b00000000;
        } 
        else if(resultado<204) // 90°
        {
            PORTB=0b11111100; 
            PORTA=0b00000000;
        } 
        else if(resultado>=204) // 100°
        {
            PORTB=0b11111111; 
            PORTA=0b11000000;
        } 
    }
}
    
