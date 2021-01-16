#include "dht22.h"

dht22Class::dht22Class(int pin) : _module(pin, DHT22) {
}
void dht22Class::begin(){
	_module.begin();	
}
void dht22Class::read_temperature(float & result, boolean & isNan){
	float h = _module.readHumidity();
	float t = _module.readTemperature();
	float f = _module.readTemperature(true);
	if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; return;}
	isNan 	= true;
	result 	= _module.computeHeatIndex(t, h, false);
}
void dht22Class::read_humidity(float & result, boolean & isNan){
	float h = _module.readHumidity();
	if (isnan(h)) {isNan = false; return;}	
	isNan 	= true;
	result 	= h;
}