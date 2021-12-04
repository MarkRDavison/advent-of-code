#include <catch/catch.hpp>
#include <2021/Day04Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 4 can apply number", "[2021][Day04]") {
		const std::vector<std::string> input = {
"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
"",
"14 21 17 24  4",
"10 16 15  9 19",
"18  8 23 26 20",
"22 11 13  6  5",
" 2  0 12  3  7",
		};

		auto& [numbers, boards] = Day04Puzzle::parseInput(input);

		auto& b = boards.front();

		REQUIRE(Day04Puzzle::applyNumber(b, 14));
		REQUIRE(Day04Puzzle::applyNumber(b, 21));
		REQUIRE(Day04Puzzle::applyNumber(b, 17));
		REQUIRE(Day04Puzzle::applyNumber(b, 24));
		REQUIRE(Day04Puzzle::applyNumber(b, 4));


		REQUIRE_FALSE(b.number[0][0].second);
		REQUIRE_FALSE(b.number[0][1].second);
		REQUIRE_FALSE(b.number[0][2].second);
		REQUIRE_FALSE(b.number[0][3].second);
		REQUIRE_FALSE(b.number[0][4].second);
	}

	TEST_CASE("Day 4 can detect when row has won", "[2021][Day04]") {
		const std::vector<std::string> input = {
"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
"",
"22 13 17 11  0",
" 8  2 23  4 24",
"21  9 14 16  7",
" 6 10  3 18  5",
" 1 12 20 15 19",
		};

		auto& [numbers, boards] = Day04Puzzle::parseInput(input);

		auto& b = boards.front();

		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][0].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][1].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][2].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][3].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][4].second = false;
		REQUIRE(Day04Puzzle::hasBoardWon(b));
	}
	TEST_CASE("Day 4 can detect when column has won", "[2021][Day04]") {
		const std::vector<std::string> input = {
"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
"",
"22 13 17 11  0",
" 8  2 23  4 24",
"21  9 14 16  7",
" 6 10  3 18  5",
" 1 12 20 15 19",
		};

		auto& [numbers, boards] = Day04Puzzle::parseInput(input);

		auto& b = boards.front();

		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[0][0].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[1][0].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[2][0].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[3][0].second = false;
		REQUIRE_FALSE(Day04Puzzle::hasBoardWon(b));
		b.number[4][0].second = false;
		REQUIRE(Day04Puzzle::hasBoardWon(b));
	}

	TEST_CASE("Day 4 Examples work", "[2021][Day04]") {
	    const std::vector<std::string> input = {
"7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1",
"",
"22 13 17 11  0",
" 8  2 23  4 24",
"21  9 14 16  7",
" 6 10  3 18  5",
" 1 12 20 15 19",
"",
" 3 15  0  2 22",
" 9 18 13 17  5",
"19  8  7 25 23",
"20 11 10 24  4",
"14 21 16 12  6",
"",
"14 21 17 24  4",
"10 16 15  9 19",
"18  8 23 26 20",
"22 11 13  6  5",
" 2  0 12  3  7",
		};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("4512" == answers.first);
		REQUIRE("1924" == answers.second);
	}

}
