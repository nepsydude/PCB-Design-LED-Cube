/* 
 * File:   wuerzel.c
 * Author: Prabesh
 *
 * Created on 11. November 2018, 10:29
 */


// PIC12F683 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA4/OSC2/CLKOUT and RA5/OSC1/CLKIN)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <math.h>

#define _XTAL_FREQ 500000

/*
 * 
 */

int zufall = 0;

//Erzeugung der Zufallszahlen durch rand-Funktion
void LedFolgeZufall()
{
    zufall =(rand()%6)+1;
    //PORTA = 0;
    TRISIO = 0b000000;
    LedLeuchten(zufall);
}

//Anzeige der Initialisierungsfolge
void LedFolge()
{
    if(RA0 == 0) //PORTAbits.
    {
        RA1 = 1;  //PORTAbits.
        __delay_ms(150);
    }
    
    if(RA0 == 0) //PORTAbits.
    {
        RA1 = 0;  //PORTAbits.
        RA5 = 1;  //PORTAbits.
        __delay_ms(150);
    }
    
    if(RA0 == 0) 
    {
        RA1 = 1;
        RA5 = 1;
        __delay_ms(150);
    }
    
    if(RA0 == 0)
    {
        RA1 = 0;
        RA2 = 1;
        __delay_ms(150);
    }
    
    if(RA0 == 0)
    {
        RA1 = 1;
        __delay_ms(150);
    }
    if(RA0 == 0)
    {
        RA1 = 0;
        RA4 = 1;
        __delay_ms(150);
    }
    //PORTA = 0;
    TRISIO = 0b000000;
}

//Funktion um die korrekte Augenzahl anzuzeigen mittels übergebener Augenzahl
void LedLeuchten(int augenzahl){
    switch(augenzahl){
        case 1:
            RA1 = 1;
            break;
         
        case 2:
            RA5 = 1;
        break;
        
        case 3:
            RA1 = 1;
            RA5 = 1;
        break;
        
        case 4:
            RA2 = 1;
            RA5 = 1;
            break;
            
        case 5:
            RA2 = 1;
            RA5 = 1;
            RA1 = 1;
            break;
            
        case 6:
            RA2 = 1;
            RA5 = 1;
            RA4 = 1;  
            break;
    }
    __delay_ms(50);
}


int main(void) {

   //Initialisierung der Systemfunktionen, Variablen und Interrupts
    SYSTEM_Initialize();
    IOCIE = 1;  
    int count = 0;
    int augenzahl = 0;
    int faktor = 0;

//Endlosschleife
    while(1){
        //Wenn keine Augenzahl vorhanden ist, gebe eine Initialisierungsblinkfolge an
        //Ansonsten Ausgabe der gespeicherten Augenanzahl
        //Bei beiden Erhöhung der Variable zur Simulation des Zeitverhaltens
        if(augenzahl == 0)
        {
            LedFolge();
            count = count+36;
        }
        else
        {
            LedLeuchten(augenzahl);
            count = count+2;
        }
        
        //Wenn die 15 Sekunden erreicht wurden, setze alle Werte zurück, schalte
        //alle LED's aus und setze den Controller im Sleep-Modus
        //Nachdem er wieder aus dem Sleepmodus erwacht, fange den Tastendruck ab
        //damit nicht automatisch wieder gewürfelt wird
        if(count >= 600)
        {
            //PORTA = 0;
            TRISIO = 0b000000;
            count = 0;
            SLEEP();
            while(RA0 == 1){}
        }
        //Solange der Taster gedrückt wirde, wird eine zugälle Augenzahl 
        //hintereinander ausgegeben und die Zeit wird zurückgesetzt.
        //Speichern der Zufallszahl als augenzahl zur Ausgabe des Ergebnisses.
        while(RA0 == 1){
            //PORTA = 0;
            TRISIO = 0b000000;
            count = 0;
            LedFolgeZufall(faktor);
            augenzahl = zufall;
        }
     }
}

