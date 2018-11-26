#define GPIONucleo					GPIOA 
#define GPIOExt									GPIOC
#define GPIO_PIN_Led1			GPIO_PIN_0
#define GPIO_PIN_Led2			GPIO_PIN_1
#define GPIO_PIN_Led3			GPIO_PIN_2
#define GPIO_PIN_Led4			GPIO_PIN_3
#define GPIO_PIN_Led5			GPIO_PIN_4
#define GPIO_PIN_Led6			GPIO_PIN_5
#define GPIO_PIN_Led7			GPIO_PIN_6
#define GPIO_PIN_Led8			GPIO_PIN_7
#define GPIO_PIN_LedAll		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7

#define GPIOSwNucleo							GPIOC
#define GPIOSw1												GPIOA
#define GPIOSw2												GPIOB
#define GPIOSw3												GPIOB
#define GPIOSw4												GPIOB
#define GPIO_PIN_Nucleo_Sw		GPIO_PIN_13
#define GPIO_PIN_Sw1							GPIO_PIN_8
#define GPIO_PIN_Sw2							GPIO_PIN_4
#define GPIO_PIN_Sw3							GPIO_PIN_5
#define GPIO_PIN_Sw4							GPIO_PIN_10
#define TIMER2													TIM2


void SystemClock_Config(void);
void ServoPin_Config(void);
void Sw_Config(void);
void SwEXTI_Config(void);
void TIM4_Config(int prescaler_value, int period_value);
void TIM2_Config(int prescaler_value, int period_value);
void TIM3_Config(int prescaler_value, int period_value);
void TIM_OC_Config(TIM_HandleTypeDef handle_n, int pulse_value1,int pulse_value2,int pulse_value3);
void TIM_PWM_Poll_Config(int pwm_value);
void TIM_PWM_IT_Config(int pwm_value);
void UART2_Config(void);
void UART3_B_Config(void);
void ADC1_Polling_Config(void);
void ADC1_Interrupt_Config(void);
void Tim_Oc_It_Stop(void);

// -------------------------------------------------------------------------------- //
