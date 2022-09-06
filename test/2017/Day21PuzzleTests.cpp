#include <catch/catch.hpp>
#include <2017/Day21Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 21 Examples work", "[2017][Day21]") {
	    const std::vector<std::string> input = {
"../.# => ##./#../...",
".#./..#/### => #..#/..../..../#..#"
		};

	    Day21Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

		REQUIRE("12" == puzzle.fastSolve(2));
	}

	TEST_CASE("2017 Day 21 mirror works", "[2017][Day21]") {
		SECTION("2x2 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"ab",
				"cd"
			};

			const auto& mirrored = Day21Puzzle::mirror(grid);
			REQUIRE("ba" == mirrored[0]);
			REQUIRE("dc" == mirrored[1]);
		}
		SECTION("3x3 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"abc",
				"def",
				"ghi"
			};

			const auto& mirrored = Day21Puzzle::mirror(grid);
			REQUIRE("cba" == mirrored[0]);
			REQUIRE("fed" == mirrored[1]);
			REQUIRE("ihg" == mirrored[2]);
		}
	}
	TEST_CASE("2017 Day 21 flip works", "[2017][Day21]") {
		SECTION("2x2 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"ab",
				"cd"
			};

			const auto& flipped = Day21Puzzle::flip(grid);
			REQUIRE("cd" == flipped[0]);
			REQUIRE("ab" == flipped[1]);
		}
		SECTION("3x3 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"abc",
				"def",
				"ghi"
			};

			const auto& flipped = Day21Puzzle::flip(grid);
			REQUIRE("ghi" == flipped[0]);
			REQUIRE("def" == flipped[1]);
			REQUIRE("abc" == flipped[2]);
		}
	}
	TEST_CASE("2017 Day 21 rotate works", "[2017][Day21]") {
		SECTION("2x2 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"ab",
				"cd"
			};

			auto rotated = Day21Puzzle::rotate(grid);

			REQUIRE("ca" == rotated[0]);
			REQUIRE("db" == rotated[1]);
			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE("dc" == rotated[0]);
			REQUIRE("ba" == rotated[1]);
			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE("bd" == rotated[0]);
			REQUIRE("ac" == rotated[1]);
			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE(grid[0] == rotated[0]);
			REQUIRE(grid[1] == rotated[1]);
		}
		SECTION("2x2 by iter works") {
			Grid grid = (Grid)std::vector<std::string>{
				"ab",
				"cd"
			};

			auto rotated = Day21Puzzle::rotate(grid, 1);

			REQUIRE("ca" == rotated[0]);
			REQUIRE("db" == rotated[1]);
			rotated = Day21Puzzle::rotate(grid, 2);
			REQUIRE("dc" == rotated[0]);
			REQUIRE("ba" == rotated[1]);
			rotated = Day21Puzzle::rotate(grid, 3);
			REQUIRE("bd" == rotated[0]);
			REQUIRE("ac" == rotated[1]);
			rotated = Day21Puzzle::rotate(grid, 4);
			REQUIRE(grid[0] == rotated[0]);
			REQUIRE(grid[1] == rotated[1]);
		}
		SECTION("3x3 works") {
			Grid grid = (Grid)std::vector<std::string>{
				"abc",
				"def",
				"ghi"
			};

			auto rotated = Day21Puzzle::rotate(grid);
			REQUIRE("gda" == rotated[0]);
			REQUIRE("heb" == rotated[1]);
			REQUIRE("ifc" == rotated[2]);

			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE("ihg" == rotated[0]);
			REQUIRE("fed" == rotated[1]);
			REQUIRE("cba" == rotated[2]);

			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE("cfi" == rotated[0]);
			REQUIRE("beh" == rotated[1]);
			REQUIRE("adg" == rotated[2]);

			rotated = Day21Puzzle::rotate(rotated);
			REQUIRE(grid[0] == rotated[0]);
			REQUIRE(grid[1] == rotated[1]);
			REQUIRE(grid[2] == rotated[2]);
		}
		SECTION("3x3 iter works") {
			Grid grid = (Grid)std::vector<std::string>{
				"abc",
				"def",
				"ghi"
			};

			auto rotated = Day21Puzzle::rotate(grid, 1);
			REQUIRE("gda" == rotated[0]);
			REQUIRE("heb" == rotated[1]);
			REQUIRE("ifc" == rotated[2]);

			rotated = Day21Puzzle::rotate(grid, 2);
			REQUIRE("ihg" == rotated[0]);
			REQUIRE("fed" == rotated[1]);
			REQUIRE("cba" == rotated[2]);

			rotated = Day21Puzzle::rotate(grid, 3);
			REQUIRE("cfi" == rotated[0]);
			REQUIRE("beh" == rotated[1]);
			REQUIRE("adg" == rotated[2]);

			rotated = Day21Puzzle::rotate(grid, 4);
			REQUIRE(grid[0] == rotated[0]);
			REQUIRE(grid[1] == rotated[1]);
			REQUIRE(grid[2] == rotated[2]);
		}
	}
}
