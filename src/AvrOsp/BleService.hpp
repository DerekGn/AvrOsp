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
#ifndef BLESERVICE_HPP
#define BLESERVICE_HPP

#include <Windows.h>
#include <Bluetoothleapis.h>

class BleService
{
	private:
		PBTH_LE_GATT_SERVICE pGattService;

	public:
		BleService(HANDLE hbleDevice, PBTH_LE_GATT_SERVICE _pGattService);

		~BleService();

		BTH_LE_UUID getServiceUuid();

		USHORT getServiceAttributeHandle();
};

#endif
