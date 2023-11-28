#include <2022/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>

namespace TwentyTwentyTwo {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Tuning Trouble", 2022, 6) {
	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::size_t solve(const std::string& _input, std::size_t _amount)
	{
		for (std::size_t i = 0; i < _input.size(); ++i)
		{
			std::unordered_set<char> current;
			const char ci = _input[i];
			bool valid = true;
			for (std::size_t j = i; j < i + _amount; ++j)
			{
				const char cj = _input[j];
				if (current.find(cj) != current.end())
				{
					valid = false;
					break;
				}
				current.insert(cj);
			}

			if (valid)
			{
				return i + _amount;
			}
		}

		throw std::runtime_error("Bad input");
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		const std::string input = m_InputLines[0];

		std::size_t part1 = solve(input, 4);
		std::size_t part2 = solve(input, 14);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
