/*****************************************************************************
*
*
*
* File              : BleGattDescriptor.cpp
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
#include "Utility.hpp"

#include <sstream>

using namespace std;

BleGattDescriptor::BleGattDescriptor(BleServiceContext & _bleServiceContext, PBTH_LE_GATT_DESCRIPTOR _pGattDescriptor)
	:bleServiceContext(_bleServiceContext)
{
	if (!_pGattDescriptor)
		throw new ErrorMsg("pGattDescriptor is nullptr");

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

BleGattDescriptorValue* BleGattDescriptor::getValue()
{
	USHORT descValueDataSize;

	HRESULT hr = BluetoothGATTGetDescriptorValue(
		bleServiceContext.getServcieHandle(),
		pGattDescriptor,
		0,
		NULL,
		&descValueDataSize,
		BLUETOOTH_GATT_FLAG_NONE);

	if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr)
	{
		stringstream msg;
		msg << "Unable to determine the descriptor value size. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	PBTH_LE_GATT_DESCRIPTOR_VALUE pDescValueBuffer = (PBTH_LE_GATT_DESCRIPTOR_VALUE)malloc(descValueDataSize);

	if (NULL == pDescValueBuffer)
	{
		Util.handleMallocFailure(descValueDataSize);
	}
	else
	{
		RtlZeroMemory(pDescValueBuffer, descValueDataSize);
	}

	hr = BluetoothGATTGetDescriptorValue(
		bleServiceContext.getServcieHandle(),
		pGattDescriptor,
		(ULONG)descValueDataSize,
		pDescValueBuffer,
		NULL,
		BLUETOOTH_GATT_FLAG_NONE);

	if (S_OK != hr)
	{
		stringstream msg;
		msg << "Unable to read the descriptor value size. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}
	
	return new BleGattDescriptorValue(pDescValueBuffer);
}
