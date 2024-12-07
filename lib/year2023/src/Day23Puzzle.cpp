#include <2023/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>
#include <unordered_map>
#include <unordered_set>
#include <queue>

namespace TwentyTwentyThree {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("A Long Walk", 2023, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct TrailCell
	{
		char c{ '#' };
	};

	typedef core::Region<TrailCell> Trails;
	typedef std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> TrailsSeenSet;

	std::vector<Vector2i> findNeighbours(
		Trails& trails,
		Vector2i current,
		TrailsSeenSet seen
	)
	{
		std::vector<Vector2i> n;
		const auto upCoord = Vector2i(current.x, current.y - 1);
		const auto up = trails.getCell(upCoord.x, upCoord.y).c;
		const auto downCoord = Vector2i(current.x, current.y + 1);
		const auto down = trails.getCell(downCoord.x, downCoord.y).c;
		const auto leftCoord = Vector2i(current.x - 1, current.y);
		const auto left = trails.getCell(leftCoord.x, leftCoord.y).c;
		const auto rightCoord = Vector2i(current.x + 1, current.y);
		const auto right = trails.getCell(rightCoord.x, rightCoord.y).c;

		// ^  >  v  <

		if ((up == '.' || up == '^') && !seen.contains(upCoord))
		{
			n.push_back(upCoord);
		}
		if ((down == '.' || down == 'v') && !seen.contains(downCoord))
		{
			n.push_back(downCoord);
		}
		if ((left == '.' || left == '<') && !seen.contains(leftCoord))
		{
			n.push_back(leftCoord);
		}
		if ((right == '.' || right == '>') && !seen.contains(rightCoord))
		{
			n.push_back(rightCoord);
		}
		return n;
	}

	struct PathFollowedInfo
	{
		Vector2i coord;
		long long distanceTravelled{ 0 };
		TrailsSeenSet travelledOver;
	};

	PathFollowedInfo followPathTillJunction(
		Trails& trails,
		TrailsSeenSet seen,
		Vector2i prev,
		Vector2i next
	)
	{


		PathFollowedInfo info;
		TrailsSeenSet followSeen(seen);
		auto curr = next;
		followSeen.insert(curr);

		while (true)
		{
			const auto& neighbours = findNeighbours(trails, curr, followSeen);
			if (neighbours.size() == 1)
			{
				// Good to go, just keep following
				curr = neighbours.front();
				followSeen.insert(curr);
				info.travelledOver.insert(curr);
				info.distanceTravelled++;
			}
			else
			{
				info.coord = curr;
				break;
			}
		}


		return info;
	}

	void recurser(
		Trails& trails,
		Vector2i current,
		long long distance,
		Vector2i goal,
		TrailsSeenSet seen,
		long long& maxDistance
	) 
	{
		if (current == goal)
		{
			if (maxDistance < distance)
			{
				maxDistance = distance;
				std::cout << "New Max Distance: " << distance << std::endl;
			}
			return;
		}

		seen.insert(current);

		long long max = distance;
		const auto neighbours = findNeighbours(trails, current, seen);

		for (const auto n : neighbours)
		{
			const auto followedInfo = followPathTillJunction(trails, seen, current, n);
			const auto currentDistance = distance + 1 + followedInfo.distanceTravelled;
			TrailsSeenSet seenNeighbour(seen);
			for (const auto& s : followedInfo.travelledOver)
			{
				seenNeighbour.insert(s);
			}

			recurser(trails, followedInfo.coord, currentDistance, goal, seenNeighbour, maxDistance);
		}

	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		Trails trails1;
		Trails trails2;
		Vector2i start;
		Vector2i end;
		for (std::size_t x = 0; x < m_InputLines[0].size(); ++x)
		{
			if (m_InputLines[0][x] == '.')
			{
				start.x = (int)x;
				break;
			}
		}
		for (std::size_t x = 0; x < m_InputLines.back().size(); ++x)
		{
			if (m_InputLines.back()[x] == '.')
			{
				end.x = (int)x;
				end.y = (int)m_InputLines.size() - 1;
				break;
			}
		}

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x)
			{
				trails1.getCell((int)x, (int)y).c = m_InputLines[y][x];
				trails2.getCell((int)x, (int)y).c = m_InputLines[y][x] == '#' ? '#' : '.';
			}
		}

		long long part1 = 0;
		long long part2 = 0;
		std::cout << "Solving part 1" << std::endl;
		recurser(trails1, start, 0, end, {}, part1);
		std::cout << "Solving part 2" << std::endl;
		recurser(trails2, start, 0, end, {}, part2);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
