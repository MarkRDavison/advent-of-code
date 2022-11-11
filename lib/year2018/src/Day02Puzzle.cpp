#include <2018/Day02Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>

namespace TwentyEighteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Inventory Management System", 2018, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		int doubles = 0;
		int triples = 0;

		std::string part2;

		for (std::size_t i = 0; i < m_InputLines.size(); ++i)
		{
			const auto& [d, t] = getDoubleTripleCount(m_InputLines[i]);
			doubles += d;
			triples += t;

			if (part2.empty())
			{
				for (std::size_t j = i + 1; j < m_InputLines.size(); ++j)
				{
					std::string same;

					for (std::size_t k = 0; k < m_InputLines[i].size(); ++k)
					{
						if (m_InputLines[i][k] == m_InputLines[j][k])
						{
							same += m_InputLines[i][k];
						}
					}

					if (same.size() == m_InputLines[i].size() - 1)
					{
						part2 = same;
					}
				}
			}
		}

		return { std::to_string(doubles * triples), part2 };
	}

	std::pair<int, int> Day02Puzzle::getDoubleTripleCount(const std::string& _string)
	{
		std::unordered_map<char, int> counts;

		for (const auto c : _string)
		{
			counts[c]++;
		}

		bool dbl = false;
		bool trp = false;
		for (const auto& [k, v] : counts)
		{
			if (v == 2)
			{
				dbl = true;
			}
			if (v == 3)
			{
				trp = true;
			}
		}

		return { dbl ? 1 : 0, trp ? 1 : 0 };
	}
}
