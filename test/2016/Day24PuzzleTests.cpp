#include <catch/catch.hpp>
#include <2016/Day24Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 24 Examples work", "[2016][Day24]") {
	    const std::vector<std::string> input = {
"###########",
"#0.1.....2#",
"#.#######.#",
"#4.......3#",
"###########"
		};

	    Day24Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("14" == answers.first);
		REQUIRE("20" == answers.second);
	}

}
