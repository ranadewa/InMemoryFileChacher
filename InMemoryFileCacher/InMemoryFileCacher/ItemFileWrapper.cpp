#include "stdafx.h"
#include "ItemFileWrapper.h"


ItemFileWrapper::ItemFileWrapper(string itemFileName)
{
	try
	{
		FileHandler::openFile(_itemFile, itemFileName);
	}
	catch (std::ifstream::failure e) {
		throw e;
	}
}

ItemFileWrapper::~ItemFileWrapper()
{
}

double ItemFileWrapper::readAndSubScribe(int key, DirtyCacheSubscriber * dcSubscriber)
{
	double value = 0;

	ExternalMemory::subscribe(key, value,  dcSubscriber);

	return value;
}

void ItemFileWrapper::writeValue(int key, double value)
{
	ExternalMemory::markAsDirty(key, value);
}
