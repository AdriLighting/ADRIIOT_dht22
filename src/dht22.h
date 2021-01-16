
#ifndef DHT22_H
#define DHT22_H
	#include <DHT.h>
	#include <Arduino.h>

	class dht22Class
	{
		DHT _module;
	public:
		dht22Class(int pin);
		~dht22Class(){};
		
		void begin 				();
		void read_temperature 	(float & result, boolean & isNan);
		void read_humidity 		(float & result, boolean & isNan);
	};

#endif // DHT22_H