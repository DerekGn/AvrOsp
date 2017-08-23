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


class BleService
{
	public:
		BleService(PBTH_LE_GATT_SERVICE pGattService);
		~BleService();
};

#endif
