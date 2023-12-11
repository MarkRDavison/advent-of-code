#include <2023/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <stdexcept>
#include <algorithm>
#include <queue>

namespace TwentyTwentyThree {

	std::unordered_set<char> Day10Puzzle::connectsRight = {
		'-', 'L', 'F', 'S'
	};
	std::unordered_set<char> Day10Puzzle::connectsLeft = {
		'-', 'J', '7', 'S'
	};
	std::unordered_set<char> Day10Puzzle::connectsUp = {
		'|', 'L', 'J', 'S'
	};
	std::unordered_set<char> Day10Puzzle::connectsDown = {
		'|', '7', 'F', 'S'
	};

	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Pipe Maze", 2023, 10) {

	}

	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<PipeMaze, Vector2i> Day10Puzzle::load(const std::vector<std::string>& _inputLines)
	{
		PipeMaze maze;

		Vector2i start = { -1,-1 };

		for (std::size_t y = 0; y < _inputLines.size(); ++y)
		{
			for (std::size_t x = 0; x < _inputLines[y].size(); ++x)
			{
				const char c = _inputLines[y][x];

				auto& cell = maze.getCell((int)x, (int)y);

				cell.originalCharacter = c;
				if (cell.originalCharacter == 'S')
				{
					cell.c = cell.originalCharacter;
					start = { (int)x, (int)y };
				}
			}
		}

		if (start.x == -1 && start.y == -1)
		{
			throw std::runtime_error("Input does not contain a starting point");
		}

		auto& startCell = maze.getCell(start.x, start.y);
		
		std::queue<Vector2i> open;
		open.push(start);
		std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> seen;

		while (!open.empty())
		{
			const auto curr = open.front(); open.pop();

			auto& currCell = maze.getCell(curr.x, curr.y);
			currCell.mainLoop = true;

			if (curr.x > maze.minX)
			{
				const auto& leftCell = maze.getCell(curr.x - 1, curr.y);
				if (connectsLeft.contains(currCell.originalCharacter) &&
					connectsRight.contains(leftCell.originalCharacter))
				{
					currCell.connectLeft = true;
					if (!seen.contains(Vector2i{ curr.x - 1, curr.y }))
					{
						seen.insert(Vector2i{ curr.x - 1, curr.y });
						open.push(Vector2i{ curr.x - 1, curr.y });
					}
				}
			}

			if (curr.x < maze.maxX)
			{
				const auto& rightCell = maze.getCell(curr.x + 1, curr.y);
				if (connectsRight.contains(currCell.originalCharacter) && 
					connectsLeft.contains(rightCell.originalCharacter))
				{
					currCell.connectRight = true;
					if (!seen.contains(Vector2i{ curr.x + 1, curr.y }))
					{
						seen.insert(Vector2i{ curr.x + 1, curr.y });
						open.push(Vector2i{ curr.x + 1, curr.y });
					}
				}
			}

			if (curr.y > maze.minY)
			{
				const auto& upCell = maze.getCell(curr.x, curr.y - 1);
				if (connectsUp.contains(currCell.originalCharacter) && 
					connectsDown.contains(upCell.originalCharacter))
				{
					currCell.connectUp = true;
					if (!seen.contains(Vector2i{ curr.x, curr.y - 1 }))
					{
						seen.insert(Vector2i{ curr.x, curr.y - 1 });
						open.push(Vector2i{ curr.x, curr.y - 1 });
					}
				}
			}

			if (curr.y < maze.maxY)
			{
				const auto& downCell = maze.getCell(curr.x, curr.y + 1);
				if (connectsDown.contains(currCell.originalCharacter) && 
					connectsUp.contains(downCell.originalCharacter))
				{
					currCell.connectDown = true;
					if (!seen.contains(Vector2i{ curr.x, curr.y + 1 }))
					{
						open.push(Vector2i{ curr.x, curr.y + 1 });
						seen.insert(Vector2i{ curr.x, curr.y + 1 });
					}
				}
			}
		}

		return { maze, start };
	}

	std::vector<std::string> Day10Puzzle::drawPipeMaze(const PipeMaze& maze)
	{
		std::vector<std::string> r;

		for (int y = maze.minY; y <= maze.maxY; ++y)
		{
			std::string row0;
			std::string row1;
			std::string row2;
			for (int x = maze.minX; x <= maze.maxX; ++x)
			{
				const auto& cell = maze.getCell(x, y);
				
				if (cell.connectUp) 
				{ row0 += " ^ "; } else 
				{ row0 += "   "; }


				if (cell.connectLeft) 
				{ row1 += "<"; } else 
				{ row1 += " "; }

				if (cell.connectDown || cell.connectLeft || cell.connectRight || cell.connectUp)
				{
					row1 += cell.originalCharacter;
				}
				else
				{
					row1 += '.';
				}

				if (cell.connectRight) 
				{ row1 += ">"; } else 
				{ row1 += " "; }


				if (cell.connectDown)
				{ row2 += " v "; } else 
				{ row2 += "   "; }
			}
			r.push_back(row0);
			r.push_back(row1);
			r.push_back(row2);
		}

		return r;
	}

	std::string Day10Puzzle::solvePart1(const PipeMaze& maze, const Vector2i& start)
	{
		std::unordered_map<Vector2i, int, Vector2_Hash_Fxn<int>> distances;
		std::unordered_map<Vector2i, int, Vector2_Hash_Fxn<int>> distancesFromOutside;
		std::queue<Vector2i> open;

		open.push(start);
		distances[start] = 0;

		while (!open.empty())
		{
			const auto curr = open.front(); open.pop();
			const auto currDistance = distances.at(curr);
			auto& currCell = maze.getCell(curr.x, curr.y);
			

			if (currCell.connectLeft)
			{
				const Vector2i l{ curr.x - 1, curr.y };
				auto currNextDistance = distances.find(l);
				if (currNextDistance == distances.end())
				{
					open.push(l);
					distances[l] = currDistance + 1;
				}
				else
				{
					const auto existingNextDistance = *currNextDistance;
					if (currDistance + 1 < existingNextDistance.second)
					{
						open.push(l);
						distances[l] = currDistance + 1;
					}
				}
			}
			if (currCell.connectRight)
			{
				const Vector2i l{ curr.x + 1, curr.y };
				auto currNextDistance = distances.find(l);
				if (currNextDistance == distances.end())
				{
					open.push(l);
					distances[l] = currDistance + 1;
				}
				else
				{
					const auto existingNextDistance = *currNextDistance;
					if (currDistance + 1 < existingNextDistance.second)
					{
						open.push(l);
						distances[l] = currDistance + 1;
					}
				}
			}
			if (currCell.connectUp)
			{
				const Vector2i l{ curr.x , curr.y - 1 };
				auto currNextDistance = distances.find(l);
				if (currNextDistance == distances.end())
				{
					open.push(l);
					distances[l] = currDistance + 1;
				}
				else
				{
					const auto existingNextDistance = *currNextDistance;
					if (currDistance + 1 < existingNextDistance.second)
					{
						open.push(l);
						distances[l] = currDistance + 1;
					}
				}
			}
			if (currCell.connectDown)
			{
				const Vector2i l{ curr.x , curr.y + 1 };
				auto currNextDistance = distances.find(l);
				if (currNextDistance == distances.end())
				{
					open.push(l);
					distances[l] = currDistance + 1;
				}
				else
				{
					const auto existingNextDistance = *currNextDistance;
					if (currDistance + 1 < existingNextDistance.second)
					{
						open.push(l);
						distances[l] = currDistance + 1;
					}
				}
			}
		}

		long long maxDistance = 0;

		for (int y = maze.minY; y <= maze.maxY; ++y)
		{
			for (int x = maze.minX; x <= maze.maxX; ++x)
			{
				if (distances.contains(Vector2i(x, y)))
				{
					maxDistance = std::max(maxDistance, (long long)distances.at(Vector2i(x, y)));
				}
			}
		}


		return std::to_string(maxDistance);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		auto [maze, start] = load(m_InputLines);

		const auto part1 = solvePart1(maze, start);

		const int newMinX = maze.minX - 1;
		const int newMaxX = maze.maxX + 1;
		const int newMinY = maze.minY - 1;
		const int newMaxY = maze.maxY + 1;

		for (int y = newMinY; y <= newMaxY; ++y)
		{
			for (int x = newMinX; x <= newMaxX; ++x)
			{
				if (x == newMinX || y == newMinY || x == newMaxX || y == newMaxY)
				{
					maze.getCell(x, y).c = '@';
				}
			}
		}

		auto theMaze = drawPipeMaze(maze);

		std::queue<Vector2i> open;
		std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> seen;

		open.push(Vector2i{ newMinX, newMinY });

		const std::unordered_set<char> path = {
		'-', 'L', 'F', 'S', '|', 'J', '7', '<', '>', 'v', '^'
		};

		while (!open.empty())
		{
			const auto curr = open.front(); open.pop();

			auto& character = theMaze[curr.y - newMinX * 3][curr.x - newMinY * 3];
			if (path.contains(character))
			{
				continue;
			}

			character = '@';

			if (curr.x > maze.minX * 3)
			{
				if (!seen.contains(Vector2i{ curr.x - 1, curr.y }))
				{
					seen.insert(Vector2i{ curr.x - 1, curr.y });
					open.push(Vector2i{ curr.x - 1, curr.y });
				}
			}

			if (curr.x <= maze.maxX * 3)
			{
				if (!seen.contains(Vector2i{ curr.x + 1, curr.y }))
				{
					seen.insert(Vector2i{ curr.x + 1, curr.y });
					open.push(Vector2i{ curr.x + 1, curr.y });
				}
			}

			if (curr.y > maze.minY * 3)
			{
				if (!seen.contains(Vector2i{ curr.x, curr.y - 1 }))
				{
					seen.insert(Vector2i{ curr.x, curr.y - 1 });
					open.push(Vector2i{ curr.x, curr.y - 1 });
				}
			}

			if (curr.y <= maze.maxY * 3)
			{
				if (!seen.contains(Vector2i{ curr.x, curr.y + 1 }))
				{
					open.push(Vector2i{ curr.x, curr.y + 1 });
					seen.insert(Vector2i{ curr.x, curr.y + 1 });
				}
			}
		}

		long long part2 = 0;

		for (const auto& r : theMaze)
		{
			for (const char c : r)
			{
				if (c == '.')
				{
					part2++;
				}
			}
		}

		return { part1, std::to_string(part2) };

	}
}
