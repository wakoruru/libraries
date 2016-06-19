#pragma once

namespace stm32plus{
template<class TimQE>
class myEnc:public TimQE{
public:
	myEnc():TimQE(){
		TimQE::initialiseEncoderCounter(65535);
		TimQE::setCounter(0);
		TimQE::enablePeripheral();
		speed=0;
		position=0;
	}
	~myEnc(){}
	inline void captureSpeed(){
		uint16_t nowCounter = TimQE::getCounter();
		int32_t diff = nowCounter - prevCounter;
		prevCounter = nowCounter;
		if(abs(diff)>32767){
			if(diff<0){
				speed = diff + 65536;
			}else{
				speed = diff - 65536;
			}
		}else{
			speed = diff;
		}
	}
	int16_t getSpeed() const{
		return speed;
	}
	inline void updatePosition(){
		captureSpeed();
		position += getSpeed();
	}
	inline void setPosition(int32_t _position){
		uint16_t nowCounter = TimQE::getCounter();
		prevCounter = nowCounter;
		position = _position;
	}
	int32_t getPosition() const{
		return position;
	}
private:
	uint16_t prevCounter;
	int16_t speed;
	int32_t position;
};
}
