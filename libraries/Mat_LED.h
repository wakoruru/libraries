#pragma once

namespace stm32plus{
	class Mat_LED{
	public:
		Mat_LED( const GpioPinRef& _Pin01, const GpioPinRef& _Pin02, const GpioPinRef& _Pin03, const GpioPinRef& _Pin04,
				 const GpioPinRef& _Pin11, const GpioPinRef& _Pin12, const GpioPinRef& _Pin13, const GpioPinRef& _Pin14
				):Pin01(_Pin01),Pin02(_Pin02),Pin03(_Pin03),Pin04(_Pin04),
				  Pin11(_Pin11),Pin12(_Pin12),Pin13(_Pin13),Pin14(_Pin14){
			Milli.initialise();
		}
		void led_matrix_fullon(){
			Pin01.set();Pin02.set();
			Pin03.set();Pin04.set();
			Pin11.set();Pin12.set();
			Pin13.set();Pin14.set();
		}
		void led_matrix_fulloff(){
			Pin01.reset();Pin02.reset();
			Pin03.reset();Pin04.reset();
			Pin11.reset();Pin12.reset();
			Pin13.reset();Pin14.reset();
		}
		void led_matrix_set(uint16_t num){
			// 行
			if((num & 0b0000000000001111) != 0) Pin01.set();
			else Pin01.reset();
			if((num & 0b0000000011110000) != 0) Pin02.set();
			else Pin02.reset();
			if((num & 0b0000111100000000) != 0) Pin03.set();
			else Pin03.reset();
			if((num & 0b1111000000000000) != 0) Pin04.set();
			else Pin04.reset();
			// 列
			if((num & 0b0001000100010001) != 0) Pin11.set();
			else Pin11.reset();
			if((num & 0b0010001000100010) != 0) Pin12.set();
			else Pin12.reset();
			if((num & 0b0100010001000100) != 0) Pin13.set();
			else Pin13.reset();
			if((num & 0b1000100010001000) != 0) Pin14.set();
			else Pin14.reset();
		}
	private:
		GpioPinRef Pin01,Pin02,Pin03,Pin04,Pin11,Pin12,Pin13,Pin14;
		MillisecondTimer Milli;
	};
}
