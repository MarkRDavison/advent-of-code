#include <2023/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>

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


    typedef std::unordered_map<std::tuple<std::size_t, std::size_t, std::size_t>, long long> Cache;

	long long getArrangements(
        Cache& cache,
        const std::string& springRow,
        const std::vector<long long> damagedSpringGroups,
        std::size_t lineIndex,
        std::size_t currentInoperableSpringCount,
        std::size_t countSpringGroupIndex
    )
	{
        const std::tuple<std::size_t, std::size_t, std::size_t> key = { lineIndex,currentInoperableSpringCount, countSpringGroupIndex };
        if (cache.contains(key))
        {
            return cache.at(key);
        }

        long long result = 0;

        if (lineIndex == springRow.size())
        {
            result = damagedSpringGroups.size() == countSpringGroupIndex ? 1 : 0;
        }
        else if (springRow[lineIndex] == '#')
        {
            result = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, currentInoperableSpringCount + 1, countSpringGroupIndex);
        }
        else if (springRow[lineIndex] == '.' || countSpringGroupIndex == damagedSpringGroups.size())
        {
            if (countSpringGroupIndex < damagedSpringGroups.size() && currentInoperableSpringCount == damagedSpringGroups[countSpringGroupIndex])
            {
                result = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, 0, countSpringGroupIndex + 1);
            }
            else if (currentInoperableSpringCount == 0)
            {
                result = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, 0, countSpringGroupIndex);
            }
            else
            {
                result = 0;
            }
        }
        else
        {
            long long activeCount = 0;
            long long damagedCount = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, currentInoperableSpringCount + 1, countSpringGroupIndex);
            
            if (currentInoperableSpringCount == damagedSpringGroups[countSpringGroupIndex])
            {
                activeCount = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, 0, countSpringGroupIndex + 1);
            }
            else if (currentInoperableSpringCount == 0)
            {
                activeCount = getArrangements(cache, springRow, damagedSpringGroups, lineIndex + 1, 0, countSpringGroupIndex);
            }

            result = damagedCount + activeCount;
        }

        cache[key] = result;
        return result;
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
        long long part1 = 0;
        long long part2 = 0;

		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, " ,");

            auto s1 = parts[0];
            auto s2 = s1 + "?" + s1 + "?" + s1 + "?" + s1 + "?" + s1;

            std::vector<long long> g1;
            std::vector<long long> g2;

			for (std::size_t i = 1; i < parts.size(); ++i)
			{
				g1.push_back(std::stoll(parts[i]));
			}

			for (std::size_t i = 0; i < 5; ++i)
			{
				for (const auto g : g1)
				{
					g2.push_back(g);
				}
			}

            const char Ending = '.';

            Cache c1;
            part1 += getArrangements(c1, s1 + Ending, g1, 0, 0, 0);

            Cache c2;
            part2 += getArrangements(c2, s2 + Ending, g2, 0, 0, 0);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
