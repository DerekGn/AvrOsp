/*****************************************************************************
*
*
*
* File              : BleDeviceContext.hpp
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
#ifndef BLEDEVICECONTEXT_HPP
#define BLEDEVICECONTEXT_HPP

#include <Windows.h>

using namespace std;

#include <string>

static const GUID UUID_DEVICE_INFO = { 0x0000180A, 0x0000, 0x1000, { 0x80, 0x00, 0x00, 0x80, 0x5F, 0x9B, 0x34, 0xFB } };

class BleDeviceContext
{
	private:
		HANDLE hBleDevice = nullptr;
		
		HANDLE hBleService = nullptr;

		wstring deviceInstanceId;

	public:
		BleDeviceContext(HANDLE hBleDevice, wstring deviceInstanceId);
		
		~BleDeviceContext();

		HANDLE getBleServiceHandle();

		HANDLE getBleDeviceHandle();

		wstring getDeviceInstanceId();
};

#endif

