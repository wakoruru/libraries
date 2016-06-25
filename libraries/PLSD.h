#pragma once

#include "config/button.h"
#include "config/exti.h"

namespace stm32plus{
template<class TEXT>
class PLSD{
private:
	TEXT exti;
	GpioPinRef pin1,pin2,pin3,pin4;
	uint8_t data;
public:
	PLSD(const Gpio& extpin,const GpioPinRef& _pin1,const GpioPinRef& _pin2,const GpioPinRef& _pin3,const GpioPinRef& _pin4)
	:exti(EXTI_Mode_Interrupt,EXTI_Trigger_Falling,extpin),pin1(_pin1),pin2(_pin2),pin3(_pin3),pin4(_pin4)
	{
		data=0;
		exti.ExtiInterruptEventSender.insertSubscriber(ExtiInterruptEventSourceSlot::bind(this,&PLSD::onInterrupt));
	}
	uint8_t datum(){
		return data;
	}
	void onInterrupt(uint8_t){
		data 	= (pin1.read() == 1)<<0
				| (pin2.read() == 1)<<1
				| (pin3.read() == 1)<<2
				| (pin4.read() == 1)<<3;
	}

};
}
