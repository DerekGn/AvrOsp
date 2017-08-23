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
#include <windows.h>
#include <Setupapi.h>
#include <BluetoothAPIs.h>

#pragma comment(lib, "Rpcrt4")
#pragma comment(lib, "SetupAPI")
#pragma comment(lib, "BluetoothAPIs")


#include "BleDevice.hpp"
#include "ErrorMsg.hpp"

#include <sstream>
#include <iomanip>

using namespace std;

string BleDevice::guidToString(GUID uuid)
{
	string guid;

	RPC_WSTR szUuid = NULL;
	if (UuidToString(&uuid, &szUuid) == RPC_S_OK)
	{
		guid = (char*)szUuid;
		RpcStringFree(&szUuid);
	}

	return string();
}

// This function works to get a handle for a BLE device based on its GUID
// Copied from http://social.msdn.microsoft.com/Forums/windowshardware/en-US/e5e1058d-5a64-4e60-b8e2-0ce327c13058/erroraccessdenied-error-when-trying-to-receive-data-from-bluetooth-low-energy-devices?forum=wdk
// From https://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/bad452cb-4fc2-4a86-9b60-070b43577cc9/is-there-a-simple-example-desktop-programming-c-for-bluetooth-low-energy-devices?forum=wdk
// Credits to Andrey_sh
HANDLE BleDevice::getBleDeviceHandle(__in GUID deviceInterfaceUUID)
{
	HDEVINFO hDI;
	SP_DEVICE_INTERFACE_DATA did;
	SP_DEVINFO_DATA dd;
	HANDLE hComm = NULL;

	hDI = SetupDiGetClassDevs(&deviceInterfaceUUID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (hDI == INVALID_HANDLE_VALUE)
	{
		stringstream msg;
		msg << "Unable to open device information set for device interface UUID: ["
			<< guidToString(deviceInterfaceUUID) << "] Reason: ["
			<< getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	did.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	dd.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD i = 0;

	for (i = 0; SetupDiEnumDeviceInterfaces(hDI, NULL, &deviceInterfaceUUID, i, &did); i++)
	{
		SP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData;

		DeviceInterfaceDetailData.cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		DWORD size = 0;

		if (!SetupDiGetDeviceInterfaceDetail(hDI, &did, NULL, 0, &size, 0))
		{
			int err = GetLastError();

			if (err == ERROR_NO_MORE_ITEMS) break;

			PSP_DEVICE_INTERFACE_DETAIL_DATA pInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)GlobalAlloc(GPTR, size);

			pInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

			if (!SetupDiGetDeviceInterfaceDetail(hDI, &did, pInterfaceDetailData, size, &size, &dd))
				break;

			hComm = CreateFile(
				pInterfaceDetailData->DevicePath,
				GENERIC_WRITE | GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			GlobalFree(pInterfaceDetailData);
		}
	}

	SetupDiDestroyDeviceInfoList(hDI);

	if (i == 0)
	{
		stringstream msg;
		msg << "Device interface UUID: ["
			<< guidToString(deviceInterfaceUUID) << "] not found";

		throw new ErrorMsg(msg.str());
	}

	return hComm;
}

PBTH_LE_GATT_SERVICE BleDevice::getGattServices(HANDLE _hBleDeviceHandle, USHORT * _pGattServiceCount)
{
	HRESULT hr = BluetoothGATTGetServices(
		_hBleDeviceHandle,
		0,
		NULL,
		_pGattServiceCount,
		BLUETOOTH_GATT_FLAG_NONE);

	if (ERROR_MORE_DATA != hr)
	{
		stringstream msg;
		msg << "Unable to determine the number of device services. Reason: ["
			<< getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	hr = BluetoothGATTGetServices(
		_hBleDeviceHandle,
		0,
		NULL,
		_pGattServiceCount,
		BLUETOOTH_GATT_FLAG_NONE);

	PBTH_LE_GATT_SERVICE pServiceBuffer = (PBTH_LE_GATT_SERVICE)
		malloc(sizeof(BTH_LE_GATT_SERVICE) * *_pGattServiceCount);

	if (nullptr == _pGattServiceCount)
	{
		stringstream msg;
		msg << "Unable to allocate [" << sizeof(BTH_LE_GATT_SERVICE) * *_pGattServiceCount << "]";

		throw new ErrorMsg(msg.str());
	}
	else
		RtlZeroMemory(pServiceBuffer, sizeof(BTH_LE_GATT_SERVICE) * *_pGattServiceCount);

	USHORT numServices;
	hr = BluetoothGATTGetServices(
		_hBleDeviceHandle,
		*_pGattServiceCount,
		pServiceBuffer,
		&numServices,
		BLUETOOTH_GATT_FLAG_NONE);

	if (S_OK != hr)
	{
		stringstream msg;
		msg << "Unable to determine the number of device services. Reason: ["
			<< getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	return pServiceBuffer;
}

PBTH_LE_GATT_CHARACTERISTIC BleDevice::getGattCharacteristics(HANDLE _hBleDeviceHandle, PBTH_LE_GATT_SERVICE _pGattService, USHORT * _pGattCharcteristicsCount)
{
	return PBTH_LE_GATT_CHARACTERISTIC();
}

PBTH_LE_GATT_CHARACTERISTIC_VALUE BleDevice::getGattCharacteristicValue(HANDLE _hBleDeviceHandle, PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic)
{
	return PBTH_LE_GATT_CHARACTERISTIC_VALUE();
}

PBTH_LE_GATT_DESCRIPTOR BleDevice::getGattDescriptors(HANDLE _hBleDeviceHandle, PBTH_LE_GATT_CHARACTERISTIC _pGattCharacteristic, USHORT * _pGattDescriptorsCount)
{
	return PBTH_LE_GATT_DESCRIPTOR();
}

PBTH_LE_GATT_DESCRIPTOR_VALUE BleDevice::getGattDescriptorValue(HANDLE _hBleDeviceHandle, PBTH_LE_GATT_DESCRIPTOR _pGattDescriptor)
{
	return PBTH_LE_GATT_DESCRIPTOR_VALUE();
}

string BleDevice::getLastError()
{
	DWORD errorMessageID = ::GetLastError();

	if (errorMessageID == 0)
		return string();

	LPSTR messageBuffer = nullptr;
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	string message(messageBuffer, size);

	LocalFree(messageBuffer);

	return message;
}

BleDevice::BleDevice(GUID _deviceInterfaceUUID)
{
	deviceInterfaceUUID = _deviceInterfaceUUID;

	hBleDevice = getBleDeviceHandle(deviceInterfaceUUID);

	pGattServiceBuffer = getGattServices(hBleDevice, &gattServiceCount);

	USHORT gattCharacteristicCount;

	for (size_t i = 0; i < gattServiceCount; i++)
	{
		gattCharacteristicCount = 0;
		PBTH_LE_GATT_CHARACTERISTIC pGattCharacteristicsBuffer = getGattCharacteristics(hBleDevice, &pGattServiceBuffer[i], &gattCharacteristicCount);

		USHORT gattDescriptorBufferCount;
		for (size_t i = 0; i < gattCharacteristicCount; i++)
		{

			gattDescriptorBufferCount = 0;
			PBTH_LE_GATT_DESCRIPTOR pGattDescriptorBuffer = getGattDescriptors(hBleDevice, &pGattCharacteristicsBuffer[i], &gattDescriptorBufferCount);
		}
	}
}

BleDevice::~BleDevice()
{
	if (hBleDevice != nullptr)
		CloseHandle(hBleDevice);

	if (pGattServiceBuffer != nullptr)
		free(pGattServiceBuffer);
}

GUID BleDevice::getDeviceInterfaceUUID()
{
	return deviceInterfaceUUID;
}
