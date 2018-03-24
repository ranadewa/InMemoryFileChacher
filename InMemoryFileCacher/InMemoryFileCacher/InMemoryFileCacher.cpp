// InMemoryFileCacher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "FileCache.h"
#include "ItemFileReader.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cerr << "Error in running the binary " << endl;
		cerr << "Format : cache <size_of_cache>  <reader_file>  <writer_file>  <items_file> " << endl;
		return 0;
	}

	int cacheSize = atoi(argv[1]);

	if (cacheSize == 0)
	{
		cerr << "Invalid Cache Size " << argv[1] << endl;
		return 0;
	}

	const char* readerFileName = argv[2];
	const char* writerFileName = argv[3];
	const char* itemFileName = argv[4];

	ifstream readerFile;
	ifstream writerFile;

	try
	{
		ItemFileWrapper itemFileWrapper(itemFileName);
	}
	catch (std::ifstream::failure e)
	{
		cerr << "Error opeining the item file " << itemFileName << endl;
		cerr << e.what() << endl;
		return 0;
	}

	try
	{
		FileHandler::readOpenFile(readerFile, readerFileName);
	}
	catch (std::ifstream::failure e)
	{
		cerr << "Error in Opening Reader File " << readerFileName << " to read" << endl;
	}

	try
	{
		FileHandler::readOpenFile(writerFile, writerFileName);
	}
	catch (std::ifstream::failure e)
	{
		cerr << "Error in Opening File " << writerFileName << " to read" << endl;
	}
	

    return 0;
}

