#include <catch/catch.hpp>
#include <2022/Day07Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 7 Examples work", "[2022][Day07]") {
	    const std::vector<std::string> input = {
"$ cd /",
"$ ls",
"dir a",
"14848514 b.txt",
"8504156 c.dat",
"dir d",
"$ cd a",
"$ ls",
"dir e",
"29116 f",
"2557 g",
"62596 h.lst",
"$ cd e",
"$ ls",
"584 i",
"$ cd ..",
"$ cd ..",
"$ cd d",
"$ ls",
"4060174 j",
"8033020 d.log",
"5626152 d.ext",
"7214296 k",
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("95437" == answers.first);
		REQUIRE("24933642" == answers.second);
	}

}
