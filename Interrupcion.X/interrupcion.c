/*
 * File:   interrupcion.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 6 de septiembre de 2021, 08:05 AM
 */


#pragma config FOSC = INTOSCIO // Se selecciona oscilador interno
#pragma config WDTEN = OFF // Se deshabilita el perro guardian
#pragma config MCLRE = ON // Se habilita el pin 1 como reset externo PONER 5V
#pragma config LVP = OFF // Se deshabilita la programacion por bajo voltaje
#pragma config ICPRT = OFF // Se deshabilita el pin para programacion y depuracion 

#include <xc.h> // Archivo cabecera para todos los programas 

#define _XTAL_FREQ 1000000 // Constante que indica la frecuencia a la que opera el microcontrolador 31Mhz maximo

void __interrupt(high_priority) Externa0(void){ //No son llamadas dentro del codigo, el micro llega solo 
    char Conta = 15;
    while(Conta){
        LATA = 255;
        __delay_ms(500);
        LATA = 0; 
        __delay_ms(500);
        Conta-=1;
    }
    INTCONbits.INT0IF = 0;
}

void main(void) {
    TRISA = 0;
    ANSELA = 0;
    LATA = 0;
    TRISB=0b1111111;
    ANSELB = 0;
    
    INTCON = 0b10010000;
    RCONbits.IPEN = 1;
    
    
    while(1){
        LATAbits.LA0 ^= 1; //Con cada ejecucion ese pin cambia de 0 a 1 y de 1 a 0 
        __delay_ms(500);   //Funcion de retardo en milisegundos
    }
    
    
    return;
}
