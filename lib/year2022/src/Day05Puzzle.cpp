#include <2022/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <stack>

namespace TwentyTwentyTwo {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Supply Stacks", 2022, 5) {
	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {

		std::vector<std::stack<char>> layout((m_InputLines[0].size() + 1)/ 4);

		std::size_t bottom = 0;
		while (!m_InputLines[bottom].empty())
		{
			bottom++;
		}

		std::size_t i = bottom + 1;

		for (std::size_t layoutIter = bottom - 2; layoutIter >= 0 && layoutIter < m_InputLines.size(); layoutIter--)
		{
			std::size_t stackIter = 0;
			for (std::size_t horizontalIter = 1; horizontalIter < m_InputLines[layoutIter].size(); horizontalIter += 4)
			{
				auto cargo = m_InputLines[layoutIter][horizontalIter];
				if (cargo != ' ')
				{
					layout[stackIter].push(m_InputLines[layoutIter][horizontalIter]);
				}
				stackIter++;
			}
		}

		auto layout2(layout);

		for (; i < m_InputLines.size(); ++i)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(m_InputLines[i], " ");

			const int amount = std::stoi(p[1]);
			const int from = std::stoi(p[3]);
			const int to = std::stoi(p[5]);

			const std::size_t fromIndex = from - 1;
			const std::size_t toIndex = to - 1;

			{	// Part 1
				for (auto amountIter = 0; amountIter < amount; ++amountIter)
				{
					const auto cargo = layout[fromIndex].top();
					layout[fromIndex].pop();
					layout[toIndex].push(cargo);
				}
			}

			{	//	Part 2
				std::stack<char> temp;
				for (auto amountIter = 0; amountIter < amount; ++amountIter)
				{
					const auto cargo = layout2[fromIndex].top();
					layout2[fromIndex].pop();
					temp.push(cargo);
				}
				while (!temp.empty())
				{
					layout2[toIndex].push(temp.top());
					temp.pop();
				}
			}
		}

		std::string part1;
		for (const auto& stack : layout)
		{
			part1 += stack.top();
		}
		std::string part2;
		for (const auto& stack : layout2)
		{
			part2 += stack.top();
		}

		return { part1, part2 };
	}
}
