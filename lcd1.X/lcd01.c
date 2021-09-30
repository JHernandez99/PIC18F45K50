/*
 * File:   lcd01.c
 * Author: Jose Luis Hernandez Camacho
 *
 * Created on 23 de septiembre de 2021, 08:54 AM
 * Control de pantalla LCD con 4 pines de informacion
 */

#pragma config FOSC = INTOSCIO //Selecciona oscilador interno
#pragma config WDTEN = OFF //Se deshabilita el perro guardian
#pragma config MCLRE = ON //Se habilita el pin 1 como reset externo
#pragma config LVP = OFF //Se deshabilita la programación por bajo voltaje
#pragma config ICPRT = OFF //Se deshabilita el pin para programación y depuración

 

#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 1000000

 

void Configuracion(void)
{
TRISA=0;    //Salidas digitales
TRISD=0;    //Salidas digitales
ANSELD=0;
ANSELA=0;
LATA=0;
}

 

void putch(char data) {
    char Activa;
    Activa = data & 0xF0;
    LATD = Activa | 0x05; //0bxxxx0101
    __delay_us(10);
    LATD = Activa | 0x01; //0bxxxx0001
    __delay_ms(1);
    Activa = data << 4;
    LATD = Activa | 0x05; // pin 2 del PORTD se conecta a la entrada E de la LCD y el otro al pin RS
    __delay_us(10);
    LATD = Activa | 0x01;    
}

 

void putcm(char data) {
    char Activa;
    Activa = data & 0xF0; //0bxxxx0100
    LATD = Activa | 0x04;
    __delay_us(10);
    LATD = Activa;
    __delay_ms(1);
    Activa = data << 4;
    LATD = Activa | 0x04;
    __delay_us(10);
    LATD = Activa;
}

 

void InicializaLCD(void)
{
__delay_ms(30);
putcm(0x02);    // Inicializa en modo 4 bits
__delay_ms(1);

 

putcm(0x28);    // Inicializa en 2 líneas 5x7
__delay_ms(1);

 

putcm(0x2C);
__delay_ms(1);

 

putcm(0x0C);
__delay_ms(1);

 

putcm(0x06);
__delay_ms(1);

 

putcm(0x80); //Posiciona el curson en 1,1
__delay_ms(1);
}

 

void main(void)
{
    Configuracion();
    
    InicializaLCD();
    
    int Valor = 125;
    
    printf(" Curso de M&M ");
    putcm(0xC2);
    printf("Hello World");
    __delay_ms(5000);
    putcm(0x01);
    
    printf("Poniendo valor en pantalla ");
    putcm(0xC2);
    printf("Valor = %d", Valor );
    while (1) {
        LATAbits.LA0 ^= 1; 
        __delay_ms(500);
    }
return;
}