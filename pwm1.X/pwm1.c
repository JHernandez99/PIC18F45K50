/*
 * File:   pwm1.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 20 de septiembre de 2021, 08:48 AM
 * 
 */


#pragma config FOSC = INTOSCIO // Se selecciona oscilador interno
#pragma config WDTEN = OFF // Se deshabilita el perro guardian
#pragma config MCLRE = ON // Se habilita el pin 1 como reset externo PONER 5V
#pragma config LVP = OFF // Se deshabilita la programacion por bajo voltaje
#pragma config ICPRT = OFF // Se deshabilita el pin para programacion y depuracion 

#include <xc.h> // Archivo cabecera para todos los programas 

#define _XTAL_FREQ 1000000 // Constante que indica la frecuencia a la que opera el microcontrolador 31Mhz maximo

void configura(void){
    TRISA=0;
    ANSELA=0b00000001;
    TRISC=0;
    ANSELC=0;
    ADCON0=0b00000001;
    ADCON1=0b00000000;
    ADCON2=0b00010000;
    CCP1CON = 0x0F;
    T2CON = 0x07;
    PR2 = 155;
    
            
}
void convierte(void){
    //int Resultado;
    ADCON0bits.GO =1;
    while(ADCON0bits.GO);
    CCPR1L = ADRESH;
    
    if (ADRESL > 127) 
        CCP1CONbits.DC1B1 = 1; 
    else
        CCP1CONbits.DC1B1 = 0; 
    ADRESL = ADRESL *2; //CORRIMIENTO
    
    if (ADRESL > 127) 
        CCP1CONbits.DC1B0 = 1; 
    else
        CCP1CONbits.DC1B0 = 0; 
    //return Resultado;
}


void main(void) {
    configura();
    __delay_ms(1);
    
    while(1){
        convierte();
        __delay_ms(50);
    
    }
    return;
}
