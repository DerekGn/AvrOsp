/*****************************************************************************
*
*
*
* File              : BleSerialDevice.cpp
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
#include "Utility.hpp"

#include <sstream>

using namespace std;

HANDLE BleDevice::getBleDeviceHandle(wstring deviceInstanceId)
{
	HDEVINFO hDI;
	SP_DEVICE_INTERFACE_DATA did;
	SP_DEVINFO_DATA dd;
	HANDLE hComm = NULL;

	hDI = SetupDiGetClassDevs(&GUID_BLUETOOTHLE_DEVICE_INTERFACE, deviceInstanceId.c_str(), NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (hDI == INVALID_HANDLE_VALUE)
	{
		stringstream msg;
		msg << "Unable to open device information set for device interface UUID: ["
			<< Util.convertToString(deviceInstanceId) << "] Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	did.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	dd.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD i = 0;

	for (i = 0; SetupDiEnumDeviceInterfaces(hDI, NULL, &GUID_BLUETOOTHLE_DEVICE_INTERFACE, i, &did); i++)
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
			<< Util.convertToString(deviceInstanceId) << "] not found";

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

	if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr)
	{
		stringstream msg;
		msg << "Unable to determine the number of gatt services. Reason: ["
			<< Util.getLastError() << "]";

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

	if (!_pGattServiceCount)
		Util.handleMallocFailure(sizeof(BTH_LE_GATT_SERVICE) * *_pGattServiceCount);
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
		msg << "Unable to determine the number of gatt services. Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	return pServiceBuffer;
}

BleDevice::BleDevice(wstring _deviceInstanceId) : hBleDevice(getBleDeviceHandle(_deviceInstanceId)), deviceContext(hBleDevice, _deviceInstanceId)
{
	deviceInstanceId = _deviceInstanceId;
	
	pGattServiceBuffer = getGattServices(hBleDevice, &gattServiceCount);

	for (size_t i = 0; i < gattServiceCount; i++)
	{
		bleGattServices.push_back(new BleGattService(deviceContext, &pGattServiceBuffer[i]));
	}
}

BleDevice::~BleDevice()
{
	for (BleGattService *s : bleGattServices)
		delete(s);

	if (pGattServiceBuffer)
		free(pGattServiceBuffer);

	if (hBleDevice)
		CloseHandle(hBleDevice);
}

wstring BleDevice::getDeviceIntstanceId()
{
	return deviceInstanceId;
}

const BleDevice::BleGattServices & BleDevice::getBleGattServices()
{
	return bleGattServices;
}
