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
#ifndef BLEGATTDESCRIPTOR_HPP
#define BLEGATTDESCRIPTOR_HPP

#include <Windows.h>
#include <Bluetoothleapis.h>

#include "BleDeviceContext.hpp"
#include "BleGattDescriptorValue.hpp"

using namespace std;

#include <list>

class BleGattDescriptor
{
	private:
		
		BleDeviceContext& bleDeviceContext;

		PBTH_LE_GATT_DESCRIPTOR pGattDescriptor = nullptr;

	public:
		BleGattDescriptor(BleDeviceContext& bleDeviceContext, PBTH_LE_GATT_DESCRIPTOR pGattDescriptor);

		~BleGattDescriptor();

		USHORT getServiceHandle();

		USHORT getCharacteristicHandle();

		BTH_LE_GATT_DESCRIPTOR_TYPE getDescriptorType();

		BTH_LE_UUID getDescriptorUuid();
		
		USHORT getAttributeHandle();

		BleGattDescriptorValue* getValue();
};
#endif
