#ifndef PAVA_H
#define	PAVA_H

#define _XTAL_FREQ 4000000

//VARIABLES
unsigned char J[]="00000", REF1[10]="Disp", REF2[55]="Dispositivo que controla la temperatura de una pava.";
unsigned char recibido, comando, command_data[10], command_data_index=0, command;
unsigned char ArrayRX[20], Indice, ArrayProc[20];
unsigned char modo;
int resultado;

//FUNCIONES
void SendSerial(unsigned char *data);
void RX_Byte(void);
void ProcesarArray(void);
unsigned char Codigo(void);

#endif	/* PAVA_H */
