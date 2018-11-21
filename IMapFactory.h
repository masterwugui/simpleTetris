#pragma once
#include "IMap.h"

class IMapFactory
{
public:
	virtual IMap * createMap() = 0;
};