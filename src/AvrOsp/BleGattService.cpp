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
#include "BleFunctions.hpp"
#include "ErrorMsg.hpp"
#include "Utility.hpp"

#include <sstream>

using namespace std;

PBTH_LE_GATT_CHARACTERISTIC BleGattService::getGattCharacteristics(HANDLE hBleDeviceHandle, 
	PBTH_LE_GATT_SERVICE pGattService, USHORT * pGattCharcteristicsCount)
{
	PBTH_LE_GATT_CHARACTERISTIC pCharBuffer = nullptr;
	USHORT expectedCharBufferCount;
	*pGattCharcteristicsCount = 0;

	HRESULT hr = BluetoothGATTGetCharacteristics(
		hBleDeviceHandle,
		pGattService,
		0,
		NULL,
		&expectedCharBufferCount,
		BLUETOOTH_GATT_FLAG_NONE);

	if (HRESULT_FROM_WIN32(ERROR_NOT_FOUND) != hr)
	{
		if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr)
		{
			stringstream msg;
			msg << "Unable to determine the number of gatt characteristics. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

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
	}
	return pCharBuffer;
}

BleGattService::BleGattService(BleDeviceContext& _bleDeviceContext, PBTH_LE_GATT_SERVICE _pGattService)
	:bleDeviceContext(_bleDeviceContext)
{
	if (!_pGattService)
		throw new ErrorMsg("pGattService is nullptr");

	pGattService = _pGattService;
	
	pGattCharacteristics = getGattCharacteristics(bleDeviceContext.getBleDeviceHandle(), pGattService, &gattCharacteristicsCount);

	for (size_t i = 0; i < gattCharacteristicsCount; i++)
		bleGattCharacteristics.push_back(new BleGattCharacteristic(bleDeviceContext, &pGattCharacteristics[i]));
}

BleGattService::~BleGattService()
{
	for (BleGattCharacteristic *c : bleGattCharacteristics)
		delete(c);

	if (pGattCharacteristics)
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

const BleGattService::BleGattCharacteristics & BleGattService::getBleCharacteristics()
{
	return bleGattCharacteristics;
}
