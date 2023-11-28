#include <2022/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <cmath>

#define UNSET -1

namespace TwentyTwentyTwo {


	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Proboscidea Volcanium", 2022, 16) {
	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	using Memoized = std::unordered_map<std::string, std::unordered_map<long, std::unordered_map<long, long>>>;

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		std::unordered_map<std::string, int> flowRates;
		std::unordered_map<std::string, std::vector<std::string>> adjacentValves;

		std::vector<std::string> valves;
		std::unordered_map<std::string, int> valveIds;

		const std::string start = "AA";

		int i = 0;
		for (const auto& l : m_InputLines)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(l, " =;,");

			const auto valve = p[1];
			const auto flow = std::stoi(p[5]);

			if (flow > 0)
			{
				valveIds[valve] = i;
				i++;
			}

			flowRates[valve] = flow;
			
			valves.push_back(valve);

			for (std::size_t i = 10; i < p.size(); ++i) {
				const auto next = p[i];
				adjacentValves[valve].push_back(next);
			}
		}
				
		Memoized cache;

		const long maxPossibleStates = (long)std::pow(2, valveIds.size()) - 1;

		long best = 0;

		auto getCache = [](Memoized& _cache, std::string _valve, long _timeRemaining, long _possibleIndex) -> long& {
			auto iter = _cache[_valve][_timeRemaining].find(_possibleIndex);

			if (iter == _cache[_valve][_timeRemaining].end())
			{
				_cache[_valve][_timeRemaining][_possibleIndex] = UNSET;
			}

			return _cache[_valve][_timeRemaining][_possibleIndex];
		};

		std::function<long(std::string, long, long)> recurser =
			[&](std::string _valve, long _timeRemaining, long _possibleIndex) -> long
		{
			if (_timeRemaining == 0)
			{
				return 0;
			}

			if (getCache(cache, _valve, _timeRemaining, _possibleIndex) == UNSET)
			{
				long score = 0;
				for (const auto& adjacent : adjacentValves[_valve])
				{
					auto score = recurser(adjacent, _timeRemaining - 1, _possibleIndex);
					score = std::max(score, score);
				}
				auto possible = 1 << valveIds[_valve];
				if (possible & _possibleIndex)
				{
					score = std::max(score, recurser(_valve, _timeRemaining - 1, _possibleIndex - possible) + flowRates[_valve] * (_timeRemaining - 1));
				}
				cache[_valve][_timeRemaining][_possibleIndex] = score;
			}

			return getCache(cache, _valve, _timeRemaining, _possibleIndex);
		};

		auto part1 = recurser(start, 30, maxPossibleStates);
		long part2 = 0;

		for (long i = 0; i <= maxPossibleStates; ++i)
		{
			const auto you = recurser(start, 26, maxPossibleStates - i);
			const auto elephant = recurser(start, 26, i);

			part2 = std::max(part2, you + elephant);
		}


		return { std::to_string(part1), std::to_string(part2) };
	}
}
