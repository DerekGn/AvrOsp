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
#include "Utility.hpp"

#include <sstream>

PBTH_LE_GATT_DESCRIPTOR BleGattCharacteristic::getGattDescriptors(HANDLE hBleDeviceHandle,
	PBTH_LE_GATT_CHARACTERISTIC pGattCharacteristic, USHORT * pGattDescriptorsCount)
{
	PBTH_LE_GATT_DESCRIPTOR pDescriptorBuffer = nullptr;
	USHORT expectedDescriptorBufferCount = 0;
	*pGattDescriptorsCount = 0;

	HRESULT hr = BluetoothGATTGetDescriptors(
		hBleDeviceHandle,
		pGattCharacteristic,
		0,
		NULL,
		&expectedDescriptorBufferCount,
		BLUETOOTH_GATT_FLAG_NONE);

	if (HRESULT_FROM_WIN32(ERROR_NOT_FOUND) != hr)
	{
		if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr)
		{
			stringstream msg;
			msg << "Unable to determine the number of gatt descriptors. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}
		
		if (expectedDescriptorBufferCount > 0)
		{
			pDescriptorBuffer = (PBTH_LE_GATT_DESCRIPTOR)
				malloc(expectedDescriptorBufferCount
					* sizeof(BTH_LE_GATT_DESCRIPTOR));

			if (NULL == pDescriptorBuffer)
			{
				Util.handleMallocFailure(sizeof(PBTH_LE_GATT_DESCRIPTOR) * expectedDescriptorBufferCount);
			}
			else
			{
				RtlZeroMemory(pDescriptorBuffer, expectedDescriptorBufferCount);
			}

			hr = BluetoothGATTGetDescriptors(
				hBleDeviceHandle,
				pGattCharacteristic,
				expectedDescriptorBufferCount,
				pDescriptorBuffer,
				pGattDescriptorsCount,
				BLUETOOTH_GATT_FLAG_NONE);

			if (S_OK != hr)
			{
				stringstream msg;
				msg << "Unable to determine the number of gatt services. Reason: ["
					<< Util.getLastError() << "]";

				throw new ErrorMsg(msg.str());
			}

			if (*pGattDescriptorsCount != expectedDescriptorBufferCount) {
				throw new ErrorMsg("descriptor count expected and descriptor count actual mismatch");
			}
		}
	}
	

	return pDescriptorBuffer;
}

BleGattCharacteristic::BleGattCharacteristic(HANDLE _hBleDevice, PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic)
{
	if (!_hBleDevice)
		throw new ErrorMsg("hBleDevice is nullptr");

	if (!_pGattCharacteristic)
		throw new ErrorMsg("pGattCharacteristic is nullptr");

	pGattCharacteristic = _pGattCharacteristic;
	hBleDevice = _hBleDevice;

	gattDescriptorsCount = 0;
	pGattDescriptors = getGattDescriptors(hBleDevice, pGattCharacteristic, &gattDescriptorsCount);

	for (size_t i = 0; i < gattDescriptorsCount; i++)
		bleGattDescriptors.push_back(new BleGattDescriptor(hBleDevice, &pGattDescriptors[i]));
}

BleGattCharacteristic::~BleGattCharacteristic()
{
	for (BleGattDescriptor *d : bleGattDescriptors)
		delete(d);

	if (pGattDescriptors)
		free(pGattDescriptors);
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

BleGattCharacteristicValue BleGattCharacteristic::getValue()
{
	PBTH_LE_GATT_CHARACTERISTIC_VALUE pCharValueBuffer = nullptr;
	USHORT charValueDataSize = 0;

	if (pGattCharacteristic->IsReadable) 
	{
		HRESULT hr = BluetoothGATTGetCharacteristicValue(
			hBleDevice,
			pGattCharacteristic,
			0,
			NULL,
			&charValueDataSize,
			BLUETOOTH_GATT_FLAG_NONE);

		if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr) 
		{
			stringstream msg;
			msg << "Unable to determine the characeristic value size. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

		pCharValueBuffer = (PBTH_LE_GATT_CHARACTERISTIC_VALUE)malloc(charValueDataSize);

		if (NULL == pCharValueBuffer) 
		{
			Util.handleMallocFailure(charValueDataSize);
		}
		else 
		{
			RtlZeroMemory(pCharValueBuffer, charValueDataSize);
		}


		hr = BluetoothGATTGetCharacteristicValue(
			hBleDevice,
			pGattCharacteristic,
			(ULONG)charValueDataSize,
			pCharValueBuffer,
			NULL,
			BLUETOOTH_GATT_FLAG_NONE);

		if (S_OK != hr)
		{
			stringstream msg;
			msg << "Unable to read the characeristic value. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}
	}
	else
	{
		throw new ErrorMsg("characteristic is not readable");
	}

	return BleGattCharacteristicValue(pCharValueBuffer);
}

const BleGattCharacteristic::BleGattDescriptors& BleGattCharacteristic::getBleDescriptors()
{
	return bleGattDescriptors;
}
