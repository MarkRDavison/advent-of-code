#include <2023/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Mirage Maintenance", 2023, 9) {
	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	MirageNumber solveForNextRootValue(MirageHistory& history)
	{
		for (std::size_t generation = history.data.size() - 1; generation > 0; generation--)
		{
			const auto gi = generation - 1;

			history.data[gi].push_back(history.data[gi].back() + history.data[gi + 1].back());
		}

		return history.data.front().back();
	}

	MirageNumber solve(std::vector<MirageHistory>& histories)
	{
		for (auto& h : histories)
		{
			std::size_t generationSolving = 0;
			while (true)
			{
				bool allZero = true;
				auto& newData = h.data.emplace_back();
				for (std::size_t i = 1; i < h.data[generationSolving].size(); ++i)
				{
					const auto left = h.data[generationSolving][i - 1];
					const auto right = h.data[generationSolving][i];
					const auto diff = right - left;
					newData.push_back(diff);
					if (diff != 0)
					{
						allZero = false;
					}
				}

				if (allZero)
				{
					h.data.at(h.data.size() - 1).push_back(0);
					break;
				}
				generationSolving++;
			}
		}

		MirageNumber res = 0;

		for (auto& h : histories)
		{
			res += solveForNextRootValue(h);
		}

		return res;
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		std::vector<MirageHistory> histories1;
		std::vector<MirageHistory> histories2;

		for (const auto& l : m_InputLines)
		{
			auto& h1 = histories1.emplace_back();
			auto& h2 = histories2.emplace_back();
			auto& given1 = h1.data.emplace_back();
			auto& given2 = h2.data.emplace_back();
			for (const auto& p : StringExtensions::splitStringByDelimeter(l, " "))
			{
				given1.emplace_back((MirageNumber)std::stoll(p));
				given2.emplace_back((MirageNumber)std::stoll(p));
			}
		}

		for (auto& h : histories2)
		{
			std::reverse(h.data[0].begin(), h.data[0].end());
		}

		auto part1 = solve(histories1);
		auto part2 = solve(histories2);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
