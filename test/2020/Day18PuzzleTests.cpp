#include <catch/catch.hpp>
#include <2020/Day18Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 18 Examples work", "[2020][Day18]") {
	    const std::vector<std::string> input = {
			"1 + 2 * 3 + 4 * 5 + 6",
			//"1 + (2 * 3) + (4 * (5 + 6))"
		};

		const auto& parsed = Day18Puzzle::parse(input);

		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[0].first);
		REQUIRE(1 == parsed[0].parsed[0].second);
		REQUIRE(Day18Struct::TokenType::Plus == parsed[0].parsed[1].first);
		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[2].first);
		REQUIRE(2 == parsed[0].parsed[2].second);
		REQUIRE(Day18Struct::TokenType::Times == parsed[0].parsed[3].first);
		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[4].first);
		REQUIRE(3 == parsed[0].parsed[4].second);
		REQUIRE(Day18Struct::TokenType::Plus == parsed[0].parsed[5].first);
		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[6].first);
		REQUIRE(4 == parsed[0].parsed[6].second);
		REQUIRE(Day18Struct::TokenType::Times == parsed[0].parsed[7].first);
		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[8].first);
		REQUIRE(5 == parsed[0].parsed[8].second);
		REQUIRE(Day18Struct::TokenType::Plus == parsed[0].parsed[9].first);
		REQUIRE(Day18Struct::TokenType::Digit == parsed[0].parsed[10].first);
		REQUIRE(6 == parsed[0].parsed[10].second);

		const auto part1 = Day18Puzzle::doPart1(parsed);
		const auto part2 = Day18Puzzle::doPart2(parsed);

		REQUIRE("71" == part1);
		REQUIRE("" == part2);
	}

}
