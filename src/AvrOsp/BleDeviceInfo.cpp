/*****************************************************************************
*
*
*
* File              : BleDeviceInfo.cpp
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
* Description       : A class that contains information about a ble device
*
*
*
****************************************************************************/
#include "BleDeviceInfo.hpp"

BleDeviceInfo::BleDeviceInfo(int _deviceId, wstring _name, BLUETOOTH_ADDRESS _address,
	unsigned long _classOfDevice, bool _connected, bool _authenticated, bool _remembered)
{
	deviceId = _deviceId;
	name = _name;
	address = _address;
	classOfDevice = _classOfDevice;
	connected = _connected;
	authenticated = _authenticated;
	remembered = _remembered;
}

BleDeviceInfo::~BleDeviceInfo()
{
}

int BleDeviceInfo::getDeviceId()
{
	return 0;
}

wstring BleDeviceInfo::getName()
{
	return name;
}

//BLUETOOTH_ADDRESS BleDeviceInfo::getAddress()
//{
//	return address;
//}

unsigned long BleDeviceInfo::getClassofDevice()
{
	return classOfDevice;
}

bool BleDeviceInfo::getConnected()
{
	return connected;
}

bool BleDeviceInfo::getAuthenticated()
{
	return authenticated;
}

bool BleDeviceInfo::getRemembered()
{
	return remembered;
}
