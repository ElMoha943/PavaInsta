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

#include <xc.h>
#include <stdlib.h>
#include <stdio.h>
#include "pava.h"
#include <string.h>

void main(){
    //Configura entradas y salidas
    ANSEL=0;
    ANSELH=0;
    OPTION_REG=0x04;
    TRISA=0b00000010;
    TRISB=0x00;
    TRISC=0x00;
    TRISC7=1;
    
    //Configura UART a 9600 baudios
    TXSTAbits.TXEN=1;
    TXSTAbits.BRGH=1;
    RCSTAbits.SPEN=1;
    RCSTAbits.CREN=1;
    BAUDCTLbits.BRG16=0;
    SPBRG=25;
    SPBRGH=0;
    
    //Configura puerto AD
    ANSEL=0;
    ANSELbits.ANS1=1;
    ADCON1bits.ADFM=1;
    ADCON1bits.VCFG0=0;
    ADCON1bits.VCFG1=0;
    ADCON0bits.ADON=1;
    ADCON0bits.CHS=1;
    
    RA3=0;
    RA4=0;
    RA5=0;
    
    int contador=0;
    while(1){
        //RECIBE UN COMANDO
        if(T0IF==1)
        {
            TMR0=TMR0+131;
            T0IF=0;
            contador++;
            if (contador==500){
                contador=0;
                //MIDE TEMPERATURA
                ADCON0bits.GO=1;
                while (ADCON0bits.GO==1)
                resultado= (ADRESH<<8)+ADRESL;
                __delay_ms(2);
//                ENCIENDE LEDS DEPENDIENDO DE LA TEMPERATURA
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
        if (RCIF == 1){
            RX_Byte();
        }
        switch(modo) //control de relees a R calefactora
        {
            case 1: //apagado, 0°
                RA3=0;
                RA4=0;
                RA5=0;
                break;
            case 2: // 80°
                RA3=1;
                RA5=0;
                RA5=0;
                break;
            case 3: // 90°
                RA3=0;
                RA4=1;
                RA5=0;
                break;
            case 4: // 100°
                RA3=0;
                RA4=0;
                RA5=1;
                break;
        }
    }
}
