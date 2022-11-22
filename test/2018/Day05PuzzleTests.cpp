#include <catch/catch.hpp>
#include <2018/Day05Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 5 Examples work", "[2018][Day05]") {
	    const std::vector<std::string> input = {"dabAcCaCBAcCcaDA"};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		REQUIRE("10" == answers.first);
		REQUIRE("4" == answers.second);
	}

}
