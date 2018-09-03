/*
 *  dht11.c:
 *	Simple test program to test the wiringPi functions
 *	DHT11 test
 */
#include <dht11_iot.h> 
#include <wiringPi.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };

void delayMicrosecondsHard (unsigned int howLong); 

static uint8_t DHT11_ReadByte ( void )
{
	uint8_t i, temp=0;

	for(i=0;i<8;i++)    
	{	 
		while(digitalRead( DHTPIN ) == LOW);
		delayMicrosecondsHard(40); 
		if(digitalRead( DHTPIN ) == HIGH ) 
        {
			while(digitalRead( DHTPIN ) == HIGH);  
            temp |= (0x01 << (7-i));
        }
        else
            temp &= ~(0x01 << (7-i));
	}
	return temp;	
}


void dht11_read(float * temperature,float * humidity)
{
    uint8_t readbuf[5] = {0};
	
	if ( wiringPiSetup() == -1 )
		exit( 1 );

	/* pull pin down for 18 milliseconds */
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, HIGH );
	delay( 18 );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	/* then pull it up for 40 microseconds */
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	/* prepare to read the pin */
	pinMode( DHTPIN, INPUT );
	
    if(digitalRead( DHTPIN ) == LOW)
    {
		while(digitalRead( DHTPIN ) == LOW);
		while(digitalRead( DHTPIN ) == HIGH); 
		
		readbuf[0]= DHT11_ReadByte();
		readbuf[1]= DHT11_ReadByte();
		readbuf[2]= DHT11_ReadByte();
		readbuf[3]= DHT11_ReadByte();
		readbuf[4]= DHT11_ReadByte();

		pinMode( DHTPIN, OUTPUT );
		digitalWrite( DHTPIN, HIGH );
		if(readbuf[4]==(readbuf[0]+readbuf[1]+readbuf[2]+readbuf[3]))
		{
			* humidity = readbuf[0]+((float)readbuf[1])/10.0;
			* temperature = readbuf[2]+((float)readbuf[3])/10.0;
			//	printf("temperature:%.1f   humidity:%.1f\r\n",* humidity, *temperature);
		}
		else
			printf("the check is wrong\r\n");
	}
    else
        printf("reading too fast\r\n");
}
