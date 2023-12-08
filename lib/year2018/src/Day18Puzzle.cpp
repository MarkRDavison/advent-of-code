#include <2018/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <unordered_map>

#define GROUND '.'
#define TREES '|'
#define LUMBER '#'

namespace TwentyEighteen {


	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Settlers of The North Pole", 2018, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void Day18Puzzle::iterate(const LumberMap& current, LumberMap& next)
	{
		for (int y = current.minY; y <= current.maxY; ++y)
		{
			for (int x = current.minX; x <= current.maxX; ++x)
			{
				int adjGround = 0;
				int adjTrees = 0;
				int adjLumber = 0;

				for (int yOff = -1; yOff <= +1; ++yOff)
				{
					for (int xOff = -1; xOff <= +1; ++xOff)
					{
						if (yOff == 0 && xOff == 0) { continue; }

						const Vector2i c{ x + xOff, y + yOff };

						if (current.minY <= c.y && c.y <= current.maxY &&
							current.minX <= c.x && c.x <= current.maxX)
						{
							const auto cell = current.getCell(c.x, c.y);

							if (cell == GROUND) { adjGround++; }
							if (cell == TREES) { adjTrees++; }
							if (cell == LUMBER) { adjLumber++; }
						}
					}
				}

				const auto currCell = current.getCell(x, y);

				next.getCell(x, y) = currCell;
				if (currCell == GROUND)
				{
					if (adjTrees >= 3)
					{
						next.getCell(x, y) = TREES;
					}
				}
				else if (currCell == TREES)
				{
					if (adjLumber >= 3)
					{
						next.getCell(x, y) = LUMBER;
					}
				}
				else if (currCell == LUMBER)
				{
					if (adjTrees == 0 || adjLumber == 0)
					{
						next.getCell(x, y) = GROUND;
					}
				}
			}
		}
	}

	void Day18Puzzle::draw(const LumberMap& map, int iteration)
	{
		if (iteration == 0)
		{
			std::cout << "Initial state:" << std::endl;
		}
		else
		{
			std::cout << "After " << iteration << " minute:" << std::endl;
		}

		for (int y = map.minY; y <= map.maxY; ++y)
		{
			for (int x = map.minX; x <= map.maxX; ++x)
			{
				std::cout << map.getCell(x, y);
			}
			std::cout << '\n';
		}
		std::cout << std::endl;
	}

	std::string getMapString(const LumberMap& map)
	{
		std::string str;

		for (int y = map.minY; y <= map.maxY; ++y)
		{
			for (int x = map.minX; x <= map.maxX; ++x)
			{
				const auto c = map.getCell(x, y);
				str += c;
			}
		}

		return str;
	}

	long long getValue(const LumberMap& map)
	{
		long long trees = 0;
		long long lumber = 0;

		for (int y = map.minY; y <= map.maxY; ++y)
		{
			for (int x = map.minX; x <= map.maxX; ++x)
			{
				const auto c = map.getCell(x, y);
				if (c == TREES) { trees++; }
				if (c == LUMBER) { lumber++; }
			}
		}

		return trees * lumber;
	}

	std::string solve(const std::vector<std::string>& lines, long long number)
	{
		LumberMap map1;
		LumberMap map2;


		for (std::size_t y = 0; y < lines.size(); ++y)
		{
			for (std::size_t x = 0; x < lines[y].size(); ++x)
			{
				map1.getCell((int)x, (int)y) = lines[y][x];
				map2.getCell((int)x, (int)y) = lines[y][x];
			}
		}

		long long periodStart = 0;
		long long periodEnd = 0;

		std::unordered_map<std::string, long long> seen;
		std::unordered_map<long long, long long> values;
		LumberMap* curr = &map1;
		LumberMap* next = &map2;
		for (long long i = 1; i <= number; ++i)
		{
			Day18Puzzle::iterate(*curr, *next);

			const auto& str = getMapString(*next);
			values.emplace(i, getValue(*next));

			if (seen.contains(str))
			{
				periodStart = seen.at(str);
				periodEnd = i;
				break;
			}

			seen.emplace(str, i);

			std::swap(curr, next);
		}

		const auto period = periodEnd - periodStart;
		const auto cycleForAnswer = number - periodStart;

		if (period > 0 && cycleForAnswer > 0)
		{
			number = periodStart + cycleForAnswer % period;
		}

		const auto answer = values.at(number);

		return std::to_string(answer);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {

		const auto part1 = solve(m_InputLines, 10);
		const auto part2 = solve(m_InputLines, 1000000000);
		
		return { part1, part2 };
	}
}
