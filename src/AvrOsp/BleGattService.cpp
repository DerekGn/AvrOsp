/*****************************************************************************
*
*
*
* File              : BleGattService.cpp
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
* Description       : A class that models a Ble Service. Its a container for a PBTH_LE_GATT_SERVICE instance
*
*
*
****************************************************************************/
#include "BleGattService.hpp"
#include "ErrorMsg.hpp"
#include "Utility.hpp"

#include <sstream>

using namespace std;

PBTH_LE_GATT_CHARACTERISTIC BleGattService::getGattCharacteristics(HANDLE hBleDeviceHandle, PBTH_LE_GATT_SERVICE pGattService, USHORT * pGattCharcteristicsCount)
{
	USHORT expectedCharBufferCount;
	HRESULT hr = BluetoothGATTGetCharacteristics(
		hBleDeviceHandle,
		pGattService,
		0,
		NULL,
		&expectedCharBufferCount,
		BLUETOOTH_GATT_FLAG_NONE);

	if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr)
	{
		stringstream msg;
		msg << "Unable to determine the number of gatt characteristics. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	PBTH_LE_GATT_CHARACTERISTIC pCharBuffer;
	if (expectedCharBufferCount > 0)
	{
		pCharBuffer = (PBTH_LE_GATT_CHARACTERISTIC)
			malloc(expectedCharBufferCount * sizeof(BTH_LE_GATT_CHARACTERISTIC));

		if (NULL == pCharBuffer)
		{
			Util.handleMallocFailure(sizeof(BTH_LE_GATT_SERVICE) * expectedCharBufferCount);
		}
		else
		{
			RtlZeroMemory(pCharBuffer,
				expectedCharBufferCount * sizeof(BTH_LE_GATT_CHARACTERISTIC));
		}

		hr = BluetoothGATTGetCharacteristics(
			hBleDeviceHandle,
			pGattService,
			expectedCharBufferCount,
			pCharBuffer,
			pGattCharcteristicsCount,
			BLUETOOTH_GATT_FLAG_NONE);

		if (S_OK != hr)
		{
			stringstream msg;
			msg << "Unable to determine the number of gatt characteristics. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

		if (*pGattCharcteristicsCount != expectedCharBufferCount)
		{
			throw new ErrorMsg("characteristic count expected and characteristic count actual mismatch");
		}
	}

	return pCharBuffer;
}

BleGattService::BleGattService(HANDLE _hBleDevice, PBTH_LE_GATT_SERVICE _pGattService)
{
	pGattService = _pGattService;
	hBleDevice = _hBleDevice;

	pGattCharacteristics = getGattCharacteristics(hBleDevice, pGattService, &gattCharacteristicsCount);

	for (size_t i = 0; i < gattCharacteristicsCount; i++)
		gattCharacteristics.push_back(new BleGattCharacteristic(hBleDevice, pGattService, &pGattCharacteristics[i]));
}

BleGattService::~BleGattService()
{
	if (pGattCharacteristics != nullptr)
		free(pGattCharacteristics);
}

BTH_LE_UUID BleGattService::getServiceUuid()
{
	return pGattService->ServiceUuid;
}

USHORT BleGattService::getServiceAttributeHandle()
{
	return pGattService->AttributeHandle;
}
