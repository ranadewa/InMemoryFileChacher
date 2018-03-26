#include "stdafx.h"
#include "ItemFileReader.h"

ItemFileReader::ItemFileReader(string readFileName,const InfoThreads & info) : InputFileHandler(readFileName, info._itemFile)
{
	openOutputFile(readFileName);

	_cache = new LRUCache(info._cacheSize, info._itemFile);
}

ItemFileReader::~ItemFileReader()
{
	closeFiles();

	delete _cache;
}

void ItemFileReader::processFile()
{
	int key =0;

	try
	{
		while (_inputFile >> key)
		{
			bool cacheHit = false;
			double value = _cache->getValue(key, cacheHit);

			string source = (cacheHit == true) ? "Cache" : "Disk";
			string outLine = std::to_string(value) + " " + source+ "\n";

			_outputFile.write(outLine.c_str(), outLine.size());
		}
	}
	catch (std::ifstream::failure e)
	{
		if (!_inputFile.eof())
		{
			cerr << "Error in Reading the File " << endl;
			cerr << e.what() << endl;
		}
	}

}

void ItemFileReader::closeFiles()
{
	closeFile(_outputFile);
}

void ItemFileReader::openOutputFile(string readFileName)
{
	int readNameLength = readFileName.length();

	string outputfileName = readFileName.substr(0, readNameLength - 4) + ".out.txt";

	try
	{
		openFile(_outputFile, outputfileName.c_str());
	}
	catch (std::ifstream::failure e)
	{
		cerr << "Error opening the write file " << outputfileName << endl;
		throw e;
	}
}
