#include <2018/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>
#include <numeric>

namespace TwentyEighteen {

	struct Point
	{
		Vector2<long long> position;
		Vector2<long long> velocity;
	};

	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("The Stars Align", 2018, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	core::Region<char> mapFromPoints(const std::vector<Point>& points, Vector2<long long>& start)
	{
		core::Region<char> map;
		start = { std::numeric_limits<long long>::max(), std::numeric_limits<long long>::max() };

		for (const auto& p : points)
		{
			map.getCell((int)p.position.x, (int)p.position.y) = '#';
			start.x = std::min(start.x, p.position.x);
			start.y = std::min(start.y, p.position.y);
		}

		return map;
	}

	void dumpPointMap(core::Region<char>& map, const Vector2<long long>& start)
	{
		for (int y = (int)start.y; y <= map.maxY; ++y)
		{
			for (int x = (int)start.x; x <= map.maxX; ++x)
			{
				std::cout << (map.getCell(x, y) == '#' ? '#' : ' ');
			}
			std::cout << std::endl;
		}
	}

	void processTime(std::vector<Point>& points)
	{
		for (auto& p : points)
		{
			p.position += p.velocity;
		}
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {


		std::vector<Point> points;

		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, "<,>");

			auto& p = points.emplace_back();
			p.position.x = std::stoi(parts[1]);
			p.position.y = std::stoi(parts[2]);
			p.velocity.x = std::stoi(parts[4]);
			p.velocity.y = std::stoi(parts[5]);
		}

		Vector2<long long> start;
		auto map = mapFromPoints(points, start);

		int time = 1;

		Vector2<long long> size = { map.maxY - map.minY, map.maxX - map.minX };

		while (true)
		{
			processTime(points);

			Vector2<long long> newstart;
			auto newmap = mapFromPoints(points, newstart);

			Vector2<long long> newSize = { newmap.maxY - newmap.minY, newmap.maxX - newmap.minX };

			if (newSize.x * newSize.y < size.x * size.y)
			{
				size = newSize;
				map = newmap;
				start = newstart;
			}
			else
			{
				dumpPointMap(map, start);
				break;
			}
			time++;
		}

		return { "See above", std::to_string(time -1)};
	}
}
