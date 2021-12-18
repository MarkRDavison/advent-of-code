#include <2021/Day17Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <zeno-engine/Core/Rect.hpp>
#include <cassert>

namespace TwentyTwentyOne {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Trick Shot", 2021, 17) {
	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<IntegerType, bool> simulate(const ze::Vector2<IntegerType>& _velocity, const ze::Rect<IntegerType>& _target) {

		ze::Vector2<IntegerType> position;
		ze::Vector2<IntegerType> velocity(_velocity);
		auto target = _target; // TODO: When contains is a const method dont have this

		IntegerType maxY = 0;

		while (position.x < _target.left + _target.width && position.y >= _target.bot) {
			position.x += velocity.x;
			position.y += velocity.y;

			if (velocity.x > 0) {
				velocity.x--;
			} else if (velocity.x < 0) {
				velocity.x++;
			}
			velocity.y--;

			maxY = std::max(maxY, position.y);

			if (target.contains(position)) {
				return { maxY, true};
			}
		}


		return { 0, false };
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		const auto& splits = ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " =.,");
		constexpr IntegerType MULTIPLIER = 4;

		assert(splits.size() == 8);

		const IntegerType xStart = std::stol(splits[3]);
		const IntegerType xEnd = std::stol(splits[4]);
		const IntegerType yStart = std::stol(splits[6]);
		const IntegerType yEnd = std::stol(splits[7]);

		const ze::Rect<IntegerType> target({ xStart, yStart }, { xEnd - xStart + 1, yEnd - yStart + 1 });

		IntegerType part1 = 0;
		IntegerType part2 = 0;

		for (IntegerType velY = -target.height * MULTIPLIER;;++velY) {
			for (IntegerType velX = 1; velX <= xEnd + 1; ++velX) {
				const auto& [maxHeight, valid] = simulate({ velX, velY }, target);

				if (valid) {
					part1 = std::max(part1, maxHeight);
					part2++;
				}
			}

			if (velY > target.height * MULTIPLIER) {
				break;
			}
		}


		return { std::to_string(part1), std::to_string(part2) };
	}
}
