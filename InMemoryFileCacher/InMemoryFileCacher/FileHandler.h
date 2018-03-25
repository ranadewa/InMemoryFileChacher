#pragma once
#include <fstream>
#include <iostream>

using namespace std;

class ItemFileWrapper;

class InputFileHandler {

public:
	InputFileHandler() {};
	InputFileHandler(string readFileName, ItemFileWrapper* itemFileWrapper);
	~ InputFileHandler();

	virtual void processFile() {};

protected:
	void openInputFile(string readFileName);

	ifstream _inputFile;
	ItemFileWrapper* _itemFile = nullptr;

private: 
	
};

template <typename T>
void openFile(T & file, const char* fileName)
{
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(fileName);
	}
	catch (std::ifstream::failure e) {
		throw e;
	}
}

template<typename T>
void closeFile(T& file)
{
	if (file.is_open())
	{
		file.close();
	}
}



