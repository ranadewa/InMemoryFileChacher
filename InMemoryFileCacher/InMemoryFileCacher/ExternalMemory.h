#pragma once
#include <unordered_map>
#include <list>

#include "DirtyCacheHandler.h"

class ExternalMemory {

public:
	ExternalMemory();
	~ExternalMemory();

	virtual double	readAndSubScribe(int key, DirtyCacheSubscriber* dcSubscriber) { return 0; };
	double  getUpdatedValue(int key, DirtyCacheSubscriber* dcSubscriber);
	void	unSubScribe(int key, DirtyCacheSubscriber* dcSubscriber);

protected: 
	void subscribe(int key, double value, DirtyCacheSubscriber*  dcSubscriber);
	void markAsDirty(int key, double value);

private:
	DirtyCacheHandler _dirtyCacheHandler;
};


