
#ifndef PAVA_H
#define	PAVA_H

#include<xc.h> // include processor files - each processor file is guarded.  

unsigned char J[5]="00001", REF1[10]="Disp", REF2[55]="Dispositivo que controla la temperatura de una pava.";
unsigned char ArrayRX[20], Indice, ArrayProc[20];
unsigned int resultado=0;
void SendSerial(unsigned char *data, unsigned char lenght);
void RX_Byte(void);
void ProcesarArray(void);
unsigned char codigo(void);
unsigned char modo;

#endif	/* PAVA_H */

