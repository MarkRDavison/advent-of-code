#include <2023/Day05Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <numeric>
#include <cassert>

namespace TwentyTwentyThree {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("If You Give A Seed A Fertilizer", 2023, 5) {
	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef long long SeedNumber;
	typedef std::vector<SeedNumber> SeedVector;

	struct RangeMapping
	{
		SeedNumber source;
		SeedNumber destination;
		SeedNumber range;
	};

	struct Map
	{
		std::string sourceName;
		std::string destinationName;

		std::vector<RangeMapping> mappings;
	};

	SeedNumber solveForSeeds(const SeedVector& seeds, const std::vector<Map>& maps)
	{
		SeedNumber res = std::numeric_limits<SeedNumber>::max();

		std::size_t i = 0;
		for (const auto seed : seeds)
		{
			auto currentValue = seed;
			//std::cout << "===============================" << std::endl;
			//std::cout << "Processing seed " << currentValue << " - " << i + 1 << "/" << seeds.size() << std::endl;
			for (const auto& mapping : maps)
			{
				bool rangeMatchFound = false;
				for (const auto& mappingRange : mapping.mappings)
				{
					if (mappingRange.source <= currentValue &&
						currentValue <= mappingRange.source + mappingRange.range)
					{
						const auto offset = mappingRange.destination - mappingRange.source;
						//std::cout << "Match found for " << mapping.sourceName << " to " << mapping.destinationName << std::endl;
						//std::cout << " - value was: " << currentValue;
						currentValue = currentValue + offset;
						rangeMatchFound = true;
						//std::cout << " is now: " << currentValue << std::endl;
						break;
					}
				}

				if (!rangeMatchFound)
				{
					//std::cout << "No match found, value unchanged for " << mapping.sourceName << " to " << mapping.destinationName << std::endl;
					currentValue = currentValue;
				}
			}

			res = std::min(res, currentValue);
			++i;
			//std::cout << "seed: " << seed << " gives val: " << currentValue << std::endl;
		}
		return res;
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		std::size_t i = 1;
		
		SeedVector seedsPart1;
		for (const auto& s : StringExtensions::splitStringByDelimeter(m_InputLines[0], " seeds:"))
		{
			seedsPart1.push_back((SeedNumber)std::stoll(s));
		}

		std::vector<Map> maps;
		Map* curr{ nullptr };
		while (i < m_InputLines.size())
		{
			const auto& l = m_InputLines[i];
			if (StringExtensions::endsWith(l, " map:"))
			{
				maps.push_back({});
				curr = &maps.back();

				const auto& p = StringExtensions::splitStringByDelimeter(l, " -");
				assert("to" == p[1]);
				curr->sourceName = p[0];
				curr->destinationName = p[2];
			}
			else
			{
				const auto& p = StringExtensions::splitStringByDelimeter(l, " ");
				if (p.size() == 3)
				{
					assert(curr != nullptr);
					auto& range = curr->mappings.emplace_back();
					range.destination = (SeedNumber)std::stoll(p[0]);
					range.source = (SeedNumber)std::stoll(p[1]);
					range.range = (SeedNumber)std::stoll(p[2]);
				}
			}

			++i;
		}

		// TODO: Multi thread this thing 
		auto part1 = solveForSeeds(seedsPart1, maps);
		SeedNumber part2 = std::numeric_limits<SeedNumber>::max();

		for (std::size_t si = 0; si < seedsPart1.size(); si += 2)
		{
			std::cout << si + 1 << " / " << seedsPart1.size() << " - start" << std::endl;
			for (std::size_t si2 = seedsPart1[si]; si2 < seedsPart1[si] + seedsPart1[si + 1]; ++si2)
			{
				auto res = solveForSeeds({ (SeedNumber)si2 }, maps);
				part2 = std::min(part2, res);

				if (si2 % 10000000 == 0)
				{
					std::cout << (si2 - seedsPart1[si] + 1) << " / " << seedsPart1[si + 1] << " - " <<
						(double)((si2 - seedsPart1[si] + 1)) / (double)(seedsPart1[si + 1]) * 100  << std::endl;
				}

			}
			std::cout << si + 1 << " / " << seedsPart1.size() << " - end" << std::endl;
		}

		return { std::to_string(part1), std::to_string(part2)};
	}
}
