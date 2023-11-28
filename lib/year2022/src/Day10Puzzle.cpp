#include <2022/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <array>

namespace TwentyTwentyTwo {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Cathode-Ray Tube", 2022, 10) {
	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void print(std::array<std::array<char, 40>, 6>& _screen)
	{
		for (const auto& r : _screen)
		{
			for (const auto& c : r)
			{
				std::cout << c;
			}
			std::cout << std::endl;
		}
	}

	void updateDraw(std::array<std::array<char, 40>, 6>& _screen, long _cycle, long _x)
	{
		const std::size_t x = _cycle % 40;
		const std::size_t y = _cycle / 40;

		if (_x + 1 == x || _x == x || _x - 1 == x)
		{
			_screen[y][x] = '#';
		}
		else
		{
			_screen[y][x] = '.';
		}
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {

		long registerX = 1;
		long cycles = 0;

		std::vector<long> interestedCycleValues;
		std::vector<long> interestedCycles{ 20, 60, 100, 140, 180, 220 };
		std::size_t interestedCycleIndex = 0;

		std::array<std::array<char, 40>, 6> screen;
		for (auto& r : screen)
		{
			for (auto& c : r)
			{
				c = ' ';
			}
		}

		bool running = true;
		while (running || cycles < 240)
		{

			for (const auto& l : m_InputLines)
			{
				const long previousCycles = cycles;
				const long previousRegisterX = registerX;

				const auto& p = StringExtensions::splitStringByDelimeter(l, " ");

				const auto& instruction = p[0];
				if (instruction == "noop")
				{
					updateDraw(screen, cycles, registerX);
					cycles++;
				}
				else if (instruction == "addx")
				{
					const auto amount = std::stol(p[1]);
					updateDraw(screen, cycles, registerX);
					cycles++;
					updateDraw(screen, cycles, registerX);
					cycles++;
					registerX += amount;
				}
				else
				{
					assert(false);
				}

				if (interestedCycleIndex >= interestedCycles.size())
				{
					running = false;
				}
				else

				{
					const auto cycleNumber = interestedCycles[interestedCycleIndex];
					if (previousCycles == cycleNumber)
					{
						interestedCycleValues.push_back(previousRegisterX);
						interestedCycleIndex++;
					}
					else if (previousCycles < cycleNumber && cycleNumber < cycles)
					{
						interestedCycleValues.push_back(previousRegisterX);
						interestedCycleIndex++;
					}
					else if (cycles == cycleNumber)
					{
						interestedCycleValues.push_back(previousRegisterX);
						interestedCycleIndex++;
					}
				}
			}
		}

		long part1 = 0;

		for (std::size_t i = 0; i < interestedCycles.size(); ++i)
		{
			const auto cycleNumber = interestedCycles[i];
			const auto registerNumber = interestedCycleValues[i];

			const auto sum = cycleNumber * registerNumber;

			part1 += sum;
		}

		print(screen);

		// TODO: OCR the screen
		return { std::to_string(part1), "See above"};
	}
}
