#pragma once
#include "IMapFactory.h"

class MapSimpleFactory : public IMapFactory
{
public:
	virtual IMap * createMap();
};