#include "../include/bme280.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mosquitto.h>

#define CLIENTID        	"3Dprinter"
#define PASSWORD        	"R3@1lY$3<uRe"
#define HOST             	"broker.local"
#define LWT    	          "3dprinter/LWT"
#define TOPIC    	        "tele/garage/SENSOR"
#define PUBLISH_INTERVAL	1




int main() {

  int rc;
	struct mosquitto * mosq;

	mosquitto_lib_init();

	mosq = mosquitto_new(CLIENTID, true, NULL);

  rc = mosquitto_username_pw_set(mosq,CLIENTID,PASSWORD);
  mosquitto_will_set(mosq, LWT, 7, "Offline", 0, true);

	rc = mosquitto_connect(mosq, HOST, 1883, 60);
	if(rc != 0){
		printf("Client could not connect to broker! Error Code: %d\n", rc);
		mosquitto_destroy(mosq);
		//return -1; 
    printf("Press Ctrl-C to exit.\n");
	}
  mosquitto_publish(mosq, NULL, LWT, 6, "Online", 0, true);
	printf("We are now connected to the broker!\n");

	int status = bme280_init();

	if(status != 0) {
		return -1;
	}
	while(1) {
		bme280_data_t data = bme280_readVal();

		char buffer[128];
		snprintf(buffer, sizeof(buffer), "{\"BME280\":{\"Temperature\":%.2f,\"Humidity\":%.2f, \"Pressure\": %.2f}}", data.temp, data.humidity, data.pressure);
		printf("{\"temperature\":%.2f,\"humidity\":%.2f, \"pressure\": %.2f}\033[0K\r", data.temp, data.humidity, data.pressure);
    fflush(stdout);
    if(rc == 0 ) {
      mosquitto_publish(mosq, NULL, TOPIC, strlen(buffer), buffer, 0, false);
    }
		sleep(PUBLISH_INTERVAL);
	}
	if(rc == 0) {
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
  }

	mosquitto_lib_cleanup();
	
	return 0;
}
