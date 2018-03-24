#pragma once
#include <atomic>
#include <unordered_map>
#include <list>

using namespace std;
class DirtyCacheHandler;

class DirtyCacheSubscriber {

	friend class DirtyCacheHandler;

public:
	DirtyCacheSubscriber() { _isDirtyCache = false; }
	
	bool isDirtyCache() { return _isDirtyCache; }

private:
	atomic<bool> _isDirtyCache;
};

class DirtyCacheHandler
{
public:
	DirtyCacheHandler();
	virtual ~DirtyCacheHandler();

	void subscribe(int key, double value, DirtyCacheSubscriber* dcSubscriber);
	void unSubscribe(int key, DirtyCacheSubscriber* dcSubscriber);
	void markAsDirty(int key, double value);
	double getValue(int key, DirtyCacheSubscriber* dcSubscriber);

private:
	unordered_map<int, pair<double, list<DirtyCacheSubscriber*>* >> _cacheSubscribers;
	void clear();
};

