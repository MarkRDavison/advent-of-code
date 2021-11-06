#include <catch/catch.hpp>
#include <2020/Day21Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 21 Examples work", "[2020][Day21]") {
	    const std::vector<std::string> input = {
"mxmxvkd kfcds sqjhc nhms(contains dairy, fish)",
"trh fvjkl sbzzf mxmxvkd(contains dairy)",
"sqjhc fvjkl(contains soy)",
"sqjhc mxmxvkd sbzzf(contains fish)",
		};

		const auto& parsed = Day21Puzzle::parse(input);

		REQUIRE(1 == parsed[0].ingredients.count("mxmxvkd"));
		REQUIRE(1 == parsed[0].ingredients.count("kfcds"));
		REQUIRE(1 == parsed[0].ingredients.count("sqjhc"));
		REQUIRE(1 == parsed[0].ingredients.count("nhms"));
		REQUIRE(1 == parsed[0].allergens.count("dairy"));
		REQUIRE(1 == parsed[0].allergens.count("fish"));

		const auto part1 = Day21Puzzle::doPart1(parsed);
		const auto part2 = Day21Puzzle::doPart2(parsed);

		REQUIRE("5" == part1);
		REQUIRE("" == part2);
	}

}
