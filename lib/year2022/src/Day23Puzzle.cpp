#include <2022/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <unordered_map>
#include <unordered_set>
#include <functional>

namespace TwentyTwentyTwo {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Unstable Diffusion", 2022, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct AshCell
	{
		char c{ '.' };
	};

	typedef core::Region<AshCell> AshMap;
	typedef std::pair<Vector2i, Vector2i> Bounds;

	bool HAS_ELF(AshMap& map, int x, int y)
	{
		const auto&cell = map.getCell(x, y);
		return cell.c == '#';
	}

	void printAshMap(const AshMap& map, const Bounds& bounds, int round)
	{
		std::cout << "=========================" << (round == 0 ? " initial" : std::to_string(round)) << "\n";

		for (int y = bounds.first.y; y <= bounds.second.y; ++y)
		{
			std::string row;

			for (int x = bounds.first.x; x <= bounds.second.x; ++x)
			{
				const auto& cell = map.getCell(x, y);
				row += cell.c;
			}

			std::cout << row << std::endl;
		}
	}
	
	std::pair<Bounds, int> process(AshMap& curr, AshMap& next, long long index)
	{
		int moved = 0;
		Bounds bounds{
			{+9999999,+9999999},
			{-9999999,-9999999}
		};

		std::unordered_map<
			Vector2i, 
			std::unordered_set<
				Vector2i, 
				Vector2_Hash_Fxn<int>>, 
			Vector2_Hash_Fxn<int>
		> proposed;

		std::unordered_set<
			Vector2i,
			Vector2_Hash_Fxn<int>> elves;

		const std::vector<std::function<bool(int, int)>> processes = {
			// Check NORTH
			[&proposed, &curr](int x, int y) -> bool {
				bool NE = HAS_ELF(curr, x - 1, y - 1);
				bool NN = HAS_ELF(curr, x + 0, y - 1);
				bool NW = HAS_ELF(curr, x + 1, y - 1);
				if (!NE && !NN && !NW)
				{
					proposed[{x, y - 1}].insert({ x, y });
					return true;
				}
				return false;
			},
			// Check SOUTH
			[&proposed, &curr](int x, int y) -> bool {
				bool SE = HAS_ELF(curr, x - 1, y + 1);
				bool SS = HAS_ELF(curr, x + 0, y + 1);
				bool SW = HAS_ELF(curr, x + 1, y + 1);
				if (!SE && !SS && !SW)
				{
					proposed[{x, y + 1}].insert({ x, y });
					return true;
				}
				return false;
			},
			// Check WEST
			[&proposed, &curr](int x, int y) -> bool {
				bool WN = HAS_ELF(curr, x - 1, y - 1);
				bool WW = HAS_ELF(curr, x - 1, y + 0);
				bool WS = HAS_ELF(curr, x - 1, y + 1);
				if (!WN && !WW && !WS)
				{
					proposed[{x - 1, y}].insert({ x, y });
					return true;
				}
				return false;
			},
			// Check EAST
			[&proposed, &curr](int x, int y) -> bool {
				bool EN = HAS_ELF(curr, x + 1, y - 1);
				bool EE = HAS_ELF(curr, x + 1, y + 0);
				bool ES = HAS_ELF(curr, x + 1, y + 1);
				if (!EN && !EE && !ES)
				{
					proposed[{x + 1, y}].insert({ x, y });
					return true;
				}
				return false;
			},
		};

		// Process - stage 1
		for (int y = curr.minY; y <= curr.maxY; ++y)
		{
			for (int x = curr.minX; x <= curr.maxX; ++x)
			{
				const auto& cell = curr.getCell(x, y);
				if (cell.c != '#') { continue; }

				int surroundingElves = 0;
				elves.insert({ x, y });

				for (int yOff = -1; yOff <= +1; ++yOff)
				{
					for (int xOff = -1; xOff <= +1; ++xOff)
					{
						if (yOff == 0 && xOff == 0) { continue; }

						if (HAS_ELF(curr, x + xOff, y + yOff))
						{
							surroundingElves++;
						}
					}
				}

				if (surroundingElves == 0)
				{
					continue;
				}

				if (processes[(index + 0) % 4](x, y))
				{
				}
				else if (processes[(index + 1) % 4](x, y))
				{
				}
				else if (processes[(index + 2) % 4](x, y))
				{
				}
				else if (processes[(index + 3) % 4](x, y))
				{
				}
			}
		}

		for (const auto& [proposedLocation, proposingElves] : proposed)
		{
			if (proposingElves.size() == 1)
			{
				next.getCell(proposedLocation.x, proposedLocation.y).c = '#';
				elves.erase(*proposingElves.begin());
				moved++;
			}
		}

		for (const auto& elf : elves)
		{
			next.getCell(elf.x, elf.y).c = '#';
		}

		// Compute bounds
		for (int y = next.minY; y <= next.maxY; ++y)
		{
			for (int x = next.minX; x <= next.maxX; ++x)
			{
				if (HAS_ELF(next, x, y))
				{
					bounds.first.x = std::min(bounds.first.x, (int)x);
					bounds.first.y = std::min(bounds.first.y, (int)y);
					bounds.second.x = std::max(bounds.second.x, (int)x);
					bounds.second.y = std::max(bounds.second.y, (int)y);
				}
			}
		}

		return { bounds, moved };
	}

	long long countCellsContainingElves(const AshMap& map, const Bounds& bounds)
	{
		long long count = 0;
		for (int y = bounds.first.y; y <= bounds.second.y; ++y)
		{
			for (int x = bounds.first.x; x <= bounds.second.x; ++x)
			{
				if (map.getCell(x, y).c == '.')
				{
					count++;
				}
			}
		}
		return count;
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {

		AshMap map1;
		AshMap map2;
		Bounds bounds{
			{+9999999,+9999999},
			{-9999999,-9999999}
		};
		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x)
			{
				const char c = m_InputLines[y][x];
				if (c == '#')
				{
					bounds.first.x = std::min(bounds.first.x, (int)x);
					bounds.first.y = std::min(bounds.first.y, (int)y);
					bounds.second.x = std::max(bounds.second.x, (int)x);
					bounds.second.y = std::max(bounds.second.y, (int)y);
				}
				map1.getCell((int)x, (int)y).c = c;
				map2.getCell((int)x, (int)y).c = '.';
			}
		}

		long long rounds = 0;
		if (getVerbose())
		{
			printAshMap(map1, bounds, rounds);
		}

		long long part1 = -1;
		long long part2 = 0;

		AshMap* curr = &map1;
		AshMap* next = &map2;

		while (true)
		{
			const auto& [b, moved] = process(*curr, *next, rounds);
			bounds = b;
			++rounds;

			curr->clear();
			std::swap(curr, next);
			if (getVerbose())
			{
				printAshMap(*curr, bounds, rounds);
			}

			if (!moved)
			{
				if (part1 == -1)
				{
					part1 = countCellsContainingElves(*curr, bounds);
				}
				part2 = rounds;
				break;
			}

			if (rounds == 10)
			{
				part1 = countCellsContainingElves(*curr, bounds);
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
