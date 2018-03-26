#include "stdafx.h"
#include "ExternalMemory.h"


ExternalMemory::ExternalMemory()
{
}


ExternalMemory::~ExternalMemory()
{
}

double ExternalMemory::getUpdatedValue(int key, DirtyCacheSubscriber * dcSubscriber)
{
	return _dirtyCacheHandler.getValue(key, dcSubscriber);
}

void ExternalMemory::unSubScribe(int key, DirtyCacheSubscriber * dcSubscriber)
{
	_dirtyCacheHandler.unSubscribe(key, dcSubscriber);
}

void ExternalMemory::subscribe(int key, double value, DirtyCacheSubscriber * dcSubscriber)
{
	_dirtyCacheHandler.subscribe(key, value, dcSubscriber);
}

void ExternalMemory::markAsDirty(int key, double value)
{
	_dirtyCacheHandler.markAsDirty(key, value);
}
