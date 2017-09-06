#include "BleServiceContext.hpp"

BleServiceContext::BleServiceContext(BleDeviceContext & _bleDeviceContext, HANDLE _hService)
	: bleDeviceContext(_bleDeviceContext)
{
	hService = _hService;
}

BleServiceContext::~BleServiceContext()
{
}

BleDeviceContext BleServiceContext::getBleDeviceContext()
{
	return bleDeviceContext;
}

HANDLE BleServiceContext::getServcieHandle()
{
	return hService;
}
