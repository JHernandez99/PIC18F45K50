/*
 * File:   eeprom.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 13 de septiembre de 2021, 08:25 AM
 * Contador que incremente con una interrupcion y guarde en la memoria EEPROM
 * el valor de la variable Conta
 *  
 * 
 */

#pragma config FOSC = INTOSCIO // Se selecciona oscilador interno
#pragma config WDTEN = OFF // Se deshabilita el perro guardian
#pragma config MCLRE = ON // Se habilita el pin 1 como reset externo PONER 5V
#pragma config LVP = OFF // Se deshabilita la programacion por bajo voltaje
#pragma config ICPRT = OFF // Se deshabilita el pin para programacion y depuracion 

#include <xc.h> // Archivo cabecera para todos los programas 

#define _XTAL_FREQ 1000000 // Constante que indica la frecuencia a la que opera el microcontrolador 31Mhz maximo
char Conta = 0;
void __interrupt(high_priority) Externa0(void){ //No son llamadas dentro del codigo, el micro llega solo 
    
   
    Conta+=1;
    
    EEDATA = Conta; // Datos a guardar 
    EECON1bits.WREN = 1; // Habilita la escritura
    EECON2 = 0x55;//Habilita la escritura
    EECON2 = 0xAA;//Habilita la escritura
    EECON1bits.WR = 1; // Escribe lo que se guardo en EEDATA
   __delay_ms(50);//ELININACION DE TRANSITORIOS
   EECON1bits.WREN = 0; // Deshabilita la escritura
   
   
   
   
    INTCONbits.INT0IF = 0;//LIMPIA BANDERA DE INTERRUPCION EXTERNA
}

void main(void) {
    TRISA = 0;
    ANSELA = 0;
    LATA = 0;
    
    TRISB=0b00000001;
    ANSELB = 0;
    
    INTCON = 0b10010000;
    RCONbits.IPEN = 1;
    
    EEADR = 0;
    EECON1 = 0b00000001; //Lectura de la EEPROM
    __delay_us(10);//Para asegurar la lectura
    Conta = EEDATA;//Tarda un ciclo de instruccion
    
    
    while(1){
        PORTBbits.RB3 ^= 1; //Con cada ejecucion ese pin cambia de 0 a 1 y de 1 a 0
        PORTA = Conta;
        __delay_ms(500);   //Funcion de retardo en milisegundos
    }
    
    
    return;
}
