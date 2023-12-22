#include <2023/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <queue>

namespace TwentyTwentyThree {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Step Counter", 2023, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> Vector2Set;
	typedef std::unordered_map<Vector2i, long long, Vector2_Hash_Fxn<int>> Vector2Map;

	struct Garden
	{
		Vector2Set rocks;
		Vector2i start;
		Vector2i size;
	};

	std::pair<std::string, std::string> Day21Puzzle::fastSolve(int numStepsPart1, int numStepsPart2)
	{
		Garden garden;

		assert(m_InputLines.size() == m_InputLines[0].size());
		assert(m_InputLines.size() % 2 == 1);

		const int offsetSize = ((int)m_InputLines.size() - 1) / 2;

		garden.size = { offsetSize * 2 + 1, offsetSize * 2 + 1 };
		garden.start = { 0,0 };

		for (std::size_t y = 0; y < m_InputLines.size(); ++y)
		{
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x)
			{
				const int yRel = (int)y - offsetSize;
				const int xRel = (int)x - offsetSize;

				if (xRel == 0 && yRel == 0)
				{
					assert(m_InputLines[y][x] == 'S');
				}

				if (m_InputLines[y][x] == '#')
				{
					garden.rocks.insert(Vector2i(xRel, yRel));
				}
			}
		}

		long long part1 = 0;
		long long part2 = 0;

		const long long stepsOutsideStart = numStepsPart2 - (long long)offsetSize;
		const long long blocksOutsideStart = stepsOutsideStart / (long long)(garden.size.x);

		if (blocksOutsideStart != 202300)
		{
			std::cout << "The magic of this doesnt work for this input, part 2 unreliable" << std::endl;
		}

		long long centerDiamondOddStepNumberCount = 0;
		long long centerDiamondEvenStepNumberCount = 0;
		long long outsideCenterDiamondOddAndEvenStepNumberCount = 0;

		Vector2Set seen;
		std::queue<std::pair<Vector2i, int>> queue;
		queue.push({ garden.start , 0});

		while (!queue.empty())
		{
			const auto [coord, stepNumber] = queue.front(); queue.pop();

			if (seen.contains(coord)) { continue; }
			seen.insert(coord);

			if (stepNumber <= numStepsPart1)
			{
				if ((stepNumber & 1) == 0)
				{
					part1++;
				}
			}

			if (stepNumber <= offsetSize)
			{
				if ((stepNumber & 1) == (numStepsPart2 & 1))
				{ 
					centerDiamondOddStepNumberCount++;
				}
				else
				{
					centerDiamondEvenStepNumberCount++;
				}
			}
			else
			{
				outsideCenterDiamondOddAndEvenStepNumberCount++;
			}

			for (const auto& off : 
				{ 
					Vector2i(-1,0), 
					Vector2i(+1,0), 
					Vector2i(0,-1), 
					Vector2i(0,+1) 
				})
			{
				const auto next = coord + off;
				if (next.x >= -offsetSize &&
					next.x <= +offsetSize &&
					next.y >= -offsetSize &&
					next.y <= +offsetSize &&
					!garden.rocks.contains(next))
				{
					queue.push({ next , stepNumber + 1 });
				}
			}
		}

		assert(blocksOutsideStart % 2 == 0);

		// Repeating diamond shape, with odd/even step number repeating, 
		// and outer corners always repeat regardless of step number oddness
		// This sums up based on the magic number of steps so we can add up the 
		// number of instances of the pre-calculated steps-per-diamond we did above

		long long evenStepNumberCenterDiamondInstanceCount = (2 * (blocksOutsideStart / 2) + 1);
		evenStepNumberCenterDiamondInstanceCount *= evenStepNumberCenterDiamondInstanceCount;

		long long oddStepNumberCenterDiamondInstanceCount = (2 * ((blocksOutsideStart + 1) / 2));
		oddStepNumberCenterDiamondInstanceCount *= oddStepNumberCenterDiamondInstanceCount;

		long long evenAndOddStepNumberOuterDiamondInstanceCount = (evenStepNumberCenterDiamondInstanceCount + oddStepNumberCenterDiamondInstanceCount) / 2;

		part2 =
			evenStepNumberCenterDiamondInstanceCount * centerDiamondOddStepNumberCount
			+ oddStepNumberCenterDiamondInstanceCount * centerDiamondEvenStepNumberCount
			+ evenAndOddStepNumberOuterDiamondInstanceCount * outsideCenterDiamondOddAndEvenStepNumberCount;

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return fastSolve(64, 26501365);
	}
}
