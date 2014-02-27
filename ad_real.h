#ifndef AD_REAL_H
#define AD_REAL_H

#include <string>
#include <vector>

#include "ad.h"

class Newspaper;

class AdReal : public Ad
{
public:
	explicit AdReal(const std::string& name) : Ad(name) {}

	std::vector<const Newspaper *> GetPlacements() const {return placements;}
	virtual void RegisterPlacement(const Newspaper * newspaper);
	virtual void UnRegisterPlacement(const Newspaper * newspaper);

private:
	std::vector<const Newspaper *> placements;
};


#endif // AD_REAL_H
