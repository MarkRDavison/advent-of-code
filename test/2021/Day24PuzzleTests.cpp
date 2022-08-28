#include <catch/catch.hpp>
#include <2021/Day24Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 24 Examples work", "[2021][Day24]") {
		{
			ArithmeticLogicUnit alu({
					"inp x",
					"mul x -1"
				}, {5});

			alu.run();

			REQUIRE(-5 == alu.get('x'));
		}
		{
			ArithmeticLogicUnit alu({
					"inp z",
					"inp x",
					"mul z 3",
					"eql z x"
				}, { 2, 6 });

			alu.run();

			REQUIRE(1 == alu.get('z'));
		}
		{
			ArithmeticLogicUnit alu({
					"inp z",
					"inp x",
					"mul z 3",
					"eql z x"
				}, { 2, 4 });

			alu.run();

			REQUIRE(0 == alu.get('z'));
		}
		{
			AluNumber inputVal = 1244;
			ArithmeticLogicUnit alu({
					"inp w",
					"add z w",
					"mod z 2",
					"div w 2",
					"add y w",
					"mod y 2",
					"div w 2",
					"add x w",
					"mod x 2",
					"div w 2",
					"mod w 2"
				}, { inputVal });

			alu.run();

			REQUIRE(0 == alu.get('z'));
			REQUIRE(0 == alu.get('y'));
			REQUIRE(1 == alu.get('x'));
			REQUIRE(1 == alu.get('w'));
		}
	}

}
