#include "main.h"
#include "stdio.h"
#include "Nucleo_F103.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

extern TIM_HandleTypeDef    TimHandle_4,TimHandle_2,TimHandle_3;
extern TIM_OC_InitTypeDef		TIM_OCInit;
extern UART_HandleTypeDef	UartHandle;
extern UART_HandleTypeDef	UartHandle_B;

#define TxBufferSize	(countof(TxBuffer) - 1)
#define RxBufferSize	0xFF
#define RxBufferSize2	0xFF
#define countof(a)	(sizeof(a) / sizeof(*(a)))

uint8_t TxBuffer[] = "\n\rTransmission Success !!\n\r\n\r";
uint8_t RxBuffer[RxBufferSize];

int part_check = 0;


int Leg_Reset1_set = 0;
int Leg_Reset2_set = 0;
int Leg_test1_1LegMove_set = 0;
int Leg_test2_TriLegMove_set = 0;
int Leg_test3_TurnLeft_set = 0;
int Leg_test4_TurnRight_set = 0;
int Leg_test5_LegCheck_set = 0;
int Leg_test6_Hand_set = 0;


//------------------------------------ �ٸ� �ʱ���� �Է� ------------------------------------------------
int leg_1_p[] = {850,800,600}; //��ü(COXA), ����(FEMUR), ��(TIBIA)
int leg_2_p[] = {850,800,600};
int leg_3_p[] = {750,900,650};
int leg_4_p[] = {750,700,550};
int leg_5_p[] = {650,800,550};
int leg_6_p[] = {650,800,550};  //�ʱⰪ, ���� �ٸ� ���� ����


int leg_1[] = {850,800,600}; //��ü(COXA), ����(FEMUR), ��(TIBIA)
int leg_2[] = {850,800,600};
int leg_3[] = {750,900,650};
int leg_4[] = {750,700,550};
int leg_5[] = {650,800,550};
int leg_6[] = {650,800,550};  //���ĵ�


//------------------------------------ <<< �ٸ� ���� >>> ------------------------------------------------
/*
	��Ʈ C ���(part_check = 0)
	TIM_OC_Config(TimHandle_2, 5�� ��, 6�� ��, 7�� ��);
	TIM_OC_Config(TimHandle_3, 8�� ��, 9�� ��, 10�� ��);
	TIM_OC_Config(TimHandle_4, 11�� ��, 12�� ��, 13�� ��);

	��Ʈ A ���(part_check = 1)
	TIM_OC_Config(TimHandle_2, 4�� ��, 5�� ��, 6�� ��);
	TIM_OC_Config(TimHandle_3, 7�� ��, 8�� ��, 9�� ��);
	TIM_OC_Config(TimHandle_4, 10�� ��, 11�� ��, 12�� ��);
*/

void Leg_Angle_Set0(){
	part_check = 0;

	for(int c=1;c<11;c++){
		TIM_OC_Config(TimHandle_4,leg_1_p[2]+((leg_1[2]-leg_1_p[2])/10*c),1300-(leg_4_p[2]+((leg_4[2]-leg_4_p[2])/10*c)),leg_5_p[2]+((leg_5[2]-leg_5_p[2])/10*c));
		HAL_Delay(20);
		TIM_OC_Config(TimHandle_3,leg_1_p[1]+((leg_1[1]-leg_1_p[1])/10*c),1300-(leg_4_p[1]+((leg_4[1]-leg_4_p[1])/10*c)),leg_5_p[1]+((leg_5[1]-leg_5_p[1])/10*c));
		HAL_Delay(20);
		TIM_OC_Config(TimHandle_2,leg_1_p[0]+((leg_1[0]-leg_1_p[0])/10*c),1500-(leg_4_p[0]+((leg_4[0]-leg_4_p[0])/10*c)),leg_5_p[0]+((leg_5[0]-leg_5_p[0])/10*c));
		HAL_Delay(20);
	}
	leg_1_p[0] = leg_1[0];
	leg_4_p[0] = leg_4[0];
	leg_5_p[0] = leg_5[0];

	leg_1_p[1] = leg_1[1];
	leg_4_p[1] = leg_4[1];
	leg_5_p[1] = leg_5[1];

	leg_1_p[2] = leg_1[2];
	leg_4_p[2] = leg_4[2];
	leg_5_p[2] = leg_5[2];
	HAL_Delay(20);
}
//------------- 1��Ʈ �ٸ� ���� ------------------------------------------------------------------------------------

void Leg_Angle_Set1(){
	part_check = 1;

	for(int c=1;c<11;c++){
		TIM_OC_Config(TimHandle_4,1300-(leg_2_p[2]+((leg_2[2]-leg_2_p[2])/10*c)),1300-(leg_6_p[2]+((leg_6[2]-leg_6_p[2])/10*c)),leg_3_p[2]+((leg_3[2]-leg_3_p[2])/10*c));
		HAL_Delay(20);
		TIM_OC_Config(TimHandle_3,1300-(leg_2_p[1]+((leg_2[1]-leg_2_p[1])/10*c)),1300-(leg_6_p[1]+((leg_6[1]-leg_6_p[1])/10*c)),leg_3_p[1]+((leg_3[1]-leg_3_p[1])/10*c));
		HAL_Delay(20);
		TIM_OC_Config(TimHandle_2,1500-(leg_2_p[0]+((leg_2[0]-leg_2_p[0])/10*c)),1500-(leg_6_p[0]+((leg_6[0]-leg_6_p[0])/10*c)),leg_3_p[0]+((leg_3[0]-leg_3_p[0])/10*c));
		HAL_Delay(20);
	}
	leg_2_p[0] = leg_2[0];
	leg_6_p[0] = leg_6[0];
	leg_3_p[0] = leg_3[0];

	leg_2_p[1] = leg_2[1];
	leg_6_p[1] = leg_6[1];
	leg_3_p[1] = leg_3[1];

	leg_2_p[2] = leg_2[2];
	leg_6_p[2] = leg_6[2];
	leg_3_p[2] = leg_3[2];
	HAL_Delay(20);
}
//-------------- 2��Ʈ �ٸ� ���� -----------------------------------------------------------------------------------

void Leg_Reset1(){

	leg_1[0] = 850; leg_1[1] = 1000; leg_1[2] = 300;
	leg_4[0] = 750; leg_4[1] = 1000; leg_4[2] = 300;
	leg_5[0] = 650; leg_5[1] = 1000; leg_5[2] = 300;
	Leg_Angle_Set0();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[0] = 850; leg_2[1] = 1000; leg_2[2] = 300;
	leg_3[0] = 750; leg_3[1] = 1000; leg_3[2] = 300;
	leg_6[0] = 650; leg_6[1] = 1000; leg_6[2] = 300;
	Leg_Angle_Set1();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);
}
//----------- �ٸ� ª�� ���� ----------------------------------------------------------------------------------

void Leg_Reset2(){

	leg_1[0] = 850; leg_1[1] = 800; leg_1[2] = 600;
	leg_4[0] = 750; leg_4[1] = 700; leg_4[2] = 550;
	leg_5[0] = 650; leg_5[1] = 800; leg_5[2] = 550;
	Leg_Angle_Set0();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[0] = 850; leg_2[1] = 800; leg_2[2] = 600;
	leg_3[0] = 750; leg_3[1] = 900; leg_3[2] = 650;
	leg_6[0] = 650; leg_6[1] = 800; leg_6[2] = 550;
	Leg_Angle_Set1();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);


}
//------------ �ٸ� ��� ����(���ĵ�) -------------------------------------------------------------------------------------

void Leg_test1_1LegMove(){

	leg_1[1] = 600; leg_1[2] = 500;            // 1�� �ٸ� ���
	Leg_Angle_Set0();
	leg_1[0] = 700;                            // 1�� �ٸ� ������
	Leg_Angle_Set0();
	leg_1[1] = 900; leg_1[2] = 700;            // 1�� �ٸ� ������
	Leg_Angle_Set0();

	leg_4[1] = 500; leg_4[2] = 450;            // 4�� �ٸ� ���
	Leg_Angle_Set0();
	leg_4[0] = 600;                            // 4�� �ٸ� ������
	Leg_Angle_Set0();
	leg_4[1] = 800; leg_4[2] = 650;            // 4�� �ٸ� ������
	Leg_Angle_Set0();

	leg_5[1] = 600; leg_5[2] = 450;            // 5�� �ٸ� ���
	Leg_Angle_Set0();
	leg_5[0] = 500;                            // 5�� �ٸ� ������
	Leg_Angle_Set0();
	leg_5[1] = 900; leg_5[2] = 650;            // 5�� �ٸ� ������
	Leg_Angle_Set0();

	HAL_Delay(200);

	leg_1[0] = 850;                            // 1�� �ٸ� �ڷ�
	leg_4[0] = 750;                            // 4�� �ٸ� �ڷ�
	leg_5[0] = 650;                            // 5�� �ٸ� �ڷ�
	Leg_Angle_Set0();

	leg_1[1] = 800; leg_1[2] = 600;            // 1�� ������
	leg_4[1] = 700; leg_4[2] = 550;            // 4�� ������
	leg_5[1] = 800; leg_5[2] = 550;            // 5�� ������
	Leg_Angle_Set0();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	///////////////////////////////////////////////////////////////

	leg_2[1] = 600; leg_2[2] = 500;             // 2�� �ٸ� ���
	Leg_Angle_Set1();
	leg_2[0] = 700;                             // 2�� �ٸ� ������
	Leg_Angle_Set1();
	leg_2[1] = 850; leg_2[2] = 650;             // 2�� �ٸ� ������
	Leg_Angle_Set1();

	leg_3[1] = 700; leg_3[2] = 550;             // 3�� �ٸ� ���
	Leg_Angle_Set1();
	leg_3[0] = 650;                             // 3�� �ٸ� ������
	Leg_Angle_Set1();
	leg_3[1] = 1000; leg_3[2] = 750;            // 3�� �ٸ� ������
	Leg_Angle_Set1();

	leg_6[1] = 600; leg_6[2] = 450;             // 6�� �ٸ� ���
	Leg_Angle_Set1();
	leg_6[0] = 500;                             // 6�� �ٸ� ������
	Leg_Angle_Set1();
	leg_6[1] = 900; leg_6[2] = 650;             // 6�� �ٸ� ������
	Leg_Angle_Set1();

	HAL_Delay(200);

	leg_2[0] = 850;                            // 2�� �ٸ� �ڷ�
	leg_3[0] = 750;                            // 3�� �ٸ� �ڷ�
	leg_6[0] = 650;                            // 6�� �ٸ� �ڷ�
	Leg_Angle_Set1();

	leg_2[1] = 800; leg_2[2] = 600;            // 2�� �ٸ� ������
	leg_3[1] = 900; leg_3[2] = 650;            // 3�� �ٸ� ������
	leg_6[1] = 800; leg_6[2] = 550;            // 6�� �ٸ� ������
	Leg_Angle_Set1();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

}
//-------------- 1�ٸ��� ������ ���� -----------------------------------------------------------------------------------

void Leg_test2_TriLegMove(){

	leg_1[1] = 600; leg_1[2] = 500;
	leg_4[1] = 500; leg_4[2] = 450;
	leg_5[1] = 600; leg_5[2] = 450;
	Leg_Angle_Set0();                                           // 1,4,5�� �ٸ� �ø���

	leg_1[0] = 700;
	leg_4[0] = 650;
	leg_5[0] = 550;
	Leg_Angle_Set0();                                           // 1,4,5�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[0] = 1000;
	leg_3[0] = 900;
	leg_6[0] = 850;
	Leg_Angle_Set1();                                            // 2,3,6�� �ٸ� �ڷ�

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_1[1] = 800; leg_1[2] = 600;
	leg_4[1] = 700; leg_4[2] = 550;
	leg_5[1] = 800; leg_5[2] = 550;
	Leg_Angle_Set0();                                             // 1,4,5�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[1] = 600; leg_2[2] = 500;
	leg_3[1] = 700; leg_3[2] = 550;
	leg_6[1] = 600; leg_6[2] = 450;
	Leg_Angle_Set1();                                             // 2,3,6�� �ٸ� �ø���

	leg_2[0] = 850;
	leg_3[0] = 750;
	leg_6[0] = 650;
	Leg_Angle_Set1();                                            // 2,3,6�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_1[0] = 850;
	leg_4[0] = 750;
	leg_5[0] = 650;
	Leg_Angle_Set0();                                            // 1,4,5�� �ٸ� �ڷ�

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[1] = 800; leg_2[2] = 600;
	leg_3[1] = 900; leg_3[2] = 650;
	leg_6[1] = 800; leg_6[2] = 550;
	Leg_Angle_Set1();                                               // 2,3,6�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);
}
//--------------- 3�ٸ��� ������ ���� ----------------------------------------------------------------------------------

void Leg_test3_TurnLeft(){

	leg_1[1] = 600; leg_1[2] = 500;
	leg_4[1] = 500; leg_4[2] = 450;
	leg_5[1] = 600; leg_5[2] = 450;
	Leg_Angle_Set0();                         // 1,4,5�� �ٸ� �ø���

	leg_1[0] = 600;
	leg_4[0] = 900;
	leg_5[0] = 400;
	Leg_Angle_Set0();                         // 1,4,5�� �ٸ� ���� ȸ��

	leg_1[1] = 800; leg_1[2] = 600;
	leg_4[1] = 700; leg_4[2] = 550;
	leg_5[1] = 800; leg_5[2] = 550;
	Leg_Angle_Set0();                         // 1,4,5�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[1] = 600; leg_2[2] = 500;
	leg_3[1] = 700; leg_3[2] = 550;
	leg_6[1] = 600; leg_6[2] = 450;
	Leg_Angle_Set1();                         // 2,3,6�� �ٸ� �ø���

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_1[0] = 850;
	leg_4[0] = 750;
	leg_5[0] = 650;
	Leg_Angle_Set0();                        // 1,4,5�� �������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[1] = 800; leg_2[2] = 600;
	leg_3[1] = 900; leg_3[2] = 650;
	leg_6[1] = 800; leg_6[2] = 550;
	Leg_Angle_Set1();                        // 2,3,6�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);
}
//---------------- �������� ȸ�� ---------------------------------------------------------------------------------

void Leg_test4_TurnRight(){

	leg_2[1] = 600; leg_2[2] = 500;
	leg_3[1] = 700; leg_3[2] = 550;
	leg_6[1] = 600; leg_6[2] = 450;
	Leg_Angle_Set1();                                         // 2,3,6�� �ٸ� �ø���

	leg_2[0] = 600;
	leg_3[0] = 1000;
	leg_6[0] = 400;
	Leg_Angle_Set1();                                         // 2,3,6�� �ٸ� ������ ȸ��

	leg_2[1] = 800; leg_2[2] = 600;
	leg_3[1] = 900; leg_3[2] = 650;
	leg_6[1] = 800; leg_6[2] = 550;
	Leg_Angle_Set1();                                         // 2,3,6�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_1[1] = 600; leg_1[2] = 500;
	leg_4[1] = 500; leg_4[2] = 450;
	leg_5[1] = 600; leg_5[2] = 450;
	Leg_Angle_Set0();                                         // 1,4,5�� �ٸ� �ø���

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[0] = 850;
	leg_3[0] = 750;
	leg_6[0] = 650;
	Leg_Angle_Set1();                                        // 2,3,6�� �ٸ� �������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_1[1] = 800; leg_1[2] = 600;
	leg_4[1] = 700; leg_4[2] = 550;
	leg_5[1] = 800; leg_5[2] = 550;
	Leg_Angle_Set0();                                        // 1,4,5�� �ٸ� ������

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);
}
//------------------ ���������� ȸ�� -------------------------------------------------------------------------------

void Leg_test5_LegCheck(){

	leg_1[0] = 850; leg_1[1] = 600; leg_1[2] = 800;
	Leg_Angle_Set0();
	leg_4[0] = 750; leg_4[1] = 600; leg_4[2] = 800;
	Leg_Angle_Set0();
	leg_5[0] = 650; leg_5[1] = 600; leg_5[2] = 800;
	Leg_Angle_Set0();

	leg_1[0] = 850; leg_1[1] = 800; leg_1[2] = 600;
	leg_4[0] = 750; leg_4[1] = 700; leg_4[2] = 550;
	leg_5[0] = 650; leg_5[1] = 800; leg_5[2] = 550;
	Leg_Angle_Set0();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);

	leg_2[0] = 850; leg_2[1] = 600; leg_2[2] = 800;
	Leg_Angle_Set1();
	leg_3[0] = 750; leg_3[1] = 600; leg_3[2] = 800;
	Leg_Angle_Set1();
	leg_6[0] = 650; leg_6[1] = 600; leg_6[2] = 800;
	Leg_Angle_Set1();

	leg_2[0] = 850; leg_2[1] = 800; leg_2[2] = 600;
	leg_3[0] = 750; leg_3[1] = 900; leg_3[2] = 650;
	leg_6[0] = 650; leg_6[1] = 800; leg_6[2] = 550;
	Leg_Angle_Set1();

	part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(120);
}
//------------------ �ٸ� �Ѱ��� ���� �׽�Ʈ -------------------------------------------------------------------------------

void Leg_test6_Hand(){
		leg_4[0] = 600; leg_4[1] = 650;
		Leg_Angle_Set0();
		leg_4[1] = 700;
		Leg_Angle_Set0();
		part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);

		leg_3[0] = 600; leg_3[1] = 850;
		Leg_Angle_Set1();
		leg_3[1] = 900;
		Leg_Angle_Set1();
		part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);

		leg_1[0] = 850; leg_1[1] = 700; leg_1[2] = 600;
		leg_5[0] = 550; leg_5[1] = 300; leg_5[2] = 550;
		Leg_Angle_Set0();
		part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);

		leg_2[0] = 850; leg_2[1] = 700; leg_2[2] = 600;
		leg_6[0] = 550; leg_6[1] = 300;leg_6[2] = 550;
		Leg_Angle_Set1();
		part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);

		HAL_Delay(300);

		for(int a = 0;a<2;a++){
			leg_5[2] = 350;
			Leg_Angle_Set0();
			part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);
			leg_6[2] = 350;
			Leg_Angle_Set1();
			part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);
			leg_5[2] = 550;
			Leg_Angle_Set0();
			part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);
			leg_6[2] = 550;
			Leg_Angle_Set1();
			part_check = 2; Tim_Oc_It_Stop(); HAL_Delay(20);
		}
}
//------------------ �� �����ٰ� ��� -------------------------------------------------------------------------------

//------------------------------------<<< �ٸ� ���� �Լ� �� >>>------------------------------------------------

int main(void)
{
		HAL_Init();
		SystemClock_Config();
		ServoPin_Config();
		UART2_Config();
		UART3_B_Config();

		TIM2_Config(127,9999);  // ���������Ϸ�, Auto-Reload(default�� 9999)
		TIM3_Config(127,9999);  //�������� PWM ���ļ��� 50Hz�̴� ���������Ϸ� 127�� ����
		TIM4_Config(127,9999);

		HAL_Delay(100);
		HAL_UART_Transmit(&UartHandle, (uint8_t*)TxBuffer, TxBufferSize ,0xFFFF);

		while (1){
			HAL_UART_Receive_IT(&UartHandle_B,(uint8_t*)RxBuffer,1);
			HAL_Delay(10);

			if(Leg_Reset1_set == 1){
				Leg_Reset1();
				Leg_Reset1_set = 0;
			}
			else if(Leg_Reset2_set == 1){
				Leg_Reset2();
				Leg_Reset2_set = 0;
			}
			else if(Leg_test1_1LegMove_set == 1){
				Leg_test1_1LegMove();
				Leg_test1_1LegMove_set = 0;
			}
			else if(Leg_test2_TriLegMove_set == 1){
				Leg_test2_TriLegMove();
				Leg_test2_TriLegMove_set = 0;
			}
			else if(Leg_test3_TurnLeft_set == 1){
				Leg_test3_TurnLeft();
				Leg_test3_TurnLeft_set = 0;
			}
			else if(Leg_test4_TurnRight_set == 1){
				 Leg_test4_TurnRight();
				 Leg_test4_TurnRight_set = 0;
			}
			else if(Leg_test5_LegCheck_set == 1){
				 Leg_test5_LegCheck();
				 Leg_test5_LegCheck_set = 0;
			}
			else if(Leg_test6_Hand_set == 1){
				 Leg_test6_Hand();
				 Leg_test6_Hand_set = 0;
			}
		}
}

//------------------------------ Ÿ�̸� ���ͷ�Ʈ�� �̿��Ͽ� ���� PWM �����߻�(High) --------------------

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(part_check == 0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET );
	}
	else if(part_check == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_SET );
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_RESET );
	}
	else if(part_check == 2){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET );
	}
}
//------------------------------ Ÿ�̸� ��ȣ�� ä�ΰ� PartCheck�� ���Ͽ� �ش��ϴ� ���� PWM �����߻�(High) --------------------

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(part_check == 0){

		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, GPIO_PIN_RESET );
		}
		////////////////////
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET );
		}
		////////////////////
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET );
		}
	}
/* ---------------------------------------------------------------------------------------------------------*/

	else if(part_check == 1){

		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM4 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET );
		}
		/////////////////////
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET );
		}
		//////////////////////
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET );
		}
		if(htim->Instance == TIM2 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET );
		}
	}
	else if(part_check == 2){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, GPIO_PIN_RESET );
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_All, GPIO_PIN_RESET );
	}
}
//------------------------------ Ÿ�̸� ��ȣ�� ä�ΰ� PartCheck�� ���Ͽ� �ش��ϴ� ���� PWM �����߻�(Low) --------------------

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandler){}
// MCU���� ���� �����ʹ� �����Ƿ� ���� ����

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandler)
{
	// 300(��ü)/400(����)/500(��) ������ ���� ����
	/*Rx_Data_int1 = ((RxBuffer[0]-48)*100)+((RxBuffer[1]-48)*10)+(RxBuffer[2]-48);
	Rx_Data_int2 = ((RxBuffer[3]-48)*100)+((RxBuffer[4]-48)*10)+(RxBuffer[5]-48);
	Rx_Data_int3 = ((RxBuffer[6]-48)*100)+((RxBuffer[7]-48)*10)+(RxBuffer[8]-48);
	Rx_Data_int4 = RxBuffer[9]-48;

	HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n\r body angle : ", 20, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)RxBuffer, 3, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n\r knee angle : ", 20, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)(RxBuffer+3), 3, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n\r foot angle : ", 20, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)(RxBuffer+6), 3, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n\r part number : ", 20, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)(RxBuffer+9), 1, 2000);
	HAL_UART_Transmit(&UartHandle, (uint8_t*)"\n\r", 2, 2000);

	if(Rx_Data_int4 == 0){
		part_check = 0;
		TIM_OC_Config(TimHandle_2,Rx_Data_int1,1500-Rx_Data_int1,Rx_Data_int1);
		TIM_OC_Config(TimHandle_3,Rx_Data_int2,1300-Rx_Data_int2,Rx_Data_int2);
		TIM_OC_Config(TimHandle_4,Rx_Data_int3,1300-Rx_Data_int3,Rx_Data_int3);
	}
	if(Rx_Data_int4 == 1){
		part_check = 1;
		TIM_OC_Config(TimHandle_2,1500-Rx_Data_int1,1500-Rx_Data_int1,Rx_Data_int1);
		TIM_OC_Config(TimHandle_3,1300-Rx_Data_int2,1300-Rx_Data_int2,Rx_Data_int2);
		TIM_OC_Config(TimHandle_4,1300-Rx_Data_int3,1300-Rx_Data_int3,Rx_Data_int3);
	} PC�� �ø��� ������� �ٸ� ���� ����� ���  */


	//---------------------  if���� ���� �Է¹��� ������ ���ۿ� �ش��ϴ� �������� set��  ---------------------------------------
	if(RxBuffer[0] == 'f'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test2_TriLegMove_set = 1;
	}
	else if(RxBuffer[0] == 'b'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	}
	else if(RxBuffer[0] == 'l'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test3_TurnLeft_set = 1;
	}
	else if(RxBuffer[0] == 'r'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test4_TurnRight_set = 1;
	}
	else if(RxBuffer[0] == 's'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_Reset2_set = 1;
	}
	else if(RxBuffer[0] == '1'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_Reset1_set = 1;
	}
	else if(RxBuffer[0] == '2'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_Reset2_set = 1;
	}
	else if(RxBuffer[0] == '3'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test1_1LegMove_set = 1;
	}
	else if(RxBuffer[0] == '4'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test5_LegCheck_set = 1;
	}
	else if(RxBuffer[0] == '5'){
	HAL_UART_Transmit_IT(&UartHandle,(uint8_t*)RxBuffer,1);
	Leg_test6_Hand_set = 1;
	}
}

// -----------------  Sorce END ---------------------------

// ------------------ ( ���� ���� 12.11 ) -------- made by LJH------------

