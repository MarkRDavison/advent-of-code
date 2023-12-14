#include <2022/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyTwo {

	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Monkey Map", 2022, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::vector<std::string> extractInstructions(const std::string& _input)
	{
		std::vector<std::string> instr;

		std::size_t i = 0;
		std::string buffer;
		while (i < _input.size())
		{
			const auto start = _input[i];
			if (start == 'L' ||
				start == 'R')
			{
				if (!buffer.empty())
				{
					instr.push_back(buffer);
					buffer.clear();
				}
				instr.push_back(std::string(1, start));
			}
			else
			{
				buffer += start;
			}
			++i;
		}
		if (!buffer.empty())
		{
			instr.push_back(buffer);
		}

		return instr;
	}

	std::size_t findFaceSize(std::size_t w, std::size_t h)
	{
		const std::vector<std::pair<std::size_t, std::size_t>> pairs = {
			{2,5},{3,4},{4,3},{5,2}
		};
		for (const auto& [x, y] : pairs)
		{
			if (h / x == w / y)
			{
				return h / x;
			}
		}

		assert(false);
	}



	long long solvePart1(
		const Vector2i& start,
		const std::vector<std::string>& map, 
		const std::vector<std::string>& instructions)
	{
		Vector2i pos(start);
		// ">v<^"
		core::Orientation dir(core::Orientation::Right);
		std::unordered_map<std::string, char> dirChars = {
			{ core::OrientationHelper::toString(core::Orientation::Right), '>' },
			{ core::OrientationHelper::toString(core::Orientation::Left), '<' },
			{ core::OrientationHelper::toString(core::Orientation::Down), 'v' },
			{ core::OrientationHelper::toString(core::Orientation::Up), '^' }
		};
		std::unordered_map<std::string, long long> facingScores = {
			{ core::OrientationHelper::toString(core::Orientation::Right), 0 },
			{ core::OrientationHelper::toString(core::Orientation::Down), 1 },
			{ core::OrientationHelper::toString(core::Orientation::Left), 2 },
			{ core::OrientationHelper::toString(core::Orientation::Up), 3 }
		};
		std::unordered_map<Vector2i, char, Vector2_Hash_Fxn<int>> locations;

		const auto printMap = 
			[&locations, &dirChars](const std::vector<std::string>& map) -> void
			{
				auto mapOutput(map);

				for (const auto& [loc, c] : locations)
				{
					mapOutput[(std::size_t)loc.y][(std::size_t)loc.x] = c;
				}

				std::cout << "===================================================" << std::endl;
				for (const auto& l : mapOutput)
				{
					std::cout << l << std::endl;
				}
			};

		const auto getNextLocation2d = 
			[](
				const std::vector<std::string>& map, 
				const Vector2i& pos, 
				core::Orientation dir
			) -> Vector2i
			{
				auto dirOffset = core::OrientationHelper::toDirection(dir);
				dirOffset.y *= -1;

				bool xChange = dirOffset.x != 0;

				char cell = ' ';
				Vector2i next = pos;

				while (cell == ' ')
				{
					next = next + dirOffset;

					if (dirOffset.x == 0)
					{
						while (next.y < 0)
						{
							next.y += (int)map.size();
						}
						while (next.y >= (int)map.size())
						{
							next.y -= (int)map.size();
						}

						const auto currWidth = (int)map[(std::size_t)next.y].size();

						while (next.x < 0)
						{
							next.x += currWidth;
						}
						while (next.x >= currWidth)
						{
							next.x -= currWidth;
						}
					}
					else
					{
						const auto currWidth = (int)map[(std::size_t)next.y].size();

						while (next.x < 0)
						{
							next.x += currWidth;
						}
						while (next.x >= currWidth)
						{
							next.x -= currWidth;
						}

						while (next.y < 0)
						{
							next.y += (int)map.size();
						}
						while (next.y >= (int)map.size())
						{
							next.y -= (int)map.size();
						}

					}

					cell = map[(std::size_t)next.y][(std::size_t)next.x];
				}

				if (cell == '.')
				{
					return next;
				}

				return pos;
			};

		locations[pos] = dirChars.at(core::OrientationHelper::toString(dir));

		for (const auto& i : instructions)
		{
			if (i == "L")
			{
				dir = core::OrientationHelper::turn(dir, core::Orientation::Left);
				locations[pos] = dirChars.at(core::OrientationHelper::toString(dir));
				continue;
			}
			if (i == "R")
			{
				dir = core::OrientationHelper::turn(dir, core::Orientation::Right);
				locations[pos] = dirChars.at(core::OrientationHelper::toString(dir));
				continue;
			}

			int offset = std::stoi(i);
			while (offset > 0)
			{
				pos = getNextLocation2d(map, pos, dir);
				locations[pos] = dirChars.at(core::OrientationHelper::toString(dir));
				offset--;
			}
		}

		const long long score = 1000 * (pos.y + 1) + 4 * (pos.x + 1) + facingScores[core::OrientationHelper::toString(dir)];

		return score;
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve()
	{
		Vector2i start;
		const auto instructions = extractInstructions(m_InputLines.back());
		std::size_t maxWidth = 0;
		std::vector<std::string> map;
		for (const auto& l : m_InputLines)
		{
			if (l.empty())
			{
				break;
			}

			map.push_back(l);
			maxWidth = std::max(maxWidth, l.size());
		}

		const auto faceSize = findFaceSize(maxWidth, map.size());

		start.x = (int)map.front().find_first_not_of(' ');

		auto part1 = solvePart1(start, map, instructions);
		auto part2 = 0;

		return { std::to_string(part1), std::to_string(part2) };
	}

}
