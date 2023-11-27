#include <catch/catch.hpp>
#include <2023/Day12Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 12 Examples work", "[2023][Day12]") {
	    const std::vector<std::string> input = {};

	    Day12Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
