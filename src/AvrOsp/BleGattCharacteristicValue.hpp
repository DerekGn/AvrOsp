/*****************************************************************************
*
*
*
* File              : BleGattCharacteristicValue.hpp
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
* Description       : A class that models a Ble Characteristic Value. Its a container for a PBTH_LE_GATT_CHARACTERISTIC_VALUE instance
*
*
*
****************************************************************************/
#ifndef BLEGATTCHARACTERISTICVALUE_HPP
#define BLEGATTCHARACTERISTICVALUE_HPP

#include <Windows.h>
#include <Bluetoothleapis.h>

class BleGattCharacteristicValue
{
	private:
		PBTH_LE_GATT_CHARACTERISTIC_VALUE pGattCharacteristicValue = nullptr;

	public:
		BleGattCharacteristicValue(__in PBTH_LE_GATT_CHARACTERISTIC_VALUE pGattCharacteristicValue);
		
		~BleGattCharacteristicValue();

		unsigned long getDataSize();

		unsigned char* getData();
};

#endif

