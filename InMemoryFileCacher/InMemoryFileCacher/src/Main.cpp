// InMemoryFileCacher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <algorithm>
#include <thread>
#include <iostream>
#include <vector> 

#include "ItemFileWrapper.h"
#include "ItemFileReader.h"
#include "ItemFileWriter.h"
#include "InfoThreads.h"

using namespace std;

template<typename T>
void processFile(const char * readerFileName, const InfoThreads & info, list<T*> &itemFileprocessors,	
											  vector<thread *> &threads)
{
	ifstream readerFile;
	try
	{
		openFile(readerFile, readerFileName);

		string readLine;

		while (std::getline(readerFile, readLine))
		{
			try
			{
				T* ifProcessor = new T(readLine, info);
				itemFileprocessors.push_back(ifProcessor);

				thread* t = new thread(&T::processFile, ifProcessor);
				threads.push_back(t);

				cout << "Thread " << t->get_id() << " Created" << endl;

			}
			catch (std::ifstream::failure e)
			{
				cerr << "ItemFile Processors not created for " << readLine << endl;
				cerr << e.what() << endl;
			}
		}
	}
	catch (std::ifstream::failure e)
	{
		if (!readerFile.eof())
		{
			cerr << "Error in Opening Reader File " << readerFileName << " to read" << endl;
			cerr << e.what() << endl;
		}
	}
}

void cleanUpMemory(list<ItemFileReader *> &itemFileReaders, list<ItemFileWriter *> &itemFileWriters, ItemFileWrapper * itemFileWrapper, vector<thread *> &threads)
{
	for_each(itemFileReaders.begin(), itemFileReaders.end(), [](ItemFileReader* reader) { delete reader; });

	for_each(itemFileWriters.begin(), itemFileWriters.end(), [](ItemFileWriter* writer) { delete writer; });

	delete itemFileWrapper;

	for_each(threads.begin(), threads.end(), [](thread* th) {	delete	th; });
}


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

	cout << "Processing Started...." << endl;

	const char* itemFileName = argv[4];
	ItemFileWrapper* itemFileWrapper = nullptr;

	try
	{
		itemFileWrapper = new ItemFileWrapper (itemFileName);
		cout << "Item Wrapper File Created" << endl;
	}
	catch (std::ifstream::failure e)
	{
		cerr << "Error opeining the item file " << itemFileName << endl;
		cerr << e.what() << endl;
		return 0;
	}

	vector<thread*> threads;
	const char* readerFileName = argv[2];
	list<ItemFileReader*> itemFileReaders;
	InfoThreads info(itemFileWrapper, cacheSize);
	
	cout << "Loading Reader files." << endl;

	processFile(readerFileName, info, itemFileReaders, threads);

	const char* writerFileName = argv[3];
	list<ItemFileWriter*> itemFileWriters;

	cout << "Loading Writer files." << endl;

	processFile(writerFileName, info, itemFileWriters, threads);

	for_each(threads.begin(), threads.end(), [](thread* th) { 
		if (th->joinable())
		{
			th->join();
		}
	});

	cout << "Reader File Processing Completed" << endl;

	itemFileWrapper->onFileProcessingComplete();

	cout << "Item File Regenerated" << endl;

	cleanUpMemory(itemFileReaders, itemFileWriters, itemFileWrapper, threads);

    return 0;
}

