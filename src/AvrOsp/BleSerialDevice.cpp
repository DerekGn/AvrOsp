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

#include <array>

#include "winrt\Windows.Storage.Streams.h"
#include "winrt\Windows.Devices.Bluetooth.h"
#include "winrt\Windows.Devices.Bluetooth.GenericAttributeProfile.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Devices::Bluetooth;

static const GUID UUID_SERIAL_SERVICE = { 0x49535343, 0xFE7D, 0x4AE5,{ 0x8F, 0xA9, 0x9F, 0xAF, 0xD2, 0x05, 0xE4, 0x55 } };
static const GUID UUID_TX_CHARACTERISTIC = { 0x49535343, 0x1E4D, 0x4BD9,{ 0xBA, 0x61, 0x23, 0xC6, 0x47, 0x24, 0x96, 0x16 } };
static const GUID UUID_RX_CHARACTERISTIC = { 0x49535343, 0x1E4D, 0x4BD9,{ 0xBA, 0x61, 0x23, 0xC6, 0x47, 0x24, 0x96, 0x16 } };

IAsyncAction writeDeviceDataAsync(const GattCharacteristic & txCharacteristic, DataWriter writer)
{
	auto status = co_await txCharacteristic.WriteValueAsync(writer.DetachBuffer(), GenericAttributeProfile::GattWriteOption::WriteWithoutResponse);
}

IAsyncAction OpenDeviceAsync(unsigned long long deviceAddress, BluetoothLEDevice & device, 
	GattCharacteristic & txCharacteristic, GattCharacteristic & rxCharacteristic)
{
	device = co_await BluetoothLEDevice::FromBluetoothAddressAsync(deviceAddress);

	auto servicesResult = co_await device.GetGattServicesForUuidAsync(UUID_SERIAL_SERVICE);

	if(servicesResult.Services().Size() == 0)
		throw new ErrorMsg("Ble serial service not found");

	auto service = servicesResult.Services().GetAt(0);

	auto characteristicsResult = co_await service.GetCharacteristicsForUuidAsync(UUID_TX_CHARACTERISTIC);

	if (characteristicsResult.Characteristics().Size() == 0)
		throw new ErrorMsg("Ble serial tx characteristic not found");

	txCharacteristic = characteristicsResult.Characteristics().GetAt(0);

	characteristicsResult = co_await service.GetCharacteristicsForUuidAsync(UUID_RX_CHARACTERISTIC);

	if (characteristicsResult.Characteristics().Size() == 0)
		throw new ErrorMsg("Ble serial rx characteristic not found");

	rxCharacteristic = characteristicsResult.Characteristics().GetAt(0);
}

BleSerialDevice::BleSerialDevice(unsigned long long _deviceAddress) :
	deviceAddress(_deviceAddress)
{
}

BleSerialDevice::~BleSerialDevice()
{
	if (device != nullptr)
		device.Close();
}

void BleSerialDevice::openChannel()
{
	OpenDeviceAsync(deviceAddress, device, txCharacteristic, rxCharacteristic).GetResults();

	rxCharacteristic.ValueChanged([&](GattCharacteristic characteristic, GattValueChangedEventArgs eventArgs)
	{
		auto reader = DataReader::FromBuffer(eventArgs.CharacteristicValue());

		for (int i = 0; i < reader.UnconsumedBufferLength(); i++)
		{
			buffer.push_back(reader.ReadByte());
		}
	});

	channelOpen = true;
}

void BleSerialDevice::closeChannel()
{
	if (device != nullptr && channelOpen)
		device.Close();

	channelOpen = false;
}

void BleSerialDevice::sendByte(long data)
{
	if (!channelOpen)
		throw new ErrorMsg("Channel not open! Cannot send to unopened channel.");

	DataWriter writer;
	writer.WriteByte(data);
	writeDeviceDataAsync(txCharacteristic, writer).get();
}

long BleSerialDevice::getByte()
{
	if(buffer.size() < 0)
	{ 
	}

	long result = buffer.front();
	buffer.pop_front();
	return result;
}

void BleSerialDevice::flushTX()
{
}

void BleSerialDevice::flushRX()
{
}

void BleSerialDevice::sendMultiple(unsigned char * data, long bufsize)
{
	if (!channelOpen)
		throw new ErrorMsg("Channel not open! Cannot send to unopened channel.");
}
