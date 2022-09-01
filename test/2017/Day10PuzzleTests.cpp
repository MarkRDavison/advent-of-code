#include <catch/catch.hpp>
#include <2017/Day10Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 10 Part 1 Example work", "[2017][Day10]") {
	    const std::vector<std::string> input = {
			"3, 4, 1, 5"
		};

	    Day10Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve(5, false, {});

		REQUIRE("12" == answer);
	}

	TEST_CASE("2017 Day 10 Part 2 Example work", "[2017][Day10]") {
		const std::vector<std::string> input = {
			"AoC 2017"
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answer = puzzle.fastSolve(256, true, { 17, 31, 73, 47, 23 });

		REQUIRE("33efeb34ea91902bb2f59c9920caa6cd" == answer);
	}

	TEST_CASE("2017 Day 10 standalone hash function works", "[2017][Day10]") {
		REQUIRE("0adf13fa40e8ea815376776af3b7b231" == Day10Puzzle::knotHash("flqrgnkx-2"));
		REQUIRE("ad3da28cd7b8fb99742c0e63672caf62" == Day10Puzzle::knotHash("flqrgnkx-3"));
	}

}
