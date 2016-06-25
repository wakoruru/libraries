#pragma once
#include "config/timer.h"
#include "devices/mpu6050.h"
#include "math.h"

namespace stm32plus{
template<class TTIM,class TI2C,int TAD0>
class MPU6050_calc:public MPU6050<TI2C,TAD0>{
private:
	TTIM timer;
	float angle_data[3];
	enum{
		coef = 0.9,
		freq = 100000,
		count = 100,
	};
public:
	MPU6050_calc():MPU6050<TI2C,TAD0>(I2C::Parameters(1000000)){
		angle_data[0]=angle_data[1]=angle_data[2]=0;
	}
	void mpu_test(){
		MPU6050<TI2C,TAD0>::setTimeout(20);
		while(!MPU6050<TI2C,TAD0>::test());
		MPU6050<TI2C,TAD0>::setup();
	}
	void calc_start(){
		timer.TimerInterruptEventSender.insertSubscriber(TimerInterruptEventSourceSlot::bind(this,&MPU6050_calc::onInterrupt));
		timer.setTimeBaseByFrequency(freq,count-1,TIM_CounterMode_CenterAligned3);
		timer.clearPendingInterruptsFlag(TIM_IT_Update);
		timer.enableInterrupts(TIM_IT_Update);
		timer.enablePeripheral();
	}
	void getAngle(float *val){
		val[0]=angle_data[0];
		val[1]=angle_data[1];
		val[2]=angle_data[2];
	}
	void onInterrupt(TimerEventType tet,uint8_t /* timerNumber */) {
		if(tet==TimerEventType::EVENT_UPDATE) {
			float acc_theta=0;
			acc_theta = atan2(MPU6050<TI2C,TAD0>::readAccX(),MPU6050<TI2C,TAD0>::readAccZ());
			angle_data[0] = coef*(angle_data[0]+MPU6050<TI2C,TAD0>::readGyrX()*(count/freq)) + (1-coef)*acc_theta;

			acc_theta = atan2(MPU6050<TI2C,TAD0>::readAccY(),MPU6050<TI2C,TAD0>::readAccZ());
			angle_data[1] = coef*(angle_data[1]+MPU6050<TI2C,TAD0>::readGyrY()*(count/freq)) + (1-coef)*acc_theta;

			angle_data[2] = (angle_data[2]+MPU6050<TI2C,TAD0>::readGyrZ()*(count/freq));
		}
	}
};
}
