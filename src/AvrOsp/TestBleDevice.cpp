// TestBleDevice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <rpc.h>

#pragma comment(lib, "Rpcrt4.lib")

#include "ErrorMsg.hpp"
#include "Utility.hpp"
#include "BleDevice.hpp"
#include "BleDeviceEnumerator.hpp"
#include "BleSerialDeviceDescriptor.hpp"

using namespace std;

#include <iostream>  
#include <iomanip>

int main()
{
	try
	{
		GUID serialInCharacteristicUUID;
		GUID serialOutCharacteristicUUID;

		RPC_STATUS ret = UuidFromString((RPC_WSTR)L"00001800-0000-0000-0000-000000000000", &serialInCharacteristicUUID);
		ret = UuidFromString((RPC_WSTR)L"781aee18-7733-4ce4-add0-91f41c67b592", &serialOutCharacteristicUUID);

		BleSerialDeviceDescriptor bleSerialDeviceDescriptor = BleSerialDeviceDescriptor("RN4870", serialInCharacteristicUUID, serialOutCharacteristicUUID);
		
		BleEnumerator.enumerate();

		for (BleDeviceInfo *i : BleEnumerator.getBleDevices())
			wcout << "Name: " << i->getName()
			<< " HardwareId: " << i->getHardwareId()
			<< " InstanceId: " << i->getInstanceId() << endl;
		
		cout << "Opening device" << endl;

		//GUID_BLUETOOTHLE_DEVICE_INTERFACE


		BleDevice bleDevice = BleDevice(BleEnumerator.getBleDevices().front()->getInstanceId());
		
		cout << "BleGattServices Count: " << bleDevice.getBleGattServices().size() << endl;

		for (BleGattService *s : bleDevice.getBleGattServices())
		{
			cout << "\tService - Guid: " << Util.guidToString(s->getServiceUuid().Value.LongUuid) << setbase(16) << " Short Id:" << s->getServiceUuid().Value.ShortUuid << endl;

			for (BleGattCharacteristic *c : s->getBleCharacteristics())
			{
				cout << "\t\tCharacteristic - Guid: " << Util.guidToString(c->getCharacteristicUuid().Value.LongUuid) << setbase(16) << " Short Id:" << c->getCharacteristicUuid().Value.ShortUuid << endl;

				if(c->getIsReadable())
				{
					BleGattCharacteristicValue value = c->getValue();
					//delete value;
				}
			}
		}
	}
	catch (ErrorMsg * e)
	{

		cout << endl << "An error occurred:" << endl;
		cout << "  [" << e->What() << "]" << endl;
		delete e;
	}


    return 0;
}

