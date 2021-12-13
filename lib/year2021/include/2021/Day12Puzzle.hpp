#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_12_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_12_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentyTwentyOne {
	
	using CaveConnections = std::unordered_map<std::string, std::unordered_set<std::string>>;
	struct PathResult {
		std::unordered_set<std::string> visitedRoutes;

		void append(const std::vector<std::string>& _path) {
			std::string p;
			for (const auto& n : _path) {
				p += n + ",";
			}
			p += "end";
			visitedRoutes.insert(p);
		}
		void merge(const PathResult& _res) {
			visitedRoutes.insert(_res.visitedRoutes.begin(), _res.visitedRoutes.end());
		}

	};
	struct Path {
		std::unordered_map<std::string, int> visitedSmall;
		std::vector<std::string> visited;
		std::string current;
		std::string duplicatedSmall;
	};

	class Day12Puzzle : public core::PuzzleBase {
	public:
		Day12Puzzle();
		~Day12Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static CaveConnections parse(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_12_PUZZLE_HPP_