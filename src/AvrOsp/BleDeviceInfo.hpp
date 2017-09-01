/*****************************************************************************
*
*
*
* File              : BleDeviceInfo.hpp
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
* Description       : A class that contains ble device information
*
*
*
****************************************************************************/
#ifndef BLEDEVICEINFO_HPP
#define BLEDEVICEINFO_HPP

#include <Windows.h>
#include <BluetoothAPIs.h>

#include <string>

using namespace std;

class BleDeviceInfo
{
	private:
		int deviceId;
		
		wstring name;
		
		BLUETOOTH_ADDRESS address;

		unsigned long classOfDevice;

		bool connected;
		
		bool authenticated;
		
		bool remembered;

	public:
		BleDeviceInfo(int deviceId, wstring name, BLUETOOTH_ADDRESS address, 
			unsigned long classofDevice, bool connected, bool authenticated, bool remembered);

		~BleDeviceInfo();

		int getDeviceId();

		wstring getName();

		BLUETOOTH_ADDRESS getAddress();

		unsigned long getClassofDevice();

		bool getConnected();

		bool getAuthenticated();

		bool getRemembered();
};

#endif
