#include <2017/Day12Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <queue>

namespace TwentySeventeen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Digital Plumber", 2017, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		std::unordered_map<std::string, std::unordered_set<std::string>> data;

		for (const auto& l : m_InputLines) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(l, " ,<->");

			for (std::size_t i = 1; i < parts.size(); ++i) {
				data[parts[0]].insert(parts[i]);
			}
		}

		std::unordered_map<std::string, std::unordered_set<std::string>> seen;

		for (const auto& kv : data) {
			const std::string root = kv.first;

			bool canRun = true;
			for (const auto& seen : seen) {
				if (seen.second.count(root) > 0) {
					canRun = false;
					break;
				}
			}
			if (!canRun) {
				continue;
			}
			
			std::queue<std::string> toSee;
			toSee.push(root);

			while (!toSee.empty()) {
				const auto current = toSee.front();
				toSee.pop();

				seen[root].insert(current);

				for (const auto next : data.at(current)) {
					if (seen[root].count(next) == 0) {
						toSee.push(next);
					}
				}
			}
		}


		std::unordered_set<std::string> seenPart1;
		std::queue<std::string> toSee;
		toSee.push("0");

		while (!toSee.empty()) {
			const auto current = toSee.front();
			toSee.pop();

			seenPart1.insert(current);

			for (const auto next : data.at(current)) {
				if (seenPart1.count(next) == 0) {
					toSee.push(next);
				}
			}
		}

		return { std::to_string(seenPart1.size()), std::to_string(seen.size()) };
	}
}
