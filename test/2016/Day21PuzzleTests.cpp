#include <catch/catch.hpp>
#include <2016/Day21Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 21 Part 1 Example work", "[2016][Day21]") {
	    const std::vector<std::string> input = {
"swap position 4 with position 0",
"swap letter d with letter b",
"reverse positions 0 through 4",
"rotate left 1 step",
"move position 1 to position 4",
"move position 3 to position 0",
"rotate based on position of letter b",
"rotate based on position of letter d"
		};

	    Day21Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve("abcde", "decab");

		REQUIRE("decab" == answers.first);
		REQUIRE("abcde" == answers.second);
	}

	TEST_CASE("2016 Day 21 parsing works", "[2016][Day21]") {
		{
			const auto& instr = Day21Puzzle::parse("swap position 4 with position 0");

			REQUIRE(InstructionType::SwapPosition == instr.type);
			REQUIRE(4 == instr.fromPosition);
			REQUIRE(0 == instr.toPosition);
		}
		{
			const auto& instr = Day21Puzzle::parse("swap letter d with letter b");

			REQUIRE(InstructionType::SwapLetter == instr.type);
			REQUIRE('d' == instr.fromLetter);
			REQUIRE('b' == instr.toLetter);
		}
		{
			const auto& instr = Day21Puzzle::parse("reverse positions 0 through 4");

			REQUIRE(InstructionType::ReversePositions == instr.type);
			REQUIRE(0 == instr.fromPosition);
			REQUIRE(4 == instr.toPosition);
		}
		{
			const auto& instr = Day21Puzzle::parse("rotate left 1 step");

			REQUIRE(InstructionType::Rotate == instr.type);
			REQUIRE(-1 == instr.steps);
		}
		{
			const auto& instr = Day21Puzzle::parse("rotate right 1 step");

			REQUIRE(InstructionType::Rotate == instr.type);
			REQUIRE(+1 == instr.steps);
		}
		{
			const auto& instr = Day21Puzzle::parse("move position 1 to position 4");

			REQUIRE(InstructionType::MovePostion == instr.type);
			REQUIRE(1 == instr.fromPosition);
			REQUIRE(4 == instr.toPosition);
		}
		{
			const auto& instr = Day21Puzzle::parse("rotate based on position of letter b");

			REQUIRE(InstructionType::RotatePosition == instr.type);
			REQUIRE('b' == instr.fromLetter);
		}
	}

	TEST_CASE("2016 Day 21 applying instructions works", "[2016][Day21]") {
		std::string string = "abcde";

		string = Day21Puzzle::apply(Day21Puzzle::parse("swap position 4 with position 0"), string);
		REQUIRE("ebcda" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("swap letter d with letter b"), string);
		REQUIRE("edcba" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("reverse positions 0 through 4"), string);
		REQUIRE("abcde" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("rotate left 1 step"), string);
		REQUIRE("bcdea" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("move position 1 to position 4"), string);
		REQUIRE("bdeac" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("move position 3 to position 0"), string);
		REQUIRE("abdec" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("rotate based on position of letter b"), string);
		REQUIRE("ecabd" == string);

		string = Day21Puzzle::apply(Day21Puzzle::parse("rotate based on position of letter d"), string);
		REQUIRE("decab" == string);
	}

}
