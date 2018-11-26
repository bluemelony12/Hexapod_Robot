#include "main.h"
#include "Nucleo_F103.h"

GPIO_InitTypeDef		    						GPIO_Init_Struct; 					    // GPIO�� �ʱ�ȭ�� ����ü ����
TIM_HandleTypeDef									TimHandle_4;
TIM_HandleTypeDef									TimHandle_2;
TIM_HandleTypeDef									TimHandle_3;
TIM_OC_InitTypeDef								TIM_OCInit;												// Ÿ�̸� Channel(OC)�� �ʱ�ȭ�� ����ü ����
UART_HandleTypeDef						UartHandle;											// UART�� �ʱ�ȭ�� ����ü ����
UART_HandleTypeDef						UartHandle_B;
ADC_HandleTypeDef							AdcHandler;											// ADC�� �ʱ�ȭ�� ����ü ����
ADC_ChannelConfTypeDef   	Adc_sConfig; 									// ADC Channel�� �ʱ�ȭ�� ����ü ����

// -------------------------------------------------------------------------------- //
// -- <5> Nucleo_F103 ������ LED�� GPIO (PA5, PC0~PC7)�� �ʱ⼳���� ��

void Tim_Oc_It_Stop(void){
	HAL_TIM_OC_Stop_IT(&TimHandle_2,TIM_CHANNEL_1);
	HAL_TIM_OC_Stop_IT(&TimHandle_2,TIM_CHANNEL_2);
	HAL_TIM_OC_Stop_IT(&TimHandle_2,TIM_CHANNEL_3);
	HAL_TIM_OC_Stop_IT(&TimHandle_3,TIM_CHANNEL_1);
	HAL_TIM_OC_Stop_IT(&TimHandle_3,TIM_CHANNEL_2);
	HAL_TIM_OC_Stop_IT(&TimHandle_3,TIM_CHANNEL_3);
	HAL_TIM_OC_Stop_IT(&TimHandle_4,TIM_CHANNEL_1);
	HAL_TIM_OC_Stop_IT(&TimHandle_4,TIM_CHANNEL_2);
	HAL_TIM_OC_Stop_IT(&TimHandle_4,TIM_CHANNEL_3);
}

void ServoPin_Config(void)
{
		__HAL_RCC_GPIOA_CLK_ENABLE();
		GPIO_Init_Struct.Pin = GPIO_PIN_All;
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_Init_Struct.Pull     = GPIO_PULLUP;
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

		__HAL_RCC_GPIOC_CLK_ENABLE();
		GPIO_Init_Struct.Pin = GPIO_PIN_All;
		GPIO_Init_Struct.Mode  = GPIO_MODE_OUTPUT_PP;
		GPIO_Init_Struct.Pull     = GPIO_PULLUP;
		GPIO_Init_Struct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);
}

void Sw_Config(void)
{
		/*// -- Nucleo Board Switch (PC13)����
		// -- <6-1> GPIOC�� Ŭ���� enable
		__HAL_RCC_GPIOC_CLK_ENABLE();

		// -- <6-2> SW1�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_PULLUP; 						// Pull Up ���
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <6-3> GPIOC�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);

		// -- Ȯ�� IO Board Switch (PA8, PB4, PB5, PB10)����
		//  SW1�� GPIO (PA8)�� �ʱ⼳��
		// -- <6-4> GPIOA�� Ŭ���� enable
		__HAL_RCC_GPIOA_CLK_ENABLE();

		// -- <6-5> SW1�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_8;	// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_PULLUP; 						// Pull Up ���
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <6-6> GPIOA�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

		//  SW2, SW3, SW4�� GPIO (PB4, PB5, PB10)�� �ʱ⼳��
		// -- <6-7> GPIOB�� Ŭ���� enable
		__HAL_RCC_GPIOB_CLK_ENABLE();

		// -- <6-8> SW�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10;		// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_INPUT; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ��Ȱ��ȭ
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <6-9> GPIOB�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);
*/

}

// -------------------------------------------------------------------------------- //
// -- <7> Nucleo_F103 ������  Switch�� GPIO (PC13, PA8, PB4, PB5, PB10)�� �ʱ⼳���� ��
//				* �� �Լ��� SW�� ������ EXTI�� �߻��ϵ��� �����Ѵ�.

void SwEXTI_Config(void)
{
		// -- Nucleo Board Switch (PC13)����
		// -- <7-1> GPIOC�� Ŭ���� enable
		/*__HAL_RCC_GPIOC_CLK_ENABLE();

		// -- <7-2> SW1�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_13;	// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ��Ȱ��ȭ
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <7-3> GPIOC�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);

		// -- Ȯ�� IO Board Switch (PA8, PB4, PB5, PB10)����
		//  SW1�� GPIO (PA8)�� �ʱ⼳��
		// -- <7-4> GPIOA�� Ŭ���� enable
		__HAL_RCC_GPIOA_CLK_ENABLE();

		// -- <7-5> SW1�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_8;	// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ��Ȱ��ȭ
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <7-6> GPIOA�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

		//  SW2, SW3, SW4�� GPIO (PB4, PB5, PB10)�� �ʱ⼳��
		// -- <7-7> GPIOB�� Ŭ���� enable
		__HAL_RCC_GPIOB_CLK_ENABLE();

		// -- <7-8> SW�� ���� ������ GPIO �Է����� ����
		GPIO_Init_Struct.Pin 		= GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10;		// GPIO���� ����� PIN ����
		GPIO_Init_Struct.Mode 	= GPIO_MODE_IT_FALLING; 				// Input Floating ���
		GPIO_Init_Struct.Pull 		= GPIO_NOPULL; 						// Pull Up / Pull Down ��Ȱ��ȭ
		GPIO_Init_Struct.Speed 	= GPIO_SPEED_FREQ_HIGH; 		// ���ۼӵ��� HIGH��

		// -- <7-9> GPIOB�� GPIO_Init_Struct�� ������ �������� �ʱ�ȭ��
		HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);

		// -- <7-10> Sw1�� EXTI�� ���� ���ͷ�Ʈ�� �켱������ �����ϰ�, ���ͷ�Ʈ�� enable��
		HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);	 //  EXTI �� priority�� ����
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);			 //  EXTI ���ͷ�Ʈ�� enable

		HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);		//  EXTI �� priority�� ����
		HAL_NVIC_EnableIRQ(EXTI4_IRQn);				//  EXTI ���ͷ�Ʈ�� enable

		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);	//  EXTI �� priority�� ����
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);			//  EXTI ���ͷ�Ʈ�� enable
		*/

}

// -------------------------------------------------------------------------------- //
// -- <8> Timer�� �ʱ⼳���� ���� �Լ�
//			  * TIM2�� Up couting ���� ���۽��� 1�ʿ� 1���� �߻��ϵ��� ���ļ��� 1 Hz�� �����Ѵ�.

void TIM4_Config(int prescaler_value, int period_value)
{

		// -- <8-1> TIM2�� clock�� enable
		__HAL_RCC_TIM4_CLK_ENABLE();

		// -- <8-2> TIM�� ���� ���� ���� (���ͷ�Ʈ�� 1�ʿ� 1���� �߻��ϵ��� ���ļ��� 1 Hz�� ����)
		TimHandle_4.Instance = TIM4;								// TIM2 ���
		TimHandle_4.Init.CounterMode = TIM_COUNTERMODE_UP;	//	Up Counter ��� ����
		TimHandle_4.Init.Prescaler = prescaler_value;					// Prescaler =6399�� ����
		TimHandle_4.Init.Period = period_value;							// ������Ʈ �̺�Ʈ �߻��� Auto-Reload �������� = 9999�� ����
		TimHandle_4.Init.ClockDivision = 0;
		TimHandle_4.Init.RepetitionCounter = 0;

		// -- <8-3> TIM2�� TimHandle�� ������ ������ �ʱ�ȭ�ϰ� TIM�� ����
		HAL_TIM_Base_Init(&TimHandle_4);
		HAL_TIM_Base_Start_IT(&TimHandle_4);

		// -- <8-4> Ÿ�̸� ���ͷ�Ʈ �켱���� ���� �� ENABLE
		HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);		// ������ �������� ������ ����Ʈ�� ������
		HAL_NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM2_Config(int prescaler_value, int period_value)
{

		// -- <8-1> TIM2�� clock�� enable
		__HAL_RCC_TIM2_CLK_ENABLE();

		// -- <8-2> TIM�� ���� ���� ���� (���ͷ�Ʈ�� 1�ʿ� 1���� �߻��ϵ��� ���ļ��� 1 Hz�� ����)
		TimHandle_2.Instance = TIM2;								// TIM2 ���
		TimHandle_2.Init.CounterMode = TIM_COUNTERMODE_UP;	//	Up Counter ��� ����
		TimHandle_2.Init.Prescaler = prescaler_value;					// Prescaler =6399�� ����
		TimHandle_2.Init.Period = period_value;							// ������Ʈ �̺�Ʈ �߻��� Auto-Reload �������� = 9999�� ����
		TimHandle_2.Init.ClockDivision = 0;					// Clock Division ����

		// -- <8-3> TIM2�� TimHandle�� ������ ������ �ʱ�ȭ�ϰ� TIM�� ����
		HAL_TIM_Base_Init(&TimHandle_2);
		HAL_TIM_Base_Start_IT(&TimHandle_2);

		// -- <8-4> Ÿ�̸� ���ͷ�Ʈ �켱���� ���� �� ENABLE
		HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);		// ������ �������� ������ ����Ʈ�� ������
		HAL_NVIC_EnableIRQ(TIM2_IRQn);
}


void TIM3_Config(int prescaler_value, int period_value)
{

		// -- <9-1> TIM2�� clock�� enable
		__HAL_RCC_TIM3_CLK_ENABLE();

		// -- <9-2> TIM�� ���� ���� ���� (���ͷ�Ʈ�� 1�ʿ� 1���� �߻��ϵ��� ���ļ��� 1 Hz�� ����)
		TimHandle_3.Instance = TIM3;								// TIM3 ���
		TimHandle_3.Init.CounterMode = TIM_COUNTERMODE_UP;	//	Down Counter ��� ����
		TimHandle_3.Init.Prescaler = prescaler_value;					// Prescaler =6399�� ����
		TimHandle_3.Init.Period = period_value;							// ������Ʈ �̺�Ʈ �߻��� Auto-Reload �������� = 9999�� ����
		TimHandle_3.Init.ClockDivision = 0;					// Clock Division ����

		// -- <9-3> TIM3�� TimHandle�� ������ ������ �ʱ�ȭ�ϰ� TIM�� ����
		HAL_TIM_Base_Init(&TimHandle_3);
		HAL_TIM_Base_Start_IT(&TimHandle_3);

		// -- <9-4> Ÿ�̸� ���ͷ�Ʈ �켱���� ���� �� ENABLE
		HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);		// ������ �������� ������ ����Ʈ�� ������
		HAL_NVIC_EnableIRQ(TIM3_IRQn);
}


void TIM_OC_Config(TIM_HandleTypeDef handle_n, int pulse_value1,int pulse_value2,int pulse_value3)
{
		// -- <10-1> TIM�� OC �������� ����
		TIM_OCInit.OCMode = TIM_OCMODE_TIMING;					// Output Compare ���۸�� ����
		TIM_OCInit.Pulse = pulse_value1;							// Capture/Compare Register(CCR)�� ������
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;			// OC ����� High�� ����
		TIM_OCInit.OCFastMode = TIM_OCFAST_ENABLE; 		// TIM Output Compare Fast�� Disable

		HAL_TIM_OC_Init(&handle_n);
		HAL_TIM_OC_ConfigChannel(&handle_n, &TIM_OCInit, TIM_CHANNEL_1);
		HAL_TIM_OC_Start_IT(&handle_n,TIM_CHANNEL_1);

		TIM_OCInit.Pulse = pulse_value2;							// Capture/Compare Register(CCR)�� ������
		HAL_TIM_OC_Init(&handle_n);
		HAL_TIM_OC_ConfigChannel(&handle_n, &TIM_OCInit, TIM_CHANNEL_2);
		HAL_TIM_OC_Start_IT(&handle_n,TIM_CHANNEL_2);

		TIM_OCInit.Pulse = pulse_value3;							// Capture/Compare Register(CCR)�� ������
		HAL_TIM_OC_Init(&handle_n);
		HAL_TIM_OC_ConfigChannel(&handle_n, &TIM_OCInit, TIM_CHANNEL_3);
		HAL_TIM_OC_Start_IT(&handle_n,TIM_CHANNEL_3);
}
// -------------------------------------------------------------------------------- //
// -- <11> Timer�� PWM ���� �ʱ⼳���� ���� �Լ�

void TIM_PWM_IT_Config(int pwm_value)
{

		/*// -- <11-1> TIM�� OC �������Ǽ���
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;
		TIM_OCInit.Pulse = pwm_value;
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;

		// -- <11-2> TIM PWM�� TimHandle�� ������ ������ �ʱ�ȭ ��
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <11-3> TIM PWM�� Channel�� TIM_OCInit�� ������ ������ �ʱ�ȭ ��
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <11-4> TIM PWM�� ������
		HAL_TIM_PWM_Start_IT(&TimHandle,TIM_CHANNEL_1);*/
}

// -------------------------------------------------------------------------------- //
// -- <12> Timer�� PWM ���� �ʱ⼳���� ���� �Լ�

void TIM_PWM_Poll_Config(int pwm_value)
{

		/*// -- <12-1> TIM�� OC �������Ǽ���
		TIM_OCInit.OCMode = TIM_OCMODE_PWM1;
		TIM_OCInit.Pulse = pwm_value;
		TIM_OCInit.OCPolarity = TIM_OCPOLARITY_HIGH;

		// -- <12-2> TIM PWM�� TimHandle�� ������ ������ �ʱ�ȭ ��
		HAL_TIM_PWM_Init(&TimHandle);

		// -- <12-3> TIM PWM�� Channel�� TIM_OCInit�� ������ ������ �ʱ�ȭ ��
 		HAL_TIM_PWM_ConfigChannel(&TimHandle, &TIM_OCInit, TIM_CHANNEL_1);

		// -- <12-4> TIM PWM�� ������
		HAL_TIM_PWM_Start(&TimHandle,TIM_CHANNEL_1);*/
}

// -------------------------------------------------------------------------------- //
// -- <13> UART�� �ʱ⼳���� ���� �Լ�
void UART2_Config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_Init_Struct.Pin	= GPIO_PIN_2;
	GPIO_Init_Struct.Mode	= GPIO_MODE_AF_PP;
	GPIO_Init_Struct.Pull	= GPIO_PULLUP;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

	GPIO_Init_Struct.Pin	= GPIO_PIN_3;
	GPIO_Init_Struct.Mode	= GPIO_MODE_INPUT;
	GPIO_Init_Struct.Pull	= GPIO_NOPULL;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

	UartHandle.Instance	= USART2;
	UartHandle.Init.BaudRate	= 9600;
	UartHandle.Init.WordLength	= UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits	= UART_STOPBITS_1;
	UartHandle.Init.Parity	= UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UartHandle.Init.Mode	= UART_MODE_TX_RX;

	HAL_UART_Init(&UartHandle);

	//HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void UART3_B_Config(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_USART3_CLK_ENABLE();

	GPIO_Init_Struct.Pin	= GPIO_PIN_10;
	GPIO_Init_Struct.Mode	= GPIO_MODE_AF_PP;
	GPIO_Init_Struct.Pull	= GPIO_PULLUP;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);

	GPIO_Init_Struct.Pin	= GPIO_PIN_11;
	GPIO_Init_Struct.Mode	= GPIO_MODE_INPUT;
	GPIO_Init_Struct.Pull	= GPIO_NOPULL;
	GPIO_Init_Struct.Speed	= GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_Init_Struct);

	UartHandle_B.Instance	= USART3;
	UartHandle_B.Init.BaudRate	= 9600;
	UartHandle_B.Init.WordLength	= UART_WORDLENGTH_8B;
	UartHandle_B.Init.StopBits	= UART_STOPBITS_1;
	UartHandle_B.Init.Parity	= UART_PARITY_NONE;
	UartHandle_B.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UartHandle_B.Init.Mode	= UART_MODE_TX_RX;

	HAL_UART_Init(&UartHandle_B);

	//HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(USART3_IRQn);
}

// -------------------------------------------------------------------------------- //
// -- <14> ADC�� �ʱ⼳���� ���� �Լ�
void ADC1_Polling_Config(void)
{
    /*// -- <14-1> ADC�� clock�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_ADC1_CLK_ENABLE();

    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_1;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

    // -- <14-2> ADC�� ���� ���� ����
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;

    // -- <14-3> ADC�� AdcHandler�� ������ ������ �ʱ�ȭ ��
    HAL_ADC_Init(&AdcHandler);

	// -- <14-4> ADC Calibration�� ����
    HAL_ADCEx_Calibration_Start(&AdcHandler);

    // -- <14-5> ADC Channel�������� ����
    Adc_sConfig.Channel	= ADC_CHANNEL_1;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_13CYCLES_5;

		// -- <14-6> ������ sConfig�� AdcHandler�� �������� �ʱ�ȭ ��
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <14-7> ADC�� ���۽�Ŵ
		HAL_ADC_Start(&AdcHandler);

		// -- <14-8> ��ȯ�� �Ϸ�� ������ ���
		HAL_ADC_PollForConversion(&AdcHandler, 10);	*/

}

// -------------------------------------------------------------------------------- //
// -- <15> ADC�� �ʱ⼳���� ���� �Լ�
void ADC1_Interrupt_Config(void)
{
    /*// -- <15-1> ADC�� clock�� Ȱ��ȭ
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_ADC1_CLK_ENABLE();

    GPIO_Init_Struct.Mode  = GPIO_MODE_ANALOG;
    GPIO_Init_Struct.Pin 	= GPIO_PIN_1;
		GPIO_Init_Struct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_Init_Struct);

    // -- <15-2> ADC�� ���� ���� ����
		AdcHandler.Instance = ADC1;
		AdcHandler.Init.ScanConvMode = DISABLE;
		AdcHandler.Init.ContinuousConvMode = ENABLE;
		AdcHandler.Init.ExternalTrigConv = ADC_SOFTWARE_START;
		AdcHandler.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandler.Init.NbrOfConversion = 1;

    // -- <15-3> ADC�� AdcHandler�� ������ ������ �ʱ�ȭ ��
    HAL_ADC_Init(&AdcHandler);

	// -- <15-4> ADC Calibration�� ����
    HAL_ADCEx_Calibration_Start(&AdcHandler);

    // -- <15-5> ADC Channel�������� ����
    Adc_sConfig.Channel	= ADC_CHANNEL_1;
    Adc_sConfig.Rank         	= 1;
    Adc_sConfig.SamplingTime 	= ADC_SAMPLETIME_13CYCLES_5;

		// -- <15-6> ������ sConfig�� AdcHandler�� �������� �ʱ�ȭ ��
		HAL_ADC_ConfigChannel(&AdcHandler, &Adc_sConfig);

		// -- <15-7> ADC�� ���۽�Ŵ
		HAL_ADC_Start_IT(&AdcHandler);

    // -- <15-7> ADC ���ͷ�Ʈ �켱���� ���� �� Ȱ��ȭ
    HAL_NVIC_SetPriority(ADC1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(ADC1_IRQn);*/

}

// -------------------------------------------------------------------------------- //
// -- <16> �ǽ�������  LED�� ON��Ű�� ���� �ð��Ŀ� �ٽ� OFF ��Ű�� �Լ�

// -------------------------------------------------------------------------------- //
//   --  <17>  System Clock �� �������ִ� �Լ�
/*				- Ŭ���� ������ ���� �����ȴ�.

  *            System Clock source   = PLL (HSI)
  *            SYSCLK(Hz)                = 64,000,000
  *            HCLK(Hz)                    = 64,000,000
  *            AHB Prescaler              = 1
  *            APB1 Prescaler            = 2
  *            APB2 Prescaler            = 1
  *            PLLMUL                      = 16
  *            Flash Latency(WS)       = 2
  */
// -------------------------------------------------------------------------------- //

void  SystemClock_Config(void)
{
		  RCC_ClkInitTypeDef clkinitstruct = {0};
		  RCC_OscInitTypeDef oscinitstruct = {0};

		  /* Configure PLL ------------------------------------------------------*/
		  /* PLL configuration: PLLCLK = (HSI / 2) * PLLMUL = (8 / 2) * 16 = 64 MHz */
		  /* PREDIV1 configuration: PREDIV1CLK = PLLCLK / HSEPredivValue = 64 / 1 = 64 MHz */
		  /* Enable HSI and activate PLL with HSi_DIV2 as source */
		  oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSI;
		  oscinitstruct.HSEState        = RCC_HSE_OFF;
		  oscinitstruct.LSEState        = RCC_LSE_OFF;
		  oscinitstruct.HSIState        = RCC_HSI_ON;
		  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		  oscinitstruct.HSEPredivValue    = RCC_HSE_PREDIV_DIV1;
		  oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
		  oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSI_DIV2;
		  oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL16;

		  if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)   {
					/* Initialization Error */
					while(1);
		  }

		  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
			 clocks dividers */
		  clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
		  clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		  clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		  clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
		  clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;

		  if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_2)!= HAL_OK)   {
					/* Initialization Error */
					while(1);
		  }
}

// -------------------------------------------------------------------------------- //
//   --  <18>  Clock ������ ������ �߻��ϸ� ó�����ִ� �Լ�
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

		  /* Infinite loop */
		  while (1)
		  {
		  }
}
#endif

// -------------------------------------------------------------------------------- //
