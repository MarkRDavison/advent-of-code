#include <2018/Day25Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector4.hpp>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <deque>

namespace TwentyEighteen {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Four-Dimensional Adventure", 2018, 25) {

	}
	Day25Puzzle::~Day25Puzzle() {

	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int manhatten4(const Vector4i& lhs, const Vector4i& rhs)
	{
		return
			std::abs(lhs.x - rhs.x) +
			std::abs(lhs.y - rhs.y) +
			std::abs(lhs.z - rhs.z) +
			std::abs(lhs.w - rhs.w);
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {
		std::vector<Vector4i> spacetime;
		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, ",");
			assert(parts.size() == 4);
			const auto point = Vector4i
			{
				std::stoi(parts[0]),
				std::stoi(parts[1]),
				std::stoi(parts[2]),
				std::stoi(parts[3])
			};
			spacetime.emplace_back(point);
		}


		std::vector<std::unordered_set<std::size_t>> edges;

		for (std::size_t i = 0; i < spacetime.size(); ++i)
		{
			edges.emplace_back();
			for (std::size_t j = 0; j < spacetime.size(); ++j)
			{
				if (manhatten4(spacetime[i], spacetime[j]) <= 3)
				{
					edges[i].insert(j);
				}
			}
		}

		int part1 = 0;

		std::unordered_set<std::size_t> seen;

		std::size_t ei = 0;
		for (const auto& index : edges)
		{
			const auto EI = ei;
			ei++;
			if (seen.contains(EI)) { continue; }

			part1++;

			std::deque<std::size_t> queue;
			queue.push_back(EI);
			while (!queue.empty())
			{
				const auto curr = queue.front(); queue.pop_front();
				if (seen.contains(curr)) { continue; }

				seen.insert(curr);
				for (const auto& edgePoint : edges[curr])
				{
					queue.push_back(edgePoint);
				}
			}
		}

		return { std::to_string(part1), "*** Free ***"};
	}
}
