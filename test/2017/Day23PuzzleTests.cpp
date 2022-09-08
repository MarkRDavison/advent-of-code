#include <catch/catch.hpp>
#include <2017/Day23Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 23 Examples work", "[2017][Day23]") {
	    const std::vector<std::string> input = {};

	    Day23Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
