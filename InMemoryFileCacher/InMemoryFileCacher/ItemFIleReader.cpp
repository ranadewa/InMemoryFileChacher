#include "stdafx.h"
#include "ItemFileReader.h"


ItemFileReader::ItemFileReader(string readFileName, string itemFileName)
{

	try {
		ItemFileProcessor::ItemFileProcessor(readFileName, itemFileName, true);

		openOutputFile(readFileName);
	}
	catch (std::ifstream::failure e){

		closeFiles();

		throw e;
	}

}

void ItemFileReader::openOutputFile(std::string readFileName)
{
	int readNameLength = readFileName.length();

	string outputfileName = readFileName.substr(0, readNameLength - 4) + ".out.txt";

	_outputFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
			_outputFile.open(outputfileName.c_str());
	}
	catch (std::ifstream::failure e) {
		throw e; 
	}

	
}

ItemFileReader::~ItemFileReader()
{
}

void ItemFileReader::processFile()
{
	

}

void ItemFileReader::closeFiles()
{
	ItemFileProcessor::closeFiles();

	if (_outputFile.is_open())
	{
		_outputFile.close();
	}
}
