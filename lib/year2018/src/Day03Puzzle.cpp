#include <2018/Day03Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <unordered_set>
#include <algorithm>
#include <cassert>

namespace TwentyEighteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("No Matter How You Slice It", 2018, 3) {

	}

	Day03Puzzle::~Day03Puzzle() {

	}

	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {

		core::Region<std::unordered_set<int>> claims;
		std::unordered_set<int> validClaims;
		std::unordered_set<int> invalidClaims;


		int part1 = 0;

		for (const auto& i : m_InputLines)
		{
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(i, "# @,:x");
			assert(5 == parts.size());

			const int id = std::stoi(parts[0]);
			const int x = std::stoi(parts[1]);
			const int y = std::stoi(parts[2]);
			const int w = std::stoi(parts[3]);
			const int h = std::stoi(parts[4]);

			validClaims.insert(id);

			for (int yy = y; yy < y + h; ++yy)
			{
				for (int xx = x; xx < x + w; ++xx)
				{
					auto& c = claims.getCell(xx, yy);
					c.insert(id);

					if (c.size() >= 2)
					{
						invalidClaims.insert(id);
						for (const auto& other : c)
						{
							invalidClaims.insert(other);
						}
						part1++;
					}
				}
			}
		}

		int part2 = 0;

		for (const auto& valid : validClaims)
		{
			if (invalidClaims.find(valid) == invalidClaims.end())
			{
				part2 = valid;
				break;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
