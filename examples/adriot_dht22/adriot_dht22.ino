#include <adriiot_dht22.h>

dht22Managment		sensor;
int id;
void setup()
{
	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  	Serial.printf("\n##################################################\n\n");


	sensor.create(D2, id);
}

void loop()
{
	float t;
	boolean state;
	sensor.module(id)->read_temperature(t, state);
	Serial.printf("\n[TEMP ] : %.2f\n", t);
	delay(1000);
}