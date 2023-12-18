#include <2023/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cassert>
#include <algorithm>

namespace TwentyTwentyThree {
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Lavaduct Lagoon", 2023, 18) {
	}

	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct DigPlan
	{
		char dir{ '?' };
		unsigned long amount{ 0 };
	};

	struct LavaDigCell
	{
		char c{ '.' };
		char dir{ '?' };
	};

	char getDirFromValue(char val)
	{
		switch (val)
		{
		case '0':
			return 'R';
		case '1':
			return 'D';
		case '2':
			return 'L';
		case '3':
			return 'U';
		default:
			assert(false);
			return '?';
		}
	}

	Vector2<long long> getOffset(char dir)
	{
		switch (dir)
		{
		case 'U':
			return { 0,-1 };
		case 'D':
			return { 0,+1 };
		case 'L':
			return { -1,0 };
		case 'R':
			return { +1,0 };
		default:
			assert(false);
			return {};
		}
	}

	long long getCapacity(const std::vector<DigPlan>& plans)
	{
		Vector2<long long> curr = { 0,0 };

		std::vector<Vector2<long long>> points;
		points.push_back({});

		long long perimeter = 0;

		std::size_t i = 0;
		for (const auto& p : plans)
		{
			const auto offset = getOffset(p.dir);
			curr.x += offset.x * p.amount;
			curr.y += offset.y * p.amount;
			perimeter += (long long)p.amount;
			points.push_back(curr);
		}

		std::reverse(points.begin(), points.end());

		long long capacity = 0;

		for (std::size_t i = 0; i < points.size() - 1; ++i)
		{
			capacity += (points[i].x + points[i + 1].x) * (points[i].y - points[i + 1].y);
		}

		return perimeter / 2 + capacity / 2 + 1;
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		std::vector<DigPlan> plans1;
		std::vector<DigPlan> plans2;
		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, " ()");
			assert(parts.size() == 3);

			auto& plan1 = plans1.emplace_back();

			plan1.dir = parts[0][0];
			plan1.amount = std::stoul(parts[1]);

			auto& plan2 = plans2.emplace_back();
			assert(parts[2].size() == 7);
			assert(parts[2][0] == '#');

			plan2.dir = getDirFromValue(parts[2][6]);

			const std::string amountHex = parts[2].substr(1, 5);

			plan2.amount = std::stoul(amountHex, nullptr, 16);
		}

		const auto part1 = getCapacity(plans1);
		const auto part2 = getCapacity(plans2);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
