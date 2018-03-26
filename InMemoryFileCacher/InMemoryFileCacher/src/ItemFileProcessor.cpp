#include "stdafx.h"
#include "ItemFileProcessor.h"

ItemFileProcessor::ItemFileProcessor(string readFileName, string itemFileName, bool readItemFile)
{

	_readFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	_itemFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		_readFile.open(readFileName.c_str());

		ios_base::openmode mode = (readItemFile == true) ? ios::in : ios::out;
		_itemFile.open(itemFileName.c_str(), mode);
	}
	catch (std::ifstream::failure e) {
		closeFiles();
		throw e;
	}


}

ItemFileProcessor::~ItemFileProcessor()
{
	closeFiles();
}

void ItemFileProcessor::closeFiles()
{
	if (_readFile.is_open())
	{
		_readFile.close();
	}

	if (_itemFile.is_open())
	{
		_itemFile.close();
	}
}
