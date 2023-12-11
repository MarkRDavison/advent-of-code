#include <2023/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>

namespace TwentyTwentyThree {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Cosmic Expansion", 2023, 11) {
	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct CosmicCell
	{
		char c{ '.' };
	};

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {

		std::vector<std::string> universe;

		std::vector<int> extraColumns;
		std::vector<int> extraRows;

		std::cout << "Original" << std::endl;
		for (const auto& r : m_InputLines)
		{
			std::cout << r << std::endl;
		}

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			universe.push_back(m_InputLines[y]);
			if (m_InputLines[y].find('#') == std::string::npos)
			{
				extraRows.push_back(y);
				universe.push_back(m_InputLines[y]);
			}
		}


		std::cout << "With extra rows" << std::endl;
		for (const auto& r : universe)
		{
			std::cout << r << std::endl;
		}


		int expandedColumns = 0;
		for (std::size_t x = 0; x < m_InputLines[0].size(); ++x)
		{
			bool emptyColumn = true;
			for (std::size_t y = 0; y < m_InputLines.size(); ++y)
			{
				if (m_InputLines[y][x] == '#')
				{
					emptyColumn = false;
					break;
				}
			}
			if (emptyColumn)
			{
				const int expandedX = x + expandedColumns;
				expandedColumns++;

				extraColumns.push_back(x);
				for (auto& row : universe)
				{
					row.insert(row.begin() + expandedX, '.');
				}
			}
		}

		std::cout << "With extra columns" << std::endl;
		for (const auto& r : universe)
		{
			std::cout << r << std::endl;
		}

		std::unordered_map<int, Vector2i> galaxyLocations;
		std::vector<std::pair<int, Vector2i>> galaxyLocationsVec;

		int galaxyNum = 1;
		for (std::size_t y = 0; y < universe.size(); ++y)
		{
			for (std::size_t x = 0; x < universe[y].size(); ++x)
			{
				if (universe[y][x] == '#')
				{
					galaxyLocations.emplace(galaxyNum, Vector2i{ (int)x,(int)y });
					galaxyLocationsVec.emplace_back(galaxyNum, Vector2i{ (int)x,(int)y });
					galaxyNum++;
				}
			}
		}

		long long part1 = 0;
		std::vector<long long> distances;

		for (std::size_t i = 0; i < galaxyLocationsVec.size(); ++i)
		{
			for (std::size_t j = i + 1; j < galaxyLocationsVec.size(); ++j)
			{
				if (i == j) { continue; }

				const auto locI = galaxyLocationsVec[i].second;
				const auto locJ = galaxyLocationsVec[j].second;

				const auto distanceX = locI.x - locJ.x;
				const auto distanceY = locI.y - locJ.y;

				distances.push_back(distanceX + distanceY);

				part1 += std::abs(distanceX) + std::abs(distanceY);
			}
		}

		for (const auto& r : extraRows)
		{
			std::cout << "Extra row at x = " << r << std::endl;
		}
		for (const auto& c : extraColumns)
		{
			std::cout << "Extra col at y = " << c << std::endl;
		}

		return { std::to_string(part1), "Part 2"};
	}
}
