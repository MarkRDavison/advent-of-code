#include <catch/catch.hpp>
#include <2022/Day17Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 17 Examples work", "[2022][Day17]") {
	    const std::vector<std::string> input = {};

	    Day17Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
