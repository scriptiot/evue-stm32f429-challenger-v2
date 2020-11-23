/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ʹ��USB�ӿڼ�����FLASHģ��U��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F429 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
	__IO uint32_t i = 0;
	
	SysTick_Init();
	/* ��ʼ��LED */
	LED_GPIO_Config();
	/* ��ʼ������ */
	Key_GPIO_Config();
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	Debug_USART_Config();
	/* ��ʼ�������� */
	GTP_Init_Panel();
	
	//��λͬʱ����1���£������ⲿFlash U��ģʽ
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
	
	/* ��ʼ��SDRAM */
	
	
	
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
