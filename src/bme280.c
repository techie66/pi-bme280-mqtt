#include "../include/bme280.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

int fd = -1; // file descriptor

// temperature
unsigned short dig_T1;
signed short dig_T2;
signed short dig_T3;

// pressure
unsigned short dig_P1;
signed short dig_P2;
signed short dig_P3;
signed short dig_P4;
signed short dig_P5;
signed short dig_P6;
signed short dig_P7;
signed short dig_P8;
signed short dig_P9;

// humidity
unsigned char dig_H1;
signed short dig_H2;
unsigned char dig_H3;
signed short dig_H4;
signed short dig_H5;
signed char dig_H6;

BME280_S32_t t_fine;

int bme280_init() {
	if (wiringPiSetup() == -1) {
		printf("BME280: wiring pi setup failed\n");
		return -1; // Failed to initialize WiringPi
	}

	fd = wiringPiI2CSetup(SLAVE_ADDRESS);
	if(fd == -1) {
		printf("Failed to init I2C communication\n");
		return -1;
	}

	int id = wiringPiI2CReadReg8(fd, REG_ID);
	if(id != ID_VAL_OK) {
		printf("I2C Failed\n");
		return -1;
	}

	// Set normal mode
	wiringPiI2CWriteReg8(fd, REG_CTRL_HUM, 0x01);
	wiringPiI2CWriteReg8(fd, REG_CTRL_MEAS, 0x27);
	wiringPiI2CWriteReg8(fd, REG_CONFIG, 0xA0);
	printf("BME280 started in NORMAL mode!\n");

	// get compensation values
	// temperature
	uint8_t digt1_l = wiringPiI2CReadReg8(fd, REG_DIG_T1_L);
	uint8_t digt1_m = wiringPiI2CReadReg8(fd, REG_DIG_T1_H);
	dig_T1 = ((unsigned short)digt1_l) | ((unsigned short)digt1_m << 8);

	uint8_t dig2_l = wiringPiI2CReadReg8(fd, REG_DIG_T2_L);
	uint8_t dig2_m = wiringPiI2CReadReg8(fd, REG_DIG_T2_H);
	dig_T2 = (int16_t)((dig2_m << 8) | dig2_l);

	uint8_t dig3_l = wiringPiI2CReadReg8(fd, REG_DIG_T3_L);
	uint8_t dig3_m = wiringPiI2CReadReg8(fd, REG_DIG_T3_H);
	dig_T3 = (int16_t)((dig3_m << 8) | dig3_l);

	// pressure
	uint8_t dig_p1_l = wiringPiI2CReadReg8(fd, REG_DIG_P1_L);
	uint8_t dig_p1_m = wiringPiI2CReadReg8(fd, REG_DIG_P1_H);
	dig_P1 = ((unsigned short)dig_p1_l) | ((unsigned short)dig_p1_m << 8);

	uint8_t dig_p2_l = wiringPiI2CReadReg8(fd, REG_DIG_P2_L);
	uint8_t dig_p2_m = wiringPiI2CReadReg8(fd, REG_DIG_P2_H);
	dig_P2 = (int16_t)((dig_p2_m << 8) | dig_p2_l);

	uint8_t dig_p3_l = wiringPiI2CReadReg8(fd, REG_DIG_P3_L);
	uint8_t dig_p3_m = wiringPiI2CReadReg8(fd, REG_DIG_P3_H);
	dig_P3 = (int16_t)((dig_p3_m << 8) | dig_p3_l);

	uint8_t dig_p4_l = wiringPiI2CReadReg8(fd, REG_DIG_P4_L);
	uint8_t dig_p4_m = wiringPiI2CReadReg8(fd, REG_DIG_P4_H);
	dig_P4 = (int16_t)((dig_p4_m << 8) | dig_p4_l);

	uint8_t dig_p5_l = wiringPiI2CReadReg8(fd, REG_DIG_P5_L);
	uint8_t dig_p5_m = wiringPiI2CReadReg8(fd, REG_DIG_P5_H);
	dig_P5 = (int16_t)((dig_p5_m << 8) | dig_p5_l);

	uint8_t dig_p6_l = wiringPiI2CReadReg8(fd, REG_DIG_P6_L);
	uint8_t dig_p6_m = wiringPiI2CReadReg8(fd, REG_DIG_P6_H);
	dig_P6 = (int16_t)((dig_p6_m << 8) | dig_p6_l);

	uint8_t dig_p7_l = wiringPiI2CReadReg8(fd, REG_DIG_P7_L);
	uint8_t dig_p7_m = wiringPiI2CReadReg8(fd, REG_DIG_P7_H);
	dig_P7 = (int16_t)((dig_p7_m << 8) | dig_p7_l);

	uint8_t dig_p8_l = wiringPiI2CReadReg8(fd, REG_DIG_P8_L);
	uint8_t dig_p8_m = wiringPiI2CReadReg8(fd, REG_DIG_P8_H);
	dig_P8 = (int16_t)((dig_p8_m << 8) | dig_p8_l);

	uint8_t dig_p9_l = wiringPiI2CReadReg8(fd, REG_DIG_P9_L);
	uint8_t dig_p9_m = wiringPiI2CReadReg8(fd, REG_DIG_P9_H);
	dig_P9 = (int16_t)((dig_p9_m << 8) | dig_p9_l);
	

	// humidity
	uint8_t dig_h1 = wiringPiI2CReadReg8(fd, REG_DIG_H1);
	dig_H1 = (unsigned char)dig_h1;

	uint8_t dig_h2_l = wiringPiI2CReadReg8(fd, REG_DIG_H2_L);
	uint8_t dig_h2_m = wiringPiI2CReadReg8(fd, REG_DIG_H2_H);
	dig_H2 = (int16_t)((dig_h2_m << 8) | dig_h2_l);

	uint8_t dig_h3 = wiringPiI2CReadReg8(fd, REG_DIG_H3);
	dig_H3 = (unsigned char)dig_h3;

	uint8_t dig_h4_h = wiringPiI2CReadReg8(fd, 0xE4);
	uint8_t dig_h4_l = wiringPiI2CReadReg8(fd, 0xE5);
	dig_H4 = (int16_t)((dig_h4_h << 4) | (dig_h4_l & 0b00001111));

	uint8_t dig_h5_h = wiringPiI2CReadReg8(fd, 0xE6);
	dig_H5 = (int16_t)((dig_h5_h << 4) | (dig_h4_l >> 4));

	uint8_t dig_h6 = wiringPiI2CReadReg8(fd, REG_DIG_H6);
	dig_H6 = (char)dig_h6;

	return 0;
}

int bme280_reset() {
	return wiringPiI2CWriteReg8(fd, REG_RESET, RESET_VAL);
}

void print_binary(uint8_t val, int bits)
{
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
        if (i % 8 == 0 && i != 0) printf(" "); // optional: space every byte
    }
    printf("\n");
}

int bme280_status() {
	return wiringPiI2CReadReg8(fd, REG_STATUS);
}

BME280_S32_t BME280_compensate_T_int32(BME280_S32_t adc_T)
{
	BME280_S32_t var1, var2, T;
	var1 = ((((adc_T>>3) - ((BME280_S32_t)dig_T1<<1))) * ((BME280_S32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((BME280_S32_t)dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)dig_T1)))
	>> 12) *
	((BME280_S32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

BME280_U32_t BME280_compensate_P_int64(BME280_S32_t adc_P)
{
	BME280_S64_t var1, var2, p;
	var1 = ((BME280_S64_t)t_fine) - 128000;
	var2 = var1 * var1 * (BME280_S64_t)dig_P6;
	var2 = var2 + ((var1*(BME280_S64_t)dig_P5)<<17);
	var2 = var2 + (((BME280_S64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (BME280_S64_t)dig_P3)>>8) + ((var1 * (BME280_S64_t)dig_P2)<<12);
	var1 = (((((BME280_S64_t)1)<<47)+var1))*((BME280_S64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((BME280_S64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((BME280_S64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((BME280_S64_t)dig_P7)<<4);
	return (BME280_U32_t)p;
}

BME280_U32_t bme280_compensate_H_int32(BME280_S32_t adc_H)
{
	BME280_S32_t v_x1_u32r;
	v_x1_u32r = (t_fine - ((BME280_S32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)dig_H4) << 20) - (((BME280_S32_t)dig_H5) *
	v_x1_u32r)) + ((BME280_S32_t)16384)) >> 15) * (((((((v_x1_u32r *
	((BME280_S32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((BME280_S32_t)dig_H3)) >> 11) +
	((BME280_S32_t)32768))) >> 10) + ((BME280_S32_t)2097152)) * ((BME280_S32_t)dig_H2) +
	8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
	((BME280_S32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (BME280_U32_t)(v_x1_u32r>>12);
}

bme280_data_t bme280_readVal() {
	bme280_data_t data = {-1, -1, -1};

	// temp
	uint8_t msb_t = wiringPiI2CReadReg8(fd, REG_TEMP);
	uint8_t lsb_t = wiringPiI2CReadReg8(fd, REG_TEMP+1);
	uint8_t xlsb_t = wiringPiI2CReadReg8(fd, REG_TEMP+2);

	int32_t adc_T = ((int32_t)msb_t << 12) | ((int32_t)lsb_t << 4) | ((xlsb_t >> 4) & 0x0F);

	// humidity
	uint8_t msb_h = wiringPiI2CReadReg8(fd, REG_HUM);
	uint8_t lsb_h = wiringPiI2CReadReg8(fd, REG_HUM+1);

	int32_t adc_H = ((int32_t)msb_h << 8) | lsb_h;

	// pressure
	uint8_t msb_p = wiringPiI2CReadReg8(fd, REG_PRESS);
	uint8_t lsb_p = wiringPiI2CReadReg8(fd, REG_PRESS+1);
	uint8_t xlsb_p = wiringPiI2CReadReg8(fd, REG_PRESS+2);

	int32_t adc_P = ((int32_t)msb_p << 12) | ((int32_t)lsb_p << 4) | ((xlsb_p >> 4) & 0x0F);

	BME280_S32_t temperature = BME280_compensate_T_int32(adc_T);
	BME280_U32_t humidity = bme280_compensate_H_int32(adc_H);
	BME280_U32_t pressure = BME280_compensate_P_int64(adc_P);

	float temp_C = temperature / 100.0;
	float hum_perc = humidity / 1024.0;
	float press_hpa = pressure / 256.0 / 100.0;;
	
	data.humidity = hum_perc;
	data.temp = temp_C;
	data.pressure = press_hpa;

	return data;
}