#pragma once
#include <fstream>

using namespace std;

class FileHandler
{
public:
	FileHandler();
	virtual ~FileHandler();

	void openFile(fstream & file, string fileName);
	static void readOpenFile(ifstream& readfile, const char* fileName);
};

