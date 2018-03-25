#pragma once
#include "ItemFileWrapper.h"

class InfoThreads
{
public:
	InfoThreads(ItemFileWrapper* itemfile, int cacheSize) { _itemFile = itemfile; _cacheSize = cacheSize; };
	~InfoThreads() {};

	ItemFileWrapper* _itemFile = nullptr;
	int				 _cacheSize = 1;
};



