/*
 * File:   Ejemplo3.c
 * Author: Luich
 *
 * Created on 26 de agosto de 2021, 09:26 AM
 * Codigo para un convertidor analogico digital
 */

#pragma config FOSC = INTOSCIO //OSCILADOR INTERNO
#pragma config WDTEN = OFF //DESHABILITA WATCH DOG
#pragma config MCLRE = ON // HABILITA PIN 1 COMO RESET
#pragma config LVP = OFF // DESHABILITA PROGRAMACION LOW VOLTAGE
#pragma config ICPRT = OFF // DESHABILITA PIN PARA PROGRAMACION Y DEPURACION

#include <xc.h>

#define _XTAL_FREQ 1000000

void configuracion(void){
    TRISA  = 0b00000000; // SALIDAS
    ANSELA = 0b00000001; // CH 1 ANALOGICO
    TRISB =0;
    ANSELB =0;
    ADCON0 = 0b00000001; // SELECCIONA EL CANAL
    ADCON1 = 0b00000000; // VOLTAGES DE REFERENCIA 
    ADCON2 = 0b10010000; // 
    /*
     * Con esto ya se activo el convertidor y se seleccionaron
     * los voltajes de referencia
     */
    }

int convierte(void){
    int resultado;
    ADCON0bits.GO = 1; // inicializa la conversion 
    while(ADCON0bits.GO);
    resultado = ADRESL + ADRESH*256;
    return resultado;
}


void main(void) {
    
    configuracion();
    __delay_ms(1);
    
    while(1){
        
        LATB = convierte()/4; // SE ENVIA EL RESULTADO DE LA CONVERSION A ADRESH    
        __delay_ms(50);
    }
    
    
    return;
}
