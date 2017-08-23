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
* Description       : A class representing a paired Ble device.
*
*
****************************************************************************/
#ifndef BLEDEVICE_HPP
#define BLDEVICE_HPP

using namespace std;

#include <Rpc.h>

#include<string>

class BleDevice
{
	private:
		HANDLE hBleDevice = NULL;
		GUID deviceInterfaceUUID;
		
		static string guidToString(__in GUID uuid);

		static HANDLE getBleDeviceHandle(__in GUID deviceInterfaceUUID);
		
		static string getLastError();

	public:
		BleDevice(__in GUID _deviceInterfaceUUID);
		
		~BleDevice();

		GUID getDeviceInterfaceUUID();
};
#endif

