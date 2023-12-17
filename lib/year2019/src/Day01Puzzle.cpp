#include <2019/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace TwentyNineteen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("The Tyranny of the Rocket Equation", 2019, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long long Day01Puzzle::getFuelRequirement(long long mass, bool fuelNeedsFuel)
	{
		auto req = mass / 3;
		req -= 2;
		
		if (fuelNeedsFuel)
		{
			long long fuelMass = req;
			while (true)
			{
				const auto additionalFuel = getFuelRequirement(fuelMass, false);
				if (additionalFuel <= 0)
				{
					break;
				}

				fuelMass = additionalFuel;
				req += additionalFuel;
			}
		}

		return std::max(req, 0ll);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		long long part1 = 0;
		long long part2 = 0;

		for (const auto& l : m_InputLines)
		{
			const auto val = std::stoll(l);
			part1 += getFuelRequirement(val, false);
			part2 += getFuelRequirement(val, true);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
