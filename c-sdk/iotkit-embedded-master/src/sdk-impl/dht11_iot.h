#ifndef _DHT11_IOT_H__
#define	_DHT11_IOT_H__


#include <wiringPi.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


void dht11_read(float * temperature,float * humidity);

#endif