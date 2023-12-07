#include <catch/catch.hpp>
#include <2018/Day16Puzzle.hpp>
#include <2018/OpCodeComputer.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 16 OpCodeComputer works", "[2018][Day16]")
	{
		OpCodeComputer<4> computer;

		computer.registers = { 3,2,1,1 };

		SECTION("MULR")
		{
			computer.runOpCode(
				OpCode
				{
					.code = OpCodeType::MULR,
					.A = 2,
					.B = 1,
					.C = 2
				});
		}
		SECTION("ADDI")
		{
			computer.runOpCode(
				OpCode
				{
					.code = OpCodeType::ADDI,
					.A = 2,
					.B = 1,
					.C = 2
				});
		}
		SECTION("SETI")
		{
			computer.runOpCode(
				OpCode
				{
					.code = OpCodeType::SETI,
					.A = 2,
					.B = 1,
					.C = 2
				});
		}

		REQUIRE(3 == computer.registers[0]);
		REQUIRE(2 == computer.registers[1]);
		REQUIRE(2 == computer.registers[2]);
		REQUIRE(1 == computer.registers[3]);
	}

	TEST_CASE("2018 Day 16 Examples work", "[2018][Day16]") 
	{
	    const std::vector<std::string> input = {
"Before: [3, 2, 1, 1]",
"9 2 1 2",
"After:  [3, 2, 2, 1]",
"",
"",
"",
"1 0 0 1",
"4 1 1 1",
		};

	    Day16Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1" == answers.first);
	}

}
