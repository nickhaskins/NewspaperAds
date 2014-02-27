
#include "ad_real.h"
#include "remove_element.h"

void AdReal::RegisterPlacement(const Newspaper * newspaper)
{
	placements.push_back(newspaper);
}

void AdReal::UnRegisterPlacement(const Newspaper * newspaper)
{
	try
	{
		placements = RemoveElement(placements, newspaper);
	}
	catch(const NotFoundException &e)
	{
		throw PlacementNotFoundException();
	}
}

