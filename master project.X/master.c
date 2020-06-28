/*
 * File:   master.c
 * Author: DELL
 *
 * Created on June 26, 2020, 7:51 PM
 */
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#define MISO      6
#define MOSI      5
#define SCK       7
#define SS        4
char data =0 ;



void SPI_MASTER_INIT (void){

    DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS);
    SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR0) ;
    
}

void SPI_MASTER_TRANSMIT (char data){
    
   // DDRB |= (1<<SS);
    
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
    
    //DDRB &= ~(1<<SS);

}


void UART_INIT_RECEIVE (int baud_rate){
    int UBRR;
    UCSRB |= (1<<RXEN);
    UCSRB |= (1<<RXCIE);
    UBRR = (F_CPU / (16.0*baud_rate)) - 1;
    if(UBRR <= 255){
        UBRRL = (char) (UBRR);
    }
     else{
        UBRRL = (char) (UBRR);
        UBRRH = (char) (UBRR >> 8);
     
     }    
    
}


ISR (USART_RXC_vect){
   
    data = UDR;
    SPI_MASTER_TRANSMIT (data);

}


int main(void) {
    SPI_MASTER_INIT();
    sei();
    UART_INIT_RECEIVE(9600);
   //  SPDR = data;    
    while (1) {
        
        
      
    }
}
