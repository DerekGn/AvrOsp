/*****************************************************************************
*
*
*
* File              : BleDeviceInfo.hpp
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
* Description       : A class that contains ble device information
*
*
*
****************************************************************************/
#ifndef BLEDEVICEINFO_HPP
#define BLEDEVICEINFO_HPP

#include <string>

using namespace std;

class BleDeviceInfo
{
private:
	wstring name;

	wstring hardwareId;

	wstring instanceId;

public:
	BleDeviceInfo(wstring name, wstring hardwareId, wstring instanceId);

	~BleDeviceInfo();

	wstring getName();

	wstring getHardwareId();

	wstring getInstanceId();
};

#endif