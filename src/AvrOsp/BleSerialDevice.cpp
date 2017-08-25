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

#include "BleSerialDevice.hpp"

BleSerialDevice::BleSerialDevice(BleSerialDeviceDescriptor _bleSerialDeviceDescriptor)
{
	bleSerialDeviceDescriptor = _bleSerialDeviceDescriptor;

	//pBleDevice = new BleDevice(bleSerialDeviceDescriptor.getBleDeviceInterfaceUUID());
}

BleSerialDevice::~BleSerialDevice()
{
	if (pBleDevice)
		delete(pBleDevice);
}

void BleSerialDevice::openChannel()
{
}

void BleSerialDevice::closeChannel()
{
}

void BleSerialDevice::sendByte(long data)
{
}

long BleSerialDevice::getByte()
{
	return 0;
}

void BleSerialDevice::flushTX()
{
}

void BleSerialDevice::flushRX()
{
}

void BleSerialDevice::sendMultiple(unsigned char * data, long bufsize)
{
}
