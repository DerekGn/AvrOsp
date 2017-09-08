#include <Windows.h>

#include <string>

using namespace std;

HANDLE getBleInterfaceHandle(GUID interfaceUUID, wstring instanceId);

HANDLE getBleServiceInterfaceHandle(GUID interfaceUUID, wstring instanceId);

void releaseBleInterfaceHandle(HANDLE hInterfaceHandle);