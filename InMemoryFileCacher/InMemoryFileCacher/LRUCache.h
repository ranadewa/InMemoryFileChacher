#pragma once
#include <list>
#include <unordered_map>
#include <iostream>

#include "DirtyCacheHandler.h"
#include "ExternalMemory.h"

using namespace std;

typedef list<int>::iterator					KEY_ITERATOR;
typedef pair<double, KEY_ITERATOR>			VALUE_KI_PAIR;
typedef unordered_map<int, VALUE_KI_PAIR>	CACHE;
typedef CACHE::iterator						CACHE_ITR;

class LRUCache : public DirtyCacheSubscriber // TODO Try using template class
{
public:
	LRUCache(int cacheSize, ExternalMemory* extMemory);
	virtual ~LRUCache();

	double getValue(int key);
	void   setValue(int key, double value);

private :
	list<int> _lruKeys;
	CACHE _cache;
	int	  _cacheSize;

	ExternalMemory* _extMemory = nullptr;

	void updateCache(CACHE_ITR & cacheIterator);
	void addNewValue(int &key, double &value);
};

