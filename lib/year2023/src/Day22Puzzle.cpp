#include <2023/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector3.hpp>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cassert>

namespace TwentyTwentyThree {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Sand Slabs", 2023, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Snapshot
	{
		int id;
		Vector3i left;
		Vector3i right;
	};
	typedef std::vector<std::vector<std::vector<int>>> Cuboid;

	struct SettledCuboidInfo
	{
		Cuboid cuboid;
		int moved{ 0 };
		std::vector<Snapshot> snapshots;
	};

	SettledCuboidInfo settle(
		Vector2i min,
		Vector2i max,
		int maxZ,
		const std::vector<Snapshot>& snapshots, 
		int excludeId)
	{
		SettledCuboidInfo info{};

		info.cuboid.resize(maxZ + 1);

		for (std::size_t z = 0; z <= maxZ; ++z)
		{
			info.cuboid.at(z).resize(max.y + 1);
			for (auto& row : info.cuboid.at(z))
			{
				row.resize(max.x + 1);
			}
		}


		for (const auto& s : snapshots)
		{
			if (s.id == excludeId) { continue; }
			int startingZ = std::min(s.left.z, s.right.z);
			int zToUse = startingZ;
			for (int z = startingZ; z > 0; --z)
			{
				bool canShift = true;
				for (int y = s.left.y; y <= s.right.y; ++y)
				{
					for (int x = s.left.x; x <= s.right.x; ++x)
					{
						if (info.cuboid.at(z).at(y).at(x) != 0)
						{
							canShift = false;
							break;
						}
					}
					if (!canShift) { break; }
				}
				if (canShift)
				{
					zToUse = z;
				}
				else
				{
					break;
				}
			}

			if (zToUse != startingZ)
			{
				info.moved++;
			}

			const int height = s.right.z - s.left.z + 1;

			for (int y = s.left.y; y <= s.right.y; ++y)
			{
				for (int x = s.left.x; x <= s.right.x; ++x)
				{
					for (int z = zToUse; z < zToUse + height; ++z)
					{
						info.cuboid[z][y][x] = s.id;
					}
				}
			}

			auto& settled = info.snapshots.emplace_back();
			settled.id = s.id;
			settled.left = { s.left.x, s.left.y, zToUse };
			settled.right = { s.right.x, s.right.y, zToUse + height - 1 };
		}

		return info;
	}

	long long solvePart1(const SettledCuboidInfo& initialSettleInfo)
	{
		long long part1 = 0;
		for (const auto& disintegratedSnapshot : initialSettleInfo.snapshots)
		{
			bool valid = true;

			for (const auto& s : initialSettleInfo.snapshots)
			{
				if (s.id == disintegratedSnapshot.id) { continue; }

				int bottomZ = std::min(s.left.z, s.right.z);

				std::unordered_set<int> restingIds;

				for (int y = s.left.y; y <= s.right.y; ++y)
				{
					for (int x = s.left.x; x <= s.right.x; ++x)
					{
						const auto beneath = initialSettleInfo.cuboid.at(bottomZ - 1).at(y).at(x);
						restingIds.insert(beneath);
					}
				}

				restingIds.erase(0);

				if (restingIds.size() == 1 && restingIds.contains(disintegratedSnapshot.id))
				{
					valid = false;
				}
			}
			if (valid)
			{
				part1++;
			}
		}

		return part1;
	}

	long long solvePart2(
		const SettledCuboidInfo& initialSettleInfo,
		Vector2i min,
		Vector2i max,
		int maxZ
	)
	{
		long long part2 = 0;
		int i = 0;
		for (const auto& snapshot : initialSettleInfo.snapshots)
		{
			const auto secondarySettleInfo = settle(min, max, maxZ, initialSettleInfo.snapshots, snapshot.id);

			part2 += secondarySettleInfo.moved;

			std::cout << ++i << " / " << initialSettleInfo.snapshots.size() << std::endl;
		}
		return part2;
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		std::vector<Snapshot> snapshots;

		Vector2i min{ std::numeric_limits<int>::max(), std::numeric_limits<int>::max() };
		Vector2i max{ std::numeric_limits<int>::min(), std::numeric_limits<int>::min() };

		int maxZ = 0;
		int id = 1;
		for (const auto& l : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(l, ",~");
			assert(parts.size() == 6);

			auto& s = snapshots.emplace_back();

			s.id = id++;

			s.left.x = std::stoi(parts[0]);
			s.left.y = std::stoi(parts[1]);
			s.left.z = std::stoi(parts[2]);
			s.right.x = std::stoi(parts[3]);
			s.right.y = std::stoi(parts[4]);
			s.right.z = std::stoi(parts[5]);

			min.x = std::min(min.x, std::min(s.left.x, s.right.x));
			min.y = std::min(min.y, std::min(s.left.y, s.right.y));
			max.x = std::max(max.x, std::max(s.left.x, s.right.x));
			max.y = std::max(max.y, std::max(s.left.y, s.right.y));
			maxZ = std::max(maxZ, std::max(s.left.z, s.right.z));
		}

		std::sort(
			snapshots.begin(), 
			snapshots.end(), 
			[](const Snapshot& lhs, const Snapshot& rhs) -> bool
			{
				return std::min(lhs.left.z, lhs.right.z) < std::min(rhs.left.z, rhs.right.z);
			});

		assert(0 == min.x);
		assert(0 == min.y);

		const auto initialSettleInfo = settle(min, max, maxZ, snapshots, -1);

		std::cout << "Solving part 1..." << std::endl;
		long long part1 = solvePart1(initialSettleInfo);
		std::cout << "Solving part 2..." << std::endl;
		long long part2 = solvePart2(initialSettleInfo, min, max, maxZ);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
