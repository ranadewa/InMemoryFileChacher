#include "stdafx.h"
#include "FileHandler.h"

InputFileHandler::InputFileHandler(string readFileName, ItemFileWrapper* itemFileWrapper)
{
	_itemFile = itemFileWrapper;
	openInputFile(readFileName);
}

InputFileHandler::~InputFileHandler()
{
	closeFile(_inputFile);
}

void InputFileHandler::openInputFile(string readFileName)
{
	try
	{
		openFile(_inputFile, readFileName.c_str());
	}
	catch (std::ifstream::failure e)
	{
	 	cerr << "Error opening the Reader file "<<  readFileName.c_str()  << endl;
		throw e;
	}
}
