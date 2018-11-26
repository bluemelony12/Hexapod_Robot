#include "main.h"
#include "stm32f1xx_it.h"					// 인터럽트 사용에 필요한 헤더 파일

// -------------------------------------------------------------------------------- //

void SysTick_Handler(void)
{	
		HAL_IncTick();
}

// -------------------------------------------------------------------------------- //

void EXTI15_10_IRQHandler(void)
{	
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
	  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}

// -------------------------------------------------------------------------------- //

void EXTI4_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);	
}

// -------------------------------------------------------------------------------- //

void EXTI9_5_IRQHandler(void)
{
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
		HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);		
}

// -------------------------------------------------------------------------------- //
// -- <1> TIM 인터럽트  IRQ handler 함수를 위한 TimHandler 변수를 외부정의 변수로 선언
extern 	TIM_HandleTypeDef									TimHandle_4;
extern	TIM_HandleTypeDef									TimHandle_2;
extern	TIM_HandleTypeDef									TimHandle_3;
extern UART_HandleTypeDef   UartHandle;
extern UART_HandleTypeDef   UartHandle_B;

// -------------------------------------------------------------------------------- //
// -- <2> TIM 인터럽트 IRQ handler 함수

void TIM4_IRQHandler(void)
{	
		// -- <2-1> TIM 인터럽트 Callback 함수
		HAL_TIM_IRQHandler(&TimHandle_4);	
}

void TIM2_IRQHandler(void)
{	
		// -- <2-1> TIM 인터럽트 Callback 함수
		HAL_TIM_IRQHandler(&TimHandle_2);	
}

// -------------------------------------------------------------------------------- //

// -- <3> TIM 인터럽트 IRQ handler 함수
void TIM3_IRQHandler(void)
{	
		// -- <3-1> TIM 인터럽트 Callback 함수
		HAL_TIM_IRQHandler(&TimHandle_3);	
}

void USART2_IRQHandler(void)
{
	// -- <2-1> UART 인터럽트 Callback 함수 
	HAL_UART_IRQHandler(&UartHandle);
}

void USART3_IRQHandler(void)
{
	// -- <2-1> UART 인터럽트 Callback 함수 
	HAL_UART_IRQHandler(&UartHandle_B);
}
// -------------------------------------------------------------------------------- //

