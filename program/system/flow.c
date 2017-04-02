#include <stdbool.h>

#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"

#include "mpu9250.h"
#include "mt9v034.h"
#include "lidar.h"

#include "delay.h"
#include "imu.h"

#include "usb_link.h"
#include "fcb_link.h"

extern TaskHandle_t fcb_link_task_handle;
extern TaskHandle_t usb_link_task_handle;

uint16_t image_buffer[IMG_WIDTH][IMG_HEIGHT];

vector3d_f_t gyro_data;
uint16_t lidar_distance;

bool do_gyro_calibrate = false; //set true to eanble the calibration function

float drift_x = 0;
float drift_y = 0;
float drift_z = 0;

void flow_estimate_task(void)
{
	/* wait until the mcu peripherial initialization is finished */
	vTaskDelay(MILLI_SECOND_TICK(5));

	if(mpu9250_init()) {
		while(1); //This is bad
	}

	if(mt9v034_init((uint32_t)image_buffer)) {
		while(1); //This is bad
	}

	/* successfully initialized the hardware == */
	gpio_on(LED_3); //red led
	vTaskResume(fcb_link_task_handle);
	vTaskResume(usb_link_task_handle);
	/* ======================================== */

	if(do_gyro_calibrate == true) {
		mpu9250_drift_error_estimate(&drift_x, &drift_y, &drift_z);
	}

	int state = 1;

	while(1) {
		mpu9250_read(&gyro_data);

		lidar_distance = lidar_read_distance();
	
		if(state == 1) {
			gpio_on(LED_1);
			//gpio_on(LED_2);
		} else {
			gpio_off(LED_1);
			//gpio_off(LED_2);
		}

		state = (state + 1) % 2;

		vTaskDelay(MILLI_SECOND_TICK(100));
	}
}
