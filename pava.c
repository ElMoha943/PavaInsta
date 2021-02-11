#include <xc.h>
#include "pava.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void SendSerial(unsigned char *data, unsigned char lenght)
{
    unsigned char x=0;
    while(x<lenght){
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
    if(codigo()){
      if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='C')&&(ArrayProc[2]=='R')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==']')) //CONSULTA REF
      {
            if(ArrayProc[4]=='1'){ 
                SendSerial(REF1,10);
            }
            if(ArrayProc[4]=='2'){ 
                SendSerial(REF2,50);
            }
        }
      }
    else if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='P')&&(ArrayProc[2]=='A')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==',')&&(ArrayProc[14]==',')&&(ArrayProc[17]==']')) //PEDIDO DE ACCION
    {
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
    else if ((ArrayProc[0]=='[')&&(ArrayProc[1]=='C')&&(ArrayProc[2]=='O')&&(ArrayProc[3]==',')&&(ArrayProc[5]==',')&&(ArrayProc[11]==',')&&(ArrayProc[14]==',')&&(ArrayProc[17]==']')) //CONSULTA A DISPOSITIVO
    {
        if(ArrayProc[4]=='1')
        {
        if(modo==1)
        {
           SendSerial("La temperatura es 0°",20); 
        }
        if(modo==2)
        {
            SendSerial("La temperatura es 80°",21);
        }
        if(modo==3)
        {
            SendSerial("La temperatura es 90°",21);
        }
        if(modo==4)
        {
            SendSerial("La temperatura es 100°",22);
        }
        }
    }
    }
unsigned char codigo(){ //[CR,1,00001]e
    unsigned char a[5];
        a[0]=ArrayProc[6];
        a[1]=ArrayProc[7];
        a[2]=ArrayProc[8];
        a[3]=ArrayProc[9];
        a[4]=ArrayProc[10];        
        if(strcmp(a,"00001")){
            return 1;
        }
        else {
            return 0;
        }
}

