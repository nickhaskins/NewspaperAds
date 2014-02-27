
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "newspaper_real.h"
#include "ad.h"

class AdMock : public Ad
{
public:
	explicit AdMock(const std::string& _name) : Ad(_name) {}

	void RegisterPlacement(const Newspaper * newspaper)
	{
		registeredPlacementInNewspaper = newspaper;
	}
	void UnRegisterPlacement(const Newspaper * newspaper)
	{
		unRegisteredPlacementInNewspaper = newspaper;
	}

	std::vector<const Newspaper *> GetPlacements() const {return std::vector<const Newspaper*>();}

	const Newspaper * GetRegisteredPlacement() const {return registeredPlacementInNewspaper;}
	const Newspaper * GetUnRegisteredPlacement() const {return unRegisteredPlacementInNewspaper;}

private:
	const Newspaper * registeredPlacementInNewspaper;
	const Newspaper * unRegisteredPlacementInNewspaper;
};

TEST(NewspaperTests, TestConstructor)
{
	std::string name = "Foo";
	NewspaperReal n(name);
	EXPECT_EQ(name, n.GetName());

	std::vector<Ad *> empty;
	EXPECT_EQ(empty, n.GetAdList());
}

TEST(NewspaperTests, TestPlaceAd)
{
	NewspaperReal n("Foo");
	AdMock a("Bar");

	n.PlaceAd(&a);
	std::vector<Ad *> ads;
	ads.push_back(&a);
	EXPECT_EQ(ads, n.GetAdList());

	EXPECT_EQ(&n, a.GetRegisteredPlacement());
}

TEST(NewspaperTests, TestRemoveAd)
{
	NewspaperReal n("Foo");
	AdMock a("Bar");
	AdMock b("Baz");

	n.PlaceAd(&a);
	n.PlaceAd(&b);

	n.RemoveAd(&b);

	std::vector<Ad *> ads;
	ads.push_back(&a);
	EXPECT_EQ(ads, n.GetAdList());

	EXPECT_EQ(b.GetUnRegisteredPlacement(), &n);

	n.RemoveAd(&a);

	std::vector<Ad *> empty;
	EXPECT_EQ(empty, n.GetAdList());

	EXPECT_EQ(a.GetUnRegisteredPlacement(), &n);
}

TEST(NewspaperTests, TestRemoveAdBeforeEnd)
{
	NewspaperReal n("Foo");
	AdMock a("Bar");
	AdMock b("Baz");

	n.PlaceAd(&a);
	n.PlaceAd(&b);

	n.RemoveAd(&a);

	std::vector<Ad *> ads;
	ads.push_back(&b);
	EXPECT_EQ(ads, n.GetAdList());

	EXPECT_EQ(a.GetUnRegisteredPlacement(), &n);
}

TEST(NewspaperTests, TestRemoveBogusAd)
{
	NewspaperReal n("Foo");
	AdMock a("Bar");

	EXPECT_THROW(n.RemoveAd(&a), Newspaper::AdNotFoundException);
}

