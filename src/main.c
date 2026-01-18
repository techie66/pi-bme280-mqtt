#include "../include/bme280.h"
#include "../include/mqtt_client_helper.h"
#include <stdio.h>
#include <unistd.h>

#define CLIENTID        	"BME280"
#define TOPIC_STATUS    	"bme280/status"
#define PUBLISH_INTERVAL	1


MQTTClient client = NULL;


int main() {
	
	client = initialize_mqtt_client(NULL, NULL, CLIENTID);
    if (!client) {
        printf("failed to init mqtt client\n");
        return -1;
    }

	int status = bme280_init();

	if(status != 0) {
		return -1;
	}
	while(1) {
		bme280_data_t data = bme280_readVal();

		char buffer[64];
		snprintf(buffer, sizeof(buffer), "{\"temperature\":%.2f,\"humidity\":%.2f, \"pressure\": %.2f}", data.temp, data.humidity, data.pressure);
		send_msg(client, buffer, TOPIC_STATUS);
		sleep(PUBLISH_INTERVAL);
	}
	
	
	return 0;
}