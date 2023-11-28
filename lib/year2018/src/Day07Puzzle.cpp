#include <2018/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

namespace TwentyEighteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("The Sum of Its Parts", 2018, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		return fastSolve(60, 5);
	}

	std::pair<std::string, int> solve(int _extraTime, int _numWorkers, const std::map<char, std::set<char>>& _prereqs)
	{
		const auto answerSize = _prereqs.size();
		int time = -1;

		struct Worker {
			char assigned{ '.' };
			int remaining{ 0 };
		};

		std::vector<Worker> workers(_numWorkers);
		auto preReqs(_prereqs);
		std::string done;

		const auto iterateWorker = [&](Worker& _w, bool _busy) -> void
		{
			if (_busy)
			{
				if (_w.assigned == '.')return;
			}
			if (!_busy)
			{
				if (_w.assigned != '.')return;
			}

			if (_w.assigned != '.')
			{
				if (_w.remaining == 0)
				{
					done += _w.assigned;
					for (auto& [k, req] : preReqs)
					{
						req.erase(_w.assigned);
					}
					_w.assigned = '.';
				}
			}
			if (_w.assigned == '.')
			{
				char toBeAssigned = '.';
				for (const auto& [k, req] : preReqs)
				{
					if (req.empty())
					{
						toBeAssigned = k;
						break;
					}
				}

				if (toBeAssigned != '.')
				{
					preReqs.erase(toBeAssigned);
					_w.assigned = toBeAssigned;
					_w.remaining = _extraTime + ((int)toBeAssigned - 'A') + 1;
				}
			}
			if (_w.assigned != '.')
			{
				_w.remaining--;
			}
		};
		do {
			time++;

			for (auto& w : workers)
			{
				iterateWorker(w, true);
			}
			for (auto& w : workers)
			{
				iterateWorker(w, false);
			}
		} while (done.size() != answerSize);

		return { done, time };
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve(int _extraTime, int _numWorkers)
	{

		std::map<char, std::set<char>> rules;
		std::map<char, std::set<char>> reverseRules;
		std::set<char> all;

		for (const auto& i : m_InputLines)
		{
			const char first = i[5];
			const char next = i[36];

			all.insert(first);
			all.insert(next);

			rules[first].insert(next);
			reverseRules[next].insert(first);
		}
		std::set<char> available(all);
		for (const auto& [k, set] : reverseRules)
		{
			available.erase(k);
		}
		for (const auto a : all)
		{
			if (!reverseRules.contains(a))
			{
				reverseRules[a].clear();
			}
		}

		auto part1 = solve(0, 1, reverseRules);
		auto part2 = solve(_extraTime, _numWorkers, reverseRules);

		return { part1.first, std::to_string(part2.second) };
	}
}
