#include <catch/catch.hpp>
#include <2023/Day22Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 22 Examples work", "[2023][Day22]") {
	    const std::vector<std::string> input = {};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
