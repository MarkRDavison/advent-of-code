#include <2022/Day22Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyTwo {

	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Monkey Map", 2022, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
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

	std::pair<std::string, std::string> Day22Puzzle::fastSolve(int _cubeSize)
	{
		bool locationSet = false;
		ze::Vector2i location{ 0, 0 };
		core::Orientation facing = core::Orientation::Right;

		Map map;

		std::size_t i = 0;
		for (i = 0; i < m_InputLines.size(); ++i)
		{
			const auto& l = m_InputLines[i];
			if (l.empty())
			{
				break;
			}

			map.push_back(l);

			int x = 0;
			for (const char c : l)
			{
				if (!locationSet && c == '.')
				{
					locationSet = true;
					location.x = x;
				}
				++x;
			}
		}

		Adjacency adjacent = processAdjacency2D(map);

		const auto& instructions = extractInstructions(m_InputLines.back());

		for (const auto& instr : instructions)
		{
			if (instr == "L")
			{
				facing = core::OrientationHelper::turn(facing, core::Orientation::Left);
			}
			else if (instr == "R")
			{
				facing = core::OrientationHelper::turn(facing, core::Orientation::Right);
			}
			else
			{
				const int val = std::stoi(instr);
				auto offset = core::OrientationHelper::toDirection(facing);
				offset.y *= -1;

				for (int i = 0; i < val; ++i)
				{
					location = adjacent.at(location).at(facing);
				}
			}
		}

		int part1 = 1000 * (location.y + 1) + 4 * (location.x + 1);

		if (facing == core::Orientation::Right)
		{
			part1 += 0;
		}
		else if (facing == core::Orientation::Down)
		{
			part1 += 1;
		}
		else if (facing == core::Orientation::Left)
		{
			part1 += 2;
		}
		else if (facing == core::Orientation::Up)
		{
			part1 += 3;
		}

		return { std::to_string(part1), "Part 2" };
	}
	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		return fastSolve(50);
	}

	Adjacency Day22Puzzle::processAdjacency2D(const Map& _map)
	{
		Adjacency adjacent;

		for (int y = 0; y < (int)_map.size(); ++y)
		{
			for (int x = 0; x < (int)_map[y].size(); ++x)
			{
				const auto cell = _map[y][x];
				if (cell == '.')
				{
					auto& neighbours = adjacent[ze::Vector2i(x, y)];

					{	// LEFT
						int nextX = x;
						int validNextX = x;
						while (true)
						{
							int nextNextX = nextX - 1;
							if (nextNextX < 0)
							{
								nextX = (int)(_map[y].size()); continue;
							}

							const auto nextNextXVal = _map[y][nextNextX];

							if (nextNextXVal == '.')
							{
								validNextX = nextNextX;
								break;
							}
							else if (nextNextXVal == '#')
							{
								break;
							}
							else if (nextNextXVal == ' ')
							{
								nextX--;
							}
							else
							{
								assert(false);
							}
						}
						neighbours[core::Orientation::Left] = ze::Vector2i(validNextX, y);
					}
					{	// RIGHT
						int nextX = x;
						int validNextX = x;
						while (true)
						{
							int nextNextX = nextX + 1;
							if (nextNextX >= _map[y].size())
							{
								nextX = -1; continue;
							}

							const auto nextNextXVal = _map[y][nextNextX];

							if (nextNextXVal == '.')
							{
								validNextX = nextNextX;
								break;
							}
							else if (nextNextXVal == '#')
							{
								break;
							}
							else if (nextNextXVal == ' ')
							{
								nextX++;
							}
							else
							{
								assert(false);
							}
						}
						neighbours[core::Orientation::Right] = ze::Vector2i(validNextX, y);
					}
					{	// UP
						int nextY = y;
						int validNextY = y;
						while (true)
						{
							int nextNextY = nextY - 1;
							if (nextNextY < 0)
							{
								nextY = (int)(_map.size()); continue;
							}

							if (_map[nextNextY].size() <= x)
							{
								nextY--;
								continue;
							}

							const auto nextNextYVal = _map[nextNextY][x];

							if (nextNextYVal == '.')
							{
								validNextY = nextNextY;
								break;
							}
							else if (nextNextYVal == '#')
							{
								break;
							}
							else if (nextNextYVal == ' ')
							{
								nextY--;
							}
							else
							{
								assert(false);
							}
						}
						neighbours[core::Orientation::Up] = ze::Vector2i(x, validNextY);
					}
					{	// DOWN
						int nextY = y;
						int validNextY = y;
						while (true)
						{
							int nextNextY = nextY + 1;
							if (nextNextY >= _map.size())
							{
								nextY = -1; continue;
							}

							if (_map[nextNextY].size() <= x)
							{
								nextY++;
								continue;
							}

							const auto nextNextYVal = _map[nextNextY][x];

							if (nextNextYVal == '.')
							{
								validNextY = nextNextY;
								break;
							}
							else if (nextNextYVal == '#')
							{
								break;
							}
							else if (nextNextYVal == ' ')
							{
								nextY++;
							}
							else
							{
								assert(false);
							}
						}
						neighbours[core::Orientation::Down] = ze::Vector2i(x, validNextY);
					}
				}
			}
		}

		return adjacent;
	}

	std::pair<Adjacency, OrientationAdjacency> Day22Puzzle::processAdjacency3D(const Map& _map, int _cubeSize, const ze::Vector2i& _startingLocation)
	{
		assert(_map.size() % _cubeSize == 0);
		Adjacency adjacent;
		OrientationAdjacency orientationAdjacent;

		std::unordered_map<char, ze::Vector2i> faceStarts;
		std::unordered_map<char, ze::Vector2i> orientationMultipliers;

		if (_cubeSize == 4)
		{
			const ze::Vector2i frontFace(8, 0);
			const ze::Vector2i downFace(8, 4);
			const ze::Vector2i leftFace(4, 4);
			const ze::Vector2i topFace(0, 4);
			const ze::Vector2i backFace(8, 8);
			const ze::Vector2i rightFace(12, 8);

			faceStarts['f'] = frontFace;
			faceStarts['d'] = downFace;
			faceStarts['l'] = leftFace;
			faceStarts['t'] = topFace;
			faceStarts['b'] = backFace;
			faceStarts['r'] = rightFace;

			orientationMultipliers['f'] = { 1,1 };
			orientationMultipliers['d'] = { 1,1 };
			orientationMultipliers['l'] = { 1,1 };
			orientationMultipliers['t'] = { 1,1 };
			orientationMultipliers['b'] = { 1,1 };
			orientationMultipliers['r'] = { 1,1 };
		}
		else if (_cubeSize == 50)
		{
			assert(false); // TODO
		}
		else
		{
			assert(false);
		}

		assert(_map[faceStarts['f'].y][faceStarts['f'].x] != ' ');
		assert(_map[faceStarts['d'].y][faceStarts['d'].x] != ' ');
		assert(_map[faceStarts['l'].y][faceStarts['l'].x] != ' ');
		assert(_map[faceStarts['t'].y][faceStarts['t'].x] != ' ');
		assert(_map[faceStarts['b'].y][faceStarts['b'].x] != ' ');
		assert(_map[faceStarts['r'].y][faceStarts['r'].x] != ' ');

		for (const auto& [f, start] : faceStarts)
		{
			for (int y = start.y; y < start.y + _cubeSize; ++y)
			{
				for (int x = start.x; x < start.x + _cubeSize; ++x)
				{
					const auto cell = _map[y][x];
					if (cell == '.')
					{
						if (y != start.y)
						{
							// Can go up without changing
							auto next = ze::Vector2i(x, y - 1);
							if (_map[next.y][next.x] != '.')
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Up] = next;
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Up] = core::Orientation::Up;
							}
							else
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Up] = ze::Vector2i(x, y);
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Up] = core::Orientation::Up;
							}
						}
						if (y != start.y + _cubeSize - 1)
						{
							// Can go down without changing
							const auto next = ze::Vector2i(x, y + 1);
							if (_map[next.y][next.x] != '.')
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Down] = next;
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Down] = core::Orientation::Down;
							}
							else
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Down] = ze::Vector2i(x, y);
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Down] = core::Orientation::Down;
							}
						}
						if (x != start.x)
						{
							// Can go left without changing
							const auto next = ze::Vector2i(x - 1, y);
							if (_map[next.y][next.x] != '.')
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Left] = next;
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Left] = core::Orientation::Left;
							}
							else
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Left] = ze::Vector2i(x, y);
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Left] = core::Orientation::Left;
							}
						}
						if (x != start.x + _cubeSize - 1)
						{
							// Can go right without changing
							const auto next = ze::Vector2i(x + 1, y);
							if (_map[next.y][next.x] != '.')
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Right] = next;
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Right] = core::Orientation::Right;
							}
							else
							{
								adjacent[ze::Vector2i(x, y)][core::Orientation::Right] = ze::Vector2i(x, y);
								orientationAdjacent[ze::Vector2i(x, y)][core::Orientation::Right] = core::Orientation::Right;
							}
						}
					}
				}
			}
		}


		for (const auto& [f, start] : faceStarts)
		{
			{	// TOP
				for (int x = start.x; x < start.x + _cubeSize; ++x)
				{
					const auto next = ze::Vector2i(x, start.y - 1);
					if (next.y >= 0)
					{
						//if (_map[next.y][next.x] )
					}
				}
			}
			{	// BOTTOM

			}
			{	// LEFT

			}
			{	// RIGHT

			}
		}

		return { adjacent, orientationAdjacent };
	}
}
