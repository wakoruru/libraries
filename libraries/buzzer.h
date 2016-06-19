#pragma once

namespace stm32plus{
	class buzzer{
	public:
		bool buzz_state;
		buzzer(const GpioPinRef& _Pin1):Pin1(_Pin1){
			Milli.initialise();
			buzz_state = false;
		}
		void pat_01(){
			buz_on();
			Milli.delay(50);
			buz_off();
			Milli.delay(50);
			buz_on();
			Milli.delay(50);
			buz_off();
			Milli.delay(50);
			buz_on();
			Milli.delay(200);
			buz_off();
		}
		void pat_02(){
			buz_on();
			Milli.delay(200);
			buz_off();
			Milli.delay(200);
			buz_on();
			Milli.delay(200);
			buz_off();
			Milli.delay(200);
			buz_on();
			Milli.delay(200);
			buz_off();
		}
	private:
		GpioPinRef Pin1;
		MillisecondTimer Milli;
		void buz_on(){
			Pin1.set();
			buzz_state = true;
		}
		void buz_off(){
			Pin1.reset();
			buzz_state = false;
		}
		void buz_toggle(){
			if(buzz_state){
				buz_off();
			}
			else{
				buz_on();
			}
		}
	};
}
