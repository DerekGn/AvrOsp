#include <Windows.h>

#include <string>

using namespace std;

HANDLE getBleInterfaceHandle(__in GUID interfaceUUID, __in wstring instanceId);

void releaseBleInterfaceHandle(__in HANDLE hinterfaceHandle);