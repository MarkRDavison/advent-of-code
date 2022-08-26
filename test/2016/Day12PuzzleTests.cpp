#include <catch/catch.hpp>
#include <2016/Day12Puzzle.hpp>
#include <2016/AssembunyMachine.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 12 Part 1 Example work", "[2016][Day12]") {
	    const std::vector<std::string> input = {
"cpy 41 a",
"inc a",
"inc a",
"dec a",
"jnz a 2",
"dec a"
		};

		AssembunyMachine machine(input);

		while (machine.programCounter >= 0 && machine.programCounter < input.size()) {
			machine.applyInstructionAtPC();
		}

		REQUIRE(42 == machine.registers[0]);
	}

}
