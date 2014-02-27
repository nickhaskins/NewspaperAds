
#include <vector>
#include <gtest/gtest.h>
#include "ad_real.h"

TEST(AdTests, TestConstructor)
{
	std::string name("Foo");
	AdReal a(name);
	EXPECT_EQ(name, a.GetName());

	std::vector<const Newspaper *> empty;
	EXPECT_EQ(empty, a.GetPlacements());
}

TEST(AdTests, TestRegisterPlacement)
{
	AdReal a("Foo");

	std::vector<const Newspaper *> placements;

	Newspaper * n1 = (Newspaper *)1;
	placements.push_back(n1);

	a.RegisterPlacement(n1);

	EXPECT_EQ(placements, a.GetPlacements());

	Newspaper * n2 = (Newspaper *)2;
	placements.push_back(n2);

	a.RegisterPlacement(n2);

	EXPECT_EQ(placements, a.GetPlacements());
}

TEST(AdTests, TestUnRegisterPlacement)
{
	AdReal a("Foo");

	Newspaper * n1 = (Newspaper *)1;
	Newspaper * n2 = (Newspaper *)2;

	a.RegisterPlacement(n1);
	a.RegisterPlacement(n2);

	a.UnRegisterPlacement(n2);

	std::vector<const Newspaper *> placements;
	placements.push_back(n1);

	EXPECT_EQ(placements, a.GetPlacements());

	a.UnRegisterPlacement(n1);
	placements = std::vector<const Newspaper *>();
	EXPECT_EQ(placements, a.GetPlacements());
}

TEST(AdTests, TestRemoveBogusPlacement)
{
	AdReal a("Foo");
	Newspaper * n1 = (Newspaper *)1;

	EXPECT_THROW(a.UnRegisterPlacement(n1), Ad::PlacementNotFoundException);
}

