#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

#include "FreeRTOS.h"
#include "task.h"

#include "core.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "usb_device.h"

#include "mpu9250.h"

#include "delay.h"

TaskHandle_t fcb_link_task_handle;
TaskHandle_t usb_link_task_handle;

void flow_estimate_task(void)
{
	while(mpu9250_init());

	/* successfully initialize the hardware == */
	gpio_on(LED_3); //red led
	vTaskResume(fcb_link_task_handle);
	vTaskResume(usb_link_task_handle);
	/* ======================================= */

	int state = 1;

	while(1) {
		if(state == 1) {
			gpio_on(LED_1);
			//gpio_on(LED_2);
		} else {
			gpio_off(LED_1);
			//gpio_off(LED_2);
		}

		state = (state + 1) % 2;

		vTaskDelay(MILLI_SECOND_TICK(500));
	}
}

void flight_ctrl_board_link_task(void)
{
	while(1) {
		uart2_puts("Hello World\n\r");

		vTaskDelay(MILLI_SECOND_TICK(500));
	}
}

void usb_link_task(void)
{
	usb_fs_init();
	char *str = "hello usb cdc\n\r";

	while(1) {
		usb_cdc_send((uint8_t *)str, strlen(str));

		vTaskDelay(500);
	}
}

int main(void)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	mpu_init();
	cpu_cache_enable();
	system_clock_init();

	gpio_init();
	uart_init();
	spi_init();

	xTaskCreate((TaskFunction_t)flow_estimate_task, "flow estimate task",
	            1024, (void *)0, tskIDLE_PRIORITY + 3, NULL);

	xTaskCreate((TaskFunction_t)flight_ctrl_board_link_task,
	            "flight control board link task",
	            1024, (void *)0, tskIDLE_PRIORITY + 2, &fcb_link_task_handle);
	vTaskSuspend(fcb_link_task_handle);

	xTaskCreate((TaskFunction_t)usb_link_task, "usb link task",
	            1024, (void *)0, tskIDLE_PRIORITY + 1, &usb_link_task_handle);
	vTaskSuspend(usb_link_task_handle);

	vTaskStartScheduler();

	return 0;
}
