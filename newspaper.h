#ifndef NEWSPAPER_H
#define NEWSPAPER_H

#include <string>
#include <vector>

class Ad;

class Newspaper
{
public:
	explicit Newspaper(const std::string& _name) : name(_name) {}

	std::string GetName() const {return name;}

	virtual std::vector<Ad *> GetAdList() const = 0;
	virtual void PlaceAd(Ad * ad) = 0;
	virtual void RemoveAd(Ad * ad) = 0;

	class AdNotFoundException {};

private:
	std::string name;
};


#endif // NEWSPAPER_H

