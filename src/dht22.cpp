#include "dht22.h"
#include <adri_tools_v2.h>
#define MAX_SENSOR 10
dht22Class 	* dht22ClassArray[MAX_SENSOR];

dht22Managment::dht22Managment(){

}

void dht22Managment::create(int value, int & result){
	dht22ClassArray[_pos] = new dht22Class(value);
	result = _pos;
	_pos++;
}

void dht22Managment::read_temperature(float & result, boolean & isNan){
	for (int i = 0; i < _pos; ++i) {dht22ClassArray[i]->read_temperature(result, isNan);}
}
void dht22Managment::read_temperatureF(float & result, boolean & isNan){
	for (int i = 0; i < _pos; ++i) {dht22ClassArray[i]->read_temperatureF(result, isNan);}
}
void dht22Managment::read_temperature(int pos, float & result, boolean & isNan){
	dht22ClassArray[pos]->read_temperature(result, isNan);
}
void dht22Managment::read_temperatureF(int pos, float & result, boolean & isNan){
	dht22ClassArray[pos]->read_temperatureF(result, isNan);
}
void dht22Managment::read_humidity(float & result, boolean & isNan){
	for (int i = 0; i < _pos; ++i) {dht22ClassArray[i]->read_humidity(result, isNan);}
}
void dht22Managment::read_humidity(int pos, float & result, boolean & isNan){
	dht22ClassArray[pos]->read_humidity(result, isNan);
}

dht22Class * dht22Managment::module(int pos){
	return dht22ClassArray[pos];
}




dht22Class::dht22Class(int pin) {
	_module = new DHT(pin, DHT22);
	begin();
}
void dht22Class::begin(){
	_module->begin();	
}
void dht22Class::read_temperature(float & result, boolean & isNan){
	float h = _module->readHumidity();
	float t = _module->readTemperature();
	float f = _module->readTemperature(true);
	if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; return;}
	isNan 	= true;
	result 	= t;
}
void dht22Class::read_temperatureF(float & result, boolean & isNan){
	float h = _module->readHumidity();
	float t = _module->readTemperature();
	float f = _module->readTemperature(true);
	if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; return;}
	isNan 	= true;
	result 	= f;
}
void dht22Class::read_temperatureIndice(float & result, boolean & isNan){
	float h = _module->readHumidity();
	float t = _module->readTemperature();
	float f = _module->readTemperature(true);
	if (isnan(h) || isnan(t) || isnan(f)) {isNan = false; return;}
	isNan 	= true;
	result 	= _module->computeHeatIndex(t, h, false);
}
void dht22Class::read_humidity(float & result, boolean & isNan){
	float h = _module->readHumidity();
	if (isnan(h)) {isNan = false; return;}	
	isNan 	= true;
	result 	= h;
}
void dht22Class::json(JsonObject & root){
	float value_1;
	float value_2;
	boolean state;
	read_temperature(value_1, state);
	read_temperatureF(value_2, state);
	root[F("v1")] = value_1;
	root[F("v2")] = value_2;
}
void dht22Class::domoticzJson(JsonObject & root){
	float value_1;
	float value_2;
	boolean state;
	read_temperature(value_1, state);
	read_humidity(value_2, state);

    int hum_stat = 0;
    if ( value_2 > 70 ) {
      	hum_stat = 3;
    } else if ( value_2 < 30 ) {
      	hum_stat = 2; 
    } else if ( value_2 >= 30 & value_2 <= 45 ) {
      	hum_stat = 0;
    } else if ( value_2 > 45 & value_2 <= 70 ) {
      	hum_stat = 1;
    }

	root[F("nvalue")] = 0;
	root[F("svalue")] = String(value_1) + ";" + String(value_2) + ";" + String(hum_stat);
}