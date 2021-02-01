#include <adri_tools_v2.h>
#include <adriiot_dht22.h>

dht22Managment		sensor;
int id;
void setup()
{
	Serial.begin(115200);
  	for(unsigned long const serialBeginTime = millis(); !Serial && (millis() - serialBeginTime > 5000); ) { }
  	fsprintf("\n##################################################\n\n");


	LittleFS.begin();	
	sensor.create(D2, id);
}

void loop()
{
	float t;
	boolean state;
	sensor.module(id)->read_temperature(t, state);
	fsprintf("\n[TEMP ] : %.2f\n", t);
	delay(1000);
}