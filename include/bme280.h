
#ifndef BME280__H
#define BME280__H

#define SLAVE_ADDRESS   0x76
#define REG_ID          0xD0
#define REG_RESET       0xE0
#define REG_CTRL_HUM    0xF2
#define REG_STATUS      0xF3
#define REG_CTRL_MEAS   0xF4
#define REG_CONFIG      0xF5
#define REG_PRESS       0xF7
#define REG_TEMP        0xFA
#define REG_HUM         0xFD

// comp registers
// temperature
#define REG_DIG_T1_L    0x88 // low byte
#define REG_DIG_T1_H    0x89 // High byte
#define REG_DIG_T2_L    0x8A
#define REG_DIG_T2_H    0x8B
#define REG_DIG_T3_L    0x8C
#define REG_DIG_T3_H    0x8D
// pressure
#define REG_DIG_P1_L    0x8E
#define REG_DIG_P1_H    0x8F
#define REG_DIG_P2_L    0x90
#define REG_DIG_P2_H    0x91
#define REG_DIG_P3_L    0x92
#define REG_DIG_P3_H    0x93
#define REG_DIG_P4_L    0x94
#define REG_DIG_P4_H    0x95
#define REG_DIG_P5_L    0x96
#define REG_DIG_P5_H    0x97
#define REG_DIG_P6_L    0x98
#define REG_DIG_P6_H    0x99
#define REG_DIG_P7_L    0x9A
#define REG_DIG_P7_H    0x9B
#define REG_DIG_P8_L    0x9C
#define REG_DIG_P8_H    0x9D
#define REG_DIG_P9_L    0x9E
#define REG_DIG_P9_H    0x9F
// humidity
#define REG_DIG_H1      0xA1
#define REG_DIG_H2_L    0xE1
#define REG_DIG_H2_H    0xE2
#define REG_DIG_H3      0xE3
#define REG_DIG_H6      0xE7


// values
#define ID_VAL_OK       0x60 // id of the sensor
#define RESET_VAL       0xB6

typedef struct {
    float temp;
    float humidity;
    float pressure;
} bme280_data_t;

typedef long int BME280_S32_t;
typedef long unsigned int BME280_U32_t;
typedef long long int BME280_S64_t;

int bme280_init();
int bme280_reset();
int bme280_status();
bme280_data_t bme280_readVal();

#endif // BME280__H