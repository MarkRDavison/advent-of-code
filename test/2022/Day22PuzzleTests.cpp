#include <catch/catch.hpp>
#include <2022/Day22Puzzle.hpp>

namespace TwentyTwentyTwo {

	void validate(const Adjacency& _adjacency, const Vector2i& _c, const Vector2i& _left, const Vector2i& _right, const Vector2i& _up, const Vector2i& _down)
	{
		REQUIRE(_left == _adjacency.at(_c).at(core::Orientation::Left));
		REQUIRE(_right == _adjacency.at(_c).at(core::Orientation::Right));
		REQUIRE(_up == _adjacency.at(_c).at(core::Orientation::Up));
		REQUIRE(_down == _adjacency.at(_c).at(core::Orientation::Down));
	}

	TEST_CASE("Day 22 processAdjacency2D works", "[2022][Day22]") {
		const Map input = {
"        ...#",
"        .#..",
"        #...",
"        ....",
"...#.......#",
"........#...",
"..#....#....",
"..........#.",
"        ...#....",
"        .....#..",
"        .#......",
"        ......#."
		};

		const auto& adjacency = Day22Puzzle::processAdjacency2D(input);

		validate(adjacency, { 8,0 }, { 8,0 }, { 9, 0 }, { 8, 11 }, { 8, 1 });
		validate(adjacency, { 9,0 }, { 8,0 }, { 10, 0 }, { 9, 11 }, { 9, 0 });
	}

	TEST_CASE("Day 22 processAdjacency3D works", "[2022][Day22]") {
		const Map input = {
"        ...#",
"        .#..",
"        #...",
"        ....",
"...#.......#",
"........#...",
"..#....#....",
"..........#.",
"        ...#....",
"        .....#..",
"        .#......",
"        ......#."
		};

		const auto& [adjacency, adjacencyOrientation] = Day22Puzzle::processAdjacency3D(input, 4, {8, 0});


	}

	TEST_CASE("Day 22 Examples work", "[2022][Day22]") {
	    const std::vector<std::string> input = {
"        ...#",
"        .#..",
"        #...",
"        ....",
"...#.......#",
"........#...",
"..#....#....",
"..........#.",
"        ...#....",
"        .....#..",
"        .#......",
"        ......#.",
"",
"10R5L5R10L4R5L5",
		};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(4);

		REQUIRE("6032" == answers.first);
	}

}
