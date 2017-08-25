/*****************************************************************************
*
*
*
* File              : BleGattCharacteristicValue.cpp
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
#include "BleGattCharacteristicValue.hpp"
#include "ErrorMsg.hpp"

BleGattCharacteristicValue::BleGattCharacteristicValue(PBTH_LE_GATT_CHARACTERISTIC_VALUE _pGattCharacteristicValue)
{
	if (!_pGattCharacteristicValue)
		throw new ErrorMsg("_pGattCharacteristicValue is nullptr");

	pGattCharacteristicValue = _pGattCharacteristicValue;
}

BleGattCharacteristicValue::~BleGattCharacteristicValue()
{
	if(pGattCharacteristicValue)
		free(pGattCharacteristicValue);
}

unsigned long BleGattCharacteristicValue::getDataSize()
{
	return pGattCharacteristicValue ? pGattCharacteristicValue->DataSize : 0;
}

unsigned char* BleGattCharacteristicValue::getData()
{
	return pGattCharacteristicValue ? pGattCharacteristicValue->Data : nullptr;
}
