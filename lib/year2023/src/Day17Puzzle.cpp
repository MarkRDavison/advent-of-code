#include <2023/Day17Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Vector3.hpp>
#include <Core/Vector4.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>
#include <numeric>
#include <cassert>
#include <queue>

#define VALID_POS(pos) (pos.x >= 0 && pos.y >= 0 && pos.x < WIDTH && pos.y < HEIGHT)
#define GET_CELL(pos) (crucibleNetwork[(std::size_t)pos.y][(std::size_t)pos.x])
#define HEURISTIC(pos) (std::abs(pos.x - end.x) + std::abs(pos.y - end.y))

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Vector2i getOffset(int dir)
{
	switch (dir)
	{
	case UP:
		return { 0, -1 };
	case DOWN:
		return { 0,+1 };
	case LEFT: 
		return { -1, 0 };
	case RIGHT:
		return { +1,0 };
	default:
		assert(false);
		return { 0,0 };
	}
}

int turnLeft(int dir)
{
	switch (dir)
	{
	case UP:
		return LEFT;
	case DOWN:
		return RIGHT;
	case LEFT:
		return DOWN;
	case RIGHT:
		return UP;
	default:
		assert(false);
		return -1;
	}
}

int turnRight(int dir)
{
	switch (dir)
	{
	case UP:
		return RIGHT;
	case DOWN:
		return LEFT;
	case LEFT:
		return UP;
	case RIGHT:
		return DOWN;
	default:
		assert(false);
		return -1;
	}
}

namespace TwentyTwentyThree {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Clumsy Crucible", 2023, 17) {
	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct CrucibleCell
	{
		int val{ 0 };
	};

	struct CrucibleState
	{
		int x{ 0 };
		int y{ 0 };
		int straightCount{ 0 };
		int dir{ RIGHT };

		bool operator==(const CrucibleState& other) const 
		{
			return x == other.x && y == other.y && straightCount == other.straightCount && dir == other.dir;
		}
	}; 
	
	struct CrucibleState_Hash_Fxn
	{
		std::size_t operator()(const CrucibleState& obj) const
		{
			return
				std::hash<int>()(obj.x) ^ 
				std::hash<int>()(obj.y) ^
				std::hash<int>()(obj.straightCount) ^
				std::hash<int>()(obj.dir);
		}
	};

	typedef std::vector<std::vector<CrucibleCell>> CrucibleMap;

	long long solveForMinMaxStraightDistance(const CrucibleMap& crucibleNetwork, int min, int max)
	{
		internal::PriorityQueue<CrucibleState, long long> queue;
		std::unordered_map<Vector4i, long long, Vector4_Hash_Fxn<int>> distances;

		const CrucibleState start{ .x = 0, .y = 0, .straightCount = 0, .dir = RIGHT };
		queue.put(start, 0);
		distances.emplace(Vector4i(start.x, start.y, start.dir, start.straightCount), 0);

		const int WIDTH = (int)crucibleNetwork[0].size();
		const int HEIGHT = (int)crucibleNetwork.size();

		const Vector2i end{ (int)(WIDTH - 1), (int)(HEIGHT - 1) };

		long long bestDistance = std::numeric_limits<long long>::max();

		long long i = 0;

		while (!queue.empty())
		{
			const auto curr = queue.get();
			const auto currDistance = distances.at(Vector4i(curr.x, curr.y, curr.dir, curr.straightCount));

			if (i % 100000 == 0)
			{
				std::cout << "QUEUE: " << queue.elements.size() << std::endl;
			}
			i++;
			if (currDistance > bestDistance)
			{
				continue;
			}
			if (curr.x == end.x && curr.y == end.y)
			{
				if (curr.straightCount >= min)
				{
					if (bestDistance > currDistance)
					{
						std::cout << (min == 1 ? "Part 1 - " : "Part 2 - ") << "FOUND A BETTER END AFTER: " << currDistance << ", queue: " << queue.elements.size() << std::endl;
						bestDistance = currDistance;
					}
				}
				continue;
			}

			// Straight
			if (curr.straightCount < max)
			{
				const Vector2i nextPosition = Vector2i{ curr.x , curr.y } + getOffset(curr.dir);
				if (VALID_POS(nextPosition))
				{
					const auto& nextCell = GET_CELL(nextPosition);
					const auto nextDistance = currDistance + nextCell.val;
					const CrucibleState next{
						.x = nextPosition.x,
						.y = nextPosition.y,
						.straightCount = curr.straightCount + 1,
						.dir = curr.dir };

					const auto& existingDistance = distances.find(Vector4i(nextPosition, next.dir, next.straightCount));
					if (existingDistance == distances.end() || (*existingDistance).second > nextDistance)
					{
						distances[Vector4i(nextPosition, next.dir, next.straightCount)] = nextDistance;
						queue.put(next, HEURISTIC(nextPosition));
					}
				}
			}
			// Left
			if (curr.straightCount >= min)
			{
				const auto newDir = turnLeft(curr.dir);
				const Vector2i nextPosition = Vector2i{ curr.x, curr.y } + getOffset(newDir);
				const auto nextDistance = currDistance;
				const CrucibleState next{
					.x = nextPosition.x,
					.y = nextPosition.y,
					.straightCount = 1,
					.dir = newDir };

				const auto& existingDistance = distances.find(Vector4i(nextPosition, next.dir, next.straightCount));
				if (existingDistance == distances.end() || (*existingDistance).second > nextDistance)
				{
					distances[Vector4i(nextPosition, next.dir, next.straightCount)] = nextDistance;
					queue.put(next, HEURISTIC(nextPosition));
				}
			}
			// Right
			if (curr.straightCount >= min)
			{
				const auto newDir = turnLeft(curr.dir);
				const Vector2i nextPosition = Vector2i{ curr.x, curr.y } + getOffset(newDir);
				const auto nextDistance = currDistance;
				const CrucibleState next{
					.x = nextPosition.x,
					.y = nextPosition.y,
					.straightCount = 1,
					.dir = newDir };

				const auto& existingDistance = distances.find(Vector4i(nextPosition, next.dir, next.straightCount));
				if (existingDistance == distances.end() || (*existingDistance).second > nextDistance)
				{
					distances[Vector4i(nextPosition, next.dir, next.straightCount)] = nextDistance;
					queue.put(next, HEURISTIC(nextPosition));
				}
			}
		}

		return bestDistance;
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		CrucibleMap crucibleNetwork;

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			auto& row = crucibleNetwork.emplace_back();
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x)
			{
				auto& cell = row.emplace_back();
				cell.val = m_InputLines[y][x] - '0';
			}
		}

		const auto part1 = solveForMinMaxStraightDistance(crucibleNetwork, 1, 3);

		const auto part2 = solveForMinMaxStraightDistance(crucibleNetwork, 4, 10);

		std::cout << "Part 2: 1153 too high" << std::endl;

		return { std::to_string(part1), std::to_string(part2) };
	}
}
