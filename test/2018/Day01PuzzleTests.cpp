#include <catch/catch.hpp>
#include <2018/Day01Puzzle.hpp>

namespace TwentyEighteen {


	TEST_CASE("2018 Day 1 Examples work", "[2018][Day01]") {
	    const std::vector<std::string> input = { "+7","+7","-2","-7","-4"};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1" == answers.first);
		REQUIRE("14" == answers.second);
	}

}
