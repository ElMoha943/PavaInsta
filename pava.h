#ifndef PAVA_H
#define	PAVA_H

#define _XTAL_FREQ 4000000

//VARIABLES
unsigned char J[5]="00000", REF1[10]="Disp", REF2[55]="Dispositivo que controla la temperatura de una pava.";
unsigned char ArrayRX[20], Indice, ArrayProc[20];
unsigned char modo;
int resultado;

//FUNCIONES
void SendSerial(unsigned char *data);
void RX_Byte(void);
void ProcesarArray(void);
unsigned char Codigo(void);

#endif	/* PAVA_H */
