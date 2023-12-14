#include <2018/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector3.hpp>
#include <Core/Pathfinding.hpp>
#include <algorithm>
#include <numeric>

namespace TwentyEighteen {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Experimental Emergency Teleportation", 2018, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Nanobot
	{
		Vector3<long long> position;
		long long radius;
	};

	struct Bounds3D
	{
		Vector3<long long> min;
		Vector3<long long> max;
	};

	long long manhatten(const Vector3<long long>& lhs, const Vector3<long long>& rhs)
	{
		return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y) + std::abs(lhs.z - rhs.z);
	}

	long long solvePart2(const std::vector<Nanobot>& nanobots)
	{
		Bounds3D bounds{
			.min{
				std::numeric_limits<long long>::max(),
				std::numeric_limits<long long>::max(),
				std::numeric_limits<long long>::max()
			},
			.max{
				std::numeric_limits<long long>::min(),
				std::numeric_limits<long long>::min(),
				std::numeric_limits<long long>::min()
			}
		};

		for (const auto& nb : nanobots)
		{
			bounds.min.x = std::min(bounds.min.x, nb.position.x);
			bounds.min.y = std::min(bounds.min.y, nb.position.y);
			bounds.min.z = std::min(bounds.min.z, nb.position.z);

			bounds.max.x = std::max(bounds.max.x, nb.position.x);
			bounds.max.y = std::max(bounds.max.y, nb.position.y);
			bounds.max.z = std::max(bounds.max.z, nb.position.z);
		}

		long long stepSize = bounds.max.x - bounds.min.x;

		Vector3<long long> best;

		while (stepSize > 0)
		{
			long long maxCount = 0;

			for (long long x = bounds.min.x; x <= bounds.max.x; x += stepSize)
			{
				for (long long y = bounds.min.y; y <= bounds.max.y; y += stepSize)
				{
					for (long long z = bounds.min.z; z <= bounds.max.z; z += stepSize)
					{
						long long count = 0;

						for (const auto& nb : nanobots)
						{
							const auto distance = manhatten(Vector3<long long>{x, y, z}, nb.position);

							if (distance - nb.radius < stepSize)
							{
								count++;
							}
						}

						if (maxCount < count)
						{
							maxCount = count;
							best = { x, y, z };
						}
						else if (maxCount == count)
						{
							if (manhatten({}, { x, y, z }) < manhatten({}, best))
							{
								best = { x,y,z };
							}
						}
					}
				}
			}

			bounds.min.x = best.x - stepSize;
			bounds.max.x = best.x + stepSize;
			bounds.min.y = best.y - stepSize;
			bounds.max.y = best.y + stepSize;
			bounds.min.z = best.z - stepSize;
			bounds.max.z = best.z + stepSize;

			stepSize /= 2;
		}

		return manhatten({}, best);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		std::vector<Nanobot> nanobots;

		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, "<,>=");
			auto& nb = nanobots.emplace_back();

			nb.position = {
				std::stoll(parts[1]),
				std::stoll(parts[2]),
				std::stoll(parts[3])
			};
			nb.radius = std::stoll(parts[5]);
		}

		std::sort(nanobots.begin(), nanobots.end(),
			[](const Nanobot& lhs, const Nanobot& rhs) -> bool
			{
				return lhs.radius > rhs.radius;
			});

		const auto& part1Nanobot = nanobots[0];

		long long part1 = 0;

		for (const auto& nb : nanobots)
		{
			const auto manhatten = 
				std::abs(part1Nanobot.position.x - nb.position.x) +
				std::abs(part1Nanobot.position.y - nb.position.y) +
				std::abs(part1Nanobot.position.z - nb.position.z);

			if (manhatten <= part1Nanobot.radius)
			{
				part1++;
			}
		}

		const auto part2 = solvePart2(nanobots);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
