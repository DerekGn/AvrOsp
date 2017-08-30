#include "BleFunctions.hpp"
#include "Utility.hpp"

#include <windows.h>
#include <Setupapi.h>
#include <BluetoothAPIs.h>

#pragma comment(lib, "Rpcrt4")
#pragma comment(lib, "SetupAPI")
#pragma comment(lib, "BluetoothAPIs")

#include <sstream>

HANDLE getBleInterfaceHandle(GUID interfaceUUID, wstring instanceId)
{
	HDEVINFO hDI;
	SP_DEVICE_INTERFACE_DATA did;
	SP_DEVINFO_DATA dd;
	HANDLE hComm = NULL;

	hDI = SetupDiGetClassDevs(&interfaceUUID, &instanceId[0], NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);

	if (hDI == INVALID_HANDLE_VALUE)
	{
		stringstream msg;
		msg << "Unable to open device information set for device interface UUID: ["
			<< Util.guidToString(interfaceUUID) << "] Reason: ["
			<< Util.getLastError() << "]";

		throw new ErrorMsg(msg.str());
	}

	did.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
	dd.cbSize = sizeof(SP_DEVINFO_DATA);

	DWORD i = 0;

	for (i = 0; SetupDiEnumDeviceInterfaces(hDI, NULL, &interfaceUUID, i, &did); i++)
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
			<< Util.guidToString(interfaceUUID) << "] not found";

		throw new ErrorMsg(msg.str());
	}

	return hComm;
}

void releaseBleInterfaceHandle(HANDLE hinterfaceHandle)
{
	if(hinterfaceHandle)
		SetupDiDestroyDeviceInfoList(hinterfaceHandle);
}
