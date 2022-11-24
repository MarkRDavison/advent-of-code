#include <2018/Day07Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
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
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		return fastSolve(60, 5);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve(int _extraTime, int _numWorkers)
	{

		std::unordered_map<char, std::set<char>> rules;
		std::unordered_map<char, std::set<char>> reverseRules;
		std::set<char> all;

		std::string part1;
		std::string part2;

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

		auto reverseRulesPart2(reverseRules);

		{	//	Part 1
			std::set<char> availablePart1(available);
			while (!availablePart1.empty())
			{
				const auto front = *availablePart1.begin();
				availablePart1.erase(front);
				part1 += front;


				for (auto& [k, set] : reverseRules)
				{
					if (!set.empty())
					{
						set.erase(front);
						if (set.empty())
						{
							availablePart1.insert(k);
						}
					}
				}
			}
		}

		int time = 0;

		{	//	Part 2
			std::string done;
			std::map<char, bool> availablePart2;
			for (const auto& k : available)
			{
				availablePart2[k] = true;
			}
			std::unordered_map<char, int> remainingWork;
			for (const auto& k : all)
			{
				remainingWork[k] = _extraTime + ((int)k - 'A') + 1;
			}

			std::vector<char> workerTasks(_numWorkers, '?');
			while (!availablePart2.empty())
			{
				for (std::size_t i = 0; i < _numWorkers; ++i)
				{
					auto& currentTask = workerTasks[i];
					if (currentTask == '?')
					{
						for (auto& [k, canBeAssigned] : availablePart2)
						{
							if (canBeAssigned)
							{
								canBeAssigned = false;
								currentTask = k;
								break;
							}
						}
					}
					if (currentTask != '?')
					{
						auto& work = remainingWork[currentTask];
						work--;
						if (work <= 0)
						{
							done += currentTask;
							availablePart2.erase(currentTask);

							for (auto& [k, set] : reverseRulesPart2)
							{
								if (!set.empty())
								{
									set.erase(currentTask);
									if (set.empty())
									{
										availablePart2[k] = true;
									}
								}
							}

							currentTask = '?';
							for (auto& [k, canBeAssigned] : availablePart2)
							{
								if (canBeAssigned)
								{
									canBeAssigned = false;
									currentTask = k;
									break;
								}
							}
						}
					}
				}

				std::cout << time << "\t";
				for (const auto t : workerTasks)
				{
					std::cout << t << "\t";
				}
				std::cout << done << std::endl;

				time++;
			}
		}


		return { part1, std::to_string(time) };
	}
}
