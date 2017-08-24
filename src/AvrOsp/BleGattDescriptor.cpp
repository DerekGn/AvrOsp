/*****************************************************************************
*
*
*
* File              : BleGattDescriptor.hpp
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
* Description       : A class that models a Ble Descriptor. Its a container for a PBTH_LE_GATT_DESCRIPTOR instance
*
*
*
****************************************************************************/

#include "BleGattDescriptor.hpp"


BleGattDescriptor::BleGattDescriptor(HANDLE _hBleDevice, PBTH_LE_GATT_DESCRIPTOR _pGattDescriptor)
{
	hBleDevice = _hBleDevice;
	pGattDescriptor = _pGattDescriptor;
}

BleGattDescriptor::~BleGattDescriptor()
{
}

USHORT BleGattDescriptor::getServiceHandle()
{
	return pGattDescriptor->ServiceHandle;
}

USHORT BleGattDescriptor::getCharacteristicHandle()
{
	return pGattDescriptor->CharacteristicHandle;
}

BTH_LE_GATT_DESCRIPTOR_TYPE BleGattDescriptor::getDescriptorType()
{
	return pGattDescriptor->DescriptorType;
}

BTH_LE_UUID BleGattDescriptor::getDescriptorUuid()
{
	return pGattDescriptor->DescriptorUuid;
}

USHORT BleGattDescriptor::getAttributeHandle()
{
	return pGattDescriptor->AttributeHandle;
}
