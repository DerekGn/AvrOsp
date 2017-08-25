/*****************************************************************************
*
*
*
* File              : BleDeviceEnumerator.hpp
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
* Description       : A class that enumerates ble devices
*
*
*
****************************************************************************/
#ifndef BLEDEVICEENUMERATOR_HPP
#define BLEDEVICEENUMERATOR_HPP

#include "BleDeviceInfo.hpp"

#include <list>

using namespace std;

class BleDeviceEnumerator
{
	private:
		list<BleDeviceInfo*> bleEnumeratedDevices;

		void deletebleEnumeratedDevices();

		wstring getDeviceRegistryStringProperty(HDEVINFO hDI, PSP_DEVINFO_DATA did, int property);

	public:
		BleDeviceEnumerator();

		~BleDeviceEnumerator();

		typedef list<BleDeviceInfo*> BleDevices;

		const BleDevices& getBleDevices();
};

extern BleDeviceEnumerator BleEnumerator;

#endif
