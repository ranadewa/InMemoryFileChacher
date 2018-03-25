#include "stdafx.h"
#include "ItemFileWrapper.h"
#include <sstream>


ItemFileWrapper::ItemFileWrapper(string itemFileName)
{
	_itemFileName = itemFileName;

	openItemFile();

	createItemsMap();

	closeFile(_itemFile);
}

void ItemFileWrapper::createItemsMap()
{
	double value = 0;
	int i = 1;

	string line; 
	try
	{
		while (std::getline(_itemFile , line))
		{
			value = (line.empty()) ? gd_NAN : atof(line.c_str());

			_itemsMap.insert({ i, value });
			i++;
		}
	}
	catch (std::ifstream::failure e)
	{
		if (!_itemFile.eof())
		{
			cerr << "Error in Reading the File " << endl;
			cerr << e.what() << endl;
		}
	}

	cout << "Item File Entries Loaded to the map. size = " << _itemsMap.size() << endl;
}

void ItemFileWrapper::openItemFile()
{
	try
	{
		openFile(_itemFile, _itemFileName.c_str());
	}
	catch (std::ifstream::failure e) {
		throw e;
	}
}

ItemFileWrapper::~ItemFileWrapper()
{
	closeFile(_itemFile);
}

double ItemFileWrapper::readAndSubScribe(int key, DirtyCacheSubscriber * dcSubscriber)
{
	double value = 0;

	lock_guard<mutex> lock(_mapMutex);

	auto itemsItr = _itemsMap.find(key);

	if (itemsItr != _itemsMap.end())
	{
		value = _itemsMap[key];
	}
	else
	{
		cerr << "Unknown value lookup on for key " << key << endl;

		return gd_NAN;
	}

	ExternalMemory::subscribe(key, value,  dcSubscriber);

	return value;
}

void ItemFileWrapper::writeValue(int key, double value)
{
	lock_guard<mutex> lock(_mapMutex);

	auto itemsItr = _itemsMap.find(key);

	if (itemsItr == _itemsMap.end())
	{
		_itemsMap.insert({ key, value });
	}
	else
	{
		_itemsMap[key] = value;
	}

	ExternalMemory::markAsDirty(key, value);
}

void ItemFileWrapper::onFileProcessingComplete()
{
	ofstream itemfile;

	try
	{
		openFile(itemfile, _itemFileName.c_str());
	}
	catch (std::ifstream::failure e) {
		throw e;
	}

	for (auto itemsIter : _itemsMap)
	{
		string outLine = ((itemsIter.second != gd_NAN) ? std::to_string(itemsIter.second) :"") + "\n";

		try
		{
			itemfile.write(outLine.c_str(), outLine.size());
		}
		catch (std::ifstream::failure e)
		{
			cerr << "Error in Writing  the File " << endl;
			cerr << e.what() << endl;
		}	
	}

	closeFile(itemfile);
}
