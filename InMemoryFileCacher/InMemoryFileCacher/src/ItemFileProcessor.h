#pragma once
#include <string>
#include <fstream>
using namespace std;

class ItemFileProcessor
{
public:
	ItemFileProcessor() {};
	ItemFileProcessor(string readFileName, string itemFileName, bool readItemFile);
	virtual ~ItemFileProcessor();

	virtual void processFile() {};


protected:
	virtual void closeFiles();

	ifstream _readFile;
	fstream  _itemFile;

private :
	
};

