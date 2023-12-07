#include <2018/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <queue>
#include <cassert>

namespace TwentyEighteen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Beverage Bandits", 2018, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}

	std::vector<Vector2i> getNeighbours(const Vector2i& coord)
	{
		return {
			{ coord.x, coord.y - 1 },
			{ coord.x - 1, coord.y },
			{ coord.x + 1, coord.y },
			{ coord.x, coord.y + 1 }
		};
	}

	bool isNeighbourOf(const Vector2i& coord, const Vector2i& potentialNeighbour)
	{
		for (const auto& n : getNeighbours(coord))
		{
			if (n == potentialNeighbour)
			{
				return true;
			}
		}

		return false;
	}

	std::vector<Vector2i> getEmptyNeighbours(const Vector2i& coord, const Cave& cave)
	{
		std::vector<Vector2i> en;

		for (const auto& c : getNeighbours(coord))
		{
			if (cave.getCell(c.x, c.y) == '.')
			{
				en.push_back(c);
			}
		}

		return en;
	}

	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	std::pair<Units, Cave> Day15Puzzle::load(const std::vector<std::string>& input)
	{
		Units units;
		Cave cave;

		for (int y = 0; y < (int)input.size(); ++y)
		{
			for (int x = 0; x < (int)input[(std::size_t)y].size(); ++x)
			{
				auto& cell = cave.getCell(x, y);

				const char c = input[y][x];

				if (c == '#')
				{
					cell = '#';
				}
				else if (c == '.')
				{
					cell = '.';
				}
				else if (c == 'G')
				{
					cell = '.';
					auto& u = units.emplace_back();
					u.type = 'G';
					u.position = { x,y };
				}
				else if (c == 'E')
				{
					cell = '.';
					auto& u = units.emplace_back();
					u.type = 'E';
					u.position = { x,y };
				}
				else
				{
					throw std::runtime_error("Invalid cell");
				}
			}
		}

		return { units, cave };
	}

	void Day15Puzzle::resetUnitsForTurn(Units& units)
	{
		for (auto& u : units)
		{
			u.hasHadTurn = false;
		}
	}

	void Day15Puzzle::sortUnitsForTurn(Units& units)
	{
		std::sort(
			units.begin(),
			units.end(),
			[](const BBUnit& lhs, const BBUnit& rhs) -> int
			{
				if (lhs.position.y == rhs.position.y)
				{
					return lhs.position.x < rhs.position.x;
				}
				return lhs.position.y < rhs.position.y;
			});
	}

	void Day15Puzzle::removeDeadUnits(Units& units)
	{
		units.erase(
			std::remove_if(
				units.begin(), 
				units.end(), 
				[](const BBUnit& u) -> bool 
				{
					return u.hitPoints < 0;
				}), 
			units.end());
	}

	Vector2iSet Day15Puzzle::identifyTargetCells(const Cave& cave, const BBUnit& activeUnit, const Units& units)
	{
		Vector2iSet targets;

		for (const auto& u : units)
		{
			if (u.type != activeUnit.type)
			{
				targets.insert(u.position);
			}
		}

		return targets;
	}

	std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> Day15Puzzle::identifyDestinationCells(const Cave& cave, const BBUnit& activeUnit, const Units& units, const Vector2iSet& targetCells)
	{
		Vector2iSet destinations;

		for (const auto& t : targetCells)
		{
			// UP
			if (cave.getCell(t.x, t.y - 1) == '.')
			{
				destinations.insert(Vector2i{ t.x,t.y - 1 });
			}
			// LEFT
			if (cave.getCell(t.x - 1, t.y) == '.')
			{
				destinations.insert(Vector2i{ t.x - 1,t.y });
			}
			// RIGHT
			if (cave.getCell(t.x + 1, t.y) == '.')
			{
				destinations.insert(Vector2i{ t.x + 1,t.y });
			}
			// DOWN
			if (cave.getCell(t.x, t.y + 1) == '.')
			{
				destinations.insert(Vector2i{ t.x,t.y + 1 });
			}
		}

		return destinations;
	}

	BBUnitMovementInfo Day15Puzzle::identifyReachableAndNearestDestinationCells(const Cave& cave, const BBUnit& activeUnit, const Units& units, const Vector2iSet& destinationCells)
	{
		Vector2iSet reachable;

		FloodCave flood;
		for (int y = 0; y <= cave.maxY; ++y)
		{
			for (int x = 0; x <= cave.maxX; ++x)
			{
				const auto& c = cave.getCell(x, y);
				flood.getCell(x, y).c = c;
			}
		}

		for (const auto& u : units)
		{
			if (u.position != activeUnit.position)
			{
				flood.getCell(u.position.x, u.position.y).c = '*';
			}
		}

		Vector2iSet seen;
		std::queue<Vector2i> active;
		Vector2iMap<int>::type activeDistances;
		active.push(activeUnit.position);
		activeDistances.emplace(activeUnit.position, 0);

		while (!active.empty())
		{
			const auto curr = active.front();
			active.pop();

			const auto currDistance = activeDistances.at(curr);

			// UP
			const auto up = Vector2i{ curr.x, curr.y - 1 };
			auto& upCell = flood.getCell(up.x, up.y);
			if (upCell.c == '.')
			{
				if (!activeDistances.contains(up))
				{
					seen.insert(up);
					active.push(up);
					activeDistances.emplace(up, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(up) > currDistance + 1)
					{
						active.push(up);
						activeDistances[up] = currDistance + 1;
					}
				}
			}
			// LEFT
			const auto left = Vector2i{ curr.x - 1, curr.y };
			auto& leftCell = flood.getCell(left.x, left.y);
			if (leftCell.c == '.')
			{
				if (!activeDistances.contains(left))
				{
					seen.insert(left);
					active.push(left);
					activeDistances.emplace(left, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(left) > currDistance + 1)
					{
						active.push(left);
						activeDistances[left] = currDistance + 1;
					}
				}
			}
			// RIGHT
			const auto right = Vector2i{ curr.x + 1, curr.y };
			auto& rightCell = flood.getCell(right.x, right.y);
			if (rightCell.c == '.')
			{
				if (!activeDistances.contains(right))
				{
					seen.insert(right);
					active.push(right);
					activeDistances.emplace(right, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(right) > currDistance + 1)
					{
						active.push(right);
						activeDistances[right] = currDistance + 1;
					}
				}
			}
			// DOWN
			const auto down = Vector2i{ curr.x, curr.y + 1 };
			auto& downCell = flood.getCell(down.x, down.y);
			if (downCell.c == '.')
			{
				if (!activeDistances.contains(down))
				{
					seen.insert(down);
					active.push(down);
					activeDistances.emplace(down, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(down) > currDistance + 1)
					{
						active.push(down);
						activeDistances[down] = currDistance + 1;
					}
				}
			}
		}

		int minDistance = std::numeric_limits<int>::max();

		for (const auto& dest : destinationCells)
		{
			if (seen.contains(dest))
			{
				reachable.insert(dest);
				minDistance = std::min(minDistance, activeDistances.at(dest));
			}
		}

		Vector2iSet nearest;

		for (const auto& r : reachable)
		{
			if (activeDistances.at(r) == minDistance)
			{
				nearest.insert(r);
			}
		}

		const auto minElement = std::min_element(
			nearest.begin(),
			nearest.end(),
			[](const Vector2i& lhs, const Vector2i& rhs) -> int
			{
				if (lhs.y == rhs.y)
				{
					return lhs.x < rhs.x;
				}
				return lhs.y < rhs.y;
			});

		return BBUnitMovementInfo
		{
			.reachable = reachable, 
			.nearest = nearest,
			.chosen = minElement == nearest.end() ? Vector2i{-1,-1} : *minElement
		};
	}

	void Day15Puzzle::identifyNextMove(const Cave& cave, const BBUnit& activeUnit, const Units& units, BBUnitMovementInfo& info)
	{
		Vector2iSet seen;
		std::queue<Vector2i> active;
		Vector2iMap<int>::type activeDistances;
		active.push(info.chosen);
		activeDistances.emplace(info.chosen, 0);

		FloodCave flood;
		for (int y = 0; y <= cave.maxY; ++y)
		{
			for (int x = 0; x <= cave.maxX; ++x)
			{
				const auto& c = cave.getCell(x, y);
				flood.getCell(x, y).c = c;
			}
		}

		for (const auto& u : units)
		{
			if (u.position != activeUnit.position)
			{
				flood.getCell(u.position.x, u.position.y).c = '*';
			}
		}

		while (!active.empty())
		{
			const auto curr = active.front();
			active.pop();

			const auto currDistance = activeDistances.at(curr);

			// UP
			const auto up = Vector2i{ curr.x, curr.y - 1 };
			const auto& upCell = flood.getCell(up.x, up.y);
			if (upCell.c == '.')
			{
				if (!activeDistances.contains(up))
				{
					seen.insert(up);
					active.push(up);
					activeDistances.emplace(up, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(up) > currDistance + 1)
					{
						active.push(up);
						activeDistances[up] = currDistance + 1;
					}
				}
			}
			// LEFT
			const auto left = Vector2i{ curr.x - 1, curr.y };
			const auto& leftCell = flood.getCell(left.x, left.y);
			if (leftCell.c == '.')
			{
				if (!activeDistances.contains(left))
				{
					seen.insert(left);
					active.push(left);
					activeDistances.emplace(left, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(left) > currDistance + 1)
					{
						active.push(left);
						activeDistances[left] = currDistance + 1;
					}
				}
			}
			// RIGHT
			const auto right = Vector2i{ curr.x + 1, curr.y };
			const auto& rightCell = flood.getCell(right.x, right.y);
			if (rightCell.c == '.')
			{
				if (!activeDistances.contains(right))
				{
					seen.insert(right);
					active.push(right);
					activeDistances.emplace(right, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(right) > currDistance + 1)
					{
						active.push(right);
						activeDistances[right] = currDistance + 1;
					}
				}
			}
			// DOWN
			const auto down = Vector2i{ curr.x, curr.y + 1 };
			const auto& downCell = flood.getCell(down.x, down.y);
			if (downCell.c == '.')
			{
				if (!activeDistances.contains(down))
				{
					seen.insert(down);
					active.push(down);
					activeDistances.emplace(down, currDistance + 1);
				}
				else
				{
					if (activeDistances.at(down) > currDistance + 1)
					{
						active.push(down);
						activeDistances[down] = currDistance + 1;
					}
				}
			}
		}

		int minDistance = std::numeric_limits<int>::max();

		for (const auto& c : getEmptyNeighbours(activeUnit.position, cave))
		{
			if (activeDistances.contains(c))
			{
				const auto currentDistance = activeDistances.at(c);
				if (currentDistance < minDistance)
				{
					minDistance = currentDistance;
					info.nextMoves.clear();
				}

				if (currentDistance == minDistance)
				{
					info.nextMoves.insert(c);
				}
			}
		}

		info.chosenNextMove = Vector2i{ -1,-1 };
		if (!info.nextMoves.empty())
		{
			const auto minElement = std::min_element(
				info.nextMoves.begin(),
				info.nextMoves.end(),
				[](const Vector2i& lhs, const Vector2i& rhs) -> int
				{
					if (lhs.y == rhs.y)
					{
						return lhs.x < rhs.x;
					}
					return lhs.y < rhs.y;
				});

			info.chosenNextMove = *minElement;
		}
	}

	void Day15Puzzle::applyNextMove(BBUnit& activeUnit, const BBUnitMovementInfo& info)
	{
		assert((info.chosenNextMove != Vector2i{ -1,-1 }));

		activeUnit.position = info.chosenNextMove;
	}
	
	void Day15Puzzle::runMovementTurn(const Cave& cave, Units& units)
	{
		// This is only for debugging, dont use during actual run
		sortUnitsForTurn(units);
		for (auto& u : units)
		{
			runMovementTurnForUnit(cave, u, units);
		}
	}

	bool Day15Puzzle::runMovementTurnForUnit(const Cave& cave, BBUnit& activeUnit, const Units& units)
	{
		const auto& targets = Day15Puzzle::identifyTargetCells(cave, activeUnit, units);
		if (targets.empty())
		{
			return false;
		}

		bool targetAlreadyInRange = false;
		for (const auto& n : getNeighbours(activeUnit.position))
		{
			for (const auto& t : targets)
			{
				if (t == n)
				{
					targetAlreadyInRange = true;
					break;
				}
			}
			if (targetAlreadyInRange)
			{
				break;
			}
		}

		if (!targetAlreadyInRange)
		{
			const auto& destinations = Day15Puzzle::identifyDestinationCells(cave, activeUnit, units, targets);

			auto info = Day15Puzzle::identifyReachableAndNearestDestinationCells(cave, activeUnit, units, destinations);

			Day15Puzzle::identifyNextMove(cave, activeUnit, units, info);

			if (info.chosenNextMove != Vector2i{ -1,-1 })
			{
				Day15Puzzle::applyNextMove(activeUnit, info);
			}
		}

		return true;
	}

	void Day15Puzzle::runAttackTurnForUnit(const Cave& cave, BBUnit& activeUnit, Units& units)
	{
		std::vector<BBUnit*> neighbours;
		for (std::size_t i = 0; i < units.size(); ++i)
		{
			if (isNeighbourOf(activeUnit.position, units[i].position) && 
				activeUnit.type != units[i].type)
			{
				neighbours.push_back(&units[i]);
			}
		}
		
		activeUnit.hasHadTurn = true;
		if (!neighbours.empty())
		{
			std::sort(
				neighbours.begin(),
				neighbours.end(),
				[](const BBUnit* lhs, const BBUnit* rhs) -> int
				{
					if (lhs->hitPoints == rhs->hitPoints)
					{
						if (lhs->position.y == rhs->position.y)
						{
							return lhs->position.x < rhs->position.x;
						}

						return lhs->position.y < rhs->position.y;
					}

					return lhs->hitPoints < rhs->hitPoints;
				}
			);

			const auto target = neighbours[0];

			target->hitPoints -= activeUnit.attackPower;

			if (target->hitPoints <= 0)
			{
				removeDeadUnits(units);
			}
		}

	}

	bool Day15Puzzle::runFullRound(const Cave& cave, Units& units)
	{
		resetUnitsForTurn(units);
		sortUnitsForTurn(units);

		while (true)
		{
			bool unitProcessed = false;

			for (auto& u : units)
			{
				if (!u.hasHadTurn)
				{
					if (!runMovementTurnForUnit(cave, u, units))
					{
						return false;
					}
					runAttackTurnForUnit(cave, u, units);
					unitProcessed = true;
					break;
				}
			}

			if (!unitProcessed)
			{
				break;
			}
		}

		return true;
	}

	std::vector<std::string> Day15Puzzle::printCaveToLines(const Cave& cave, const Units& units)
	{
		std::vector<std::string> lines;

		for (int y = 0; y <= cave.maxY; ++y)
		{
			auto& l = lines.emplace_back();
			for (int x = 0; x <= cave.maxX; ++x)
			{
				l += cave.getCell(x, y);
			}
		}

		for (const auto& u : units)
		{
			lines[u.position.y][u.position.x] = u.type;
		}

		return lines;
	}
	void Day15Puzzle::printBeverageCave(const Cave& cave, const Units& units)
	{
		std::vector<const BBUnit*> sortedUnits;
		for (const auto& u : units)
		{
			sortedUnits.push_back(&u);
		}

		std::sort(
			sortedUnits.begin(),
			sortedUnits.end(),
			[](const BBUnit* lhs, const BBUnit* rhs) -> int
			{
				if (lhs->position.y == rhs->position.y)
				{
					return lhs->position.x < rhs->position.x;
				}

				return lhs->position.y < rhs->position.y;
			}
		);

		const auto& lines = printCaveToLines(cave, units);

		for (std::size_t i = 0; i < lines.size(); ++i)
		{
			std::cout << lines[i] << "\t";
			bool first = true;
			for (const auto& u : sortedUnits)
			{
				if (u->position.y == i)
				{
					if (!first)
					{
						std::cout << ", ";
					}

					std::cout << u->type << "(" << u->hitPoints << ")";

					first = false;
				}
			}

			std::cout << std::endl;
		}
	}
	bool Day15Puzzle::compareCaveToLives(const Cave& cave, const Units& units, const std::vector<std::string>& caveRepresentation)
	{
		const auto& lines = printCaveToLines(cave, units);

		if (lines.size() != caveRepresentation.size())
		{
			return false;
		}

		for (std::size_t i = 0; i < lines.size(); ++i)
		{
			if (lines[i] != caveRepresentation[i])
			{
				return false;
			}
		}

		return true;
	}

	int Day15Puzzle::runToCompletion(const Cave& cave, Units& units)
	{
		int i = 0;
		while (true)
		{
			if (!Day15Puzzle::runFullRound(cave, units))
			{
				i--;
			}
			++i;
			int goblins = 0;
			int elves = 0;

			for (const auto& u : units)
			{
				if (u.type == 'G')
				{
					goblins++;
				}
				else if (u.type == 'E')
				{
					elves++;
				}
			}

			if (goblins == 0 || elves == 0)
			{
				break;
			}
		}

		return i;
	}

	std::string Day15Puzzle::solvePart1(const Cave& cave, Units& units)
	{
		const auto completedRounds = Day15Puzzle::runToCompletion(cave, units);
		int remainingHealth = 0;

		for (const auto& u : units)
		{
			remainingHealth += u.hitPoints;
		}

		return std::to_string(completedRounds * remainingHealth);
	}
	std::string Day15Puzzle::solvePart2(const Cave& cave, const Units& units)
	{
		int elves = 0;
		for (const auto& u : units)
		{
			if (u.type == 'E')
			{
				elves++;
			}
		}
		int attackPower = 4;
		while (true)
		{
			Units upAttackedUnits;
			for (const auto& u : units)
			{
				upAttackedUnits.push_back(u);
				if (u.type == 'E')
				{
					upAttackedUnits.back().attackPower = attackPower;
				}
			}

			const auto completedRounds = Day15Puzzle::runToCompletion(cave, upAttackedUnits);
			int remainingHealth = 0;

			int aliveElves = 0;

			for (const auto& u : upAttackedUnits)
			{
				remainingHealth += u.hitPoints;
				if (u.type == 'E')
				{
					aliveElves++;
				}
			}


			bool valid = aliveElves == elves;

			std::cout << "Attack power of " << attackPower << " was" << (valid ? "" : " not") << " successful." << std::endl;
			
			if (valid)
			{
				return std::to_string(completedRounds * remainingHealth);
			}

			attackPower++;
		}
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		auto [units1, cave1] = load(m_InputLines);
		auto [units2, cave2] = load(m_InputLines);

		const auto part1 = solvePart1(cave1, units1);
		const auto part2 = solvePart2(cave2, units2);

		return { part1, part2 };
	}
}
