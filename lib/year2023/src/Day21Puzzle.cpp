#include <2023/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

namespace TwentyTwentyThree {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Step Counter", 2023, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct StepCell
	{
		char c{ '.' };
	};

	typedef std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> CoordSet;
	typedef core::Region<StepCell> Garden;

	void printGarden(const Garden& garden, const CoordSet& set)
	{
		std::cout << "====================" << std::endl;
		for (int y = garden.minY; y <= garden.maxY; ++y)
		{
			std::string row;
			for (int x = garden.minX; x <= garden.maxX; ++x)
			{
				if (set.contains(Vector2i(x, y)))
				{
					row += 'O';
				}
				else
				{
					row += garden.getCell(x, y).c;
				}
			}
			std::cout << row << std::endl;
		}
	}

	void addCellIfAllowed(
		Garden& garden,
		CoordSet& map,
		const Vector2i& coord
	)
	{
		auto& gardenCell = garden.getCell(coord.x, coord.y);
		if (gardenCell.c == '#')
		{
			return;
		}

		map.insert(coord);
	}

	long long getReachablePlots(Garden garden, const Vector2i& start, int maxSteps)
	{
		CoordSet map1;
		CoordSet map2;

		map1.emplace(start);

		CoordSet* currMap = &map1;
		CoordSet* nextMap = &map2;

		for (int i = 0; i < maxSteps; ++i)
		{
			for (const auto& coord : *currMap)
			{
				addCellIfAllowed(garden, *nextMap, coord + Vector2i(-1, 0));
				addCellIfAllowed(garden, *nextMap, coord + Vector2i(+1, 0));
				addCellIfAllowed(garden, *nextMap, coord + Vector2i(0, -1));
				addCellIfAllowed(garden, *nextMap, coord + Vector2i(0, +1));
			}

			std::swap(currMap, nextMap);
			nextMap->clear();
		}

		long long canReach = 0;

		for (const auto& [coord, count] : *currMap)
		{
			canReach++;
		}

		if (maxSteps > 64)
		{
			printGarden(garden, *currMap);
		}

		return canReach;
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve(int numStepsPart1, int numStepsPart2)
	{
		Garden garden;

		Vector2i start;

		Vector2i offset = { 
			(int)(m_InputLines.size() - 1) / 2, 
			(int)(m_InputLines.size() - 1) / 2
		};

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x)
			{
				auto& cell = garden.getCell((int)(x) - offset.x, (int)(y) - offset.y);
				cell.c = m_InputLines[y][x];

				if (cell.c == 'S')
				{
					start = { (int)(x) - offset.x, (int)(y) - offset.y };
				}
			}
		}

		assert(m_InputLines.size() == m_InputLines[0].size());
		assert(start.x == 0 && start.y == 0);

		const auto part1 = getReachablePlots(garden, start, numStepsPart1);
		
		auto part2 = 0;

		if (m_InputLines.size() > 15)
		{
			part2 = getReachablePlots(garden, start, numStepsPart2);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return fastSolve(64, 64 + 1 * 131);// 26501365);
	}
}
