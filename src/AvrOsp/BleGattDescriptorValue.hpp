/*****************************************************************************
*
*
*
* File              : BleGattDestriptorValue.hpp
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
* Description       : A class that models a Ble Characteristic. Its a container for a PBTH_LE_GATT_CHARACTERISTIC instance
*
*
*
****************************************************************************/
#ifndef BLEGATTDESCRIPTORVALUE_HPP
#define BLEGATTDESCRIPTORVALUE_HPP

#include <Windows.h>
#include <Bluetoothleapis.h>

using namespace std;

class BleGattDescriptorValue
{
	private:
		PBTH_LE_GATT_DESCRIPTOR_VALUE pGattDescriptorValue;

	public:
		BleGattDescriptorValue(PBTH_LE_GATT_DESCRIPTOR_VALUE pGattDescriptorValue);

		~BleGattDescriptorValue();

		BTH_LE_GATT_DESCRIPTOR_TYPE GetDescriptorType();

		BTH_LE_UUID getDescriptorUuid();

		BOOLEAN getIsReliableWriteEnabled();

		BOOLEAN getIsAuxiliariesWritable();

		BOOLEAN getIsSubscribeToNotification();

		BOOLEAN getIsSubscribeToIndication();

		BOOLEAN getIsBroadcast();

		unsigned char getFormat();

		unsigned char getExponent();

		BTH_LE_UUID getUnit();

		unsigned char getNameSpace();

		BTH_LE_UUID getDescription();

		unsigned long getDataSize();

		unsigned char* getData();
};

#endif
