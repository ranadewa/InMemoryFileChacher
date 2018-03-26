#include "stdafx.h"
#include "ItemFileWriter.h"


ItemFileWriter::ItemFileWriter(string readFileName, const InfoThreads& info) : InputFileHandler(readFileName, info._itemFile)
{

}

ItemFileWriter::~ItemFileWriter()
{
}

void ItemFileWriter::processFile()
{
	int key = 0 ;
	double value = 0;

	try
	{
		while (_inputFile >> key >> value)
		{
			_itemFile->writeValue(key, value);
		}
	}
	catch (std::ifstream::failure e)
	{
		if (!_inputFile.eof())
		{
			cerr << "Error in Reading the File " << endl;
			cerr << e.what() << endl;

			throw e;
		}
	}
}
