#include "stdafx.h"
#include "LRUCache.h"



LRUCache::LRUCache(int cacheSize, ExternalMemory * extMemory)
{
	_cacheSize = cacheSize;
	_extMemory = extMemory;

	_lruKeys.clear();
	_cache.clear();
}
LRUCache::~LRUCache()
{
}

double LRUCache::getValue(int key)
{
	auto cacheIterator = _cache.find(key);

	if (cacheIterator == _cache.end() )  //key not found in the cache get it from the external MemoryLocation
	{
		double value = _extMemory->readAndSubScribe(key, this);

		addNewValue(key, value);

		return value;
	}
	
	// Value exists get it to the front
	updateCache(cacheIterator);

	return cacheIterator->second.first;
}

void LRUCache::setValue(int key, double value)
{
	auto cacheIterator = _cache.find(key);

	if (cacheIterator != _cache.end())  // Item exist for that index. Update the same
	{
		updateCache(cacheIterator);
		_cache[key] = { value, _lruKeys.begin() };
	}
	else {

		addNewValue(key, value);
	}	
}

void LRUCache::addNewValue(int &key, double &value)
{
	if (_lruKeys.size() == _cacheSize)  // Max size breached. Remove the last element. 
	{
		int key = _lruKeys.back();
		_lruKeys.pop_back();

		_cache.erase(key);
		_extMemory->unSubScribe(key, this);
	}

	_lruKeys.push_front(key);
	_cache.insert({ key,{ value, _lruKeys.begin() } });
}

void LRUCache::updateCache(CACHE_ITR& cacheIterator)
{
	_lruKeys.erase(cacheIterator->second.second);  // Remove it from the current position

	_lruKeys.push_front(cacheIterator->first); // add the key as the front element

	if (isDirtyCache())  // Check if cache is made Dirty externally
	{
		double newValue = _extMemory->getUpdatedValue(cacheIterator->first, this);

		cacheIterator->second.first = newValue;
	}

	cacheIterator->second.second = _lruKeys.begin(); // update the cache
}
