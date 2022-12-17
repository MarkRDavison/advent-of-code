#include <2022/Day17Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <Core/Region.hpp>
#include <zeno-engine/Core/Vector2.hpp>

#define WIDTH 7

namespace TwentyTwentyTwo {

	template<typename T>
	struct vector2_hash_fxn_TODO_CORE_ME3 {
		std::size_t operator()(const ze::Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Pyroclastic Flow", 2022, 17) {
	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	using BigNumber = long long;

	struct Rock {
		int width{ 0 };
		int height{ 0 };

		std::vector<ze::Vector2<BigNumber>> shape;
	};

	struct ChamberCell {
		char c{ '.' };
	};

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		
		std::vector<Rock> rocks {
			Rock{.width = 4, .height = 1, .shape =
			{
				// "####"
				{0,0},{1,0},{2,0},{3,0}
			}},
			Rock{.width = 3, .height = 3, .shape =
			{
				// ".#.", "###", ".#."
				{1,0},{0,1},{1,1},{2,1},{1,2}
			}},
			Rock{.width = 3, .height = 3, .shape =
			{
				// "..#", "..#", "###"
				{0,0},{1,0},{2,0},{2,1},{2,2}
			}},
			Rock{.width = 1, .height = 4, .shape =
			{
				// "#", "#", "#", "#"
				{0,0},{0,1},{0,2},{0,3}
			}},
			Rock{.width = 2, .height = 2, .shape =
			{
				// "##", "##"
				{0,0},{1,0},{0,1},{1,1}
			}},
		};

		using Grid = std::unordered_set<ze::Vector2<BigNumber>, vector2_hash_fxn_TODO_CORE_ME3<BigNumber>>;
		Grid grid;

		std::size_t ri = 0;
		std::size_t ji = 0;
		BigNumber highestRockPosition = -1;

		BigNumber part1 = 0;
		BigNumber rowMaximums[WIDTH];
		for (BigNumber i = 0; i < WIDTH; ++i)
		{
			rowMaximums[i] = -1;
		}

		std::unordered_map<std::string, BigNumber> hashes;

		BigNumber prev = -1;
		BigNumber prevHeight = -1;
		BigNumber cycleStart = -1;
		BigNumber fastModeTowerHeight = 0;

		BigNumber rockMovementIndex = 0;

		const BigNumber ROCKS = 1000000000000;

		struct CycleState {
			BigNumber rockNumber;
			BigNumber highestRockPosition;
			BigNumber rockMovementIndex;
		};
		std::unordered_map<std::string, CycleState> hashedCycleStateMap{};

		for (BigNumber rockNumber = 0; rockNumber < ROCKS; ++rockNumber)
		{
			if (rockNumber == 2022)
			{
				part1 = highestRockPosition + 1;
			}
			const auto& rock = rocks[ri];

			ze::Vector2<BigNumber> rockPosition = { 2, 4 + highestRockPosition };

			while (true)
			{
				const auto jetOffset = m_InputLines[0][ji] == '<' ? -1 : +1;
				ji = (ji + 1) % m_InputLines[0].size();

				// Apply jet
				bool valid = true;
				for (const auto& rockCell : rock.shape)
				{
					const auto globalRockCellPosition = rockCell + rockPosition + ze::Vector2<BigNumber>(jetOffset, 0);

					if (globalRockCellPosition.x < 0 || 
						globalRockCellPosition.x >= WIDTH || 
						grid.contains(globalRockCellPosition))
					{
						valid = false;
						break;
					}
				}
				if (valid)
				{
					rockPosition += ze::Vector2<BigNumber>(jetOffset, 0);
				}
				else
				{
					// NOOP
				}

				// Apply drop
				valid = true;
				Grid temp;
				for (const auto& rockCell : rock.shape)
				{
					const auto globalRockCellPosition = rockCell + rockPosition + ze::Vector2<BigNumber>(0, -1);
					temp.insert(globalRockCellPosition - ze::Vector2<BigNumber>(0, -1));
					if (globalRockCellPosition.x < 0 ||
						globalRockCellPosition.x >= WIDTH ||
						globalRockCellPosition.y < 0 ||
						grid.contains(globalRockCellPosition))
					{
						valid = false;
					}
				}
				if (valid)
				{
					rockPosition += ze::Vector2<BigNumber>(0, -1);
				}
				else
				{
					for (const auto& c : temp)
					{
						grid.insert(c);
						highestRockPosition = std::max(highestRockPosition, c.y);
						rowMaximums[c.x] = std::max(rowMaximums[c.x], c.y);
					}
				}

				rockMovementIndex++;

				if ( part1 > 0 && rockMovementIndex % m_InputLines[0].size() == 0)
				{
					std::stringstream hash{};
					hash << rockPosition.x << ':' << rockPosition.y - highestRockPosition
						<< ':' << ri;

					for (auto i = 0; i < WIDTH; ++i)
					{
						hash << ":" << highestRockPosition - rowMaximums[i];
					}


					if (!hashedCycleStateMap.contains(hash.str())) 
					{
						hashedCycleStateMap[hash.str()] = CycleState{ 
							.rockNumber = rockNumber,
							.highestRockPosition = highestRockPosition,
							.rockMovementIndex = rockMovementIndex
						};
					}
					else
					{
						const auto& prev = hashedCycleStateMap[hash.str()];

						CycleState loopSize = { 
							.rockNumber = rockNumber - prev.rockNumber,
							.highestRockPosition = highestRockPosition - prev.highestRockPosition,
							.rockMovementIndex  = rockMovementIndex - prev.rockMovementIndex
						};

						const auto cyclesThatFit = (ROCKS - rockNumber - 1) / loopSize.rockNumber;

						rockNumber += loopSize.rockNumber * cyclesThatFit;
						fastModeTowerHeight = loopSize.highestRockPosition * cyclesThatFit;
						rockMovementIndex += loopSize.rockMovementIndex * cyclesThatFit;

						hashedCycleStateMap = {};
					}
				}

				if (!valid)
				{
					break;
				}
			}

			ri = (ri + 1) % rocks.size();
		}

		const auto part2 = highestRockPosition + fastModeTowerHeight + 1;

		return { std::to_string(part1), std::to_string(part2) };
	}
}
