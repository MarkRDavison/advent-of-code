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

		map[-_min.y][-_min.x] = 's';

		const int numKnots = (int)_knots.size();
		for (int i = numKnots - 1; i >= 0; --i)
		{
			const auto& knot = _knots[(std::size_t)i];
			if (i == 0)
			{
				map[-_min.y + knot.y][-_min.x + knot.x] = 'H';
			}
			else {
				map[-_min.y + knot.y][-_min.x + knot.x] = (char)(i + '0');
			}
		}

		std::reverse(map.begin(), map.end());
		std::cout << "==========" << std::endl;
		for (auto& r : map)
		{
			std::cout << r << std::endl;
		}

	}

	std::size_t solve(const std::vector<std::string>& _input, int _length, bool _verbose)
	{
		ze::Vector2i min{-10, -10};
		ze::Vector2i max{+10, +10};

		std::vector<ze::Vector2i> knotLocations(_length);

		std::unordered_map < ze::Vector2i, int> tailVisits;
		tailVisits[knotLocations.back()]++;


		for (const auto& l : _input)
		{
			if (_verbose)
			{
				std::cout << "Before: " << l << std::endl;
				print(knotLocations, min, max);
			}

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
				const auto previousCurrentLocation = knotLocations.front();
				auto& headLocation = knotLocations.front();
				headLocation += core::OrientationHelper::toDirection(dir);

				min.x = std::min(min.x, headLocation.x);
				min.y = std::min(min.y, headLocation.y);
				max.x = std::max(max.x, headLocation.x);
				max.y = std::max(max.y, headLocation.y);

				for (std::size_t knotIndex = 1; knotIndex < knotLocations.size(); ++knotIndex)
				{
					const auto aheadKnot = knotLocations[knotIndex - 1];
					auto& currentKnot = knotLocations[knotIndex];

					const auto difference = ze::Vector2i{
						std::abs(aheadKnot.x - currentKnot.x),
						std::abs(aheadKnot.y - currentKnot.y)
					};
					auto offset = ze::Vector2i{
						aheadKnot.x - currentKnot.x,
						aheadKnot.y - currentKnot.y
					};

					if (difference.x <= 1 && difference.y <= 1) { break; }

					if (difference.x > 1 && aheadKnot.x != currentKnot.x && aheadKnot.y == currentKnot.y)
					{
						if (difference.x == 2)
						{
							offset.x /= 2;
						}
						if (difference.y == 2)
						{
							offset.y /= 2;
						}
						currentKnot += offset;
					}
					else if (difference.y > 1 && aheadKnot.y != currentKnot.y && aheadKnot.x == currentKnot.x)
					{
						if (difference.x == 2)
						{
							offset.x /= 2;
						}
						if (difference.y == 2)
						{
							offset.y /= 2;
						}
						currentKnot += offset;
					}
					else 
					{
						assert(difference.x == 1 || difference.x == 2);
						assert(difference.y == 1 || difference.y == 2);	

						if (difference.x == 2)
						{
							offset.x /= 2;
						}
						if (difference.y == 2)
						{
							offset.y /= 2;
						}
						currentKnot += offset;
					}

					if (knotIndex == knotLocations.size() - 1)
					{
						tailVisits[currentKnot]++;
					}

					min.x = std::min(min.x, currentKnot.x);
					min.y = std::min(min.y, currentKnot.y);
					max.x = std::max(max.x, currentKnot.x);
					max.y = std::max(max.y, currentKnot.y);
				}
				if (_verbose)
				{
					print(knotLocations, min, max);
				}
			}
		}
		if (_verbose)
		{
			print(knotLocations, min, max);
		}

		return tailVisits.size();
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		
		return {
			std::to_string(solve(m_InputLines, 2, getVerbose())),
			std::to_string(solve(m_InputLines, 10, getVerbose()))
		};
	}
}
