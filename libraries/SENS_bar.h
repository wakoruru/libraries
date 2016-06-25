#pragma once
namespace stm32plus{
	class SENS_bar{
		GpioPinRef pin1,pin2,pin3,pin4,pin5,pin6,pin7,pin8;
		uint8_t pin_num,state;
	public:

		SENS_bar(const GpioPinRef& _Pin1,
				 const GpioPinRef& _Pin2,
				 const GpioPinRef& _Pin3,
				 const GpioPinRef& _Pin4,
				 const GpioPinRef& _Pin5,
				 const GpioPinRef& _Pin6,
				 const GpioPinRef& _Pin7,
				 const GpioPinRef& _Pin8):
			pin1(_Pin1),
			pin2(_Pin2),
			pin3(_Pin3),
			pin4(_Pin4),
			pin5(_Pin5),
			pin6(_Pin6),
			pin7(_Pin7),
			pin8(_Pin8){
			state=0;
		}
		uint8_t input_pin( bool logic){
			state=0;
			state	= (pin1.read() == logic)<<0
					| (pin2.read() == logic)<<1
					| (pin3.read() == logic)<<2
					| (pin4.read() == logic)<<3
					| (pin5.read() == logic)<<4
					| (pin6.read() == logic)<<5
					| (pin7.read() == logic)<<6
					| (pin8.read() == logic)<<7;
			return state;
		}

	};
}
