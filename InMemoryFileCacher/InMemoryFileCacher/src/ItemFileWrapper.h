#pragma once

#include <map>
#include <mutex>

#include "ExternalMemory.h"
#include "FileHandler.h"
#include <string>

using namespace std;

class ItemFileWrapper: public ExternalMemory
{
public:
	ItemFileWrapper(string itemFileName);	
	virtual ~ItemFileWrapper();

	double	readAndSubScribe(int key, DirtyCacheSubscriber* dirtyCacheHandler) override;
	void	writeValue(int key, double value);

	void	onFileProcessingComplete();

private:
	mutex  _mapMutex;
	string  _itemFileName;
	fstream _itemFile;
	map<int, double> _itemsMap;

	void createItemsMap();
	void openItemFile();
};

