#include "stdafx.h"
#include "DirtyCacheHandler.h"


DirtyCacheHandler::DirtyCacheHandler()
{
}


DirtyCacheHandler::~DirtyCacheHandler()
{
	clear();
}

void DirtyCacheHandler::subscribe(int key, double value, DirtyCacheSubscriber * dcSubscriber)
{
	auto cacheSubIter = _cacheSubscribers.find(key);

	if (cacheSubIter != _cacheSubscribers.end()) // subscriber list already exists
	{
		list<DirtyCacheSubscriber*>* subscribers = cacheSubIter->second.second;
		subscribers->push_back(dcSubscriber);
	}
	else
	{
		list<DirtyCacheSubscriber*>* newSubscriberlist = new list<DirtyCacheSubscriber*>; // USE an Object pool
		newSubscriberlist->push_back(dcSubscriber);
		_cacheSubscribers.insert({ key,{ value, newSubscriberlist } });
	}

}

void DirtyCacheHandler::unSubscribe(int key, DirtyCacheSubscriber * dcSubscriber)
{
	auto cacheSubIter = _cacheSubscribers.find(key);

	if (cacheSubIter != _cacheSubscribers.end())
	{
		list<DirtyCacheSubscriber*>* subscribers = cacheSubIter->second.second;

		subscribers->remove(dcSubscriber);

		if (subscribers->empty())
		{
			delete subscribers;
			_cacheSubscribers.erase(key);
		}
	}
	else
	{
		// Todo Error path
	}
}

void DirtyCacheHandler::markAsDirty(int key, double value)
{
	auto cacheSubIter = _cacheSubscribers.find(key);

	if (cacheSubIter != _cacheSubscribers.end()) // Subscribers found for the given iterator 
	{
		cacheSubIter->second.first = value;

		list<DirtyCacheSubscriber*>* subscribers = cacheSubIter->second.second;

		for (auto listItr = subscribers->begin(); listItr != subscribers->end(); listItr++)
		{
			(*listItr)->_isDirtyCache = true;
		}
	}
}

double DirtyCacheHandler::getValue(int key, DirtyCacheSubscriber* dcSubscriber)
{
	auto cacheSubIter = _cacheSubscribers.find(key);

	if (cacheSubIter != _cacheSubscribers.end())
	{
		dcSubscriber->_isDirtyCache = false; // Updated Value return

		return cacheSubIter->second.first;
	}

	return 0.0; // Error
}

void DirtyCacheHandler::clear()
{
	for (auto mapIter = _cacheSubscribers.begin(); mapIter != _cacheSubscribers.end(); mapIter++)
	{
		list<DirtyCacheSubscriber*>* subscribers = mapIter->second.second;

		if (subscribers != nullptr)
		{
			delete subscribers;
		}		
	}
}
