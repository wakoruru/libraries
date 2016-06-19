#pragma once
namespace stm32plus{
	class IO_SENS{
		GpioPinRef pin1,pin2,pin3,pin4,pin5;
		uint8_t pin_num,state;
	public:
		IO_SENS(){
			pin_num = 0;
			state=0;
		}
		IO_SENS(const GpioPinRef& _Pin1):pin1(_Pin1){
			pin_num = 1;
			state=0;
		}
		IO_SENS(const GpioPinRef& _Pin1,const GpioPinRef& _Pin2):pin1(_Pin1),pin2(_Pin2){
			pin_num = 2;
			state=0;
		}
		IO_SENS(const GpioPinRef& _Pin1,const GpioPinRef& _Pin2,const GpioPinRef& _Pin3):pin1(_Pin1),pin2(_Pin2),pin3(_Pin3){
			pin_num = 3;
			state=0;
		}
		IO_SENS(const GpioPinRef& _Pin1,const GpioPinRef& _Pin2,const GpioPinRef& _Pin3,const GpioPinRef& _Pin4):pin1(_Pin1),pin2(_Pin2),pin3(_Pin3),pin4(_Pin4){
			pin_num = 4;
			state=0;
		}
		IO_SENS(const GpioPinRef& _Pin1,const GpioPinRef& _Pin2,const GpioPinRef& _Pin3,const GpioPinRef& _Pin4,const GpioPinRef& _Pin5):pin1(_Pin1),pin2(_Pin2),pin3(_Pin3),pin4(_Pin4),pin5(_Pin5){
			pin_num = 5;
			state=0;
		}
		uint8_t input_pin( bool logic){

			if(pin_num == 1){
				state=0;
				state = (pin1.read() == logic)<<0;
				return state;
			}
			else if(pin_num == 2){
				state=0;
				state	= (pin1.read() == logic)<<0
						| (pin2.read() == logic)<<1;
				return state;
			}
			else if(pin_num == 3){
				state=0;
				state	= (pin1.read() == logic)<<0
						| (pin2.read() == logic)<<1
						| (pin3.read() == logic)<<2;
				return state;
			}
			else if(pin_num == 4){
				state=0;
				state	= (pin1.read() == logic)<<0
						| (pin2.read() == logic)<<1
						| (pin3.read() == logic)<<2
						| (pin4.read() == logic)<<3;
				return state;
			}
			else if(pin_num == 5){
				state=0;
				state	= (pin1.read() == logic)<<0
						| (pin2.read() == logic)<<1
						| (pin3.read() == logic)<<2
						| (pin4.read() == logic)<<3
						| (pin5.read() == logic)<<4;
				return state;
			}
			else{
				state=0;
				return state;
			}
		}

	};
}
