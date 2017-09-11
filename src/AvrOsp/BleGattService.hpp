/*****************************************************************************
*
*
*
* File              : BleService.hpp
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
#ifndef BLEGATTSERVICE_HPP
#define BLEGATTSERVICE_HPP

using namespace std;

#include <Windows.h>
#include <Bluetoothleapis.h>

#include "BleGattCharacteristic.hpp"

#include <list>

class BleGattService
{
	private:
		
		BleDeviceContext& bleDeviceContext;

		USHORT gattCharacteristicsCount = 0;

		PBTH_LE_GATT_SERVICE pGattService = nullptr;

		list<BleGattCharacteristic*> bleGattCharacteristics;

		PBTH_LE_GATT_CHARACTERISTIC pGattCharacteristics = nullptr;

		static PBTH_LE_GATT_CHARACTERISTIC getGattCharacteristics(HANDLE hBleDeviceHandle, 
			PBTH_LE_GATT_SERVICE pGattService, USHORT * pGattCharcteristicsCount);

	public:
		BleGattService(BleDeviceContext & bleDeviceContext, PBTH_LE_GATT_SERVICE pGattService);

		~BleGattService();

		BTH_LE_UUID getServiceUuid();

		USHORT getServiceAttributeHandle();

		typedef list<BleGattCharacteristic*> BleGattCharacteristics;

		const BleGattCharacteristics& getBleCharacteristics();
};

#endif
