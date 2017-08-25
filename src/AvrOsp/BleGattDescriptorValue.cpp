/*****************************************************************************
*
*
*
* File              : BleGattDestriptorValue.cpp
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

#include "BleGattDescriptorValue.hpp"

BleGattDescriptorValue::BleGattDescriptorValue(PBTH_LE_GATT_DESCRIPTOR_VALUE _pGattDescriptorValue)
{
	pGattDescriptorValue = _pGattDescriptorValue;
}

BleGattDescriptorValue::~BleGattDescriptorValue()
{
	if (pGattDescriptorValue != nullptr)
		free(pGattDescriptorValue);
}

BTH_LE_GATT_DESCRIPTOR_TYPE BleGattDescriptorValue::GetDescriptorType()
{
	return pGattDescriptorValue->DescriptorType;
}

BTH_LE_UUID BleGattDescriptorValue::getDescriptorUuid()
{
	return pGattDescriptorValue->DescriptorUuid;
}

BOOLEAN BleGattDescriptorValue::getIsReliableWriteEnabled()
{
	return pGattDescriptorValue->CharacteristicExtendedProperties.IsReliableWriteEnabled;
}

BOOLEAN BleGattDescriptorValue::getIsAuxiliariesWritable()
{
	return pGattDescriptorValue->CharacteristicExtendedProperties.IsAuxiliariesWritable;
}

BOOLEAN BleGattDescriptorValue::getIsSubscribeToNotification()
{
	return pGattDescriptorValue->ClientCharacteristicConfiguration.IsSubscribeToNotification;
}

BOOLEAN BleGattDescriptorValue::getIsSubscribeToIndication()
{
	return pGattDescriptorValue->ClientCharacteristicConfiguration.IsSubscribeToIndication;
}

BOOLEAN BleGattDescriptorValue::getIsBroadcast()
{
	return pGattDescriptorValue->ServerCharacteristicConfiguration.IsBroadcast;
}

unsigned char BleGattDescriptorValue::getFormat()
{
	return pGattDescriptorValue->CharacteristicFormat.Format;
}

unsigned char BleGattDescriptorValue::getExponent()
{
	return pGattDescriptorValue->CharacteristicFormat.Exponent;
}

BTH_LE_UUID BleGattDescriptorValue::getUnit()
{
	return pGattDescriptorValue->CharacteristicFormat.Unit;
}

unsigned char BleGattDescriptorValue::getNameSpace()
{
	return pGattDescriptorValue->CharacteristicFormat.NameSpace;
}

BTH_LE_UUID BleGattDescriptorValue::getDescription()
{
	return pGattDescriptorValue->CharacteristicFormat.Description;
}

unsigned long BleGattDescriptorValue::getDataSize()
{
	return pGattDescriptorValue->DataSize;
}

unsigned char* BleGattDescriptorValue::getData()
{
	return pGattDescriptorValue->Data;
}
