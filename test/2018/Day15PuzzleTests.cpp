#include <catch/catch.hpp>
#include <2018/Day15Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 15 load works", "[2018][Day15]") {
	    const std::vector<std::string> input = {
 "#######",
 "#.G.E.#",
 "#E.G.E#",
 "#.G.E.#",
 "#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		for (int y = 0; y < 5; ++y)
		{
			for (int x = 0; x < 7; ++x)
			{
				if (x == 0 || y == 0 || x == 6 || y == 4)
				{
					REQUIRE('#' == cave.getCell(x, y));
				}
				else
				{
					REQUIRE('.' == cave.getCell(x, y));
				}
			}
		}

		REQUIRE(7 == units.size());

		REQUIRE('G' == units[0].type);
		REQUIRE(Vector2i{ 2,1 } == units[0].position);

		REQUIRE('E' == units[1].type);
		REQUIRE(Vector2i{ 4,1 } == units[1].position);

		REQUIRE('E' == units[2].type);
		REQUIRE(Vector2i{ 1,2 } == units[2].position);

		REQUIRE('G' == units[3].type);
		REQUIRE(Vector2i{ 3,2 } == units[3].position);

		REQUIRE('E' == units[4].type);
		REQUIRE(Vector2i{ 5,2 } == units[4].position);

		REQUIRE('G' == units[5].type);
		REQUIRE(Vector2i{ 2,3 } == units[5].position);

		REQUIRE('E' == units[6].type);
		REQUIRE(Vector2i{ 4,3 } == units[6].position);
	}

	TEST_CASE("2018 Day 15 resetUnitsForTurn works", "[2018][Day15]")
	{
		std::vector<BBUnit> units = {
			BBUnit{.type = 'G', .position = Vector2i{2,1}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{4,1}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{1,2}, .hasHadTurn = true },
			BBUnit{.type = 'G', .position = Vector2i{3,2}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{5,2}, .hasHadTurn = true },
			BBUnit{.type = 'G', .position = Vector2i{2,3}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{4,3}, .hasHadTurn = true }
		};

		Day15Puzzle::resetUnitsForTurn(units);

		for (const auto& u : units)
		{
			REQUIRE_FALSE(u.hasHadTurn);
		}
	}

	TEST_CASE("2018 Day 15 sortUnitsForTurn works", "[2018][Day15]")
	{
		std::vector<BBUnit> units = {
			BBUnit{.type = 'E', .position = Vector2i{5,2}, .hasHadTurn = true },
			BBUnit{.type = 'G', .position = Vector2i{2,3}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{4,3}, .hasHadTurn = true },
			BBUnit{.type = 'G', .position = Vector2i{2,1}, .hasHadTurn = true },
			BBUnit{.type = 'G', .position = Vector2i{3,2}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{4,1}, .hasHadTurn = true },
			BBUnit{.type = 'E', .position = Vector2i{1,2}, .hasHadTurn = true },
		};

		Day15Puzzle::sortUnitsForTurn(units);

		REQUIRE(Vector2i{2,1} == units[0].position);
		REQUIRE(Vector2i{4,1} == units[1].position);
		REQUIRE(Vector2i{1,2} == units[2].position);
		REQUIRE(Vector2i{3,2} == units[3].position);
		REQUIRE(Vector2i{5,2} == units[4].position);
		REQUIRE(Vector2i{2,3} == units[5].position);
		REQUIRE(Vector2i{4,3} == units[6].position);
	}

	TEST_CASE("2018 Day 15 identifyTargetCells works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
 "#######",
 "#.G.E.#",
 "#E.G.E#",
 "#.G.E.#",
 "#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		Day15Puzzle::sortUnitsForTurn(units);

		SECTION("For goblins") 
		{
			for (const auto& u : units)
			{
				if (u.type != 'G') { continue; }
				const BBUnit& g = u;

				const auto& targets = Day15Puzzle::identifyTargetCells(cave, g, units);

				REQUIRE(4 == targets.size());
				REQUIRE(targets.contains(Vector2i{ 4,1 }));
				REQUIRE(targets.contains(Vector2i{ 1,2 }));
				REQUIRE(targets.contains(Vector2i{ 5,2 }));
				REQUIRE(targets.contains(Vector2i{ 4,3 }));
			}
		}

		SECTION("For elves")
		{
			for (const auto& u : units)
			{
				if (u.type != 'E') { continue; }
				const BBUnit& e = u;

				const auto& targets = Day15Puzzle::identifyTargetCells(cave, e, units);

				REQUIRE(3 == targets.size());
				REQUIRE(targets.contains(Vector2i{ 2,1 }));
				REQUIRE(targets.contains(Vector2i{ 3,2 }));
				REQUIRE(targets.contains(Vector2i{ 2,3 }));
			}
		}
	}

	TEST_CASE("2018 Day 15 identifyDestinationCells works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
 "#######",
 "#E..G.#",
 "#...#.#",
 "#.G.#G#",
 "#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		Day15Puzzle::sortUnitsForTurn(units);

		const auto& targets = Day15Puzzle::identifyTargetCells(cave, units[0], units);

		const auto& destinations = Day15Puzzle::identifyDestinationCells(cave, units[0], units, targets);

		REQUIRE(6 == destinations.size());
		REQUIRE(destinations.contains(Vector2i{3,1}));
		REQUIRE(destinations.contains(Vector2i{5,1}));
		REQUIRE(destinations.contains(Vector2i{2,2}));
		REQUIRE(destinations.contains(Vector2i{5,2}));
		REQUIRE(destinations.contains(Vector2i{1,3}));
		REQUIRE(destinations.contains(Vector2i{3,3}));
	}

	TEST_CASE("2018 Day 15 identifyReachableDestinationCells works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
 "#######",
 "#E..G.#",
 "#...#.#",
 "#.G.#G#",
 "#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		Day15Puzzle::sortUnitsForTurn(units);

		const auto& targets = Day15Puzzle::identifyTargetCells(cave, units[0], units);

		const auto& destinations = Day15Puzzle::identifyDestinationCells(cave, units[0], units, targets);

		const auto& info = Day15Puzzle::identifyReachableAndNearestDestinationCells(cave, units[0], units, destinations);

		REQUIRE(4 == info.reachable.size());
		REQUIRE(info.reachable.contains(Vector2i{ 3,1 }));
		REQUIRE(info.reachable.contains(Vector2i{ 2,2 }));
		REQUIRE(info.reachable.contains(Vector2i{ 1,3 }));
		REQUIRE(info.reachable.contains(Vector2i{ 3,3 }));

		REQUIRE(3 == info.nearest.size());
		REQUIRE(info.nearest.contains(Vector2i{ 3,1 }));
		REQUIRE(info.nearest.contains(Vector2i{ 2,2 }));
		REQUIRE(info.nearest.contains(Vector2i{ 1,3 }));

		REQUIRE(Vector2i{ 3,1 } == info.chosen);
	}

	TEST_CASE("2018 Day 15 identifyNextMove works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
 "#######",
 "#.E...#",
 "#.....#",
 "#...G.#",
 "#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		Day15Puzzle::sortUnitsForTurn(units);

		const auto& targets = Day15Puzzle::identifyTargetCells(cave, units[0], units);

		const auto& destinations = Day15Puzzle::identifyDestinationCells(cave, units[0], units, targets);

		auto info = Day15Puzzle::identifyReachableAndNearestDestinationCells(cave, units[0], units, destinations);

		Day15Puzzle::identifyNextMove(cave, units[0], units, info);

		REQUIRE(3 == destinations.size());
		REQUIRE(destinations.contains(Vector2i{ 4,2 }));
		REQUIRE(destinations.contains(Vector2i{ 3,3 }));
		REQUIRE(destinations.contains(Vector2i{ 5,3 }));

		REQUIRE(3 == info.reachable.size());
		REQUIRE(info.reachable.contains(Vector2i{ 4,2 }));
		REQUIRE(info.reachable.contains(Vector2i{ 3,3 }));
		REQUIRE(info.reachable.contains(Vector2i{ 5,3 }));

		REQUIRE(2 == info.nearest.size());
		REQUIRE(info.nearest.contains(Vector2i{ 4,2 }));
		REQUIRE(info.nearest.contains(Vector2i{ 3,3 }));

		REQUIRE(Vector2i{ 4,2 } == info.chosen);

		REQUIRE(2 == info.nextMoves.size());
		REQUIRE(info.nextMoves.contains(Vector2i{ 3,1 }));
		REQUIRE(info.nextMoves.contains(Vector2i{ 2,2 }));

		REQUIRE(Vector2i{ 3,1 } == info.chosenNextMove);
	}

	TEST_CASE("2018 Day 15 applyNextMove works", "[2018][Day15]")
	{
		BBUnit unit{};
		BBUnitMovementInfo info;
		info.chosenNextMove = { 3,6 };

		Day15Puzzle::applyNextMove(unit, info);

		REQUIRE(unit.position == info.chosenNextMove);
	}

	TEST_CASE("2018 Day 15 runMovementTurn works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
"#########",
"#G..G..G#",
"#.......#",
"#.......#",
"#G..E..G#",
"#.......#",
"#.......#",
"#G..G..G#",
"#########",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#########",
"#G..G..G#",
"#.......#",
"#.......#",
"#G..E..G#",
"#.......#",
"#.......#",
"#G..G..G#",
"#########",
			}));

		Day15Puzzle::runMovementTurn(cave, units);

		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#########",
"#.G...G.#",
"#...G...#",
"#...E..G#",
"#.G.....#",
"#.......#",
"#G..G..G#",
"#.......#",
"#########",
			}));

		Day15Puzzle::runMovementTurn(cave, units);

		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#########",
"#..G.G..#",
"#...G...#",
"#.G.E.G.#",
"#.......#",
"#G..G..G#",
"#.......#",
"#.......#",
"#########",
			}));

		Day15Puzzle::runMovementTurn(cave, units);

		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#########",
"#.......#",
"#..GGG..#",
"#..GEG..#",
"#G..G...#",
"#......G#",
"#.......#",
"#.......#",
"#########",
			}));

		Day15Puzzle::runMovementTurn(cave, units);

		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#########",
"#.......#",
"#..GGG..#",
"#..GEG..#",
"#G..G...#",
"#......G#",
"#.......#",
"#.......#",
"#########",
			}));

	}

	TEST_CASE("2018 Day 15 runAttackTurnForUnit works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
"#######",
"#G....#",
"#..G..#",
"#..EG.#",
"#..G..#",
"#...G.#",
"#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		units[0].hitPoints = 9;
		units[1].hitPoints = 4;
		units[3].hitPoints = 2;
		units[4].hitPoints = 2;
		units[5].hitPoints = 1;

		Day15Puzzle::runAttackTurnForUnit(cave, units[2], units);

		REQUIRE(units.size() == 5);
	}

	TEST_CASE("2018 Day 15 runFullRound works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
"#######",
"#.G...#",
"#...EG#",
"#.#.#G#",
"#..G#E#",
"#.....#",
"#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		//std::cout << "Initially:" << std::endl;
		//Day15Puzzle::printBeverageCave(cave, units);

		const int rounds = 47;
		for (int i = 1; i <= rounds; ++i)
		{
			Day15Puzzle::runFullRound(cave, units);
			//std::cout << "\nAfter " << i << " round:" << std::endl;
			//Day15Puzzle::printBeverageCave(cave, units);
		}


		REQUIRE(Day15Puzzle::compareCaveToLives(cave, units, {
"#######",
"#G....#",
"#.G...#",
"#.#.#G#",
"#...#.#",
"#....G#",
"#######",
			}));
	}

	TEST_CASE("2018 Day 15 runToCompletion works", "[2018][Day15]")
	{
		SECTION("example 1")
		{

			const std::vector<std::string> input = {
	"#######",
	"#.G...#",
	"#...EG#",
	"#.#.#G#",
	"#..G#E#",
	"#.....#",
	"#######",
			};

			auto [units, cave] = Day15Puzzle::load(input);

			const auto completedRounds = Day15Puzzle::runToCompletion(cave, units);
			int remainingHealth = 0;

			for (const auto& u : units)
			{
				remainingHealth += u.hitPoints;
			}

			REQUIRE(47 == completedRounds);
			REQUIRE(590 == remainingHealth);
		}
		SECTION("example 2")
		{
			const std::vector<std::string> input = {
"#######",
"#G..#E#",
"#E#E.E#",
"#G.##.#",
"#...#E#",
"#...E.#",
"#######",
			};

			auto [units, cave] = Day15Puzzle::load(input);

			const auto completedRounds = Day15Puzzle::runToCompletion(cave, units);
			int remainingHealth = 0;

			for (const auto& u : units)
			{
				remainingHealth += u.hitPoints;
			}

			REQUIRE(37 == completedRounds);
			REQUIRE(982 == remainingHealth);
		}
	}

	TEST_CASE("2018 Day 15 solvePart2 works", "[2018][Day15]")
	{
		const std::vector<std::string> input = {
"#######",
"#.G...#",
"#...EG#",
"#.#.#G#",
"#..G#E#",
"#.....#",
"#######",
		};

		auto [units, cave] = Day15Puzzle::load(input);

		const auto res = Day15Puzzle::solvePart2(cave, units);

		REQUIRE("4988" == res);
	}
}
