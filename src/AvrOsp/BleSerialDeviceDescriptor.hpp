/*****************************************************************************
*
*
*
* File              : BleSerialDeviceDescriptor.hpp
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
* Description       : A class that describes an instance of a BleSerialDevice
*
*
*
****************************************************************************/
#ifndef BLESERIALDEVICEDESCRIPTOR_HPP
#define BLESERIALDEVICEDESCRIPTOR_HPP

using namespace std;

#include <Rpc.h>
#include <string>

class BleSerialDeviceDescriptor
{
	private:
		string bleSerialDeviceType;			// The ble serial device type
		GUID serialInCharacteristicUUID;	// The characteristic for serial in data
		GUID serialOutCharacteristicUUID;	// The characteristic for serial out data

	public:
		BleSerialDeviceDescriptor();

		BleSerialDeviceDescriptor(string _bleSerialDeviceType, GUID _serialInCharacteristicUUID, GUID _serialOutCharacteristicUUID);
		
		~BleSerialDeviceDescriptor();

		GUID getBleDeviceInterfaceUUID();

		GUID getSerialInCharacteristicUUID();

		GUID getSerialOutCharacteristicUUID();
};

#endif
