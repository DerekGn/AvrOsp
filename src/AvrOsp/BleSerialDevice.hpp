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
#ifndef BLEDEVICE_HPP
#define BLEDEVICE_HPP

using namespace std;

//#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <setupapi.h>
#include <devguid.h>
#include <regstr.h>
#include <bthdef.h>
#include <Bluetoothleapis.h>
#pragma comment(lib, "SetupAPI")
#pragma comment(lib, "BluetoothApis.lib")

#include "CommChannel.hpp"
#include "ErrorMsg.hpp"

class BleSerialDevice : public CommChannel
{
	protected:
		HANDLE hBleDevice = NULL;
		GUID deviceServiceGuid;
		PBTH_LE_GATT_SERVICE pServicesBuffer = NULL;
		PBTH_LE_GATT_CHARACTERISTIC pCharacteristicsBuffer = NULL;

	private:
		HANDLE GetBleHandle(__in GUID deviceServiceGuid);
		PBTH_LE_GATT_SERVICE GetBleDeviceServices(HANDLE hBleDevice);
		PBTH_LE_GATT_CHARACTERISTIC GetBleDeviceCharacteristics(HANDLE hBleDevice, PBTH_LE_GATT_SERVICE pServicesBuffer);

	public:
		BleSerialDevice(string deviceServiceUUID);

		~BleSerialDevice();

		// Open the communication channel.
		virtual void openChannel();

		// Close the communication channel.
		virtual void closeChannel();

		// Transmit a single byte.
		virtual void sendByte(long data);

		// Receive a single byte.
		virtual long getByte();

		// Flush the transmit buffer.
		virtual void flushTX();

		// Flush the receive buffer.
		virtual void flushRX();

		// Transmit multiple bytes.
		virtual void sendMultiple(unsigned char * data, long bufsize);
};
#endif
