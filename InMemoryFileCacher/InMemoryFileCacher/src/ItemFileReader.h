#pragma once
#include <iostream>

#include "LRUCache.h"
#include "ItemFileProcessor.h"
#include "ItemFileWrapper.h"
#include "FileHandler.h"
#include "InfoThreads.h"

using namespace std;
/*
	Below class reads the readerfile given and looks up the indices in the reader f
*/
class ItemFileReader  : public InputFileHandler
{
public:
	ItemFileReader(string readFileName, const InfoThreads & info);
	virtual ~ItemFileReader();

	void processFile() override;

protected:
	void closeFiles() ;

private:
	ItemFileReader();
	void openOutputFile(string readFileName);

	ofstream _outputFile;
	LRUCache* _cache = nullptr;
};

