#pragma once

#include "ExternalMemory.h"
#include "FileHandler.h"

using namespace std;

class ItemFileWrapper: public ExternalMemory, public FileHandler
{
public:
	ItemFileWrapper(string itemFileName);
	virtual ~ItemFileWrapper();

	double	readAndSubScribe(int key, DirtyCacheSubscriber* dirtyCacheHandler) override;
	void	writeValue(int key, double value);

private:
	fstream _itemFile;
	
};

