/*****************************************************************************
*
*
*
* File              : BleService.cpp
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
#include "BleService.hpp"

BleService::BleService(HANDLE hbleDevice, PBTH_LE_GATT_SERVICE _pGattService)
{
	pGattService = _pGattService;
}

BleService::~BleService()
{
}

BTH_LE_UUID BleService::getServiceUuid()
{
	return pGattService->ServiceUuid;
}

USHORT BleService::getServiceAttributeHandle()
{
	return pGattService->AttributeHandle;
}
