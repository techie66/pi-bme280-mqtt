# Installation
## Install Dependencies
`sudo apt install libmosquitto-dev`
Download WiringPi from [https://github.com/WiringPi/WiringPi/releases]
`sudo dpkg -i ~/Downloads/wiringpi_3.18_arm64.deb`
## Configure
Edit `src/main.c`
| Option | Description |
|--------|-------------|
|CLIENTID|Client ID / username|
|PASSWORD|Client Password|
|HOST|MQTT server|
|LWT|Topic to publish last will and testament|
|TOPIC|MQTT topic to publish data to|
|PUBLISH_INTERVAL|How often in seconds to send updates|

## Build
`make`

# Usage
Run
`./main`

## Output

### Normal
```
We are now connected to the broker!
BME280 started in NORMAL mode!
{"temperature":23.75,"humidity":100.00, "pressure": 1006.09}
```

### Connection Problem
```
Client could not connect to broker! Error Code: 15
Press Ctrl-C to exit.
We are now connected to the broker!
BME280 started in NORMAL mode!
temperature":24.03,"humidity":100.00, "pressure": 998.90}
```
