#pragma once

#include "ItemFileWrapper.h"
#include "FileHandler.h"
#include "InfoThreads.h"

class ItemFileWriter : public InputFileHandler
{
public:
	
	ItemFileWriter(string readFileName, const InfoThreads& info);
	virtual ~ItemFileWriter();

	void processFile() override;

private:
	ItemFileWriter() {};
};

