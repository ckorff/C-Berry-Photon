#include <stdint.h>
#include <application.h>
#include "RAIO8870.h"
#include "tft.h"


// initialization of GPIO and SPI
// ----------------------------------------------------------
void TFT_init_board ( void )
{
	// *************** set the pins to be an output and turn them on
	
	pinMode( OE, OUTPUT );
	digitalWrite( OE, HIGH );
	
	pinMode( RAIO_RST, OUTPUT );
	digitalWrite( RAIO_RST, HIGH );
	
	pinMode( RAIO_CS, OUTPUT );
	digitalWrite( RAIO_CS, HIGH );
	
	pinMode( RAIO_RS, OUTPUT );
	digitalWrite( RAIO_RS, HIGH );
	
	pinMode( RAIO_WR, OUTPUT );
	digitalWrite( RAIO_WR, HIGH );
	
	pinMode( RAIO_RD, OUTPUT );
	digitalWrite( RAIO_RD, HIGH );
		
	
	
	// *************** now the inputs
	

	pinMode( RAIO_WAIT, INPUT_PULLUP );
	
	pinMode( RAIO_INT, INPUT_PULLUP );
	
	
		
	// *************** set pins for SPI
	
    SPI.begin(SPI_MODE_MASTER, A2);
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    
    
}


// hard reset of the graphic controller and the tft
// ----------------------------------------------------------
void TFT_hard_reset( void )
{
	digitalWrite( RAIO_RST, LOW );
    delay( 10 );
 	digitalWrite( RAIO_RST, HIGH );
 	delay( 1 );
}


// wait during raio is busy
// ----------------------------------------------------------
void TFT_wait_for_raio ( void )
{
	while ( !digitalRead( RAIO_WAIT ) );
}


// write data via SPI to tft
// ----------------------------------------------------------
void TFT_SPI_data_out ( uint16_t data )
{
	union my_union number;
	char buffer[2];

	number.value = data;
	buffer[0] = (char) number.split.high;
	buffer[1] = (char) number.split.low;
	
	digitalWrite(A2,LOW);
	SPI.transfer( buffer[0] );
	SPI.transfer( buffer[1] );
	digitalWrite(A2,HIGH);

}


// write byte to register
// ----------------------------------------------------------
void TFT_RegWrite( uint16_t reg )
{
	digitalWrite( RAIO_RS, HIGH );               
	digitalWrite( RAIO_CS, LOW ); 
    digitalWrite( RAIO_WR, LOW ); 
    digitalWrite( OE, LOW );
       
    TFT_SPI_data_out ( reg );
    
    digitalWrite( RAIO_WR, HIGH ); 
 	digitalWrite( RAIO_CS, HIGH ); 
	digitalWrite( OE, HIGH );
}


// write byte to tft
// ----------------------------------------------------------
void TFT_DataWrite( uint16_t data )
{ 
	digitalWrite( RAIO_RS, LOW ); 
	digitalWrite( RAIO_CS, LOW ); 
    digitalWrite( RAIO_WR, LOW ); 
    digitalWrite( OE, LOW );
    
    TFT_SPI_data_out ( data );
        
    digitalWrite( RAIO_WR, HIGH );
	digitalWrite( RAIO_CS, HIGH ); 
	digitalWrite( OE, HIGH );
};


// write 'count'-bytes to tft
// ----------------------------------------------------------
void TFT_DataMultiWrite( uint16_t *data, uint32_t count )
{
    

	digitalWrite( RAIO_RS, LOW ); 
	digitalWrite( RAIO_CS, LOW ); 
	digitalWrite( OE, LOW );
                  
	for (uint32_t i = 0; i < count; i++ )
  SPI.transfer(*data+i);

	
	digitalWrite( RAIO_CS, HIGH ); 
	digitalWrite( OE, HIGH );

}
