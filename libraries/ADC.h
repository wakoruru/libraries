#pragma once
#include "config/adc.h"

namespace stm32plus{
template<class TADC,class TDMA,class TIF>
	class ADC_utility{
	private:
	volatile bool _ready;
	TADC adc;
	TDMA dma;
	public:
	ADC_utility(){}
	void init(int16_t readBuffer[],int num){
		_ready = false;
		dma.DmaInterruptEventSender.insertSubscriber(DmaInterruptEventSourceSlot::bind(this,&ADC_utility::onComplete));
		dma.enableInterrupts(TIF::COMPLETE);
		dma.beginRead(readBuffer,num+1);
	}
	void adc_Read(){
        adc.startRegularConversion();
        while(!_ready);
        _ready=false;
	}
	void onComplete(DmaEventType det) {
	  if(det==DmaEventType::EVENT_COMPLETE)
		_ready=true;
	}
	};
}
