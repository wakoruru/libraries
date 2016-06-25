#pragma once

namespace stm32plus{
class PID{
private:
public:
	PID(){}
	float PID_calc(float Kp=0.5,float Ki=0.5,float Kd=0.5,int wg,int wn,int wb,int T){
		float PWM=0;
		float Vi = Vi + (wg -wn)*T;
		PWM = Kp*(wg-wn)+Ki*Vi+Kd*((wn-wb)/T);
	}
};
}
