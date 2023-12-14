#include <2022/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyTwo {

	typedef int DIRECTION;
	typedef int FACE;
	typedef std::unordered_map<DIRECTION, DIRECTION> OPP_DIR_MAP;
	typedef std::unordered_map<Vector2i, FACE, Vector2_Hash_Fxn<int>> COORDS_TO_FACE_MAP;
	typedef std::unordered_map<FACE, Vector2i> FACE_TO_COORDS_MAP;
	typedef std::unordered_map<Vector2i, Vector2i, Vector2_Hash_Fxn<int>> FACE_DIR_TO_FACE_DIR_MAP;

	constexpr DIRECTION RIGHT = 0;
	constexpr DIRECTION DOWN = 1;
	constexpr DIRECTION LEFT = 2;
	constexpr DIRECTION UP = 3;

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
		return -1;
	}

	Vector2i getDirectionOffset(DIRECTION dir)
	{
		switch (dir)
		{
		case DOWN:
			return { 0, +1 };
		case UP:
			return { 0,-1 };
		case RIGHT:
			return { +1,0 };
		case LEFT:
			return { -1,0 };
		default:
			return {};
		}
	}

	bool needsToDoComplicated3dMovement(
		const Vector2i& position, 
		const COORDS_TO_FACE_MAP& coordsToFace,
		DIRECTION dir,
		int faceSize)
	{
		const auto newPosition = position + getDirectionOffset(dir);
		if (newPosition == position) { return false; }

		Vector2i faceCoords = { newPosition.x / faceSize, newPosition.y / faceSize };

		if (newPosition.x < 0)
		{
			faceCoords.x--;
		}
		if (newPosition.y < 0)
		{
			faceCoords.y--;
		}

		return !coordsToFace.contains(faceCoords);
	}

	Vector2i toDirection(DIRECTION dir)
	{
		switch (dir)
		{
		case UP: return { 0,-1 };
		case DOWN: return { 0,+1 };
		case LEFT: return { -1,0 };
		case RIGHT: return { +1,0 };
		default: return {};
		}
	}

	DIRECTION turn(DIRECTION curr, DIRECTION turn)
	{
		assert(turn == LEFT || turn == RIGHT);
		switch (curr) {
		case LEFT:
			return turn == LEFT ? DOWN : UP;
		case RIGHT:
			return turn == LEFT ? UP : DOWN;
		case UP:
			return turn == LEFT ? LEFT : RIGHT;
		case DOWN:
			return turn == LEFT ? RIGHT : LEFT;
		default:
			return curr;
		}
	}

	std::pair<Vector2i, DIRECTION> doComplicated3dMovement(
		const Vector2i& position,
		const COORDS_TO_FACE_MAP& coordsToFace,
		const FACE_TO_COORDS_MAP& faceToCoords,
		const FACE_DIR_TO_FACE_DIR_MAP& faceDirMap,
		DIRECTION dir,
		int faceSize
	)
	{
		Vector2i newPosition = position;
		DIRECTION newDirection = dir;


		Vector2i faceCoords = { newPosition.x / faceSize, newPosition.y / faceSize };

		if (newPosition.x < 0)
		{
			faceCoords.x--;
		}
		if (newPosition.y < 0)
		{
			faceCoords.y--;
		}
		const auto currentFace = coordsToFace.at(faceCoords);

		const auto oldFace = coordsToFace.at({ position.x / faceSize, position.y / faceSize });
		const auto& [newFace, newDir] = faceDirMap.at({ currentFace, dir });

		//const auto oldFaceCoords = faceToCoords.at(newFace);
		const auto newFaceCoords = faceToCoords.at(newFace);

		const auto newGlobalFaceCoords = newFaceCoords * faceSize;

		bool leavingHorizontal = dir == LEFT || dir == RIGHT;

		bool oppositeFaceMod = (oldFace % 2) != (newFace % 2);

		bool onTop = newDir == DOWN;
		bool onBottom = newDir == UP;
		bool onLeft = newDir == RIGHT;
		bool onRight = newDir == LEFT;

		if (onTop)
		{
			const auto newY = newGlobalFaceCoords.y;
			if (leavingHorizontal)
			{				
				if (oppositeFaceMod)
				{
					const auto newXFace = position.y % faceSize;
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
				else
				{
					const auto newXFace = (faceSize - (position.y % faceSize) - 1);
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
			}
			else 
			{
				if (oppositeFaceMod)
				{
					assert(false);
				}
				else
				{
					const auto newXFace = position.x % faceSize;
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
			}
		}
		else if (onBottom)
		{
			const auto newY = newGlobalFaceCoords.y + faceSize - 1;
			if (leavingHorizontal)
			{
				if (oppositeFaceMod)
				{
					const auto newXFace = position.y % faceSize;
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (oppositeFaceMod)
				{
					const auto newXFace = (faceSize - (position.x % faceSize) - 1);
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
				else
				{
					const auto newXFace = position.x % faceSize;
					const auto newX = newGlobalFaceCoords.x + newXFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
			}
		}
		else if (onLeft)
		{
			const auto newX = newGlobalFaceCoords.x;

			if (leavingHorizontal)
			{
				if (oppositeFaceMod)
				{
					const auto newYFace = (faceSize - (position.y % faceSize) - 1);
					const auto newY = newGlobalFaceCoords.y + newYFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
				else
				{
					assert(false);
				}
			}
			else
			{
				if (oppositeFaceMod)
				{
					const auto newYFace = position.x % faceSize;
					const auto newY = newGlobalFaceCoords.y + newYFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
				else
				{
					const auto newYFace = position.x % faceSize;
					const auto newY = newGlobalFaceCoords.y + newYFace;

					newPosition = { newX, newY };
					newDirection = newDir;
				}
			}
		}
		else if (onRight)
		{
			const auto newX = newGlobalFaceCoords.x + faceSize - 1;

			if (leavingHorizontal)
			{
				const auto newYFace = (faceSize - (position.y % faceSize) - 1);
				const auto newY = newGlobalFaceCoords.y + newYFace;

				newPosition = { newX, newY };
				newDirection = newDir;
			}
			else
			{
				const auto newYFace = position.x % faceSize;
				const auto newY = newGlobalFaceCoords.y + newYFace;

				newPosition = { newX, newY };
				newDirection = newDir;
			}
		}
		else
		{
			assert(false);
		}

		/*
		with face size 4
		using coord = {8,2}
		So going LEFT from FACE 1

		look up faceAndDirectionToFaceAndDirection.at({1, LEFT})

		returns {3, DOWN}


		faceToCoords.at(1) => {2,0}
		faceToCoords.at(3) => {1,1}

		opposite axis to LEFT is Y
		opposite axis to DOWN is X

		new coord y = faceToCoords.at(3).y * faceSize

		since (face id 1) % 2  == (face id 3 % 2)

		new coord x = faceToCoords.at(3).x * faceSize + (coord.y % faceSize)

		*/

		return { newPosition, newDirection };
	}

	long long solvePart2(
		const Vector2i& start,
		const std::vector<std::string>& map,
		const std::vector<std::string>& instructions,
		std::size_t faceSize
	)
	{
		Vector2i pos(start);
		auto cube(map);

		/*
		
		      11
			  11

      22  33  44
	  22  33  44

		      55  66
			  55  66


		*/

		const OPP_DIR_MAP oppositeDirection = {
			{RIGHT, LEFT},
			{LEFT, RIGHT},
			{UP, DOWN},
			{DOWN, UP}
		};

		const std::unordered_map<DIRECTION, char> dirChars = {
			{ RIGHT, '>' },
			{ LEFT, '<' },
			{ DOWN, 'v' },
			{ UP, '^' }
		};
		const std::unordered_map<DIRECTION, long long> facingScores = {
			{ RIGHT, 0 },
			{ DOWN, 1 },
			{ LEFT, 2 },
			{ UP, 3 }
		};


		FACE_DIR_TO_FACE_DIR_MAP faceAndDirectionToFaceAndDirection;
		COORDS_TO_FACE_MAP coordsToFace;
		FACE_TO_COORDS_MAP faceToCoords;

		if (faceSize == 4)
		{
			coordsToFace = {
				{{2,0}, 1},
				{{0,1}, 2},
				{{1,1}, 3},
				{{2,1}, 4},
				{{2,2}, 5},
				{{3,2}, 6}
			};

			faceAndDirectionToFaceAndDirection = {
				{ {1, LEFT}, {3, DOWN} },
				{ {1, UP}, {2, DOWN} },
				{ {2, LEFT}, {6, UP} },
				{ {2, DOWN}, {5, UP} },
				{ {3, DOWN}, {5, RIGHT}},
				{ {1, RIGHT}, {6, LEFT} },
				{ {4, RIGHT}, {6, DOWN} }
			};
		}
		else if (faceSize == 50)
		{
			coordsToFace = {
				{{1,0}, 1},
				{{2,0}, 2},
				{{1,1}, 3},
				{{0,2}, 4},
				{{1,2}, 5},
				{{0,3}, 6}
			};

			faceAndDirectionToFaceAndDirection = {
				{ {1, UP}, {6, RIGHT} },
				{ {1, LEFT}, {4, RIGHT} },
				{ {3, LEFT}, {4, DOWN} },
				{ {2, DOWN}, {3, LEFT} },
				{ {2, RIGHT}, {5, LEFT} },
				{ {5, DOWN}, {6, LEFT} },
				{ {2, UP}, {6, UP} },
			};
		}
		else
		{
			std::cout << "Unhandled" << std::endl;
			exit(-1);
		}

		{
			FACE_DIR_TO_FACE_DIR_MAP temp;
			for (const auto& [from, to] : faceAndDirectionToFaceAndDirection)
			{
				const Vector2i newFrom = { to.x, oppositeDirection.at(to.y) };
				const Vector2i newTo = { from.x, oppositeDirection.at(from.y) };
				temp[newFrom] = newTo;
			}

			for (const auto& [from, to] : temp)
			{
				faceAndDirectionToFaceAndDirection[from] = to;
			}
		}
		{
			for (const auto& [coord, face] : coordsToFace)
			{
				faceToCoords[face] = coord;
			}
		}

		std::unordered_map<Vector2i, char, Vector2_Hash_Fxn<int>> locations;

		const auto printMap =
			[&locations, &dirChars](const std::vector<std::string>& map, const std::string& instr) -> void
			{
				auto mapOutput(map);

				for (const auto& [loc, c] : locations)
				{
					mapOutput[(std::size_t)loc.y][(std::size_t)loc.x] = c;
				}

				std::cout << "===================================================" << std::endl;
				std::cout << "                   " << instr << std::endl;
				for (const auto& l : mapOutput)
				{
					std::cout << l << std::endl;
				}
			};
		int face = 1;

		auto dir = RIGHT;
		locations[pos] = dirChars.at(dir);

		std::string lastInstr = "START";

		for (const auto& i : instructions) 
		{
			//printMap(cube, lastInstr);
			lastInstr = i;
			if (i == "L")
			{
				dir = turn(dir, LEFT);
				locations[pos] = dirChars.at(dir);
				continue;
			}
			if (i == "R")
			{
				dir = turn(dir, RIGHT);
				locations[pos] = dirChars.at(dir);
				continue;
			}

			int offset = std::stoi(i);
			while (offset > 0)
			{
				auto newPosition = pos;
				auto newDirection = dir;
				if (needsToDoComplicated3dMovement(pos, coordsToFace, dir, (int)faceSize))
				{
					const auto& [newP, newD] = doComplicated3dMovement(
						pos, 
						coordsToFace, 
						faceToCoords,
						faceAndDirectionToFaceAndDirection, 
						dir, 
						(int)faceSize);
					newPosition = newP;
					newDirection = newD;
				}
				else
				{
					auto dirOffset = toDirection(dir);
					newPosition = pos + dirOffset;
				}

				const auto c = cube[newPosition.y][newPosition.x];

				if (c == '#')
				{
					break;
				}
				else if (c == '.')
				{
					pos = newPosition;
					dir = newDirection;
					locations[pos] = dirChars.at(dir);
				}
				else
				{
					assert(false);
				}

				offset--;
			}
		}

		//printMap(cube, lastInstr);

		const long long score = 1000 * (pos.y + 1) + 4 * (pos.x + 1) + facingScores.at(dir);

		return score;
	}

	long long solvePart1(
		const Vector2i& start,
		const std::vector<std::string>& map, 
		const std::vector<std::string>& instructions
	)
	{
		Vector2i pos(start);

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
		auto part2 = solvePart2(start, map, instructions, faceSize);
		
		return { std::to_string(part1), std::to_string(part2) };
	}

}
