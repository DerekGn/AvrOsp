/*****************************************************************************
*
*
*
* File              : BleGattCharacteristic.cpp
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

#include "BleGattCharacteristic.hpp"

PBTH_LE_GATT_DESCRIPTOR BleGattCharacteristic::getGattDescriptors(HANDLE _hBleDeviceHandle, PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic, USHORT * _pGattDescriptorsCount)
{
	return PBTH_LE_GATT_DESCRIPTOR();
}

BleGattCharacteristic::BleGattCharacteristic(HANDLE _hBleDevice, PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic)
{
	pGattCharacteristic = _pGattCharacteristic;
	hBleDevice = _hBleDevice;


}

BleGattCharacteristic::~BleGattCharacteristic()
{
}

USHORT BleGattCharacteristic::getServiceHandle()
{
	return pGattCharacteristic->ServiceHandle;
}

BTH_LE_UUID BleGattCharacteristic::getCharacteristicUuid()
{
	return pGattCharacteristic->CharacteristicUuid;
}

USHORT BleGattCharacteristic::getAttributeHandle()
{
	return pGattCharacteristic->AttributeHandle;
}

USHORT BleGattCharacteristic::getCharacteristicValueHandle()
{
	return pGattCharacteristic->CharacteristicValueHandle;
}

BOOLEAN BleGattCharacteristic::getIsBroadcastable()
{
	return pGattCharacteristic->IsBroadcastable;
}

BOOLEAN BleGattCharacteristic::getIsReadable()
{
	return pGattCharacteristic->IsReadable;
}

BOOLEAN BleGattCharacteristic::getIsWritable()
{
	return pGattCharacteristic->IsWritable;
}

BOOLEAN BleGattCharacteristic::getIsWritableWithoutResponse()
{
	return pGattCharacteristic->IsWritableWithoutResponse;
}

BOOLEAN BleGattCharacteristic::getIsSignedWritable()
{
	return pGattCharacteristic->IsSignedWritable;
}

BOOLEAN BleGattCharacteristic::getIsNotifiable()
{
	return pGattCharacteristic->IsNotifiable;
}

BOOLEAN BleGattCharacteristic::getIsIndicatable()
{
	return pGattCharacteristic->IsIndicatable;
}

BOOLEAN BleGattCharacteristic::getHasExtendedProperties()
{
	return pGattCharacteristic->HasExtendedProperties;
}
