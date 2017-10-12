/*****************************************************************************
*
* 
*
* File              : BleSerialDevice.hpp
* Compiler          : Dev-C++ 4.9.8.0 - http://bloodshed.net/dev/
* Revision          : $Revision: 1164 $
* Date              : $Date: 2017-08-16 00:00:00 +0200 (on, 02 aug 2006) $
* Updated by        : $Author: dgoslin $
*
* Support mail      : 
*
* Target platform   : Win32
*
* AppNote           : AVR911 - AVR Open-source Programmer
*
* Description       : A class providing serial communication through a paired Ble device.
*                     This class is derived from the CommChannel abstract class.
*
*
****************************************************************************/
#ifndef BLESERIALDEVICE_HPP
#define BLESERIALDEVICE_HPP

#include "BleSerialDeviceDescriptor.hpp"
#include "CommChannel.hpp"
#include "ErrorMsg.hpp"

using namespace std;

class BleSerialDevice : public CommChannel
{
	private:

		BleSerialDeviceDescriptor bleSerialDeviceDescriptor;

	public:
		BleSerialDevice(BleSerialDeviceDescriptor _bleSerialDeviceDescriptor);

		~BleSerialDevice();

		// Open the communication channel.
		virtual void openChannel();

		// Close the communication channel.
		virtual void closeChannel();

		// Transmit a single byte.
		virtual void sendByte(long data);

		// Receive a single byte.
		virtual long getByte();

		// Flush the transmit buffer.
		virtual void flushTX();

		// Flush the receive buffer.
		virtual void flushRX();

		// Transmit multiple bytes.
		virtual void sendMultiple(unsigned char * data, long bufsize);
};
#endif
