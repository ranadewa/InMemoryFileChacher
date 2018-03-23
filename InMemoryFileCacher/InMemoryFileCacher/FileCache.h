#pragma once
#include <list>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef list<int>::iterator					KEY_ITERATOR;
typedef pair<double, KEY_ITERATOR>			VALUE_KI_PAIR;
typedef unordered_map<int, VALUE_KI_PAIR>	CACHE;
typedef CACHE::iterator						CACHE_ITR;

class FileCache  // TODO Try using template class
{
public:
	FileCache(int cacheSize) { _cacheSize = cacheSize;  }
	virtual ~FileCache();

	double getIndex(int index);
	void   setValue(int index, double value);

private :
	list<int> _lruKeys;
	CACHE _cache;
	int	  _cacheSize;

	void updateCache(CACHE_ITR & cacheIterator);
};

