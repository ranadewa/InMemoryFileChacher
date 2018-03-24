#include "stdafx.h"
#include "FileHandler.h"


FileHandler::FileHandler()
{
}


FileHandler::~FileHandler()
{
}

void FileHandler::openFile(fstream & file, string fileName)
{
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		file.open(fileName.c_str());
	}
	catch (std::ifstream::failure e) {
		throw e;
	}
}

void FileHandler::readOpenFile(ifstream & readfile, const char * fileName)
{
	readfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		readfile.open(fileName);
	}
	catch (std::ifstream::failure e) {

		throw e;
	}
}
