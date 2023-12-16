#include <2023/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Orientation.hpp>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <queue>

#define EMPTY '.'
#define VERTICAL '|'
#define HORIZONTAL '-'
#define FORWARD '/'
#define BACKWARD '\\'

namespace TwentyTwentyThree {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("The Floor Will Be Lava", 2023, 16) {
	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Beam
	{
		int id;
		Vector2i position;
		core::Orientation dir;
	};

	typedef std::vector<std::string> Contraption;
	typedef std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> BeamLocations;

	void printContraption(const Contraption& contraption)
	{
		Contraption curr(contraption);

		for (const auto& r : curr)
		{
			std::cout << r << std::endl;
		}
	}

	std::size_t solveForStartingBeam(Contraption contraption, const Beam& start)
	{
		std::queue<Beam> queue;
		queue.push(start);

		BeamLocations locations;

		while (!queue.empty())
		{
			const auto curr = queue.front(); queue.pop();

			auto offset = core::OrientationHelper::toDirection(curr.dir);
			offset.y *= -1;

			const auto nextPosition = curr.position + offset;

			if (nextPosition.x < 0 ||
				nextPosition.y < 0 ||
				nextPosition.x >= (int)contraption.size() ||
				nextPosition.y >= (int)contraption[0].size())
			{
				continue;
			}

			auto& nextCell = contraption[(std::size_t)nextPosition.y][(std::size_t)nextPosition.x];
			if (nextCell == EMPTY)
			{
				if (curr.dir == core::Orientation::Right)
				{
					nextCell = '>';
				}
				else if (curr.dir == core::Orientation::Left)
				{
					nextCell = '<';
				}
				else if (curr.dir == core::Orientation::Up)
				{
					nextCell = '^';
				}
				else if (curr.dir == core::Orientation::Down)
				{
					nextCell = 'v';
				}

				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = curr.dir });
			}
			else if (nextCell == VERTICAL && core::OrientationHelper::isHorizontal(curr.dir))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Up });
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Down });
			}
			else if (nextCell == VERTICAL && !core::OrientationHelper::isHorizontal(curr.dir))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = curr.dir });
			}
			else if (nextCell == HORIZONTAL && !core::OrientationHelper::isHorizontal(curr.dir))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Left });
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Right });
			}
			else if (nextCell == HORIZONTAL && core::OrientationHelper::isHorizontal(curr.dir))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = curr.dir });
			}
			else if (nextCell == FORWARD && curr.dir == core::Orientation::Right)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Up });
			}
			else if (nextCell == FORWARD && curr.dir == core::Orientation::Left)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Down });
			}
			else if (nextCell == FORWARD && curr.dir == core::Orientation::Up)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Right });
			}
			else if (nextCell == FORWARD && curr.dir == core::Orientation::Down)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Left });
			}
			else if (nextCell == BACKWARD && curr.dir == core::Orientation::Right)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Down });
			}
			else if (nextCell == BACKWARD && curr.dir == core::Orientation::Up)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Left });
			}
			else if (nextCell == BACKWARD && curr.dir == core::Orientation::Down)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Right });
			}
			else if (nextCell == BACKWARD && curr.dir == core::Orientation::Left)
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = core::Orientation::Up });
			}
			else if (core::OrientationHelper::isHorizontal(curr.dir) && (nextCell == '<' || nextCell == '>'))
			{
				// All good. just stop
			}
			else if (core::OrientationHelper::isHorizontal(curr.dir) && (nextCell == '^' || nextCell == 'v'))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = curr.dir });
			}
			else if (!core::OrientationHelper::isHorizontal(curr.dir) && (nextCell == '^' || nextCell == 'v'))
			{
				// All good. just stop
			}
			else if (!core::OrientationHelper::isHorizontal(curr.dir) && (nextCell == '<' || nextCell == '>'))
			{
				locations.insert(nextPosition);
				queue.push(Beam{ .id = curr.id, .position = nextPosition, .dir = curr.dir });
			}
			else
			{
				std::cout << "UNHANDLED - " << nextPosition.x << ", " << nextPosition.y << " -> " << core::OrientationHelper::toString(curr.dir) << std::endl;
				assert(false);
			}

		}

		return locations.size();
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		Contraption contraption(m_InputLines);

		const std::size_t part1 = solveForStartingBeam(
			contraption, 
			Beam{ .id = 1, .position = { -1,0 }, .dir = core::Orientation::Right });

		std::size_t part2 = 0;

		for (int x = 0; x < contraption[0].size(); ++x)
		{
			// along the top
			const Beam beamTop{ .id = 1, .position = { x,-1 }, .dir = core::Orientation::Down };

			part2 = std::max(part2, solveForStartingBeam(contraption, beamTop));

			// along the bottom
			const Beam beamBot{ .id = 1, .position = { x, (int)contraption.size()}, .dir = core::Orientation::Up };

			part2 = std::max(part2, solveForStartingBeam(contraption, beamBot));
		}

		for (int y = 0; y < contraption.size(); ++y)
		{
			// along the left
			const Beam beamLeft{ .id = 1, .position = { -1, y }, .dir = core::Orientation::Right };

			part2 = std::max(part2, solveForStartingBeam(contraption, beamLeft));

			// along the right
			const Beam beamRight{ .id = 1, .position = { (int)contraption[0].size(), y}, .dir = core::Orientation::Left};

			part2 = std::max(part2, solveForStartingBeam(contraption, beamRight));
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
