/*
 * File:   pracitca1.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 15 de septiembre de 2021, 07:57 PM
 * Programa que genera el parpadeo de un LED con retardo
 */


#pragma config FOSC = INTOSCIO // Oscillator Selection (Internal oscillator)
#pragma config WDTEN = OFF // Watchdog Timer Enable bits (WDT disabled in hardware)
#pragma config MCLRE = ON // Master Clear Reset Pin Enable (MCLR pin enabled; RE3 input disabled)
#pragma config LVP = OFF // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF // Dedicated In-Circuit Debug/Programming Port Enable (ICPORT disabled)
#include <xc.h>

#define _XTAL_FREQ 1000000 // Frecuencia por default

void main(void) {
    
    TRISD=0;
    ANSELD=0;
     
   
    while(1){
        LATDbits.LD1^=1;
        __delay_ms(500);
    }
    
    return;
    
}
