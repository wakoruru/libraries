#pragma once

#include "config/stm32plus.h"
#include "config/timer.h"

namespace stm32plus{
	template<class TTIM,class TCH1,class TCH2>
	class Motor_H:public TTIM{
	public:
		enum{
			MAX_COMPARE = 500
		};
		Motor_H():TTIM(){
			this->setTimeBaseByFrequency(10000000, MAX_COMPARE-1);
			TCH1::initCompareForPwmOutput();
			TCH2::initCompareForPwmOutput();
			this->enablePeripheral();
		}
		void setOutput(float duty){
			if(duty > 1.0f){
				duty = 1.0f;
			}
			else if(duty < -1.0f){
				duty = -1.0f;
			}
			duty = duty*0.95;

			int16_t value = (int16_t)(duty * MAX_COMPARE);
			  if(value>0){
				  TCH1::setCompare(0);
				  TCH2::setCompare(value);
			  } else {
				  TCH1::setCompare(-value);
				  TCH2::setCompare(0);
			  }
		}
		inline void stop(){
			setOutput(0);
		}
	private:
	};
}
