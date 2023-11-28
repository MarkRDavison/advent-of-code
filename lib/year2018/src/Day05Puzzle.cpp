#include <2018/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <numeric>

namespace TwentyEighteen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Alchemical Reduction", 2018, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void reduce(std::string& _chemical)
	{
		for (std::size_t i = 1; i < _chemical.size(); ++i)
		{
			const char lhs = _chemical[i - 1];
			const char rhs = _chemical[i];
			if (lhs != rhs && std::tolower(lhs) == std::tolower(rhs))
			{
				_chemical.erase(i - 1, 2);
				break;
			}
		}
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {

		std::size_t part1;
		std::size_t part2 = std::numeric_limits<std::size_t>::max();

		{
			std::string chemical(m_InputLines[0]);
			std::size_t startingSize;
			do {
				startingSize = chemical.size();
				if (startingSize % 100 == 0 || startingSize % 100 == 1)
				{
					std::cout << "Part 1 - size: " << startingSize << std::endl;
				}
				reduce(chemical);
			} while (startingSize != chemical.size());
			part1 = chemical.size();
		}

		for (int i = 'a'; i <= 'z'; ++i)
		{
			std::string chemical(m_InputLines[0]);
			chemical.erase(std::remove(chemical.begin(), chemical.end(), (char)i), chemical.end());
			chemical.erase(std::remove(chemical.begin(), chemical.end(), std::toupper((char)i)), chemical.end());
			std::size_t startingSize;
			do {
				startingSize = chemical.size();
				if (startingSize % 100 == 0 || startingSize % 100 == 1)
				{
					std::cout << "Part 2 - testing without " << (char)i << "/" << (char)std::toupper((char)i) << " - size: " << startingSize << std::endl;
				}
				reduce(chemical);
			} while (startingSize != chemical.size());
			part2 = std::min(part2, chemical.size());
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
