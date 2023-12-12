#include <2023/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Hot Springs", 2023, 12) {
	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int valid(const std::string& springs, const std::vector<long long>& groups)
	{
		const auto unknownIndex = springs.find('?');
		if (unknownIndex != std::string::npos)
		{
			if (unknownIndex > 1)
			{
				const auto& segments = StringExtensions::splitStringByDelimeter(springs.substr(0, unknownIndex), ".");
				if (segments.size() > groups.size())
				{
					return 0;
				}
				if (segments.size() > 0)
				{
					for (std::size_t i = 0; i < segments.size() - 1; ++i)
					{
						if (segments[i].size() != (std::size_t)groups[i])
						{
							return 0;
						}
					}
				}
			}

			auto gapReplaced = springs;
			gapReplaced[unknownIndex] = '.';
			auto springReplaced = springs;
			springReplaced[unknownIndex] = '#';

			const auto gapValid = valid(gapReplaced, groups);
			const auto springValid = valid(springReplaced, groups);

			return gapValid + springValid;
		}
		else
		{
			const auto& segments = StringExtensions::splitStringByDelimeter(springs, ".");

			if (segments.size() != groups.size())
			{
				return 0;
			}

			for (std::size_t i = 0; i < segments.size(); ++i)
			{
				if (segments[i].size() != (std::size_t)groups[i])
				{
					return 0;
				}
			}

			return 1;
		}
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		std::vector<Spring> springs;
		std::vector<Spring> springs2;

		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, " ,");

			auto& s = springs.emplace_back();
			auto& s2 = springs2.emplace_back();

			s.springs = parts[0];

			s2.springs = s.springs + "?" + s.springs + "?" + s.springs + "?" + s.springs + "?" + s.springs;

			for (std::size_t i = 1; i < parts.size(); ++i)
			{
				s.groups.push_back(std::stoll(parts[i]));
			}

			for (std::size_t i = 0; i < 5; ++i)
			{
				for (const auto g : s.groups)
				{
					s2.groups.push_back(g);
				}
			}
		}

		long long part1 = 0;
		long long part2 = 0;

		std::size_t i = 0;
		for (const auto& spring : springs)
		{
			part1 += (long long)valid(spring.springs, spring.groups);
			i++;
			std::cout << "1: " << i << " / " << springs.size() << std::endl;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
