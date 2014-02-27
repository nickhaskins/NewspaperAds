#include <iostream>
#include <vector>

#include "newspaper_real.h"
#include "ad_real.h"

int main()
{
    std::vector<NewspaperReal> newspapers;
    newspapers.push_back(NewspaperReal("The Guardian"));
    newspapers.push_back(NewspaperReal("The New York Times"));

    std::vector<AdReal> ads;
    ads.push_back(AdReal("Buy now!"));
    ads.push_back(AdReal("Only 3 days left!"));

    newspapers[0].PlaceAd(&ads[0]);
    newspapers[0].PlaceAd(&ads[1]);
    newspapers[1].PlaceAd(&ads[0]);

    for(
        std::vector<NewspaperReal>::iterator it = newspapers.begin();
        it != newspapers.end();
        ++it
        )
    {
        std::cout << "The newspaper '" << it->GetName() << "' has the following ads:" << std::endl;

        std::vector<Ad *> adList = it->GetAdList();
        for(
            std::vector<Ad *>::iterator subit = adList.begin();
            subit != adList.end();
            ++subit
            )
        {
            const Ad * ad = *subit;
            std::cout << "'" << ad->GetName() << "'" << std::endl;
        }
    }

    std::cout << std::endl;

    for(
        std::vector<AdReal>::iterator it = ads.begin();
        it != ads.end();
        ++it
        )
    {
        std::cout << "The ad '" << it->GetName() << "' is in the following newspapers:" << std::endl;

        std::vector<const Newspaper *> placements = it->GetPlacements();
        for(
            std::vector<const Newspaper *>::iterator subit = placements.begin();
            subit != placements.end();
            ++subit
            )
        {
            const Newspaper * newspaper = *subit;
            std::cout << "'" << newspaper->GetName() << "'" << std::endl;
        }
    }

    return 0;
}

