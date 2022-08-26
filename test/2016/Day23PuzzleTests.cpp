#include <catch/catch.hpp>
#include <2016/Day23Puzzle.hpp>
#include <2016/AssembunyMachine.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 23 toggle works", "[2016][Day23]") {
	    const std::vector<std::string> input = {
"cpy 2 a",
"tgl a",
"tgl a",
"tgl a",
"cpy 1 a",
"dec a",
"dec a"
		};

		AssembunyMachine machine(input);

		
		while (machine.programCounter >= 0 && machine.programCounter < input.size()) {

			machine.applyInstructionAtPC();
		}

		REQUIRE(3 == machine.registers[0]);
	}

}
