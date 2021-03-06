#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#include "gpio.h"
#include "usb_device.h"

#include "mpu9250.h"
#include "mt9v034.h"

#include "flow.h"
#include "usb_link.h"
#include "system_time.h"

#define HEADER_MSG_SIZE 32

extern flow_t flow;

extern vector3d_f_t gyro_data;
extern vector3d_f_t accel_data;

extern uint16_t lidar_distance;

extern vector3d_f_t gyro_bias;

float led_blink_time_previous = 0;

static void usb_send_header_message(void)
{
	/* The size of the data is too big so need to be seperated into 3 part */
	char header_message[HEADER_MSG_SIZE];
	header_message[0] = '@';
	header_message[1] = 'u';
	header_message[2] = 'f';
	int append_size = 3;

	//lidar distance
	memcpy(header_message + append_size, &lidar_distance, sizeof(uint16_t));
	append_size += sizeof(uint16_t);

#if (DO_IMU_CALIBRATION == 0)
	uint8_t imu_calib_enable = 0;
	memcpy(header_message + append_size, &imu_calib_enable, sizeof(uint8_t));
	append_size += sizeof(uint8_t);
	//gyro x
	memcpy(header_message + append_size, &gyro_data.x, sizeof(float));
	append_size += sizeof(float);
	//gyro y
	memcpy(header_message + append_size, &gyro_data.y, sizeof(float));
	append_size += sizeof(float);
	//gyro z
	memcpy(header_message + append_size, &gyro_data.z, sizeof(float));
	append_size += sizeof(float);
#else
	uint8_t imu_calib_enable = 1;
	memcpy(header_message + append_size, &imu_calib_enable, sizeof(uint8_t));
	append_size += sizeof(uint8_t);

	//gyro drift x
	memcpy(header_message + append_size, &gyro_bias.x, sizeof(float));
	append_size += sizeof(float);
	//gyro drift y
	memcpy(header_message + append_size, &gyro_bias.y, sizeof(float));
	append_size += sizeof(float);
	//gyro drift z
	memcpy(header_message + append_size, &gyro_bias.z, sizeof(float));
	append_size += sizeof(float);
#endif

	//accel x
	memcpy(header_message + append_size, &accel_data.x, sizeof(float));
	append_size += sizeof(float);
	//accel y
	memcpy(header_message + append_size, &accel_data.y, sizeof(float));
	append_size += sizeof(float);
	//accel z
	memcpy(header_message + append_size, &accel_data.z, sizeof(float));
	append_size += sizeof(float);

	uint8_t image_width = IMG_WIDTH, image_height = IMG_HEIGHT;

	memcpy(header_message + append_size, &image_width, sizeof(uint8_t));
	append_size += sizeof(uint8_t);

	memcpy(header_message + append_size, &image_height, sizeof(uint8_t));
	append_size += sizeof(uint8_t);

	usb_cdc_send((uint8_t *)header_message, HEADER_MSG_SIZE);
}

/* foward sending the image without calculating the optical flow */
void usb_image_foward(void)
{
	/* send header message */
	usb_send_header_message();

	/* send image */
	const size_t half_image_size = sizeof(flow.image[0].frame) / 2;
	usb_cdc_send((uint8_t *)flow.image[0].frame, half_image_size);
	usb_cdc_send((uint8_t *)flow.image[0].frame + half_image_size, half_image_size);
}

#if (DISABLE_USB == 0)
/* send gyroscope data, image and flow flow visualization data */
void usb_send_flow_info(void)
{
	float current_time = get_time_sec();
	if((current_time - led_blink_time_previous) > 0.5) {
		gpio_toggle(LED_3);
		led_blink_time_previous = current_time;
	}

	/* send header message */
	usb_send_header_message();

	/* send image */
	size_t send_size = sizeof(flow.image[0].frame);
	usb_cdc_send((uint8_t *)flow.image[0].frame, send_size);

	/* send image */
	send_size = sizeof(flow.match_x);
	usb_cdc_send((uint8_t *)flow.match_x, send_size);

	/* send image */
	send_size = sizeof(flow.match_y);
	usb_cdc_send((uint8_t *)flow.match_y, send_size);
}
#endif
