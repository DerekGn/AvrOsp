/*****************************************************************************
*
*
*
* File              : BleDeviceEnumerator.cpp
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
* Description       : A class that enumerates ble devices
*
*
*
****************************************************************************/
#include <windows.h>
#include <bthdef.h>
#include <devguid.h>
#include <setupapi.h>
#include <bluetoothleapis.h>

#include "BleDeviceEnumerator.hpp"
#include "Utility.hpp"

#include <sstream>
#include <memory>

using namespace std;

BleDeviceEnumerator BleEnumerator;

inline std::wstring& rtrim_null(std::wstring& s)
{
	s.erase(s.find_first_of(L'\0', 0));
	return s;
}

void BleDeviceEnumerator::deletebleEnumeratedDevices()
{
	bleEnumeratedDevices.clear();
}

wstring BleDeviceEnumerator::getDeviceRegistryStringProperty(HDEVINFO hDI, SP_DEVINFO_DATA did, int property)
{
	wstring text;
	DWORD bufferSize = 0;

	while (!SetupDiGetDeviceRegistryProperty(
		hDI,
		&did,
		property,
		NULL,
		(PBYTE)&text[0],
		bufferSize,
		&bufferSize))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			text.resize(bufferSize);
		else
			break;
	}

	return text;
}

BleDeviceEnumerator::BleDeviceEnumerator()
{
}

BleDeviceEnumerator::~BleDeviceEnumerator()
{
	deletebleEnumeratedDevices();
}

const BleDeviceEnumerator::BleDevices & BleDeviceEnumerator::getBleDevices()
{
	deletebleEnumeratedDevices();

	SP_DEVINFO_DATA did;
	DWORD i;

	HDEVINFO hDI = SetupDiGetClassDevs(&GUID_BLUETOOTHLE_DEVICE_INTERFACE, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (INVALID_HANDLE_VALUE == hDI)
	{
		stringstream msg;
		msg << "Unable to get handle to device information elements. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	did.cbSize = sizeof(SP_DEVINFO_DATA);

	try
	{
		for (i = 0; SetupDiEnumDeviceInfo(hDI, i, &did); i++)
		{
			wstring name = getDeviceRegistryStringProperty(hDI, did, SPDRP_FRIENDLYNAME);

			wstring hwId = getDeviceRegistryStringProperty(hDI, did, SPDRP_HARDWAREID);

			wstring deviceInstanceId;
			DWORD bufferSize = 0;

			while (!SetupDiGetDeviceInstanceId(
				hDI,
				&did,
				&deviceInstanceId[0],
				bufferSize,
				&bufferSize))
			{
				if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
					deviceInstanceId.resize(bufferSize);
				else
					break;
			}

			if (name.size() > 0)
			{
				bleEnumeratedDevices.push_back(new BleDeviceInfo(rtrim_null(name), rtrim_null(hwId), rtrim_null(deviceInstanceId)));
			}
		}
	}
	catch (const std::exception&)
	{
		if (hDI)
			SetupDiDestroyDeviceInfoList(hDI);
	}

	return bleEnumeratedDevices;
}