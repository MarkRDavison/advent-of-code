#include <2022/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <cassert>

namespace TwentyTwentyTwo {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Treetop Tree House", 2022, 8) {
	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {

		core::Region<int> forest;

		int y = 0;
		for (const auto& l : m_InputLines)
		{
			int x = 0;
			for (const char c : l)
			{
				forest.getCell(x, y) = (int)(c - '0');
				x++;
			}

			y++;
		}

		const int size = forest.maxX - forest.minX + 1;
		assert(size == forest.maxY - forest.minY + 1);

		int part1 = 0;
		int part2 = 0;

		for (int y = forest.minY; y <= forest.maxY; ++y)
		{
			for (int x = forest.minX; x <= forest.maxX; ++x)
			{

				const int current = forest.getCell(x, y);

				int invalidatedCount = 0;
				
				bool visible = true;
				// UP
				for (int yCheck = y - 1; yCheck >= forest.minY; --yCheck)
				{
					const int toCheck = forest.getCell(x, yCheck);
					if (toCheck >= current)
					{
						// Not visible
						invalidatedCount++;
						visible = false;
						break;
					}
				}
				
				// DOWN
				if (!visible)
				{
					visible = false;
					for (int yCheck = y + 1; yCheck <= forest.maxY; ++yCheck)
					{
						const int toCheck = forest.getCell(x, yCheck);
						if (toCheck >= current)
						{
							// Not visible
							invalidatedCount++;
							visible = false;
							break;
						}
					}
				}
				
				// LEFT
				if (!visible)
				{
					visible = false;
					for (int xCheck = x - 1; xCheck >= forest.minX; --xCheck)
					{
						const int toCheck = forest.getCell(xCheck, y);
						if (toCheck >= current)
						{
							// Not visible
							invalidatedCount++;
							visible = false;
							break;
						}
					}
				}
				
				// RIGHT
				if (!visible)
				{
					visible = false;
					for (int xCheck = x + 1; xCheck <= forest.maxX; ++xCheck)
					{
						const int toCheck = forest.getCell(xCheck, y);
						if (toCheck >= current)
						{
							// Not visible
							invalidatedCount++;
							visible = false;
							break;
						}
					}
				}

				if (invalidatedCount < 4)
				{
					part1++;
				}

				{


					int upScore = 0;
					int downScore = 0;
					int leftScore = 0;
					int rightScore = 0;

					// UP
					for (int yCheck = y - 1; yCheck >= forest.minY; --yCheck)
					{
						const int toCheck = forest.getCell(x, yCheck);
						upScore ++;
						if (toCheck >= current)
						{
							break;
						}
					}

					// DOWN
					for (int yCheck = y + 1; yCheck <= forest.maxY; ++yCheck)
					{
						const int toCheck = forest.getCell(x, yCheck);
						downScore ++;
						if (toCheck >= current)
						{
							break;
						}
					}

					// LEFT
					for (int xCheck = x - 1; xCheck >= forest.minX; --xCheck)
					{
						const int toCheck = forest.getCell(xCheck, y);
						leftScore ++;
						if (toCheck >= current)
						{
							break;
						}
					}

					// RIGHT
					for (int xCheck = x + 1; xCheck <= forest.maxX; ++xCheck)
					{
						const int toCheck = forest.getCell(xCheck, y);
						rightScore ++;
						if (toCheck >= current)
						{
							break;
						}
					}

					int scenicScore = upScore * downScore * leftScore * rightScore;

					part2 = std::max(scenicScore, part2);
				}


			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
