#include <2021/Day14Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <cassert>

namespace TwentyTwentyOne {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Extended Polymerization", 2021, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static long long solve(PolymerTemplates _templates, const std::string _polymer, unsigned _iterations) {

		std::unordered_map<std::string, long long> pairs;

		for (unsigned i = 1; i < _polymer.size(); ++i) {
			const auto pair = _polymer.substr(i - 1, 2);
			pairs[pair]++;
		}

		for (unsigned i = 0; i < _iterations; ++i) {
			std::unordered_map<std::string, long long> newPairs;
			for (const auto& [k, v] : pairs) {
				newPairs[k[0] + _templates[k]] += v;
				newPairs[_templates[k] + k[1]] += v;
			}
			pairs = newPairs;
		}

		std::unordered_map<char, long long> occurences;

		for (const auto& [k, v] : pairs) {
			occurences[k[0]] += v;
			occurences[k[1]] += v;
		}

		occurences[_polymer.front()] += 1;
		occurences[_polymer.back()] += 1;


		const auto [min, max] = std::minmax_element(occurences.begin(), occurences.end(),
			[](const auto& _lhs, const auto& _rhs) -> bool {
				return _lhs.second < _rhs.second;
			}
		);

		return (*max).second / 2 - (*min).second / 2;
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {		
		auto [polymer, templates] = parse(m_InputLines);

		const auto part1 = solve(templates, polymer, 10);
		const auto part2 = solve(templates, polymer, 40);

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::pair<std::string, PolymerTemplates> Day14Puzzle::parse(const std::vector<std::string>& _inputLines) {
		PolymerTemplates templates;

		for (unsigned i = 2; i < _inputLines.size(); ++i) {
			const auto& p = ze::StringExtensions::splitStringByDelimeter(_inputLines[i], " ->");
			assert(2 == p.size());

			templates[p[0]] = p[1];
		}

		return { _inputLines[0], templates };
	}

}
