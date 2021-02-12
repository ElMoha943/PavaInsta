#ifndef PAVA_H
#define	PAVA_H

#define _XTAL_FREQ 4000000

//VARIABLES
unsigned char J[5]="00001", REF1[10]="Disp", REF2[55]="Dispositivo que controla la temperatura de una pava.";
unsigned char ArrayRX[20], Indice, ArrayProc[20];
unsigned int resultado=0;
unsigned char codigo(void);
unsigned char modo;

//FUNCIONES
void SendSerial(unsigned char *data, unsigned char lenght);
void RX_Byte(void);
void ProcesarArray(void);

#endif	/* PAVA_H */
