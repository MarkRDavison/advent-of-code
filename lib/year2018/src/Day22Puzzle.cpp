#include <2018/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Vector3.hpp>
#include <Core/Pathfinding.hpp>
#include <array>

#define TORCH 0
#define CLIMBING 1
#define NEITHER 2

#define ROCKY 0
#define WET 1
#define NARROW 2

namespace TwentyEighteen {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Mode Maze", 2018, 22) {

	}
	Day22Puzzle::~Day22Puzzle() {

	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[TORCH]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct ModeMazeCell
	{
		char c{ '?' };
		long long erosionIndex{ 0 };
		long long geologicalIndex{ 0 };
		int tool{ 0 };
	};

	// Layer 0 = torch, layer 1 = climbing gear, layer 2 = neither
	typedef std::array<std::vector<std::vector<ModeMazeCell>>, 3> ModeMaze;
	typedef std::unordered_map<Vector3<int>, int, Vector3_Hash_Fxn<int>> Distances;

	bool canEnter(const ModeMaze& maze, const Vector3i& coord)
	{
		const auto tool = coord.z;
		const auto& nextCell = maze[tool][coord.y][coord.x];
		const auto nextRegion = nextCell.erosionIndex % 3;

		if (tool == TORCH && nextRegion == WET)
		{
			return false;
		}

		if (tool == NEITHER && nextRegion == ROCKY)
		{
			return false;
		}

		if (tool == CLIMBING && nextRegion == NARROW)
		{
			return false;
		}

		return true;
	}

	bool canSwapFromTool(const ModeMaze& maze, const Vector2i& coord, int currentTool)
	{
		if (canEnter(maze, { coord, currentTool }))
		{
			return true;
		}

		std::cout << "LIMITED!" << std::endl;
		return false;
	}

	void validateAndAddCell(
		const ModeMaze& map,
		const Vector3i& next,
		const Vector2i& coordinates,
		int tool,
		int newDistance,
		internal::PriorityQueue<Vector3<int>, int>& queue,
		Distances& distances)
	{
		if (canEnter(map, next))
		{
			if (!distances.contains(next) || distances.at(next) > newDistance)
			{
				distances[next] = newDistance;
				queue.put(next, std::abs(coordinates.x - next.x) + std::abs(coordinates.y - next.y) + 7 * std::abs(tool - next.z));
			}
		}
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		const long long depth = std::stoll(StringExtensions::splitStringByDelimeter(m_InputLines[0], " ")[1]);
		const Vector2i target = {
			std::stoi(StringExtensions::splitStringByDelimeter(m_InputLines[1], " ,")[1]),
			std::stoi(StringExtensions::splitStringByDelimeter(m_InputLines[1], " ,")[2])
		};

		ModeMaze map;

		const auto Width = std::min((std::size_t)target.x + 250, (std::size_t)target.x * 3);
		const auto Height = std::min((std::size_t)target.y + 250, (std::size_t)target.y * 3);

		for (std::size_t y = 0; y < Height; ++y)
		{
			auto& row0 = map[TORCH].emplace_back();
			auto& row1 = map[CLIMBING].emplace_back();
			auto& row2 = map[NEITHER].emplace_back();
			row0.resize(Width);
			row1.resize(Width);
			row2.resize(Width);

			for (std::size_t x = 0; x < Width; ++x)
			{
				auto& cell0 = row0[x];

				cell0.geologicalIndex = 0;

				if ((x == 0 && y == 0) ||
					((int)x == target.x && (int)y == target.y))
				{
				}
				else if (x == 0)
				{
					cell0.geologicalIndex = y * 48271;
				}
				else if (y == 0)
				{
					cell0.geologicalIndex = x * 16807;
				}
				else
				{
					cell0.geologicalIndex =
						map[TORCH][y][x - 1].erosionIndex * 
						map[TORCH][y - 1][x].erosionIndex;
				}

				cell0.erosionIndex = (cell0.geologicalIndex + depth) % 20183;
				switch (cell0.erosionIndex % 3)
				{
				case 0:
					cell0.c = '.';
					break;
				case 1:
					cell0.c = '=';
					break;
				case 2:
					cell0.c = '|';
					break;
				}

				map[TORCH][y][x].tool = 0;
				map[CLIMBING][y][x].tool = 0;
				map[NEITHER][y][x].tool = 0;

				map[CLIMBING][y][x].c = map[TORCH][y][x].c;
				map[NEITHER][y][x].c = map[TORCH][y][x].c;
				map[CLIMBING][y][x].erosionIndex = map[TORCH][y][x].erosionIndex;
				map[NEITHER][y][x].erosionIndex = map[TORCH][y][x].erosionIndex;
				map[CLIMBING][y][x].geologicalIndex = map[TORCH][y][x].geologicalIndex;
				map[NEITHER][y][x].geologicalIndex = map[TORCH][y][x].geologicalIndex;
			}
		}

		long long part1 = 0;

		for (std::size_t y = 0; y <= (std::size_t)target.y; ++y)
		{
			for (std::size_t x = 0; x <= (std::size_t)target.x; ++x)
			{
				part1 += map[TORCH][y][x].erosionIndex % 3;
			}
		}

		Vector3<int> start{ 0, 0, TORCH };
		Vector3<int> end{ target.x, target.y, TORCH };

		constexpr int TOOL_CHANGE_COST = 7;

		internal::PriorityQueue<Vector3<int>, int> queue;
		queue.put(start, 0);
		Distances distances;
		distances[start] = 0;

		while (!queue.empty())
		{
			const auto curr = queue.get();


			const auto coordinates = Vector2i{ curr.x, curr.y };
			const auto tool = curr.z;
			const auto currentDistance = distances.at(curr);

			const auto& currentCell = map[tool][coordinates.y][coordinates.x];
			const auto currentRegion = currentCell.erosionIndex % 3;


			if (curr == end)
			{
				if (getVerbose())
				{
					std::cout << "Found end!: " << currentDistance << ", queue size: " << queue.elements.size() << std::endl;
				}
				continue;
			}

			if (coordinates.x > 0)
			{
				// Left
				const Vector3i next{ coordinates.x - 1, coordinates.y, tool };
				const auto newDistance = currentDistance + 1;

				validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
			}

			if (coordinates.x < Width - 1)
			{
				// Right
				const Vector3i next{ coordinates.x + 1, coordinates.y, tool };
				const auto newDistance = currentDistance + 1;

				validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
			}

			if (coordinates.y > 0)
			{
				// Up
				const Vector3i next{ coordinates.x, coordinates.y - 1, tool };
				const auto newDistance = currentDistance + 1;

				validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
			}

			if (coordinates.y < Height - 1)
			{
				// Down
				const Vector3i next{ coordinates.x, coordinates.y + 1, tool };
				const auto newDistance = currentDistance + 1;

				validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
			}

			if (canEnter(map, {coordinates, TORCH}))
			{
				if (canSwapFromTool(map, coordinates, tool))
				{
					const Vector3i next{ coordinates.x, coordinates.y, TORCH };

					const auto newDistance = currentDistance + TOOL_CHANGE_COST;
					validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
				}
			}


			if (canEnter(map, { coordinates, CLIMBING }))
			{
				if (canSwapFromTool(map, coordinates, tool))
				{
					const Vector3i next{ coordinates.x, coordinates.y, CLIMBING };

					const auto newDistance = currentDistance + TOOL_CHANGE_COST;
					validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
				}
			}

			if (canEnter(map, { coordinates, NEITHER }))
			{
				if (canSwapFromTool(map, coordinates, tool))
				{
					const Vector3i next{ coordinates.x, coordinates.y, NEITHER };

					const auto newDistance = currentDistance + TOOL_CHANGE_COST;
					validateAndAddCell(map, next, coordinates, tool, newDistance, queue, distances);
				}
			}
		}

		const auto part2 = distances.at(end);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
