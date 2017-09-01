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
#include <BluetoothAPIs.h>
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

void BleDeviceEnumerator::checkBleRadioPresent(unsigned long classofDevice)
{
	unsigned long radioClassOfDevice = 0;

	HANDLE hRadio = INVALID_HANDLE_VALUE;
	BLUETOOTH_FIND_RADIO_PARAMS params = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
	HBLUETOOTH_RADIO_FIND hf = BluetoothFindFirstRadio(&params, &hRadio);

	if (hf == nullptr)
	{
		throw new ErrorMsg("Ble radio not present or not functioning.");
	}

	BLUETOOTH_RADIO_INFO info = { sizeof(BLUETOOTH_RADIO_INFO) };

	if (BluetoothGetRadioInfo(&hRadio, &info) == ERROR_SUCCESS)
	{
		radioClassOfDevice = info.ulClassofDevice;
	}

	CloseHandle(hRadio);
	BluetoothFindRadioClose(hf);

	if (radioClassOfDevice != info.ulClassofDevice)
	{
		throw new ErrorMsg("Radio not capable of BLE");
	}
}

void BleDeviceEnumerator::enumerateBleDevices(bool returnAuthenticated, bool returnRemembered, bool returnUnknown, 
	bool fReturnConnected, bool issueInquiry, unsigned char timeoutMultiplier)
{
	BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams = {
		sizeof(BLUETOOTH_DEVICE_SEARCH_PARAMS),
		returnAuthenticated,
		returnRemembered,
		returnUnknown,
		fReturnConnected,
		issueInquiry,
		timeoutMultiplier,
		NULL
	};
	BLUETOOTH_FIND_RADIO_PARAMS findParams = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
	BLUETOOTH_DEVICE_INFO deviceInfo = { sizeof(BLUETOOTH_DEVICE_INFO),0, };
	BLUETOOTH_RADIO_INFO btRadioInfo = { sizeof(BLUETOOTH_RADIO_INFO),0, };
	HBLUETOOTH_DEVICE_FIND btDeviceFind;
	HBLUETOOTH_RADIO_FIND hbtRadioFind;
	HANDLE hRadio = nullptr;
	int deviceId = 0;
	int radioId = 0;

	hbtRadioFind = BluetoothFindFirstRadio(&findParams, &hRadio);

	if (hbtRadioFind == nullptr)
	{
		stringstream msg;
		msg << "Unable to get handle to first bluetooth radio. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	do
	{
		DWORD getRadio = BluetoothGetRadioInfo(hRadio, &btRadioInfo);

		if (getRadio != ERROR_SUCCESS)
		{
			stringstream msg;
			msg << "Unable to get radio information. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

		searchParams.hRadio = hRadio;
		ZeroMemory(&btRadioInfo, sizeof(BLUETOOTH_DEVICE_INFO));
		btRadioInfo.dwSize = sizeof(BLUETOOTH_DEVICE_INFO);

		btDeviceFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);

		if (btDeviceFind == nullptr)
		{
			stringstream msg;
			msg << "Unable to get handle to first bluetooth device. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

		radioId++;
		deviceId = 0;

		do
		{
			BLUETOOTH_ADDRESS* address = new BLUETOOTH_ADDRESS();
			
			for (size_t i = 0; i < 6; i++)
				address->rgBytes[i] = deviceInfo.Address.rgBytes[i];
		
			bleEnumeratedDevices.push_back(new BleDeviceInfo(deviceId++, std::wstring(deviceInfo.szName), address,
				deviceInfo.ulClassofDevice, deviceInfo.fConnected, deviceInfo.fAuthenticated, deviceInfo.fRemembered));

			if (!BluetoothFindNextDevice(btDeviceFind, &deviceInfo))
				break;

		} while (BluetoothFindNextDevice(btDeviceFind, &deviceInfo));

		if (BluetoothFindDeviceClose(btDeviceFind) != TRUE)
		{
			stringstream msg;
			msg << "Unable to close bluetooth device find. Reason: ["
				<< Util.getLastError() << "]";

			throw new ErrorMsg(msg.str());
		}

	} while (BluetoothFindNextRadio(&findParams, &hRadio));

	if (BluetoothFindRadioClose(hbtRadioFind) != TRUE)
	{
		stringstream msg;
		msg << "Unable to close bluetooth radio find. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}
}

void BleDeviceEnumerator::deletebleEnumeratedDevices()
{
	bleEnumeratedDevices.clear();
}

BleDeviceEnumerator::BleDeviceEnumerator()
{
}

BleDeviceEnumerator::~BleDeviceEnumerator()
{
	deletebleEnumeratedDevices();
}

void BleDeviceEnumerator::enumerate(bool returnAuthenticated, bool returnRemembered, bool returnUnknown, 
	bool fReturnConnected, bool issueInquiry, unsigned char timeoutMultiplier)
{
	checkBleRadioPresent(0);

	deletebleEnumeratedDevices();

	enumerateBleDevices(returnAuthenticated, returnRemembered, returnUnknown, fReturnConnected, issueInquiry, timeoutMultiplier);
}

const BleDeviceEnumerator::BleDevices & BleDeviceEnumerator::getBleDevices()
{
	checkBleRadioPresent(0);

	deletebleEnumeratedDevices();
	
	return bleEnumeratedDevices;
}
