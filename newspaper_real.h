#ifndef NEWSPAPER_REAL_H
#define NEWSPAPER_REAL_H

#include <string>
#include <vector>

#include "newspaper.h"

class Ad;

class NewspaperReal : public Newspaper
{
public:
	explicit NewspaperReal(const std::string& name) : Newspaper(name) {}

	void PlaceAd(Ad * ad);
	void RemoveAd(Ad * ad);
	std::vector<Ad *> GetAdList() const {return adList;}

private:
	std::vector<Ad *> adList;
};


#endif // NEWSPAPER_REAL_H

