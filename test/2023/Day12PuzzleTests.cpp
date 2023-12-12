#include <catch/catch.hpp>
#include <2023/Day12Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 12 Examples work", "[2023][Day12]") {
	    const std::vector<std::string> input = {
"???.### 1,1,3",
".??..??...?##. 1,1,3",
"?#?#?#?#?#?#?#? 1,3,1,6",
"????.#...#... 4,1,1",
"????.######..#####. 1,6,5",
"?###???????? 3,2,1",
		};

	    Day12Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("21" == answers.first);
		REQUIRE("525152" == answers.second);
	}

}
