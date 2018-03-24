#pragma once
#include "ItemFileProcessor.h"

/*
	Below class reads the readerfile given and looks up the indices in the reader f
*/
class ItemFileReader :public ItemFileProcessor
{
public:
	ItemFileReader(string readFileName, string itemFileName);
	virtual ~ItemFileReader();

	void processFile() override;

protected:
	void closeFiles() override;

private:
	ItemFileReader();
	void openOutputFile(std::string readFileName);

	ofstream _outputFile;


};

