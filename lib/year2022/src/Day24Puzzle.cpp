#include <2022/Day24Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <Core/Vector3.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cassert>

#define UP '^'
#define DOWN 'v'
#define LEFT '<'
#define RIGHT '>'

namespace TwentyTwentyTwo {
	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Blizzard Basin", 2022, 24) {
	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef std::vector<std::vector<std::string>> Graph;
	typedef std::unordered_map<Vector3<int>, int, Vector3_Hash_Fxn<int>> GraphDistances;
	typedef std::unordered_set<Vector3<int>, Vector3_Hash_Fxn<int>> GraphSeen;
	typedef std::unordered_map<Vector3<int>, Vector3<int>, Vector3_Hash_Fxn<int>> GraphFromDistances;

	int solve(const Graph& graph, const Vector2i& start, const Vector2i& end, int time)
	{
		const auto layers = graph.size();
		const auto height = graph[0].size();
		const auto width = graph[0][0].size();

		const Vector3i starting = { start, time };

		internal::PriorityQueue<Vector3<int>, int> queue;
		queue.put(starting, 0);
		GraphDistances distances;
		distances[starting] = 0;
		GraphFromDistances from;

		const auto addToQueueIfBetter = 
			[&from, &distances, &queue, end, &graph](const Vector3i& prev, const Vector3i& next, int nextDistance) -> void
			{
				const auto actualZ = (int)(next.z % graph.size());
				const auto cell = graph[actualZ][next.y][next.x];
				if (cell != '.' && cell != 'E' && cell != 'S')
				{
					return;
				}

				if (distances.contains(next))
				{
					const auto currentNextDistance = distances.at(next);
					if (nextDistance >= currentNextDistance)
					{
						return;
					}
				}

				from[next] = prev;
				distances[next] = nextDistance;
				queue.put(next, std::abs(next.x - end.x) + std::abs(next.y - end.y));
			};

		int bestDistance = std::numeric_limits<int>::max();

		long i = 0;
		while (!queue.empty())
		{
			const auto curr = queue.get();
			const auto currentDistance = distances.at(curr);

			if (curr.x == end.x && curr.y == end.y)
			{
				bestDistance = std::min(bestDistance, currentDistance);
				continue;
			}

			if (bestDistance < currentDistance)
			{
				continue;
			}

			// RIGHT
			{
				Vector3i next{ curr.x + 1, curr.y, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}

			// DOWN
			if (curr.y < height - 1)
			{
				Vector3i next{ curr.x, curr.y + 1, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}

			// LEFT
			{
				Vector3i next{ curr.x - 1, curr.y, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}
			
			// UP
			if (curr.y > 0)
			{
				Vector3i next{ curr.x, curr.y - 1, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}
			
			// WAIT
			{
				Vector3i next{ curr.x, curr.y, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}
		}

		Vector3i bestEnding;
		int best = std::numeric_limits<int>::max();

		for (const auto& [loc, dist] : distances)
		{
			if (loc.x == end.x && loc.y == end.y)
			{
				if (best > dist)
				{
					best = dist;
					bestEnding = loc;
				}
			}
		}

		if (best == std::numeric_limits<int>::max())
		{
			std::cout << "Never found an ending :(" << std::endl;

			return best;
		}

		Vector3i currBacktrace = bestEnding;

		while (true)
		{
			if (currBacktrace.x == starting.x && currBacktrace.y == starting.y)
			{
				break;
			}

			currBacktrace = from.at(currBacktrace);
		}

		return best + 1; // Counted distances between nodes
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		int startX = 0;
		int endX = 0;

		std::vector<std::string> frame;
		std::vector<std::pair<Vector2i, char>> blizzards;
		const std::unordered_set<char> blizzardChars = { 
			UP, 
			DOWN, 
			LEFT, 
			RIGHT
		};
		const std::unordered_map<char, Vector2i> blizzardDirs = {
			{ UP, {0, -1} },
			{ DOWN, {0, +1} },
			{ LEFT, {-1, 0} },
			{ RIGHT, {+1, 0} }
		};

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			auto& frameRow = frame.emplace_back();
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x) 
			{
				char c = m_InputLines[y][x];
				if (y == 0 && c == '.')
				{
					startX = (int)x;
					frameRow.push_back('S');
					continue;
				}
				if (y == m_InputLines.size() - 1 && c == '.')
				{
					endX = (int)x;
					frameRow.push_back('E');
					continue;
				}

				if (blizzardChars.contains(c))
				{
					blizzards.emplace_back(Vector2i{ -1 + (int)x, -1 + (int)y }, c);
					c = '.';
				}

				frameRow.push_back(c);
			}
		}

		const int sizeX = (int)m_InputLines[0].size() - 2;
		const int sizeY = (int)m_InputLines.size() - 2;

		const auto cycleLength = std::lcm(sizeX, sizeY) + 1;

		const Vector2i start{ startX, 0 };
		const Vector2i end{ endX, sizeY + 1 };

		const int INTERNAL_WIDTH = (int)m_InputLines[0].size() - 2;
		const int INTERNAL_HEIGHT = (int)m_InputLines.size() - 2;

		Graph graph;

		for (int cycleI = 0; cycleI < cycleLength; ++cycleI)
		{
			std::vector<std::string> currentState = frame;
			std::unordered_map<Vector2i, std::pair<int, char>, Vector2_Hash_Fxn<int>> locs;
			for (const auto& b : blizzards)
			{
				if (!locs.contains(b.first))
				{
					locs[b.first] = { 1, b.second };
				}
				else
				{
					locs[b.first].first++;
				}
			}
			for (const auto& [loc, info] : locs)
			{
				currentState[loc.y + 1][loc.x + 1] = (info.first > 1 ? info.first + '0' : info.second);
			}
			if (cycleI != 0)
			{
				graph.emplace_back(currentState);
			}
			for (auto& b : blizzards)
			{
				b.first += blizzardDirs.at(b.second);
				if (b.first.x < 0)
				{
					b.first.x = INTERNAL_WIDTH - 1;
				}
				if (b.first.y < 0)
				{
					b.first.y = INTERNAL_HEIGHT - 1;
				}
				if (b.first.x >= INTERNAL_WIDTH)
				{
					b.first.x = 0;
				}
				if (b.first.y >= INTERNAL_HEIGHT)
				{
					b.first.y = 0;
				}
			}
		}

		const auto part1 = solve(graph, start, end, 0); 
		const auto part2a = solve(graph, end, start, part1);		
		const auto part2b = solve(graph, start, end, part1 + part2a);
		
		return { std::to_string(part1), std::to_string(part1 + part2a + part2b) };
	}
}
