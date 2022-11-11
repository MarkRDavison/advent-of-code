#include <catch/catch.hpp>
#include <2018/Day02Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 2 Part 1 double triple count works", "[2018][Day02]")
	{
		auto answer = Day02Puzzle::getDoubleTripleCount("abcdef");
		REQUIRE(0 == answer.first);
		REQUIRE(0 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("bababc");
		REQUIRE(1 == answer.first);
		REQUIRE(1 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("abbcde");
		REQUIRE(1 == answer.first);
		REQUIRE(0 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("abcccd");
		REQUIRE(0 == answer.first);
		REQUIRE(1 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("aabcdd");
		REQUIRE(1 == answer.first);
		REQUIRE(0 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("abcdee");
		REQUIRE(1 == answer.first);
		REQUIRE(0 == answer.second);
		answer = Day02Puzzle::getDoubleTripleCount("ababab");
		REQUIRE(0 == answer.first);
		REQUIRE(1 == answer.second);
	}

	TEST_CASE("2018 Day 2 Part 1 Example work", "[2018][Day02]") 
	{
	    const std::vector<std::string> input = {
			"abcdef",
			"bababc",
			"abbcde",
			"abcccd",
			"aabcdd",
			"abcdee",
			"ababab"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("12" == answers.first);
	}

	TEST_CASE("2018 Day 2 Part 2 Example work", "[2018][Day02]") 
	{
	    const std::vector<std::string> input = {
			"abcde",
			"fghij",
			"klmno",
			"pqrst",
			"fguij",
			"axcye",
			"wvxyz"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("fgij" == answers.second);
	}

}
