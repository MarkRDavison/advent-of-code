#include <2017/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <ranges>

namespace TwentySeventeen {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("High-Entropy Passphrases", 2017, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		int part1 = 0;
		int part2 = 0;

		for (const auto& i : m_InputLines) {
			std::unordered_map<std::string, int> words;
			std::unordered_map<std::string, int> anagrams;

			for (auto& w : StringExtensions::splitStringByDelimeter(i, " ")) {
				words[w]++;

				std::ranges::sort(w);
				anagrams[w]++;
			}

			const auto duplicates = std::ranges::any_of(words, [&](auto const& e) { return e.second > 1; });
			if (!duplicates) {
				part1++;
			}

			const auto duplicateAnagrams = std::ranges::any_of(anagrams, [&](auto const& e) { return e.second > 1; });
			if (!duplicateAnagrams) {
				part2++;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
