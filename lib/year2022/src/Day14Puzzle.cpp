#include <2022/Day14Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <algorithm>
#include <cassert>

namespace TwentyTwentyTwo {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Regolith Reservoir", 2022, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct RegolithCell {
		char val{ '.' };
	};

	void dump(core::Region<RegolithCell>& _region, int _minX, int _maxX)
	{
		for (int y = 0; y <= _region.maxY; ++y)
		{
			for (int x = _minX; x <= _maxX; ++x)
			{
				std::cout << _region.getCell(x, y).val;
			}
			std::cout << std::endl;
		}

	}

	bool isOpen(core::Region<RegolithCell>& _region, ze::Vector2i _coord)
	{
		const auto& cell = _region.getCell(_coord.x, _coord.y);

		if (cell.val == '#' || cell.val == 'o')
		{
			return false;
		}

		return true;
	}

	int solvePart1(core::Region<RegolithCell> _region, int _maxY, int _minX, int _maxX)
	{
		std::cout << "I: " << 0 << std::endl;
		dump(_region, _minX, _maxX);

		bool landed = true;
		int i = 0;
		while (landed)
		{
			i++;
			ze::Vector2i target = { 500, 0 };

			while (true)
			{
				if (target.y > _maxY)
				{
					landed = false;
					break;
				}
				// BELOW
				else if (isOpen(_region, target + ze::Vector2i(0, 1)))
				{
					target.y++;
				}
				else if (isOpen(_region, target + ze::Vector2i(-1, 1)))
				{
					target.x--;
					target.y++;
				}
				else if (isOpen(_region, target + ze::Vector2i(+1, 1)))
				{
					target.x++;
					target.y++;
				}
				else
				{
					auto& cell = _region.getCell(target.x, target.y);
					cell.val = 'o';
					break;
				}
			}

			std::cout << "I: " << i << std::endl;
			//dump(region, minX, maxX);
		}
		dump(_region, _minX, _maxX);

		return i - 1;
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {

		core::Region<RegolithCell> region;
		int minX = 500;
		int maxX = 500;

		int maxY = 0;

		region.getCell(500, 0).val = '+';

		for (const auto& l : m_InputLines)
		{
			std::vector<ze::Vector2i> coords;

			for (const auto& c : ze::StringExtensions::splitStringByDelimeter(l, " ->"))
			{
				const auto& coordPart = ze::StringExtensions::splitStringByDelimeter(c, ",");
				assert(coordPart.size() == 2);

				auto val = coords.emplace_back(ze::Vector2i{ std::stoi(coordPart[0]), std::stoi(coordPart[1])});

				minX = std::min(minX, val.x);
				maxX = std::max(maxX, val.x);
				maxY = std::max(maxY, val.y);
			}

			for (std::size_t i = 1; i < coords.size(); ++i)
			{
				const auto& from = coords[i - 1];
				const auto& to = coords[i];

				if (from.x == to.x)
				{
					auto offset = (from.y - to.y) / std::abs(from.y - to.y);

					for (int y = from.y; ; y -= offset)
					{
						auto& cell = region.getCell(from.x, y);
						cell.val = '#';

						if (y == to.y) break;
					}
				}
				else if (from.y == to.y)
				{
					auto offset = (from.x - to.x) / std::abs(from.x - to.x);

					for (int x = from.x; ; x -= offset)
					{
						auto& cell = region.getCell(x, from.y);
						cell.val = '#';

						if (x == to.x) break;
					}
				}
				else
				{
					assert(false);
				}
			}
		}

		const auto part1 = solvePart1(region, maxY + 3, minX, maxX);

		std::cout << "I: " << 0 << std::endl;
		dump(region, minX, maxX);

		int infiniteFloorY = maxY + 2;

		bool landed = true;
		int i = 0;
		while (landed)
		{
			i++;
			ze::Vector2i target = { 500, 0 };


			while (true)
			{
				minX = std::min(minX, target.x);
				maxX = std::max(maxX, target.x);
				const auto targetIsInfiniteFloor = target.y + 1 == infiniteFloorY;
				// BELOW
				if (!targetIsInfiniteFloor && isOpen(region, target + ze::Vector2i(0, 1)))
				{
					target.y++;
				}
				else if (!targetIsInfiniteFloor && isOpen(region, target + ze::Vector2i(-1, 1)))
				{
					target.x--;
					target.y++;
				}
				else if (!targetIsInfiniteFloor && isOpen(region, target + ze::Vector2i(+1, 1)))
				{
					target.x++;
					target.y++;
				}
				else
				{
					if (target == ze::Vector2i(500, 0))
					{
						dump(region, minX, maxX);
						return { std::to_string(part1), std::to_string(i) };
					}
					auto& cell = region.getCell(target.x, target.y);
					cell.val = 'o';
					break;
				}
			}

			std::cout << "I: " << i << std::endl;
			//dump(region, minX, maxX);
		}
		dump(region, minX, maxX);
		return { std::to_string(part1), "Part 2"};
	}
}
