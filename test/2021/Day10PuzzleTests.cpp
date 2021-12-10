#include <catch/catch.hpp>
#include <2021/Day10Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 10 Examples work", "[2021][Day10]") {
	    const std::vector<std::string> input = {
"[({(<(())[]>[[{[]{<()<>>",
"[(()[<>])]({[<{<<[]>>(",
"{([(<{}[<>[]}>{[]{[(<()>",
"(((({<>}<{<{<>}{[]{[]{}",
"[[<[([]))<([[{}[[()]]]",
"[{[{({}]{}}([{[{{{}}([]",
"{<[[]]>}<{[{[{[]{()[[[]",
"[<(<(<(<{}))><([]([]()",
"<{([([[(<>()){}]>(<<{{",
"<{([{{}}[<[[[<>{}]]]>[]]",
		};

	    Day10Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("26397" == answers.first);
		REQUIRE("288957" == answers.second);
	}

	TEST_CASE("Day 10 isCorrupt works", "[2021][Day10]") {
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("()").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("[]").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("{}").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("<>").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("([])").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("{()()()}").corrupt);
		REQUIRE_FALSE(Day10Puzzle::isCorrupt("<([{}])>").corrupt);
		REQUIRE(Day10Puzzle::isCorrupt("{([(<{}[<>[]}>{[]{[(<()>").corrupt);
		REQUIRE(Day10Puzzle::isCorrupt("[[<[([]))<([[{}[[()]]]").corrupt);
		REQUIRE(Day10Puzzle::isCorrupt("[{[{({}]{}}([{[{{{}}([]").corrupt);
		REQUIRE(Day10Puzzle::isCorrupt("[<(<(<(<{}))><([]([]()").corrupt);
		REQUIRE(Day10Puzzle::isCorrupt("<{([([[(<>()){}]>(<<{{").corrupt);
	}

	TEST_CASE("Day 10 complete works", "[2021][Day10]") {
		auto chunk = "<{([{{}}[<[[[<>{}]]]>[]]";
		auto res = Day10Puzzle::complete(Day10Puzzle::isCorrupt(chunk), chunk);
		REQUIRE("<{([{{}}[<[[[<>{}]]]>[]]])}>" == res.complete);
		REQUIRE(294 == res.score);
	}
}
