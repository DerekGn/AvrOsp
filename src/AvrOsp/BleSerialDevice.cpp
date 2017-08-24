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
* Description       : A class providing serial communication through a paired Ble device.
*                     This class is derived from the CommChannel abstract class.
*
*
****************************************************************************/

#include "BleSerialDevice.hpp"

HANDLE BleSerialDevice::GetBleHandle(GUID deviceServiceGuid)
{
	HDEVINFO hDI;
	SP_DEVICE_INTERFACE_DATA did;
	SP_DEVINFO_DATA dd;
	GUID bluetoothInterfaceGUID = deviceServiceGuid;
	HANDLE hComm = NULL;

	hDI = SetupDiGetClassDevs(&bluetoothInterfaceGUID, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (hDI == INVALID_HANDLE_VALUE)
		throw new ErrorMsg("Unable to open ble device information handle");

	did.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	dd.cbSize = sizeof(SP_DEVINFO_DATA);

	for (DWORD i = 0; SetupDiEnumDeviceInterfaces(hDI, NULL, &bluetoothInterfaceGUID, i, &did); i++) {
		SP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData;

		DeviceInterfaceDetailData.cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

		DWORD size = 0;

		if (!SetupDiGetDeviceInterfaceDetail(hDI, &did, NULL, 0, &size, 0)) {
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
	return hComm;
}

PBTH_LE_GATT_SERVICE BleSerialDevice::GetBleDeviceServices(HANDLE hBleDevice, USHORT* pgattServiceCount)
{
	char buffer[50];
	USHORT serviceBufferCount;
	////////////////////////////////////////////////////////////////////////////
	// Determine Services Buffer Size
	////////////////////////////////////////////////////////////////////////////

	HRESULT hr = BluetoothGATTGetServices(
		hBleDevice,
		0,
		NULL,
		&serviceBufferCount,
		BLUETOOTH_GATT_FLAG_NONE);

	if (HRESULT_FROM_WIN32(ERROR_MORE_DATA) != hr) {
		sprintf_s(buffer, "BluetoothGATTGetServices - Buffer Size 0x%x", hr);
		throw new ErrorMsg(buffer);
	}

	PBTH_LE_GATT_SERVICE pServiceBuffer = (PBTH_LE_GATT_SERVICE)
		malloc(sizeof(BTH_LE_GATT_SERVICE) * serviceBufferCount);

	if (NULL == pServiceBuffer)
		throw new ErrorMsg("pServiceBuffer out of memory\r\n");
	else
		RtlZeroMemory(pServiceBuffer, sizeof(BTH_LE_GATT_SERVICE) * serviceBufferCount);
	
	////////////////////////////////////////////////////////////////////////////
	// Retrieve Services
	////////////////////////////////////////////////////////////////////////////

	USHORT numServices;
	hr = BluetoothGATTGetServices(
		hBleDevice,
		serviceBufferCount,
		pServiceBuffer,
		&numServices,
		BLUETOOTH_GATT_FLAG_NONE);

	if (S_OK != hr) {
		sprintf_s(buffer, "BluetoothGATTGetServices - Buffer Size 0x%x", hr);
		throw new ErrorMsg(buffer);
	}

	return pServiceBuffer;
}

//BleSerialDevice::BleSerialDevice(GUID bleDeviceInterfaceId)
//{
//	/*if (deviceServiceUUID.length() == 0)
//		throw new ErrorMsg("Device service UUID cannot be empty!");
//
//	if (deviceServiceUUID.length() < 32)
//		throw new ErrorMsg("Device service UUID cannot be less than 32 characters!");
//
//	HRESULT err = CLSIDFromString(wstring(deviceServiceUUID.begin(), deviceServiceUUID.end()).c_str(), &deviceServiceGuid);
//
//	if(err != NOERROR)
//		throw new ErrorMsg("Device service UUID is incorrectly formatted guid");*/
//}

BleSerialDevice::BleSerialDevice(BleSerialDeviceDescriptor _bleSerialDeviceDescriptor)
{
	bleSerialDeviceDescriptor = _bleSerialDeviceDescriptor;
}

BleSerialDevice::~BleSerialDevice()
{
	if(hBleDevice != NULL)
		CloseHandle(hBleDevice);
}

void BleSerialDevice::openChannel()
{
	/*hBleDevice = GetBleHandle(deviceServiceGuid);

	pServicesBuffer = GetBleDeviceServices(hBleDevice, &gattServiceCount);

	pCharacteristicsBuffer = GetBleDeviceCharacteristics(hBleDevice, pServicesBuffer, &gattCharacteristicCount);*/
}

void BleSerialDevice::closeChannel()
{
}

void BleSerialDevice::sendByte(long data)
{
}

long BleSerialDevice::getByte()
{
	return 0;
}

void BleSerialDevice::flushTX()
{
}

void BleSerialDevice::flushRX()
{
}

void BleSerialDevice::sendMultiple(unsigned char * data, long bufsize)
{
}
