#include <catch/catch.hpp>
#include <2021/Day06Puzzle.hpp>

namespace TwentyTwentyOne {
	TEST_CASE("Day 6 iterateLanternFish works", "[2021][Day06]") {
		std::unordered_map<LanternFishNumber, LanternFishNumber> lanternFish;

		lanternFish = { {3, 2}, {4, 1}, {1, 1}, {2, 1} };

		auto newLanternFish = Day06Puzzle::iterateLanternFish(lanternFish);
		REQUIRE(newLanternFish[2] == 2);
		REQUIRE(newLanternFish[0] == 1);
		REQUIRE(newLanternFish[1] == 1);

		newLanternFish = Day06Puzzle::iterateLanternFish(newLanternFish);
		REQUIRE(newLanternFish[1] == 2);
		REQUIRE(newLanternFish[2] == 1);
		REQUIRE(newLanternFish[6] == 1);
		REQUIRE(newLanternFish[8] == 1);
		REQUIRE(newLanternFish[0] == 1);

		newLanternFish = Day06Puzzle::iterateLanternFish(newLanternFish);
		REQUIRE(newLanternFish[0] == 2);
		REQUIRE(newLanternFish[1] == 1);
		REQUIRE(newLanternFish[5] == 1);
		REQUIRE(newLanternFish[6] == 1);
		REQUIRE(newLanternFish[7] == 1);
		REQUIRE(newLanternFish[8] == 1);

		newLanternFish = Day06Puzzle::iterateLanternFish(newLanternFish);
		REQUIRE(newLanternFish[6] == 3);
		REQUIRE(newLanternFish[8] == 2);
		REQUIRE(newLanternFish[5] == 1);
		REQUIRE(newLanternFish[4] == 1);
		REQUIRE(newLanternFish[0] == 1);
	}

	TEST_CASE("Day 6 Examples work", "[2021][Day06]") {
	    const std::vector<std::string> input = {
			"3,4,3,1,2"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5934" == answers.first);
		REQUIRE("26984457539" == answers.second);
	}

}
