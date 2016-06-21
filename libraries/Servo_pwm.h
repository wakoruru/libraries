#pragma once

#include "config/stm32plus.h"
#include "config/timer.h"

namespace stm32plus{
	template<class TTIM>
	class Servo_pwm{
	private:
		TTIM timer;
	public:
		enum{
			FREQ = 100000,
			MAX_COMPARE = 2000
		};
		Servo_pwm(){
			timer.setTimeBaseByFrequency(FREQ, MAX_COMPARE-1);
			timer.initCompareForPwmOutput();
			timer.enablePeripheral();
		}
		void setDuty(int duty){
			timer.setDutyCycle(duty);
		}
	};
}
