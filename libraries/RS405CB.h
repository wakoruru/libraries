#pragma once

namespace stm32plus{
template<class USARTX>
	class RS405CB{
	uint16_t i=0;
	uint16_t TxData[12]={0};
	uint16_t checksum = 0;
	GpioPinRef REDE;
	USARTX usart;
	MicrosecondDelay Micro;
	public:
	RS405CB(const GpioPinRef& _rede):REDE(_rede),usart(115200){
		Micro.initialise();
		REDE.reset();
	}void Limit(uint16_t ID, uint16_t high, uint16_t low){
		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x00;
		TxData[4]=0x08;
		TxData[5]=0x04;
		TxData[6]=0x01;
		TxData[7]=(0x00FF &  high);
		TxData[8]=(0x00FF & (high>>8));
		TxData[9]=(0x00FF &  low);
		TxData[10]=(0x00FF& (low>>8));
		for(i=2;i<=10;i++){
			checksum = checksum^TxData[i];
		}
		TxData[11] = checksum;
		REDE.set();
		for(i=0;i<=11;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();
	}
	void ID(uint16_t ID, uint16_t data){
		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x00;
		TxData[4]=0x04;
		TxData[5]=0x01;
		TxData[6]=0x01;
		TxData[7]=data;
		for(i=2;i<=7;i++){
			checksum = checksum^TxData[i];
		}
		TxData[8] = checksum;
		REDE.set();
		for(i=0;i<=8;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();

		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x40;
		TxData[4]=0xFF;
		TxData[5]=0x00;
		TxData[6]=0x00;
		for(i=2;i<=6;i++){
			checksum = checksum^TxData[i];
		}
		TxData[7] = checksum;
		REDE.set();
		for(i=0;i<=7;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();
	}
	void Torque(uint16_t ID, uint16_t data){
		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x00;
		TxData[4]=0x24;
		TxData[5]=0x01;
		TxData[6]=0x01;
		TxData[7]=data;
		for(i=2;i<=7;i++){
			checksum = checksum^TxData[i];
		}
		TxData[8] = checksum;
		REDE.set();
		for(i=0;i<=8;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();
	}
	void Move(uint16_t ID, int16_t Angle, int16_t Speed){
		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x00;
		TxData[4]=0x1E;
		TxData[5]=0x04;
		TxData[6]=0x01;
		TxData[7]=(0x00FF &  Angle);
		TxData[8]=(0x00FF & (Angle>>8));
		TxData[9]=(0x00FF &  Speed);
		TxData[10]=(0x00FF& (Speed>>8));
		for(i=2;i<=10;i++){
			checksum = checksum^TxData[i];
		}
		TxData[11] = checksum;
		REDE.set();
		for(i=0;i<=11;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();
	}
	void Reset(uint16_t ID){
		checksum = 0;
		TxData[0]=0xFA;
		TxData[1]=0xAF;
		TxData[2]=ID;
		TxData[3]=0x10;
		TxData[4]=0xFF;
		TxData[5]=0xFF;
		TxData[6]=0x00;
		for(i=2;i<=6;i++){
			checksum = checksum^TxData[i];
		}
		TxData[7] = checksum;
		REDE.set();
		for(i=0;i<=7;i++){
			usart.send(TxData[i]);
		}
		Micro.delay(250);
		REDE.reset();
	}
	};

}
