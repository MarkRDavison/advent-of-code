#include <2023/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <numeric>
#include <cassert>

#define ROUND 'O'
#define CUBE '#'
#define EMPTY '.'

namespace TwentyTwentyThree {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Parabolic Reflector Dish", 2023, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef std::vector<std::string> Platform;

	void runCycle(Platform& platform)
	{
		// Tilt NORTH
		bool changeMade = true;
		while (changeMade)
		{
			changeMade = false;

			for (std::size_t x = 0; x < platform[0].size(); ++x)
			{
				for (std::size_t y = 0; y < platform.size() - 1; ++y)
				{
					auto& curr = platform[y][x];
					auto& above = platform[y + 1][x];
					if (curr == EMPTY && above == ROUND)
					{
						std::swap(curr, above);
						changeMade = true;
					}
				}
			}
		}

		// Tilt WEST
		changeMade = true;
		while (changeMade)
		{
			changeMade = false;

			for (std::size_t y = 0; y < platform.size(); ++y)
			{
				for (std::size_t x = 0; x < platform[0].size() - 1; ++x)
				{
					auto& curr = platform[y][x];
					auto& above = platform[y][x + 1];
					if (curr == EMPTY && above == ROUND)
					{
						std::swap(curr, above);
						changeMade = true;
					}
				}
			}
		}

		// Tilt SOUTH
		changeMade = true;
		while (changeMade)
		{
			changeMade = false;

			for (std::size_t x = 0; x < platform[0].size(); ++x)
			{
				for (std::size_t y = platform.size() - 1; y != 0; --y)
				{
					auto& curr = platform[y][x];
					auto& above = platform[y - 1][x];
					if (curr == EMPTY && above == ROUND)
					{
						std::swap(curr, above);
						changeMade = true;
					}
				}
			}
		}

		// Tilt EAST
		changeMade = true;
		while (changeMade)
		{
			changeMade = false;

			for (std::size_t y = 0; y < platform.size(); ++y)
			{
				for (std::size_t x = platform[0].size() - 1; x != 0 ; --x)
				{
					auto& curr = platform[y][x];
					auto& above = platform[y][x - 1];
					if (curr == EMPTY && above == ROUND)
					{
						std::swap(curr, above);
						changeMade = true;
					}
				}
			}
		}
	}

	std::string join(const Platform& platform)
	{
		return std::accumulate(
			std::next(platform.begin()),
			platform.end(),
			platform[0],
			[](const std::string& lhs, const std::string& rhs)
			{
				return lhs + rhs;
			}
		);
	}

	long long getTotalLoad(const Platform& platform)
	{
		long long totalLoad = 0;

		for (std::size_t i = 0; i < platform.size(); ++i)
		{
			for (std::size_t x = 0; x < platform[0].size(); ++x)
			{
				if (platform[i][x] == ROUND)
				{
					totalLoad += platform.size() - i;
				}
			}
		}

		return totalLoad;
	}

	long long solvePart2(Platform platform)
	{
		std::unordered_map<std::string, std::size_t> platformToIndex;
		std::unordered_map<std::size_t, long long> indexToLoad;

		std::size_t i = 0;

		std::size_t periodStart = 0;
		std::size_t periodEnd = 0;

		constexpr std::size_t targetI = 1'000'000'000;

		while (true)
		{
			runCycle(platform); ++i;

			const auto key = join(platform);

			if (platformToIndex.contains(key))
			{
				periodStart = platformToIndex.at(key);
				periodEnd = i;
				break;
			}
			else
			{
				platformToIndex[key] = i;
				indexToLoad[i] = getTotalLoad(platform);
			}
		}

		const auto period = periodEnd - periodStart;
		const auto cycle = targetI - periodStart;

		assert(period > 0);
		assert(cycle > 0);

		const auto sameLoadIndex = periodStart + cycle % period;

		assert(indexToLoad.contains(sameLoadIndex));

		return indexToLoad[sameLoadIndex];
	}

	long long solvePart1(Platform platform)
	{
		std::size_t i = 1;

		bool changeMade = true;
		while (changeMade)
		{
			changeMade = false;

			for (std::size_t x = 0; x < platform[0].size(); ++x)
			{
				for (std::size_t y = 0; y < platform.size() - 1; ++y)
				{
					auto& curr = platform[y][x];
					auto& above = platform[y + 1][x];
					if (curr == EMPTY && above == ROUND)
					{
						std::swap(curr, above);
						changeMade = true;
					}
				}
			}

			++i;
		}


		return getTotalLoad(platform);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		const auto part1 = solvePart1(m_InputLines);
		const auto part2 = solvePart2(m_InputLines);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
