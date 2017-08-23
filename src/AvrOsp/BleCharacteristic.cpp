#include "BleCharacteristic.hpp"

BleCharacteristic::BleCharacteristic(PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic)
{
	pGattCharacteristic = _pGattCharacteristic;
}

BleCharacteristic::~BleCharacteristic()
{
}

USHORT BleCharacteristic::getServiceHandle()
{
	return pGattCharacteristic->ServiceHandle;
}

BTH_LE_UUID BleCharacteristic::getCharacteristicUuid()
{
	return pGattCharacteristic->CharacteristicUuid;
}

USHORT BleCharacteristic::getAttributeHandle()
{
	return pGattCharacteristic->AttributeHandle;
}

USHORT BleCharacteristic::getCharacteristicValueHandle()
{
	return pGattCharacteristic->CharacteristicValueHandle;
}

BOOLEAN BleCharacteristic::getIsBroadcastable()
{
	return pGattCharacteristic->IsBroadcastable;
}

BOOLEAN BleCharacteristic::getIsReadable()
{
	return pGattCharacteristic->IsReadable;
}

BOOLEAN BleCharacteristic::getIsWritable()
{
	return pGattCharacteristic->IsWritable;
}

BOOLEAN BleCharacteristic::getIsWritableWithoutResponse()
{
	return pGattCharacteristic->IsWritableWithoutResponse;
}

BOOLEAN BleCharacteristic::getIsSignedWritable()
{
	return pGattCharacteristic->IsSignedWritable;
}

BOOLEAN BleCharacteristic::getIsNotifiable()
{
	return pGattCharacteristic->IsNotifiable;
}

BOOLEAN BleCharacteristic::getIsIndicatable()
{
	return pGattCharacteristic->IsIndicatable;
}

BOOLEAN BleCharacteristic::getHasExtendedProperties()
{
	return pGattCharacteristic->HasExtendedProperties;
}
