#include <catch/catch.hpp>
#include <2017/Day03Puzzle.hpp>

namespace TwentySeventeen {

	void expectTest(int _input, int _expected) {
		const std::vector<std::string> input = {
			std::to_string(_input)
		};

		Day03Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		REQUIRE(std::to_string(_expected) == answers.first);
	}

	TEST_CASE("2017 Day 3 Examples work", "[2017][Day03]") {
		expectTest(26, 5);
		expectTest(12, 3);
		expectTest(16, 3);
		expectTest(20, 3);
		expectTest(23, 2);
		expectTest(24, 3);
		expectTest(1024, 31);
	}

}
