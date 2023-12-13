#include <2018/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <queue>
#include <stack>

namespace TwentyEighteen {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("A Regular Map", 2018, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {

		RegularMap map;

		auto regex = m_InputLines[0].substr(1, m_InputLines[0].size() - 2);

		static const std::unordered_map<char, Vector2i> dirs = {
			{ 'N', { 0, -1 } },
			{ 'W', { -1, 0 } },
			{ 'E', { +1, 0 } },
			{ 'S', { 0, +1 } }
		};

		static const std::unordered_map<char, std::function<void(const Vector2i&)>> roomEntryTarget = {
			{ 'N', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorSouthOpened = true; }},
			{ 'W', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorEastOpened = true; }},
			{ 'E', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorWestOpened = true; }},
			{ 'S', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorNorthOpened = true; }}
		};

		static const std::unordered_map<char, std::function<void(const Vector2i&)>> roomEntrySource = {
			{ 'N', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorNorthOpened = true; }},
			{ 'W', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorWestOpened = true; }},
			{ 'E', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorEastOpened = true; }},
			{ 'S', [&map](const Vector2i& c) -> void { map.getCell(c.x, c.y).doorSouthOpened = true; }}
		};

		std::stack<Vector2i> coordStack;

		Vector2i coord({ 0,0 });
		char last = '?';
		while (!regex.empty())
		{
			const auto c = regex[0];
			regex.erase(regex.begin(), regex.begin() + 1);
			if (dirs.contains(c))
			{
				roomEntrySource.at(c)(coord);
				coord += dirs.at(c);
				roomEntryTarget.at(c)(coord);
			}
			else if (c == '(')
			{
				coordStack.push(coord);
			}
			else if (c == '|')
			{
				coord = coordStack.top();
			}
			else if (c == ')')
			{
				coordStack.pop();
			}

			last = c;
		}

		long long part1 = 0;
		long long part2 = 0;

		{
			std::queue<Vector2i> open;
			open.push(Vector2i());
			std::unordered_map<Vector2i, long long, Vector2_Hash_Fxn<int>> distances;
			distances.emplace(Vector2i(), 0);

			while (!open.empty())
			{
				const auto curr = open.front(); open.pop();
				const auto currDistance = distances.at(curr);
				const auto nextDistance = currDistance + 1;
				auto& currCell = map.getCell(curr.x, curr.y);

				if (currCell.doorNorthOpened)
				{
					const Vector2i next{ curr.x, curr.y - 1 };
					if (!distances.contains(next) || nextDistance < distances.at(next))
					{
						distances[next] = nextDistance;
						open.push(next);
					}
				}
				if (currCell.doorSouthOpened)
				{
					const Vector2i next{ curr.x, curr.y + 1 };
					if (!distances.contains(next) || nextDistance < distances.at(next))
					{
						distances[next] = nextDistance;
						open.push(next);
					}
				}
				if (currCell.doorWestOpened)
				{
					const Vector2i next{ curr.x - 1, curr.y };
					if (!distances.contains(next) || nextDistance < distances.at(next))
					{
						distances[next] = nextDistance;
						open.push(next);
					}
				}
				if (currCell.doorEastOpened)
				{
					const Vector2i next{ curr.x + 1, curr.y };
					if (!distances.contains(next) || nextDistance < distances.at(next))
					{
						distances[next] = nextDistance;
						open.push(next);
					}
				}
			}

			for (const auto& [coord, distance] : distances)
			{
				part1 = std::max(part1, distance);
				if (distance >= 1000)
				{
					part2++;
				}
			}
		}


		return { std::to_string(part1), std::to_string(part2) };
	}
}
