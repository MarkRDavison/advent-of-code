#include <catch/catch.hpp>
#include <2022/Day16Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 16 Examples work", "[2022][Day16]") {
	    const std::vector<std::string> input = {
"Valve AA has flow rate=0; tunnels lead to valves DD, II, BB",
"Valve BB has flow rate=13; tunnels lead to valves CC, AA",
"Valve CC has flow rate=2; tunnels lead to valves DD, BB",
"Valve DD has flow rate=20; tunnels lead to valves CC, AA, EE",
"Valve EE has flow rate=3; tunnels lead to valves FF, DD",
"Valve FF has flow rate=0; tunnels lead to valves EE, GG",
"Valve GG has flow rate=0; tunnels lead to valves FF, HH",
"Valve HH has flow rate=22; tunnel leads to valve GG",
"Valve II has flow rate=0; tunnels lead to valves AA, JJ",
"Valve JJ has flow rate=21; tunnel leads to valve II",
		};

	    Day16Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1651" == answers.first);
		REQUIRE("1707" == answers.second);
	}

}
