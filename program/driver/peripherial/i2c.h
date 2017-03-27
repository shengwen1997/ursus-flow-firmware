#ifndef __I2C_H__
#define __I2C_H__

void i2c_init(void);

void i2c1_read(uint16_t device_address, uint8_t *data, uint16_t size);
void i2c1_write(uint16_t device_address, uint8_t *data, uint16_t size);

#endif