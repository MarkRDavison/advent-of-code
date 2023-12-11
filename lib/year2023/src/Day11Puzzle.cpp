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

	int getCountOfElementsLessThan(const std::vector<int>& vec, int val)
	{
		int count = 0;

		for (const auto& v : vec)
		{
			if (v < val)
			{
				count++;
			}
		}

		return count;
	}

	long long calculateAnswerForExpansion(
		const std::vector<std::pair<int, Vector2i>>& galaxyLocationsVec,
		const std::vector<int>& extraColumns,
		const std::vector<int>& extraRows,
		int multi)
	{
		long long answer = 0;

		for (std::size_t i = 0; i < galaxyLocationsVec.size(); ++i)
		{
			for (std::size_t j = i + 1; j < galaxyLocationsVec.size(); ++j)
			{
				if (i == j) { continue; }

				const auto locI = galaxyLocationsVec[i].second;
				const auto locJ = galaxyLocationsVec[j].second;

				const auto extraX_I = multi * getCountOfElementsLessThan(extraColumns, locI.x);
				const auto extraX_J = multi * getCountOfElementsLessThan(extraColumns, locJ.x);

				const auto extraY_I = multi * getCountOfElementsLessThan(extraRows, locI.y);
				const auto extraY_J = multi * getCountOfElementsLessThan(extraRows, locJ.y);

				const auto distanceX = (locI.x + extraX_I) - (locJ.x + extraX_J);
				const auto distanceY = (locI.y + extraY_I) - (locJ.y + extraY_J);

				answer += std::abs(distanceX) + std::abs(distanceY);
			}
		}

		return answer;
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {

		std::vector<std::string> universe;

		std::vector<int> extraColumns;
		std::vector<int> extraRows;

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			universe.push_back(m_InputLines[y]);
			if (m_InputLines[y].find('#') == std::string::npos)
			{
				extraRows.push_back(y);
			}
		}


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
				extraColumns.push_back(x);
			}
		}

		std::vector<std::pair<int, Vector2i>> galaxyLocationsVec;

		int galaxyNum = 1;
		for (std::size_t y = 0; y < universe.size(); ++y)
		{
			for (std::size_t x = 0; x < universe[y].size(); ++x)
			{
				if (universe[y][x] == '#')
				{
					galaxyLocationsVec.emplace_back(galaxyNum, Vector2i{ (int)x,(int)y });
					galaxyNum++;
				}
			}
		}

		const auto part1 = calculateAnswerForExpansion(galaxyLocationsVec, extraColumns, extraRows, 1);

		const auto part2 = calculateAnswerForExpansion(galaxyLocationsVec, extraColumns, extraRows, 1000000-1);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
