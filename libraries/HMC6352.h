#pragma once

namespace stm32plus {

	template<class TI2C>
	class HMC6352 : public TI2C{
		MillisecondTimer Micro;
	public:
		enum{
			SLAVE_ADDRESS = (0x21 << 1)
		};
		HMC6352(typename I2C::Parameters params):TI2C(params){
			this->setSlaveAddress(SLAVE_ADDRESS);
			this->enablePeripheral();
			Micro.initialise();
			operationMode_ = getOpMode();
		}
		inline int16_t sample() {
			uint8_t tx[1];
			uint8_t rx[2];
		    if (operationMode_ == 0x00 || operationMode_ == 0x01) {
		        tx[0] = 0x41;
		        TI2C::writeBytes((SLAVE_ADDRESS << 1) & 0xFE, tx, 1);
		        Micro.delay(10);
		    }
		    TI2C::readBytes((SLAVE_ADDRESS << 1) | 0x01, rx, 2);
		    Micro.delay(10);
		    return (((int)rx[0] << 8) | (int)rx[1]);
		}
		int16_t getOpMode(){
			int16_t response=0;
			response = read(0x67,0x74);
			return (response&0x00000003);
		}
		void setOpMode(int16_t mode, int16_t periodicSetReset, int16_t measurementRate) {

		    char opModeByte = mode;

		    if (periodicSetReset == 1) {
		        opModeByte |= 0x10;
		    }

		    if (measurementRate == 5) {
		        opModeByte |= 0x20;
		    } else if (measurementRate == 10) {
		        opModeByte |= 0x40;
		    } else if (measurementRate == 20) {
		        opModeByte |= 0x60;
		    }

		    write(0x47, 0x74, opModeByte);
		    write(0x77, 0x08, opModeByte);

		    operationMode_ = mode;

		}
		int16_t read(int EepromOrRam, int address){
			uint8_t tx[2];
			uint8_t rx[1];

			tx[0] = EepromOrRam;
			tx[1] = address;

			TI2C::writeBytes(SLAVE_ADDRESS&0xFE,tx,2);
			Micro.delay(10);
			TI2C::readBytes(SLAVE_ADDRESS|0x01,rx,1);
			Micro.delay(10);
			return (rx[0]);
		}
		void write(uint8_t EepromOrRam, uint8_t address, uint8_t data) {

		    uint8_t tx[3];

		    tx[0] = EepromOrRam;
		    tx[1] = address;
		    tx[2] = data;

		    TI2C::writeBytes(SLAVE_ADDRESS&0xFE, tx, 3);
		    Micro.delay(10);

		}

	private:
		int16_t operationMode_;

	};

}
