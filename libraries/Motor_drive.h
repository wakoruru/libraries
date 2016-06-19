#pragma once

/* For Relay And Pwm Motor Driver*/

#include "config/stm32plus.h"
#include "config/timer.h"

namespace stm32plus{
	template<class TTIM,class TCH>
	class Motor_drive:public TTIM{
	public:
		GpioPinRef pin1,pin2;
		bool motor_rot=false;
		enum{
			Freq = 5000
		};
		Motor_drive(const GpioPinRef& _pin1,const GpioPinRef& _pin2):TTIM(),pin1(_pin1),pin2(_pin2){
			this->setTimeBaseByFrequency(10000000,Freq-1);
			TCH::initCompareForPwmOutput();
			this->enablePeripheral();
		}
		void Setpwm(float duty){
			//duty = duty / 0.70710678;
			if(duty > 1.0f){
				duty = 1.0f;

			}
			else if(duty < 0.0f){
					duty=duty*-1.0f;
			}
			duty = 1.0-duty;
			TCH::setCompare(duty*Freq);
		}
		void Forward(){
			motor_rot=true;
			pin1.set();
			pin2.reset();
		}
		void Backward(){
			motor_rot=true;
			pin1.reset();
			pin2.set();
		}
		void Stop(){
			motor_rot=false;
			Setpwm(0);
			pin1.reset();
			pin2.reset();
		}
	private:
	};
}
