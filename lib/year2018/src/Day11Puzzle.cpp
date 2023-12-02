#include <2018/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Clock.hpp>

namespace TwentyEighteen {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Chronal Charge", 2018, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	core::Region<ChronalChargeNumber> Day11Puzzle::CreateSummedAreaTable(core::Region<ChronalChargeNumber> powerLevels)
	{
		constexpr int SIZE = 300;
		core::Region<ChronalChargeNumber> sat;

		for (int y = 0; y < SIZE; ++y)
		{
			for (int x = 0; x < SIZE; ++x)
			{


				ChronalChargeNumber current = powerLevels.getCell(x, y);

				auto sum = current;

				if (x > 0)
				{
					sum += sat.getCell(x - 1, y);
				}
				if (y > 0)
				{
					sum += sat.getCell(x, y - 1);
				}
				if (x > 0 && y > 0)
				{
					sum -= sat.getCell(x - 1, y - 1);
				}

				sat.getCell(x, y) = sum;
			}
		}

		return sat;
	}
	core::Region<ChronalChargeNumber> Day11Puzzle::CreatePowerLevels(ChronalChargeNumber serialNumber)
	{
		constexpr int SIZE = 300;

		core::Region<ChronalChargeNumber> powerLevels;

		for (int y = 0; y < SIZE; ++y)
		{
			for (int x = 0; x < SIZE; ++x)
			{
				powerLevels.getCell(x, y) = GetPowerNumber(serialNumber, { x, y });
			}
		}

		return powerLevels;
	}
	ChronalChargeNumber Day11Puzzle::GetSquareSum(core::Region<ChronalChargeNumber> powerLevels, Vector2i coords, int squareSize)
	{
		ChronalChargeNumber sum = 0;

		for (int y = coords.y; y < coords.y + squareSize; ++y)
		{
			for (int x = coords.x; x < coords.x + squareSize; ++x)
			{
				sum += powerLevels.getCell(x, y);
			}
		}

		return sum;
	}

	ChronalChargeNumber Day11Puzzle::GetSquareSumUsingSAT(core::Region<ChronalChargeNumber> sat, Vector2i coords, int squareSize)
	{
		auto D = sat.getCell(coords.x + squareSize - 1, coords.y + squareSize - 1);
		auto A = sat.getCell(coords.x - 1, coords.y - 1);
		auto C = sat.getCell(coords.x - 1, coords.y + squareSize - 1);
		auto B = sat.getCell(coords.x + squareSize - 1, coords.y - 1);

		ChronalChargeNumber sum = D - B - C + A;

		return sum;
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {

		constexpr int SIZE = 300;

		ChronalChargeNumber serial = (ChronalChargeNumber)std::stol(m_InputLines[0]);

		Vector2i maxCoord = { 1,1 };
		ChronalChargeNumber maxSquareSum = 0;

		int squareSize = 3;

		auto powerLevels = CreatePowerLevels(serial);
		auto sat = CreateSummedAreaTable(powerLevels);

		for (int y = 0; y < SIZE - squareSize + 1; ++y)
		{
			for (int x = 0; x < SIZE - squareSize + 1; ++x)
			{
				auto newSum = GetSquareSumUsingSAT(sat, { x,y }, squareSize);
				if (newSum > maxSquareSum)
				{
					std::cout << "New winner at " << x << "," << y << " with sum: " << newSum << std::endl;
					maxSquareSum = newSum;
					maxCoord = { x,y };
				}
			}
		}

		auto part1 = std::to_string(maxCoord.x) + "," + std::to_string(maxCoord.y);

		maxCoord = { 1,1 };
		maxSquareSum = 0;
		ChronalChargeNumber maxSize = 1;
		for (int VAR_SIZE = 1; VAR_SIZE <= SIZE; ++VAR_SIZE)
		{
			Clock clock;
			std::cout << "Running part 2 with size: " << VAR_SIZE << std::endl;
			for (int y = 0; y < SIZE - VAR_SIZE + 1; ++y)
			{
				for (int x = 0; x < SIZE - VAR_SIZE + 1; ++x)
				{
					auto newSum = GetSquareSumUsingSAT(sat, { x,y }, VAR_SIZE);
					if (newSum > maxSquareSum)
					{
						std::cout << "New winner at " << x << "," << y << "," << VAR_SIZE << " with sum: " << newSum << std::endl;
						maxSquareSum = newSum;
						maxCoord = { x,y };
						maxSize = VAR_SIZE;
					}
				}
			}

			std::cout << " - took " << clock.getElapsedTime() << "s" << std::endl;
		}

		return { 
			part1,
			std::to_string(maxCoord.x) + "," + std::to_string(maxCoord.y) +  "," + std::to_string(maxSize)
		};
	}

	ChronalChargeNumber Day11Puzzle::GetPowerNumber(ChronalChargeNumber serialNumber, Vector2< ChronalChargeNumber> coords)
	{
		ChronalChargeNumber powerNumber = coords.x + 10;
		powerNumber *= coords.y;
		powerNumber += serialNumber;
		powerNumber *= (coords.x + 10);
		powerNumber = (powerNumber / 100) % 10;
		powerNumber -= 5;
		return powerNumber;
	}
}
