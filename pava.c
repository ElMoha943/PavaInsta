#include<xc.h>
#include"pava.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void SendSerial(unsigned char *data)
{
    unsigned char lenght;
    unsigned char x=0;
    while(data[x]!='\0'){
        while(PIR1bits.TXIF==0){}   
        TXREG=data[x];
        x++;
    }
}

void RX_Byte(void){
    unsigned char i;
    ArrayRX[Indice] = RCREG;
    while(PIR1bits.TXIF == 0){}
    TXREG = ArrayRX[Indice];
    if (ArrayRX[Indice] == 'e'){
        // ArrayRX a ArrayProc
        for (i=0;i<Indice;i++){
            ArrayProc[i] = ArrayRX[i];
        }
        ProcesarArray();
        Indice = 0;
    }
    else{
        Indice++;
    }
}

void ProcesarArray(void){
    if((ArrayProc[6]==RD0+'0')&&(ArrayProc[7]==RD1+'0')&&(ArrayProc[8]==RD2+'0')&&(ArrayProc[9]==RD3+'0')&&(ArrayProc[10]==RD4+'0')){
    //CONSULTA REF [RC,1,00001]e
        if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='C')&&(ArrayProc[2]=='R')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==']')){
            // En posiciones 6 a 10 tengo los caracteres que representan el número de dispositivo con quien se quiere comunicar 
            if(ArrayProc[4]=='1'){ // El maestro me solicita la REF1
                SendSerial(REF1);
            }
            if(ArrayProc[4]=='2'){ // El maestro me solicita la REF2
                SendSerial(REF2);
            }
        }
        //PEDIDO DE ACCION [PA,4,00001,xx,xx]e
        else if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='P')&&(ArrayProc[2]=='A')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==',')&&(ArrayProc[14]==',')&&(ArrayProc[17]==']')){
            if(ArrayProc[4]=='1') 
            {
                modo=1;
            }
            else if(ArrayProc[4]=='2') 
            {    
                modo=2;
            }
            else if(ArrayProc[4]=='3') 
            {
                modo=3;
            }
            else if(ArrayProc[4]=='4') 
            {      
                modo=4;
            }
        }
        //CONSULTA A DISPOSITIVO [CO,1,00001,XX,XX]e
        else if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='C')&&(ArrayProc[2]=='O')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==',')&&(ArrayProc[14]==',')&&(ArrayProc[17]==']')){
            if(ArrayProc[4]=='1')
            {
                unsigned char cosa[4];
                int valor = (((float)resultado)*5/1023)*100;
                cosa[0] = (valor/100)+'0';
                cosa[1] = ((valor/10)%10)+'0';
                cosa[2] = (valor%10)+'0';
                cosa[3] = 'C';
                SendSerial(cosa);
            }
        }
    }
}
