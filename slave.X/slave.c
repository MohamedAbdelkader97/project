/*
 * File:   slave.c
 * Author: DELL
 *
 * Created on June 26, 2020, 8:04 PM
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#define MISO      6
#define MOSI      5
#define SCK       7
#define SS        4


char x;

void SPI_SLAVE_INIT (void){

    DDRB |= (1<<MISO);
    SPCR |= (1<<SPE) | (1<<SPR0) ;
}

char SPI_SLAVE_RECEIVE (void){
    
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}


int main(void) {
    
    SPI_SLAVE_INIT();
    DDRC=0XFF;
    while (1) {
        
        x=SPI_SLAVE_RECEIVE();
        
        if(x=='O'){
           PORTC |= (1<<0);
        }
        
        else if(x=='F') {
            PORTC &= ~(1<<0);
        }
        
        else if(x=='A'){
            PORTC |= (1<<1);
        }
        
        else if(x=='B'){
            PORTC &= ~(1<<1);
        }
        
        
    
        
    }
}
