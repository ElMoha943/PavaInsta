#ifndef PAVA_H
#define	PAVA_H

#define _XTAL_FREQ 4000000

//VARIABLES
unsigned char J[5]="00001", REF1[10]="Disp", REF2[50]="Dispositivo que controla la temperatura de una pava.";
unsigned char recibido, comando, command_data[10], command_data_index=0, command;
unsigned char ArrayRX[20], Indice, ArrayProc[20];
unsigned char modo;

//FUNCIONES
void SendSerial(unsigned char *data, unsigned char lenght);
void RX_Byte(void);
void ProcesarArray(void);
unsigned char Codigo(void);

#endif	/* PAVA_H */
