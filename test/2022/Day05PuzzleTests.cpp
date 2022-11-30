#include <catch/catch.hpp>
#include <2022/Day05Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 5 Examples work", "[2022][Day05]") {
	    const std::vector<std::string> input = {};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
