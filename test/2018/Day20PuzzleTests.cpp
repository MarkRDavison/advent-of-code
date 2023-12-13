#include <catch/catch.hpp>
#include <2018/Day20Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 20 Examples work", "[2018][Day20]") {
	    const std::vector<std::string> input = { "^WSSEESWWWNW(S|NENNEEEENN(ESSSSW(NWSW|SSEN)|WSWWN(E|WWS(E|SS))))$"};

	    Day20Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("31" == answers.first);
	}

}
