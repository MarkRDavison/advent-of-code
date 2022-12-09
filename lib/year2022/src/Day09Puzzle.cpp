#include <2022/Day09Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Orientation.hpp>
#include <unordered_map>
#include <cassert>

namespace std {
	template<>
	struct hash<ze::Vector2i> {
		size_t operator()(const ze::Vector2i& obj) const {
			return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y);
		}
	};
}

namespace TwentyTwentyTwo {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Rope Bridge", 2022, 9) {
	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void print(const std::vector<ze::Vector2i>& _knots, const ze::Vector2i& _min, const ze::Vector2i& _max)
	{
		const auto height = _max.y - _min.y + 1;
		const auto width = _max.x - _min.x + 1;

		std::vector<std::string> map;
		for (int y = 0; y < height; ++y)
		{
			map.push_back(std::string(width, '.'));
		}

		map[0][0] = 's';

		const int numKnots = (int)_knots.size();
		for (int i = numKnots - 1; i >= 0; --i)
		{
			const auto& knot = _knots[(std::size_t)i];
			if (i == 0)
			{
				map[knot.y][knot.x] = 'H';
			}
			else {
				map[knot.y][knot.x] = (char)(i + '0');
			}
		}

		std::reverse(map.begin(), map.end());
		std::cout << "==========" << std::endl;
		for (auto& r : map)
		{
			std::cout << r << std::endl;
		}

	}

	std::size_t solve(const std::vector<std::string>& _input, int _length)
	{
		ze::Vector2i min{0, 0};
		ze::Vector2i max{5, 5};

		std::vector<ze::Vector2i> knotLocations(_length);

		std::unordered_map < ze::Vector2i, int> tailVisits;
		tailVisits[knotLocations.back()]++;


		for (const auto& l : _input)
		{
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, " ");

			const int amount = std::stoi(p[1]);
			core::Orientation dir;
			if (p[0] == "R")
			{
				dir = core::Orientation::Right;
			}
			else if (p[0] == "L")
			{
				dir = core::Orientation::Left;
			}
			else if (p[0] == "U")
			{
				dir = core::Orientation::Up;
			}
			else if (p[0] == "D")
			{
				dir = core::Orientation::Down;
			}
			else
			{
				assert(false);
			}

			for (int i = 0; i < amount; ++i) {
				auto& headLocation = knotLocations.front();
				headLocation += core::OrientationHelper::toDirection(dir);

				print(knotLocations, min, max);
				for (std::size_t knotIndex = 1; knotIndex < knotLocations.size() - 1; ++knotIndex)
				{
					const auto previousCurrentLocation = knotLocations[knotIndex];
					auto& currentLocation = knotLocations[knotIndex];
					auto& followerLocation = knotLocations[knotIndex + 1];

					currentLocation += core::OrientationHelper::toDirection(dir);
					min.x = std::min(min.x, currentLocation.x);
					max.x = std::max(max.x, currentLocation.x);
					min.x = std::min(min.y, currentLocation.y);
					max.x = std::max(max.y, currentLocation.y);

					const auto difference = ze::Vector2i{
						std::abs(currentLocation.x - followerLocation.x),
						std::abs(currentLocation.y - followerLocation.y)
					};

					if (difference.x <= 1 && difference.y <= 1) { break; }
					if (difference.x > 1 && currentLocation.x != followerLocation.x && currentLocation.y == followerLocation.y)
					{
						followerLocation += core::OrientationHelper::toDirection(dir);
					}
					else if (difference.y > 1 && currentLocation.y != followerLocation.y && currentLocation.x == followerLocation.x)
					{
						followerLocation += core::OrientationHelper::toDirection(dir);
					}
					else
					{
						followerLocation = previousCurrentLocation;
					}

					if (knotIndex == knotLocations.size() - 2)
					{
						tailVisits[followerLocation]++;
					}
				}
			}
		}

		return tailVisits.size();
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {

		

		return {
			"",//std::to_string(solve(m_InputLines, 2)),
			std::to_string(solve(m_InputLines, 10))
		};
	}
}
