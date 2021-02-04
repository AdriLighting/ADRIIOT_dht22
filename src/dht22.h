
#ifndef DHT22_H
#define DHT22_H
	#include <DHT.h>
	#include <Arduino.h>
	#include <ArduinoJson.h>

	class dht22Class
	{
		DHT  * _module;
		float _last_t = 0;
		float _last_h = 0;
		float _last_f = 0;
		float _last_i = 0;
	public:
		dht22Class(int pin);
		~dht22Class(){};
		
		void begin 				();
		void read_temperature 		(float & result, boolean & isNan);
		void read_temperatureF 		(float & result, boolean & isNan);
		void read_temperatureIndice	(float & result, boolean & isNan);

		void read_humidity 		(float & result, boolean & isNan);
		void json 				(JsonObject & root);
		void domoticzJson		(JsonObject & root);
	};
	class dht22Managment
	{
	private:
		int _pos = 0;
	public:
		dht22Managment();
		~dht22Managment(){};

		void create 			(int value, int & result);

		void read_temperature	(float & result, boolean & isNan);
		void read_temperatureF	(float & result, boolean & isNan);
		void read_temperature	(int pos, float & result, boolean & isNan);
		void read_temperatureF	(int pos, float & result, boolean & isNan);

		void read_humidity 		(float & result, boolean & isNan);
		void read_humidity 		(int pos, float & result, boolean & isNan);
		
		dht22Class * module(int pos);
	};
#endif // DHT22_H