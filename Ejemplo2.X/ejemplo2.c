/*
 * File:   ejemplo2.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 23 de agosto de 2021, 08:17 AM
 */


#pragma config FOSC = INTOSCIO // Se selecciona oscilador interno
#pragma config WDTEN = OFF // Se deshabilita el perro guardian
#pragma config MCLRE = ON // Se habilita el pin 1 como reset externo PONER 5V
#pragma config LVP = OFF // Se deshabilita la programacion por bajo voltaje
#pragma config ICPRT = OFF // Se deshabilita el pin para programacion y depuracion 

#include <xc.h> // Archivo cabecera para todos los programas 

#define _XTAL_FREQ 1000000 // Constante que indica la frecuencia a la que opera el microcontrolador 31Mhz maximo


void main(void) {
    
    //OSCCON = 0b00110000; //Esto es exadecimal 0x10
                    //Podemos cargarlo en binario como 0b00110000
    TRISB = 0; //Registro para definir los pines del puerto A como salidas (todos como 0)
    ANSELB = 0;//Registro para definir los pines del puerto A como digitales (todos como 0)
    
    char contador = 15; //las variables son de 8 bits = 1 byte
    int contador2 = 128; //variable de 2 bytes =  16 bits 
    
    TRISD = 0;
    ANSELD = 0;
    
    while(1){
        //LATCbits.LATC0 ^= 1; //Con cada ejecucion ese pin cambia de 0 a 1 y de 1 a 0 
        //LATB = 0x0F;
        LATB = contador2;
        LATD = contador2/256; // realiza un corrimiento a la derecha 
        
        __delay_ms(250);   //Funcion de retardo en milisegundos
        //LATB = 0b11110000;
        //__delay_ms(500);
        contador2 += 1;
    }
    
    return;
}