#include <catch/catch.hpp>
#include <2018/Day07Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 7 Examples work", "[2018][Day07]") {
	    const std::vector<std::string> input = {
"Step C must be finished before step A can begin.",
"Step C must be finished before step F can begin.",
"Step A must be finished before step B can begin.",
"Step A must be finished before step D can begin.",
"Step B must be finished before step E can begin.",
"Step D must be finished before step E can begin.",
"Step F must be finished before step E can begin."
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(0, 2);

		REQUIRE("CABDFE" == answers.first);
		REQUIRE("15" == answers.second);
	}

}
