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

	long long solve(const Graph& graph, const Vector2i& start, const Vector2i& end, long i)
	{
		const auto layers = graph.size();
		const auto height = graph[0].size();
		const auto width = graph[0][0].size();

		const Vector3i starting = { start, 0 };

		internal::PriorityQueue<Vector3<int>, int> queue;
		queue.put(starting, 0);
		GraphDistances distances;
		distances[starting] = 0;
		GraphFromDistances from;

		const auto addToQueueIfBetter = 
			[&from, &distances, &queue, end, &graph](const Vector3i& prev, const Vector3i& next, int nextDistance) -> void
			{
				const auto cell = graph[(int)(next.z % graph.size())][next.y][next.x];
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
				queue.put(next, std::abs(end.x - next.x) + std::abs(end.y - next.y));
			};

		int bestDistance =  std::numeric_limits<int>::max();

		while (!queue.empty())
		{
			const auto curr = queue.get();
			const auto currentDistance = distances.at(curr);
			if ((++i % 10000) == 0)
			{
				std::cout << i << " - queue size: " << queue.elements.size() << ", dist: " << currentDistance << std::endl;
			}

			if (curr.x == end.x && curr.y == end.y)
			{
				bestDistance = std::min(bestDistance, currentDistance);
				std::cout << "FOUND AN END" << std::endl;
				continue;
			}

			if (bestDistance < currentDistance)
			{
				continue;
			}

			// RIGHT
			if (curr.x < width - 1)
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
			if (curr.x > 1)
			{
				Vector3i next{ curr.x - 1, curr.y, curr.z + 1 };
				const auto nextDistance = currentDistance + 1;
				addToQueueIfBetter(curr, next, nextDistance);
			}
			
			// UP
			if (curr.y > 1)
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

		/*
		i.e. every cycleLength iterations we return back to the original
		so we do some 3-d path finding
		the height/first one is cycleLength
		then for every layer, its sizeX + 2 x sizeY + 2, that includes the boundaries though

		each step has 5 steps
		 - left
		 - right
		 - up
		 - down
		 - wait (moves to the (layer + 1) % layerCount)

		*/

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

		std::cout << "Best ending was at " << bestEnding.x << ", " << bestEnding.y << ", " << bestEnding.z << std::endl;

		Vector3i currBacktrace = bestEnding;
		while (true)
		{
			std::cout << "Then " << currBacktrace.x << ", " << currBacktrace.y << ", " << currBacktrace.z << std::endl;
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
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x) 
			{
				char c = m_InputLines[y][x];
				if (y == 0 && c == '.')
				{
					startX = (int)x;
				}
				if (y == m_InputLines.size() - 1 && c == '.')
				{
					endX = (int)x;
				}

				if (blizzardChars.contains(c))
				{
					blizzards.emplace_back(Vector2i{ -1 + (int)x, -1 + (int)y }, c);
					c = '.';
				}
			}
		}

		const int sizeX = (int)m_InputLines[0].size() - 2;
		const int sizeY = (int)m_InputLines.size() - 2;

		const auto cycleLength = std::lcm(sizeX, sizeY);

		const Vector2i start{ startX, 0 };
		const Vector2i end{ endX, sizeY + 1 };
		
		Graph graph;

		graph.resize(cycleLength);
		std::vector<std::string> test;
		bool temp = true;
		for (auto& layer : graph)
		{
			if (temp)
			{
				test.resize(sizeY + 2);
			}
			layer.resize(sizeY + 2);
			for (std::size_t y = 0; y < layer.size(); ++y)
			{
				if (y == 0)
				{
					layer[y] = std::string(sizeX + 2, '#');
					layer[y][start.x] = 'S';

					if (temp)
					{
						test[y] = std::string(sizeX + 2, '#');
						test[y][start.x] = 'S';
					}
				}
				else if (y == layer.size() - 1)
				{
					layer[y] = std::string(sizeX + 2, '#');
					layer[y][end.x] = 'E';
					if (temp)
					{
						test[y] = std::string(sizeX + 2, '#');
						test[y][end.x] = 'E';
					}
				}
				else
				{
					layer[y] = "#" + std::string(sizeX, '.') +"#";
					if (temp)
					{
						test[y] = "#" + std::string(sizeX, '.') + "#";
					}
				}
			}
			temp = false;
		}


		if (false) {
			std::vector<std::vector<std::string>> testLayers;

			auto testInit(test);
			for (const auto& [pos, c] : blizzards)
			{
				testInit[pos.y + 1][pos.x + 1] = c;
			}
			std::cout << "LCM: " << cycleLength << " - TEST INITIAL" << std::endl;
			for (const auto& r : testInit)
			{
				std::cout << r << std::endl;
			}
			int i = 0;
			while (i < cycleLength * 4)
			{
				auto& testCurr = testLayers.emplace_back(test);
				for (auto& [pos, c] : blizzards)
				{
					const auto offset = blizzardDirs.at(c);
 					pos += offset;
					if (pos.x < 0)
					{
						pos.x += sizeX;
					}
					if (pos.y < 0)
					{
						pos.y += sizeY;
					}
					if (pos.x >= sizeX)
					{
						pos.x -= sizeX;
					}
					if (pos.y >= sizeY)
					{
						pos.y -= sizeY;
					}

					testCurr[pos.y + 1][pos.x + 1] = c;
				}
				i++;
				std::cout << "LCM: " << cycleLength << " - TEST " << i << std::endl;
				for (const auto& r : testCurr)
				{
					std::cout << r << std::endl;
				}
			}

			for (std::size_t ti = 0; ti < testLayers.size(); ++ti)
			{
				const auto& first = testLayers[ti % cycleLength];
				const auto& curr = testLayers[ti];

				for (std::size_t ty = 0; ty < curr.size(); ty++)
				{
					for (std::size_t tx = 0; tx < curr[ty].size(); tx++)
					{
						assert(first[ty][tx] == curr[ty][tx]);
					}
				}

				std::cout << "Validated " << ti << " against " << ti % cycleLength << std::endl;
			}
			return { "","" };
		}


		for (std::size_t i = 0; i < cycleLength; ++i)
		{
			auto& layer = graph.at(i);
			for (auto& [pos, c] : blizzards)
			{
				pos += blizzardDirs.at(c);
				if (pos.x < 0)
				{
					pos.x += sizeX;
				}
				if (pos.y < 0)
				{
					pos.y += sizeY;
				}
				if (pos.x >= sizeX)
				{
					pos.x -= sizeX;
				}
				if (pos.y >= sizeY)
				{
					pos.y -= sizeY;
				}

				layer[pos.y + 1][pos.x + 1] = c;
			}
		}


		const auto part1 = solve(graph, start, end, 0);

		return { std::to_string(part1), "Part 2"};
	}
}
