/*****************************************************************************
*
*
*
* File              : BleGattCharacteristic.hpp
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
#include <Windows.h>
#include <Bluetoothleapis.h>

class BleGattCharacteristic
{
	private:
		HANDLE hBleDevice;

		PBTH_LE_GATT_CHARACTERISTIC pGattCharacteristic;

		static PBTH_LE_GATT_DESCRIPTOR getGattDescriptors(__in HANDLE _hBleDeviceHandle, __in PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic, _Out_ USHORT * _pGattDescriptorsCount);

	public:
		BleGattCharacteristic(HANDLE hBleDevice, PBTH_LE_GATT_CHARACTERISTIC pGattCharacteristic);
		
		~BleGattCharacteristic();

		USHORT getServiceHandle();

		BTH_LE_UUID getCharacteristicUuid();

		USHORT getAttributeHandle();
		
		USHORT getCharacteristicValueHandle();
		
		BOOLEAN getIsBroadcastable();

		BOOLEAN getIsReadable();

		BOOLEAN getIsWritable();

		BOOLEAN getIsWritableWithoutResponse();

		BOOLEAN getIsSignedWritable();

		BOOLEAN getIsNotifiable();

		BOOLEAN getIsIndicatable();

		BOOLEAN getHasExtendedProperties();
};

