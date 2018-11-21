#include "MapSimpleFactory.h"
#include "BaseMap.h"

IMap * MapSimpleFactory::createMap()
{
	return new BaseMap(10, 15);
}
