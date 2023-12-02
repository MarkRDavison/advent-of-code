#include <2023/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <unordered_map>

namespace TwentyTwentyThree {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Cube Conundrum", 2023, 2) {
	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct CubeConundrumGame
	{

	};

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		std::vector<CubeConundrumGame> games;

		const std::unordered_map<std::string, long long> contents = {
			{ "red", 12 }, { "green", 13 }, { "blue", 14 }
		};

		long long part1 = 0;
		long long part2 = 0;
		long long gameNumber = 0;

		for (const auto& l : m_InputLines)
		{
			gameNumber++;
			const auto& parts = StringExtensions::splitStringByDelimeter(l, ":;");

			bool possible = true;

			std::unordered_map<std::string, long long> minContents = {
				{ "red", 0 }, { "green", 0 }, { "blue", 0 }
			};

			for (std::size_t i = 1; i < parts.size(); ++i)
			{
				const auto& roundParts = StringExtensions::splitStringByDelimeter(parts[i], ", ");

				assert(roundParts.size() % 2 == 0);

				for (std::size_t j = 0; j < roundParts.size(); j += 2)
				{
					const auto& amount = std::stoll(roundParts[j + 0]);
					const auto& type = roundParts[j + 1];

					minContents[type] = std::max(minContents[type], amount);

					if (contents.at(type) < amount)
					{
						possible = false;
					}
				}
			}

			if (possible)
			{
				part1 += gameNumber;
			}

			part2 += 
				minContents.at("red") * 
				minContents.at("green") * 
				minContents.at("blue");
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
