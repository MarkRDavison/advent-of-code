#include <catch/catch.hpp>
#include <2021/Day18Puzzle.hpp>

namespace TwentyTwentyOne {
	
	std::string solve(const std::vector<std::string>& _input) {

		auto num = Day18Puzzle::parse(_input[0]);
		for (std::size_t i = 1; i < _input.size(); ++i) {
			const auto newNum = Day18Puzzle::parse(_input[i]);
			std::cout << "===============================" << std::endl;
			std::cout << "  " << num->render() << std::endl;
			std::cout << "+ " << newNum->render() << std::endl;
			num = Day18Puzzle::add(num, newNum);
			std::cout << "= " << num->render() << std::endl;
			num = Day18Puzzle::reduce(num);
		}

		return num->render();
	}
	TEST_CASE("Day 18 big example works", "[2021][Day18]") {
		SECTION("step 1") {
			const std::vector<std::string> input = {
				"[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
				"[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]"
			};
			REQUIRE("[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]" == solve(input));
		}
		SECTION("step 2") {
			const std::vector<std::string> input = {
				"[[[[4,0],[5,4]],[[7,7],[6,0]]],[[8,[7,7]],[[7,9],[5,0]]]]",
				"[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]"
			};
			REQUIRE("[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]" == solve(input));
		}
		SECTION("step 3") {
			const std::vector<std::string> input = {
				"[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]",
				"[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]"
			};
			REQUIRE("[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]" == solve(input));
		}
		SECTION("step 4") {
			const std::vector<std::string> input = {
				"[[[[7,0],[7,7]],[[7,7],[7,8]]],[[[7,7],[8,8]],[[7,7],[8,7]]]]",
				"[7,[5,[[3,8],[1,4]]]]"
			};
			REQUIRE("[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]" == solve(input));
		}
		SECTION("step 5") {
			const std::vector<std::string> input = {
				"[[[[7,7],[7,8]],[[9,5],[8,7]]],[[[6,8],[0,8]],[[9,9],[9,0]]]]",
				"[[2,[2,2]],[8,[8,1]]]"
			};
			REQUIRE("[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]" == solve(input));
		}
		SECTION("step 6") {
			const std::vector<std::string> input = {
				"[[[[6,6],[6,6]],[[6,0],[6,7]]],[[[7,7],[8,9]],[8,[8,1]]]]",
				"[2,9]"
			};
			REQUIRE("[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]" == solve(input));
		}
		SECTION("step 7") {
			const std::vector<std::string> input = {
				"[[[[6,6],[7,7]],[[0,7],[7,7]]],[[[5,5],[5,6]],9]]",
				"[1,[[[9,3],9],[[9,0],[0,7]]]]"
			};
			REQUIRE("[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]" == solve(input));
		}
		SECTION("step 8") {
			const std::vector<std::string> input = {
				"[[[[7,8],[6,7]],[[6,8],[0,8]]],[[[7,7],[5,0]],[[5,5],[5,6]]]]",
				"[[[5,[7,4]],7],1]"
			};
			REQUIRE("[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]" == solve(input));
		}
		SECTION("step 9") {
			const std::vector<std::string> input = {
				"[[[[7,7],[7,7]],[[8,7],[8,7]]],[[[7,0],[7,7]],9]]",
				"[[[[4,2],2],6],[8,7]]"
			};
			REQUIRE("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" == solve(input));
		}
		SECTION("All in one") {
			const std::vector<std::string> input = {
"[[[0,[4,5]],[0,0]],[[[4,5],[2,6]],[9,5]]]",
"[7,[[[3,7],[4,3]],[[6,3],[8,8]]]]",
"[[2,[[0,8],[3,4]]],[[[6,7],1],[7,[1,6]]]]",
"[[[[2,4],7],[6,[0,5]]],[[[6,8],[2,8]],[[2,1],[4,5]]]]",
"[7,[5,[[3,8],[1,4]]]]",
"[[2,[2,2]],[8,[8,1]]]",
"[2,9]",
"[1,[[[9,3],9],[[9,0],[0,7]]]]",
"[[[5,[7,4]],7],1]",
"[[[[4,2],2],6],[8,7]]",
			};
			REQUIRE("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]" == solve(input));
		}
		SECTION("little example") {
			const std::vector<std::string> input = {
				"[[[[4,3],4],4],[7,[[8,4],9]]]",
				"[1,1]"
			};
			REQUIRE("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" == solve(input));
		}
	}
	TEST_CASE("Day 18 adding a list and then reducing works", "[2021][Day18]") {
		SECTION("1,1 -> 6,6 works") {
			const std::vector<std::string> input = {
				"[1,1]", "[2,2]", "[3,3]", "[4,4]", "[5,5]", "[6,6]"
			};
			REQUIRE("[[[[5,0],[7,4]],[5,5]],[6,6]]" == solve(input));
		}
		SECTION("1,1 -> 4,4 works") {
			const std::vector<std::string> input = {
				"[1,1]", "[2,2]", "[3,3]", "[4,4]"
			};
			REQUIRE("[[[[1,1],[2,2]],[3,3]],[4,4]]" == solve(input));
		}
		SECTION("1,1 -> 5,5 works") {
			const std::vector<std::string> input = {
				"[1,1]", "[2,2]", "[3,3]", "[4,4]", "[5,5]"
			};
			REQUIRE("[[[[3,0],[5,3]],[4,4]],[5,5]]" == solve(input));
		}
	}
	TEST_CASE("Day 18 reducing works", "[2021][Day18]") {
		SECTION("Basic looking but not actually") {
			const auto snailNumber = Day18Puzzle::parse("[[[[[1,1],[2,2]],[3,3]],[4,4]],[5,5]]");
			const auto reduced = Day18Puzzle::reduce(snailNumber);
			REQUIRE("[[[[3,0],[5,3]],[4,4]],[5,5]]" == reduced->render());
		}
		SECTION("Basic") {
			const auto snailNumber = Day18Puzzle::parse("[[[[[4,3],4],4],[7,[[8,4],9]]],[1,1]]");
			const auto reduced = Day18Puzzle::reduce(snailNumber);
			REQUIRE("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" == reduced->render());
		}
	}
	TEST_CASE("Day 18 splitting works", "[2021][Day18]") {
		SECTION("[[[[0,7],4],[[7,8],[0,13]]],[1,1]] works") {
			const auto snailNumber = Day18Puzzle::parse("[[[[0,7],4],[[7,8],[0,13]]],[1,1]]");
			const auto splitted = Day18Puzzle::split(snailNumber);
			REQUIRE("[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]" == splitted.second->render());
		}
		SECTION("[[[[0,7],4],[15,[0,13]]],[1,1]] works") {
			const auto snailNumber = Day18Puzzle::parse("[[[[0,7],4],[15,[0,13]]],[1,1]]");
			const auto splitted = Day18Puzzle::split(snailNumber);
			REQUIRE("[[[[0,7],4],[[7,8],[0,13]]],[1,1]]" == splitted.second->render());
		}
	}
	TEST_CASE("Day 18 exploding works", "[2021][Day18]") {
		SECTION("[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]] works") {
			const auto snailNumber = Day18Puzzle::parse("[[[[0,7],4],[[7,8],[0,[6,7]]]],[1,1]]");
			const auto exploded = Day18Puzzle::explode(snailNumber);
			REQUIRE("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]" == exploded.second->render());
		}
		SECTION("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]] works") {
			const auto snailNumber = Day18Puzzle::parse("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
			const auto exploded = Day18Puzzle::explode(snailNumber);
			REQUIRE("[[3,[2,[8,0]]],[9,[5,[7,0]]]]" == exploded.second->render());
		}
		SECTION("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]] works") {
			const auto snailNumber = Day18Puzzle::parse("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]");
			const auto exploded = Day18Puzzle::explode(snailNumber);
			REQUIRE("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]" == exploded.second->render());
		}
		SECTION("[[6,[5,[4,[3,2]]]],1] works") {
			const auto snailNumber = Day18Puzzle::parse("[[6,[5,[4,[3,2]]]],1]");
			const auto exploded = Day18Puzzle::explode(snailNumber);
			REQUIRE("[[6,[5,[7,0]]],3]" == exploded.second->render());
		}
		SECTION("[7,[6,[5,[4,[3,2]]]]] works") {
			const auto snailNumber = Day18Puzzle::parse("[7,[6,[5,[4,[3,2]]]]]");
			const auto exploded = Day18Puzzle::explode(snailNumber);
			REQUIRE("[7,[6,[5,[7,0]]]]" == exploded.second->render());
		}
		SECTION("[[[[[9,8],1],2],3],4] works") {
			const auto exploded = Day18Puzzle::explode(Day18Puzzle::parse("[[[[[9,8],1],2],3],4]"));
			REQUIRE("[[[[0,9],2],3],4]" == exploded.second->render());
		}
	}

	TEST_CASE("Day 18 adding snail fish numbersworks", "[2021][Day18]") {
		SECTION("Simple addition works") {
			const auto lhs = Day18Puzzle::parse("[1,2]");
			const auto rhs = Day18Puzzle::parse("[3,4]");

			const auto added = Day18Puzzle::add(lhs, rhs);

			REQUIRE(added->type == SnailFishNumber::Type::Node);

			REQUIRE(lhs == added->left);
			REQUIRE(lhs->type == SnailFishNumber::Type::Node);
			REQUIRE(rhs == added->right);
			REQUIRE(rhs->type == SnailFishNumber::Type::Node);
		}
		SECTION("Adding multiple things works") {
			auto sum = Day18Puzzle::add(Day18Puzzle::parse("[1,1]"), Day18Puzzle::parse("[2,2]"));
			sum = Day18Puzzle::add(sum, Day18Puzzle::parse("[3,3]"));
			sum = Day18Puzzle::add(sum, Day18Puzzle::parse("[4,4]"));

			REQUIRE("[[[[1,1],[2,2]],[3,3]],[4,4]]" == sum->render());
		}
		SECTION("Adding more multiple things works") {
			auto sum = Day18Puzzle::add(Day18Puzzle::parse("[1,1]"), Day18Puzzle::parse("[2,2]"));
			sum = Day18Puzzle::add(sum, Day18Puzzle::parse("[3,3]"));
			sum = Day18Puzzle::add(sum, Day18Puzzle::parse("[4,4]"));
			sum = Day18Puzzle::add(sum, Day18Puzzle::parse("[5,5]"));

			REQUIRE("[[[[[1,1],[2,2]],[3,3]],[4,4]],[5,5]]" == sum->render());
		}
	}
	TEST_CASE("Day 18 parsing snail fish works", "[2021][Day18]") {
		const std::vector<std::string> input = {
			"[1,2]", "[1,[2,3]]", "[[1,2],3]", "[[1,9],[8,5]]",
			"[[[[1,2],[3,4]],[[5,6],[7,8]]],9]",
			"[[[9,[3,8]],[[0,9],6]],[[[3,7],[4,9]],3]]",
			"[[[[1,3],[5,3]],[[1,3],[8,7]]],[[[4,9],[6,9]],[[8,2],[7,3]]]]",
			"[[[[6,7],[6,7]],[[7,7],[0,7]]],[[[8,7],[7,7]],[[8,8],[8,0]]]]"
		};

		for (const auto& i : input) {
			SECTION(i + " works") {
				const auto num = Day18Puzzle::parse(i);
				REQUIRE(i == num->render());
			}
		}
	}
	TEST_CASE("Day 18 Magnitude works", "[2021][Day18]") {
		REQUIRE(29 == Day18Puzzle::magnitude(Day18Puzzle::parse("[9,1]")));
		REQUIRE(129 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[9,1],[1,9]]")));
		REQUIRE(143 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[1,2],[[3,4],5]]")));
		REQUIRE(1384 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[[[0,7],4],[[7,8],[6,0]]],[8,1]]")));
		REQUIRE(445 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[[[1,1],[2,2]],[3,3]],[4,4]]")));
		REQUIRE(791 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[[[3,0],[5,3]],[4,4]],[5,5]]")));
		REQUIRE(1137 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[[[5,0],[7,4]],[5,5]],[6,6]]")));
		REQUIRE(3488 == Day18Puzzle::magnitude(Day18Puzzle::parse("[[[[8,7],[7,7]],[[8,6],[7,7]]],[[[0,7],[6,6]],[8,7]]]")));
	}
	TEST_CASE("Day 18 Examples work", "[2021][Day18]") {
	    const std::vector<std::string> input = {
"[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
"[[[5,[2,8]],4],[5,[[9,9],0]]]",
"[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
"[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
"[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
"[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
"[[[[5,4],[7,7]],8],[[8,3],8]]",
"[[9,3],[[9,9],[6,[4,9]]]]",
"[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
"[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]",
		};

	    Day18Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("4140" == answers.first);
		REQUIRE("3993" == answers.second);
	}

}
