#include "stdafx.h"
#include "FileCache.h"



FileCache::~FileCache()
{
}

double FileCache::getIndex(int index)
{
	auto cacheIterator = _cache.find(index);

	if (cacheIterator == _cache.end() )
	{
		return 0.0;
	}
	
	// Value exists get it to the front
	updateCache(cacheIterator);

	return cacheIterator->second.first;
}

void FileCache::setValue(int key, double value)
{
	auto cacheIterator = _cache.find(key);

	if (cacheIterator != _cache.end())  // Item exist for that index. Update the same
	{
		updateCache(cacheIterator);
		_cache[key] = { value, _lruKeys.begin() };
	}
	else {

		if (_lruKeys.size() == _cacheSize)  // Max size breached. Remove the last element. 
		{
			int key = _lruKeys.back();
			_lruKeys.pop_back();

			_cache.erase(key);

			cout << key << " removed" << endl;
		}

		_lruKeys.push_front(key);
		_cache.insert({ key, { value, _lruKeys.begin()} });
	}	
}

void FileCache::updateCache(CACHE_ITR& cacheIterator)
{
	_lruKeys.erase(cacheIterator->second.second);  // Remove it from the current position

	_lruKeys.push_front(cacheIterator->first); // add the key as the front element

	cacheIterator->second.second = _lruKeys.begin(); // update the cache
}
