#ifndef AD_H
#define AD_H

#include <string>
#include <vector>

class Newspaper;

class Ad
{
public:
	explicit Ad(const std::string& _name) : name(_name) {}

	std::string GetName() const {return name;}

	virtual std::vector<const Newspaper *> GetPlacements() const = 0;
	virtual void RegisterPlacement(const Newspaper * newspaper) = 0;
	virtual void UnRegisterPlacement(const Newspaper * newspaper) = 0;

	class PlacementNotFoundException {};

private:
	std::string name;
};


#endif // AD_H
