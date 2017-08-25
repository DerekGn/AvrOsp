#include "BleGattDescriptorValue.hpp"

BleGattDescriptorValue::BleGattDescriptorValue(PBTH_LE_GATT_DESCRIPTOR_VALUE _pGattDescriptorValue)
{
	pGattDescriptorValue = _pGattDescriptorValue;
}

BleGattDescriptorValue::~BleGattDescriptorValue()
{
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
