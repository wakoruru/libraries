#pragma once
/* [UHM with F4Discovery NMD] */
/* NMD_swithch_IO
 * ├>PB14
 * ├>PB13
 * ├>PB15
 * ├>PD11
 * ├>PA8
 * ├>PC8
 * ├>PC9
 * └>PC6
 */
/* NMD_switch_PWM
 * ├>PE9  : Timer1
 * ├>PE11 : Timer1
 * ├>PE14 : Timer1
 * └>PE13 : Timer1
 */
/* PSD
 * ├>PB0
 * ├>PC1
 * ├>PC2
 * ├>PA1
 * ├>PC4
 * └>PC5
 */
/* USB
 * ├>Usart2
 * ├RX>PA3
 * └TX>PA2
 */
/* Parallel communication
 * ├>PC13
 * ├>PE6  pole:out
 * ├>PE5  pole:open
 * ├>PE4  fan:↑
 * ├>PE3  fan:↓
 * └>PB8  pole:in
 */
/* QEI_HW
 * ├A>PB7 : Timer4
 * ├B>PB6 : Timer4
 * ├A>PB5 : Timer3
 * ├B>PB4 : Timer3
 * ├A>PB3 : Timer2
 * ├B>PA15: Timer2
 * ├A>PA0 : Timer5
 * └B>PA1 : Timer5
 */
/* mode switch
 * ├>PB12
 * ├>PB11
 * ├>PE15
 * ├>PE12
 * ├>PE10
 * ├>PE8
 * ├>PE7
 * ├>PB2
 * ├>PB1
 * ├>PD7
 * ├>PD3
 * └>PD1
 */
/* servo
 * ├>Usart3_remap1
 * ├TX>PD8
 * ├RX>PD9
 * └REDE>PD10
 */
/* buzzer
 * └>PD0
 */
/* Config --------------------------------------------------------------------*/
#include "config/stm32plus.h"
#include "config/timing.h"
#include "config/timer.h"
#include "config/gpio.h"
#include "config/usart.h"
/* board */
#include "board/f4discovery.h"
/* Device --------------------------------------------------------------------*/
#include "devices/led.h"
#include "devices/button.h"
#include "devices/mpu6050.h"
/* mecha_lib -----------------------------------------------------------------*/
#include "./Motor_drive.h"
#include "./RS405CB.h"
#include "./buzzer.h"
#include "./encoder.h"
#include "./IO_SENS.h"
#include "./Haga_cir.h"
/*----------------------------------------------------------------------------*/
using namespace stm32plus;/* Variables -----------------------------------------------------------------*/
struct ps3{
	int UP;
	int DOWN;
	int RIGHT;
	int LEFT;
	int MARU;
	int BATSU;
	int SANKAKU;
	int SHIKAKU;
	int R1;
	int R2;
	int R3;
	int L1;
	int L2;
	int L3;
	int SELECT;
	int START;
	int ANALOG;
	float X1;
	float Y1;
	float X2;
	float Y2;
};
struct omn{
	float rate;
	float theta;
	bool flag[8];
};
namespace stm32plus{
/* usings */
	using enc_1 = Timer4<
			Timer4GpioFeature<TIMER_REMAP_NONE,TIM4_CH1_IN,TIM4_CH2_IN>,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising>
	>;
	using enc_2 = Timer3<
			Timer3GpioFeature<TIMER_REMAP_PARTIAL2,TIM3_CH1_IN,TIM3_CH2_IN >,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising
			>
	>;
	using enc_3 = Timer2<
			Timer2GpioFeature<TIMER_REMAP_FULL,TIM2_CH1_IN,TIM2_CH2_IN>,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising
			>
	>;
	using enc_4 = Timer5<
			Timer5GpioFeature<TIMER_REMAP_NONE,TIM5_CH1_IN,TIM5_CH2_IN>,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising
			>
	>;
	using Enc1 = myEnc<enc_1>;
	using Enc2 = myEnc<enc_2>;
	using Enc3 = myEnc<enc_3>;
	using Enc4 = myEnc<enc_4>;
	using Timer1Pwm = Timer1<
			Timer1InternalClockFeature,
			TimerChannel1Feature<>,	TimerChannel2Feature<>,	TimerChannel3Feature<>,	TimerChannel4Feature<>,
			Timer1GpioFeature<
			TIMER_REMAP_FULL,
			TIM1_CH1_OUT,TIM1_CH2_OUT,TIM1_CH3_OUT,TIM1_CH4_OUT>
	>;
	using Motor1_CH = TimerChannel1Feature<>;
	using Motor2_CH = TimerChannel2Feature<>;
	using Motor3_CH = TimerChannel4Feature<>;
	using Motor4_CH = TimerChannel3Feature<>;
	using Motor1 = Motor_drive<Timer1Pwm,Motor1_CH>;
	using Motor2 = Motor_drive<Timer1Pwm,Motor2_CH>;
	using Motor3 = Motor_drive<Timer1Pwm,Motor3_CH>;
	using Motor4 = Motor_drive<Timer1Pwm,Motor4_CH>;
	using servo_USART = Usart3_Remap1<>;
	using rs405cb = RS405CB<servo_USART>;
/*class Encoders*/
	class Encoders:private Enc1,private Enc2, private Enc3, private Enc4{
	public:
		Encoders():Enc1(),Enc2(),Enc3(),Enc4(){
			now1=0;now2=0;now3=0;now4=0;
			pas1=0;pas2=0;pas3=0;pas4=0;
		}
		~Encoders(){}
		inline uint32_t getCounter1()const{
			return Enc1::getCounter();
		}
		inline uint32_t getCounter2()const{
			return Enc2::getCounter();
		}
		inline uint32_t getCounter3()const{
			return Enc3::getCounter();
		}
		inline uint32_t getCounter4()const{
			return Enc4::getCounter();
		}
		inline uint32_t getSpeed1(){
			pas1 = now1;
			now1 = getCounter1();
			dif1 = now1-pas1;
			return dif1;
		}
		inline uint32_t getSpeed2(){
			pas2 = now2;
			now2 = getCounter2();
			dif2 = now2-pas2;
			return dif2;
		}
		inline uint32_t getSpeed3(){
			pas3 = now3;
			now3 = getCounter3();
			dif3 = now3-pas3;
			return dif3;
		}
		inline uint32_t getSpeed4(){
			pas4 = now4;
			now4 = getCounter4();
			dif4 = now4-pas4;
			return dif4;
		}
	private:
		uint32_t now1,now2,now3,now4;
		uint32_t pas1,pas2,pas3,pas4;
		uint32_t dif1,dif2,dif3,dif4;
	};
/*class UHM*/
	class UHM{
		/**/
		GpioD<DefaultDigitalOutputFeature<12,13,14,15>> pdleds;
		/**/
		GpioA<DefaultDigitalOutputFeature<8>> pamds;
		GpioB<DefaultDigitalOutputFeature<11,13,14,15>> pbmds;
		GpioC<DefaultDigitalOutputFeature<6,8,9>> pcmds;
		GpioD<DefaultDigitalOutputFeature<11>> pdmds;
		/**/
		GpioD<DefaultDigitalOutputFeature<0>> buz;
		/*rede*/
		GpioD<DefaultDigitalOutputFeature<10>> rede;
		/*mode*/
		GpioB<DefaultDigitalInputFeature<1,2,11,12>> modeb;
		GpioD<DefaultDigitalInputFeature<1,3,7>> moded;
		GpioE<DefaultDigitalInputFeature<7,8,10,12,15>> modee;
		/*cir*/
		GpioB<DefaultDigitalInputFeature<8>> cirb;
		GpioC<DefaultDigitalOutputFeature<13>> circ;
		GpioE<DefaultDigitalOutputFeature<3,4,5,6>> cire;
	public:
		bool pole_state=false,pole_save=true;
		uint8_t pole_count=0;
		Led led1,led2,led3,led4;
		Motor1 motor1;
		Motor2 motor2;
		Motor3 motor3;
		Motor4 motor4;
		buzzer buzz;
		rs405cb servo;
		IO_SENS mode1,mode2,mode3,mode4;
		Haga_cir communication;
		Encoders encoders;
		UHM():
			led1(pdleds[13]),
			led2(pdleds[12]),
			led3(pdleds[14]),
			led4(pdleds[15]),
			motor1(pbmds[14],pbmds[13]),
			motor2(pbmds[15],pdmds[11]),
			motor3(pamds[8],pcmds[8]),
			motor4(pcmds[9],pcmds[6]),
			buzz(buz[0]),
			servo(rede[10]),
			mode1(modeb[12],modeb[11],modee[15]),
			mode2(modee[12],modee[10],modee[8]),
			mode3(modee[7],modeb[2],modeb[1]),
			mode4(moded[7],moded[3],moded[1]),
			communication(cire[5],cire[4],cire[3],cire[6],cirb[8],circ[13]),
			encoders()
		{
			led1.Off();
			led2.Off();
			led3.Off();
			led4.Off();
			motor1.Stop();
			motor2.Stop();
			motor3.Stop();
			motor4.Stop();
		}
	};

};
