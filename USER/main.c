/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   使用USB接口及板载FLASH模拟U盘
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F429 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f4xx.h"
#include "./Bsp/led/bsp_led.h" 
#include "./key/bsp_key.h" 
#include "./Bsp/usart/bsp_debug_usart.h"
#include "./bsp/flash/bsp_spi_flash.h"
#include "./sdram/bsp_sdram.h"
#include "./lcd/bsp_lcd.h"
#include "./systick/bsp_SysTick.h"
#include "./touch/gt9xx.h"

#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h"

#include "malloc.h"
#include "evm_main.h"
#include "evm.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE     USB_OTG_dev __ALIGN_END ;
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
	__IO uint32_t i = 0;
	
	SysTick_Init();
	/* 初始化LED */
	LED_GPIO_Config();
	/* 初始化按键 */
	Key_GPIO_Config();
	/* 初始化调试串口，一般为串口1 */
	Debug_USART_Config();
	/* 初始化触摸屏 */
	GTP_Init_Panel();
	
	//复位同时按键1按下，进入外部Flash U盘模式
	if( Key_Scan(KEY1_GPIO_PORT,KEY1_PIN) == KEY_ON  )
	{
		USBD_Init(&USB_OTG_dev,
            USB_OTG_HS_CORE_ID,
            &USR_desc,
            &USBD_MSC_cb, 
            &USR_cb);
	
		while(1)
		{
			Delay_ms(500);
			LED3_TOGGLE; 
		}
	}  
	
	/* 初始化SDRAM */
	
	
	
	LCD_Init();
	LCD_LayerInit();
	LTDC_Cmd(ENABLE);
	
	LCD_SetLayer(LCD_BACKGROUND_LAYER);	
	
	LCD_Clear(LCD_COLOR_BLACK);
	
	
	evm_main(NULL);
	
	while(1)
	{
		Delay_ms(200);
		LED3_TOGGLE; 
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
