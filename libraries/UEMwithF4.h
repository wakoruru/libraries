#pragma once
/* [UEM with F4Discovery] */
/* USB
 * ├>Usart2
 * ├RX>PD5
 * └TX>PD6
 */
/* PLSD √
 * ├>PD11
 * ├>PB12
 * ├>PB13
 * ├>PB14
 * ├>PB15
 */
/* servo √
 * ├>Usart3_remap1
 * ├TX>PD8
 * ├RX>PD9
 * └REDE>PD10
 */
/* QEI_HW
 * ├A>PA0 : Timer2
 * ├B>PA1 : Timer2
 * ├A>PA6 : Timer3
 * ├B>PA7 : Timer3
 * ├A>PC6 : Timer8
 * ├B>PC7 : Timer8
 * ├A>PE9 : Timer1
 * └B>PE11: Timer1
 */
/* mode switch
 * ├01>PA3
 * ├02>PA6
 * ├03>PA7
 * ├04>PC4
 * ├05>PC5
 * ├06>PB0
 * ├07>PB1
 * ├08>PB2
 * ├09>PE7
 * ├10>PE8
 * ├11>PE9
 * ├12>PE10
 * ├13>PE11
 * ├14>PE12
 * ├15>PE13
 * ├16>PE14
 * ├17>PE15
 * └18>PE10
 */
/* Parallel communication
 * ├>PD7
 * ├>PB3
 * ├>PB4
 * ├>PB5
 * ├>PB6
 * └>PB7
 */
/* LED_high　√
 * ├>PB8
 * ├>PB9
 * ├>PE0
 * └>PE1
 */
/* LED_low　√
 * ├>PE2
 * ├>PE3
 * ├>PE4
 * └>PE5
 */
/* Config --------------------------------------------------------------------*/
#include "config/stm32plus.h"
#include "config/timing.h"
#include "config/timer.h"
#include "config/gpio.h"
#include "config/usart.h"
/* Device --------------------------------------------------------------------*/
#include "libraries/RS405CB.h"
#include "libraries/encoder.h"
#include "libraries/PLSD.h"
#include "libraries/Mat_LED.h"
#include "libraries/Bluetooth.h"
/*----------------------------------------------------------------------------*/
/* defines -------------------------------------------------------------------*/
#define LEFT	uhm.btn[0]
#define DOWN	uhm.btn[1]
#define RIGHT	uhm.btn[2]
#define UP		uhm.btn[3]
#define START	uhm.btn[4]
#define R3		uhm.btn[5]
#define L3		uhm.btn[6]
#define SELECT	uhm.btn[7]
#define SHIKAKU	uhm.btn[8]
#define BATSU	uhm.btn[9]
#define MARU	uhm.btn[10]
#define SANKAKU	uhm.btn[11]
#define R1		uhm.btn[12]
#define L1		uhm.btn[13]
#define R2		uhm.btn[14]
#define L2		uhm.btn[15]
#define PS		uhm.btn[16]
using namespace stm32plus;
/* Variables -----------------------------------------------------------------*/
namespace stm32plus{
	struct Masking{
		const uint8_t mask1 = 0b00000001;
		const uint8_t mask2 = 0b00000010;
		const uint8_t mask3 = 0b00000100;
		const uint8_t mask4 = 0b00001000;
		const uint8_t mask5 = 0b00010000;
		const uint8_t mask6 = 0b00100000;
		const uint8_t mask7 = 0b01000000;
		const uint8_t mask8 = 0b10000000;
	};
/* usings */
	using enc_1 = Timer3<
			Timer3GpioFeature<TIMER_REMAP_PARTIAL2,TIM3_CH1_IN,TIM3_CH2_IN >,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising
			>
	>;
	using enc_2 = Timer2<
			Timer2GpioFeature<TIMER_REMAP_FULL,TIM2_CH1_IN,TIM2_CH2_IN>,
			TimerEncoderFeature<
			EncoderCounterEdge::Inputs1And2,
			EncoderPolarity::Rising,
			EncoderPolarity::Rising
			>
	>;
	using Enc1 = myEnc<enc_1>;
	using Enc2 = myEnc<enc_2>;
	using servo_USART = Usart3_Remap1<>;
	using rs405cb = RS405CB<servo_USART>;
	using plsd = PLSD<Exti11>;
	typedef Usart2InterruptFeature bt_interrupt;
#ifdef bluetooth
	using bt_usart = Usart2_Remap1<Usart2InterruptFeature>;
	using BT1 = Bluetooth<bt_usart,bt_interrupt>;
#endif
/*class Encoders*/
	class Encoders:private Enc1,private Enc2{
	public:
		Encoders():Enc1(),Enc2(){
			now1=0;now2=0;
			pas1=0;pas2=0;
		}
		~Encoders(){}
		inline uint32_t getCounter1()const{
			return Enc1::getCounter();
		}
		inline uint32_t getCounter2()const{
			return Enc2::getCounter();
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
	private:
		uint32_t now1,now2;
		uint32_t pas1,pas2;
		uint32_t dif1,dif2;
	};
/*class UHM*/
	class UHM{
		/*line sensor*/
		GpioA<DefaultDigitalInputFeature<3,6,7>> sensa;
		GpioB<DefaultDigitalInputFeature<0,1,2,3,4,5,6,7,10>> sensb;
		GpioC<DefaultDigitalInputFeature<4,5>> sensc;
		GpioD<DefaultDigitalInputFeature<7>> sensd;
		GpioE<DefaultDigitalInputFeature<7,8,9,10,11,12,13,14,15>> sense;
		/*matrix led*/
		GpioB<DefaultDigitalOutputFeature<8,9>> matb;
		GpioE<DefaultDigitalOutputFeature<0,1,2,3,4,5>> mate;
		/*servo*/
		GpioD<DefaultDigitalOutputFeature<10>> rede;
		/*PLSD*/
		GpioD<DefaultDigitalInputFeature<11>> plsd_trigger;
		GpioB<DefaultDigitalInputFeature<12,13,14,15>> plsd_state;
	public:
		rs405cb servo;
		Encoders encoders;
		Mat_LED matrix;
		plsd mode;
#ifdef bluetooth
		int btn[17];
		Masking Mask;
		BT1 bt1;
#endif
		UHM():
			servo(rede[10]),
			encoders(),
			matrix(matb[8],matb[9],mate[0],mate[1],mate[2],mate[3],mate[4],mate[5]),
			mode(plsd_trigger[11],plsd_state[12],plsd_state[13],plsd_state[14],plsd_state[15])
#ifdef bluetooth
			,bt1()
#endif
		{
		}
	};

};
