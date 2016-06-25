#pragma once
#include "config/timer.h"

namespace stm32plus{
template<class TTIM>
class Tim_int{
private:
	TTIM timer;
public:
	Tim_int(uint16_t freq,uint16_t count){
		timer.TimerInterruptEventSender.insertSubscriber(TimerInterruptEventSourceSlot::bind(this,&Tim_int::onInterrupt));
		timer.setTimeBaseByFrequency(freq,count,TIM_CounterMode_CenterAligned3);
		timer.clearPendingInterruptsFlag(TIM_IT_Update);
		timer.enableInterrupts(TIM_IT_Update);
	}
	void Tim_start(){
		timer.enablePeripheral();
	}
	void onInterrupt(TimerEventType tet,uint8_t /* timerNumber */) {
		if(tet==TimerEventType::EVENT_UPDATE) {
		}
	}
};
}
