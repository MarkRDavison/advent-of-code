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

	typedef std::tuple<long long, long long, long long, long long, long long, long long> Key6LongLong;
	typedef std::unordered_map<Key6LongLong, long long> Key6LongLongMap;

	struct Bounds3D
	{
		Vector3<long long> min;
		Vector3<long long> max;

		bool isUnit() const { return min == max; }

		Bounds3D increase(long long i) const
		{
			return Bounds3D{
				.min {
					min.x - i,
					min.y - i,
					min.z - i
				},
				.max {
					max.x + i,
					max.y + i,
					max.z + i
				}
			};
		}

		Key6LongLong createKey() const
		{
			return { min.x, min.y, min.z, max.x, max.y, max.z };
		}

		bool contains(const Vector3<long long>& point) const
		{
			return
				min.x <= point.x && point.x <= max.x &&
				min.y <= point.y && point.y <= max.y &&
				min.z <= point.z && point.z <= max.z;
		}

		void print() const
		{
			std::cout
				<< min.x << "," << min.y << "," << min.z << " to "
				<< max.x << "," << max.y << "," << max.z << std::endl;
		}
	};

	std::vector<Bounds3D> splitToOctree(const Bounds3D& bounds)
	{
		std::vector<Bounds3D> subBounds;

		if (bounds.isUnit())
		{
			return subBounds;
		}

		const auto xDim = bounds.max.x - bounds.min.x + 1;
		const auto yDim = bounds.max.y - bounds.min.y + 1;
		const auto zDim = bounds.max.z - bounds.min.z + 1;

		const auto xMinDim = bounds.min.x + xDim / 2;
		const auto xMaxMinDim = xMinDim + 1;
		const auto yMinDim = bounds.min.y + yDim / 2;
		const auto yMaxMinDim = yMinDim + 1;
		const auto zMinDim = bounds.min.z + zDim / 2;
		const auto zMaxMinDim = zMinDim + 1;


		subBounds.push_back(Bounds3D
			{
				.min = { bounds.min.x, bounds.min.y, bounds.min.z },
				.max = { xMinDim, yMinDim, zMinDim }
			});


		subBounds.push_back(Bounds3D
			{
				.min = { xMaxMinDim, bounds.min.y, bounds.min.z },
				.max = { bounds.max.x, yMinDim, zMinDim }
			});

		subBounds.push_back(Bounds3D
			{
				.min = { bounds.min.x, yMaxMinDim, bounds.min.z },
				.max = { xMinDim, bounds.max.y, zMinDim }
			});

		subBounds.push_back(Bounds3D
			{
				.min = { bounds.min.x, bounds.min.y, zMaxMinDim },
				.max = { xMinDim, yMinDim, bounds.max.z }
			});


		subBounds.push_back(Bounds3D
			{
				.min = { bounds.min.x, yMaxMinDim, zMaxMinDim },
				.max = { xMinDim, bounds.max.y, bounds.max.z }
			});

		subBounds.push_back(Bounds3D
			{
				.min = { xMaxMinDim, bounds.min.y, zMaxMinDim },
				.max = { bounds.max.x, yMinDim, bounds.max.z }
			});

		subBounds.push_back(Bounds3D
			{
				.min = { xMaxMinDim, yMaxMinDim, bounds.min.z },
				.max = { bounds.max.x, bounds.max.y, zMinDim }
			});


		subBounds.push_back(Bounds3D
			{
				.min = { xMaxMinDim, yMaxMinDim, zMaxMinDim },
				.max = { bounds.max.x, bounds.max.y, bounds.max.z }
			});

		return subBounds;
	}

	bool nanobotInRangeOfCube(const Bounds3D& bounds, const Nanobot& nanobot)
	{
		auto r2 = nanobot.radius * nanobot.radius;
		long long dmin = 0;

		if (nanobot.position.x < bounds.min.x)
		{
			dmin += (long long)(std::sqrt(nanobot.position.x - bounds.min.x));
		}
		else if (nanobot.position.x > bounds.max.x)
		{
			dmin += (long long)(std::sqrt(nanobot.position.x - bounds.max.x));
		}

		if (nanobot.position.y < bounds.min.y)
		{
			dmin += (long long)(std::sqrt(nanobot.position.y - bounds.min.y));
		}
		else if (nanobot.position.y > bounds.max.y)
		{
			dmin += (long long)(std::sqrt(nanobot.position.y - bounds.max.y));
		}
		
		if (nanobot.position.z < bounds.min.z)
		{
			dmin += (long long)(std::sqrt(nanobot.position.z - bounds.min.z));
		}
		else if (nanobot.position.z > bounds.max.z)
		{
			dmin += (long long)(std::sqrt(nanobot.position.z - bounds.max.z));
		}

		return dmin <= r2;
	}

	long long manhatten(const Vector3<long long>& lhs, const Vector3<long long>& rhs)
	{
		return std::abs(lhs.x - rhs.x) + std::abs(lhs.y - rhs.y) + std::abs(lhs.z - rhs.z);
	}

	long long getPossibleIntersections(const Bounds3D& bounds, const std::vector<Nanobot>& nanobots)
	{
		long long possibleIntersections = 0;

		for (const auto& nb : nanobots)
		{
			if (bounds.increase(nb.radius).contains(nb.position))
			{
				possibleIntersections++;
			}
		}

		return possibleIntersections;
	}

	long long getNanobotsInRange(const std::vector<Nanobot>& nanobots, const Vector3<long long>& pos)
	{
		long long inRange = 0;

		for (const auto& nb : nanobots)
		{
			if (manhatten(pos, nb.position) <= nb.radius)
			{
				inRange++;
			}
		}

		return inRange;
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

		long long maxInRange = 0;
		Vector3<long long> loc;

		for (const auto& nb : nanobots)
		{
			bounds.min.x = std::min(bounds.min.x, nb.position.x);
			bounds.min.y = std::min(bounds.min.y, nb.position.y);
			bounds.min.z = std::min(bounds.min.z, nb.position.z);

			bounds.max.x = std::max(bounds.max.x, nb.position.x);
			bounds.max.y = std::max(bounds.max.y, nb.position.y);
			bounds.max.z = std::max(bounds.max.z, nb.position.z);
		}

		long long bestInRange=-1;
		for (const auto& nb2 : nanobots)
		{
			if (manhatten(nb2.position, nanobots[0].position) <= nanobots[0].radius)
			{
				bestInRange++;
			}
		}

		long long scanDelta = std::min(1'000'000ll, bounds.max.x - bounds.min.x);
		const long long scanWaves = 6;

		Vector3<long long> bestLoc = nanobots[0].position;

		while (scanDelta > 0)
		{
			std::cout << "Scanning with delta of " << scanDelta <<", best: " << bestLoc.x << "," << bestLoc.y << "," << bestLoc.z << std::endl;

			bool breakOut = false;
			
			for (long long waveI = 0; waveI < scanWaves; ++waveI)
			{
				if (breakOut) { break; }
				const auto xOff = (waveI - scanWaves / 2) * scanDelta;
				for (long long waveJ = 0; waveJ < scanWaves; ++waveJ)
				{
					if (breakOut) { break; }
					const auto yOff = (waveJ - scanWaves / 2) * scanDelta;
					for (long long waveK = 0; waveK < scanWaves; ++waveK)
					{
						const auto zOff = (waveK - scanWaves / 2) * scanDelta;

						const auto scanLoc = bestLoc + Vector3<long long>{xOff, yOff, zOff};

						const auto inRange = getNanobotsInRange(nanobots, scanLoc);

						if (inRange > bestInRange || (scanDelta < 2 && inRange >= bestInRange))
						{
							bool newBest = true;
							if (inRange == bestInRange)
							{
								const auto existingManhatten = std::abs(bestLoc.x) + std::abs(bestLoc.y) + std::abs(bestLoc.z);
								const auto newManhatten = std::abs(scanLoc.x) + std::abs(scanLoc.y) + std::abs(scanLoc.z);

								if (newManhatten > existingManhatten)
								{
									newBest = false;
								}
							}

							if (newBest)
							{
								bestInRange = inRange;
								bestLoc = scanLoc;
								std::cout << "new best at " << scanLoc.x << "," << scanLoc.y << "," << scanLoc.z << ", in range: " << inRange << std::endl;

								if (scanDelta > 1)
								{
									breakOut = true;
									break;
								}
							}
						}
					}
				}
			}
			if (scanDelta == 1)
			{
				break;
			}
			scanDelta /= 2;
		}

		return std::abs(bestLoc.x) + std::abs(bestLoc.y) + std::abs(bestLoc.z);
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

		std::cout << "Part 2 : 134049259 is too high" << std::endl;
		std::cout << "Part 2 : " << part2 << std::endl;
		std::cout << "Part 2 : 89915526 maybe at (15972003, 44657553, 29285970)" << std::endl;
		std::cout << "Part 2 : 88664811 is too low" << std::endl;
		std::cout << "Part 2 : 99467293 is wrong" << std::endl;		

		return { std::to_string(part1), std::to_string(part2) };
	}
}
