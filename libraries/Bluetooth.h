#pragma once

#include "config/stm32plus.h"
#include "config/usart.h"

namespace stm32plus{
template<class USARTX,class INT>
	class Bluetooth{
	private:
	uint8_t _index;
	typedef INT Interrupts;
	USARTX usart;
	Nvic _Nvic;
	public:
	uint8_t _buffer[5];
	Bluetooth():usart(57600){
		_buffer[0] = 0;_buffer[1] = 0;_buffer[2] = 0;_buffer[3] = 0;_buffer[4] = 0;
		_Nvic.initialise();
	}
	//初期化
	void init(){
		usart.UsartInterruptEventSender.insertSubscriber(UsartInterruptEventSourceSlot::bind(this,&Bluetooth::onInterrupt));
		usart.enableInterrupts(Interrupts::RECEIVE);
		_index = 0;
	}
	//割り込み処理
	void onInterrupt(UsartEventType uet){
		if(uet==UsartEventType::EVENT_RECEIVE){
			uint8_t _data;
			_data = usart.receive();
			if(_data == '$'){
				_index = 1;
				return;
			}
			if(_index != 0){
				_buffer[_index-1] = _data;
				_index++;
				if(_index == 5){
					_index = 0;
				}
				return;
			}
		}
	}
};
}
