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

		void checkBleRadioPresent(unsigned long classofDevice);

		void enumerateBleDevices(bool returnAuthenticated, bool returnRemembered, bool returnUnknown, 
			bool fReturnConnected, bool issueInquiry, unsigned char timeoutMultiplier);

	public:
		BleDeviceEnumerator();

		~BleDeviceEnumerator();

		void enumerate(bool returnAuthenticated, bool returnRemembered, bool returnUnknown, 
			bool fReturnConnected, bool issueInquiry, unsigned char timeoutMultiplier);

		typedef list<BleDeviceInfo*> BleDevices;

		const BleDevices& getBleDevices();
};

extern BleDeviceEnumerator BleEnumerator;

#endif
