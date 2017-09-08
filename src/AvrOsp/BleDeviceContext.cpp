/*****************************************************************************
*
*
*
* File              : BleDeviceContext.cpp
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
* Description       : A container class for bleDevice context for child characeristics and services
*
*
*
****************************************************************************/
#include "BleDeviceContext.hpp"
#include "BleFunctions.hpp"

BleDeviceContext::BleDeviceContext(HANDLE _hBleDevice, wstring _deviceInstanceId)
{
	hBleDevice = _hBleDevice;
	deviceInstanceId = _deviceInstanceId;
	hBleService = getBleServiceInterfaceHandle(UUID_DEVICE_INFO, deviceInstanceId);
}

BleDeviceContext::~BleDeviceContext()
{
	if (hBleService)
		releaseBleInterfaceHandle(hBleService);
}

HANDLE BleDeviceContext::getBleServiceHandle()
{
	return hBleService;
}

HANDLE BleDeviceContext::getBleDeviceHandle()
{
	return hBleDevice;
}

wstring BleDeviceContext::getDeviceInstanceId()
{
	return deviceInstanceId;
}

