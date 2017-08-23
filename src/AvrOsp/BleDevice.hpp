/*****************************************************************************
*
*
*
* File              : BleSerialDevice.hpp
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
* Description       : A class representing a paired Ble device.
*
*
****************************************************************************/
#ifndef BLEDEVICE_HPP
#define BLDEVICE_HPP

using namespace std;

#include <Rpc.h>
#include <bluetoothleapis.h>

#include <list>
#include <string>

#include "BleGattService.hpp"

class BleDevice
{
private:

	list<BleGattService*> gattServices;

	HANDLE hBleDevice = nullptr;

	GUID deviceInterfaceUUID;

	USHORT gattServiceCount = 0;

	PBTH_LE_GATT_SERVICE pGattServiceBuffer = nullptr;
	
	static string guidToString(__in GUID uuid);

	static HANDLE getBleDeviceHandle(__in GUID deviceInterfaceUUID);

	static PBTH_LE_GATT_SERVICE getGattServices(__in HANDLE hBleDeviceHandle, _Out_ USHORT * pGattServiceCount);
	
	//static PBTH_LE_GATT_CHARACTERISTIC_VALUE getGattCharacteristicValue(__in HANDLE _hBleDeviceHandle, __in PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic);

	//static PBTH_LE_GATT_DESCRIPTOR_VALUE getGattDescriptorValue(__in HANDLE _hBleDeviceHandle, __in PBTH_LE_GATT_DESCRIPTOR _pGattDescriptor);

public:
	BleDevice(GUID _deviceInterfaceUUID);

	~BleDevice();

	GUID getDeviceInterfaceUUID();
};
#endif
