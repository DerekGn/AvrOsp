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

BleDeviceInfo::BleDeviceInfo(wstring _name, wstring _hardwareId, wstring _instanceId)
{
	name = _name;
	hardwareId = _hardwareId;
	instanceId = _instanceId;
}

BleDeviceInfo::~BleDeviceInfo()
{
}

wstring BleDeviceInfo::getName()
{
	return name;
}

wstring BleDeviceInfo::getHardwareId()
{
	return hardwareId;
}

wstring BleDeviceInfo::getInstanceId()
{
	return instanceId;
}
