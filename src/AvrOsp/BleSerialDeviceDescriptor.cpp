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
#include "BleSerialDeviceDescriptor.hpp"

using namespace std;

BleSerialDeviceDescriptor::BleSerialDeviceDescriptor()
{
}

BleSerialDeviceDescriptor::BleSerialDeviceDescriptor(string _bleSerialDeviceType, GUID _serialInCharacteristicUUID, GUID _serialOutCharacteristicUUID)
{
	bleSerialDeviceType = _bleSerialDeviceType;
	serialInCharacteristicUUID = _serialInCharacteristicUUID;
	serialOutCharacteristicUUID = _serialOutCharacteristicUUID;
}

BleSerialDeviceDescriptor::~BleSerialDeviceDescriptor()
{
}

GUID BleSerialDeviceDescriptor::getSerialInCharacteristicUUID()
{
	return serialInCharacteristicUUID;
}

GUID BleSerialDeviceDescriptor::getSerialOutCharacteristicUUID()
{
	return serialOutCharacteristicUUID;
}
