
#include "newspaper_real.h"
#include "ad.h"
#include "common.h"
#include <string>

void NewspaperReal::PlaceAd(Ad * ad)
{
	adList.push_back(ad);
	ad->RegisterPlacement(this);
}

void NewspaperReal::RemoveAd(Ad * ad)
{
	try
	{
		adList = RemoveElement<Ad*>(adList, ad);
	}
	catch(const NotFoundException & e)
	{
		throw AdNotFoundException();
	}
	ad->UnRegisterPlacement(this);
}

