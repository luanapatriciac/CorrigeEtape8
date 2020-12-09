#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include "pugixml.hpp"

#include "Circle.h"
#include "Group.h"

using std::vector;
using std::unique_ptr;
using std::make_unique;

TEST(TestReadXML, TestCircle) {
	std::string xml = R"(
<?xml version = "1.0"?>
<Circle label="testCircle" x="0" y="1" r="2" color="Black"/>
)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	EXPECT_NE(0, result);
	Circle c{ doc.child("Circle") };
	EXPECT_EQ("testCircle", c.get_label());
	EXPECT_EQ(0., c.get_x());
	EXPECT_EQ(1., c.get_y());
	EXPECT_EQ(2., c.get_r());
	EXPECT_EQ("Black", c.get_color());
}

TEST(TestReadXML, TestGroup1) {
	std::string xml = R"(
<?xml version = "1.0"?>
<Group label="testGroup" x="0" y="1">
     <Circle label="testCircle1" x="2" y="3" r="4" color="Black"/>
     <Circle label="testCircle2" x="5" y="6" r="7" color="Black"/>
</Group>
)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	EXPECT_NE(0, result);
	Group g{ doc.child("Group") };
	EXPECT_EQ("testGroup", g.get_label());
	EXPECT_EQ(0., g.get_x());
	EXPECT_EQ(1., g.get_y());
	// Test des enfants du groupe
	vector<unique_ptr<Shape>> & children = g.get_children();
	EXPECT_EQ("testCircle1", children[0]->get_label());
	EXPECT_EQ(2., children[0]->get_x());
	EXPECT_EQ(3., children[0]->get_y());
	EXPECT_EQ("testCircle2", children[1]->get_label());
	EXPECT_EQ(5., children[1]->get_x());
	EXPECT_EQ(6., children[1]->get_y());
}

TEST(TestReadXML, TestGroup2) {
	std::string xml = R"(
<?xml version = "1.0"?>
<Group label="testGroup1" x="0" y="1">
     <Circle label="testCircle" x="2" y="3" r="4" color="Black"/>
     <Group label="testGroup2" x="5" y="6"/>
</Group>
)";
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_string(xml.c_str());
	EXPECT_NE(0, result);
	Group g{ doc.child("Group") };
	EXPECT_EQ("testGroup1", g.get_label());
	EXPECT_EQ(0., g.get_x());
	EXPECT_EQ(1., g.get_y());
	// Test des enfants du groupe
	vector<unique_ptr<Shape>> & children = g.get_children();
	EXPECT_EQ("testCircle", children[0]->get_label());
	EXPECT_EQ(2., children[0]->get_x());
	EXPECT_EQ(3., children[0]->get_y());
	EXPECT_EQ("testGroup2", children[1]->get_label());
	EXPECT_EQ(5., children[1]->get_x());
	EXPECT_EQ(6., children[1]->get_y());
}

TEST(TestAbsoluteCoord, Test1) {
	unique_ptr<Group> g2 = make_unique<Group>("G2", 2, 3);
	g2->add(make_unique<Circle>("C21", 4, 5, 6, "Black"));
	g2->add(make_unique<Circle>("C22", 7, 8, 9, "Black"));
	Group * pg2 = g2.get();
	Group g1("G1", 0, 1);
	g1.add(std::move(g2));

	std::map<std::string, std::pair<double, double>> s2pair;

	g1.compute_absolute_xy(0, 0, s2pair);

	EXPECT_EQ(0, s2pair["G1"].first);
	EXPECT_EQ(1, s2pair["G1"].second);
	// Pour les autres tests, utilisation d'une forme plus concise
	EXPECT_EQ(std::make_pair(2., 4.), s2pair["G2"]);
	EXPECT_EQ(std::make_pair(6., 9.), s2pair["C21"]);
	EXPECT_EQ(std::make_pair(9., 12.), s2pair["C22"]);

}
