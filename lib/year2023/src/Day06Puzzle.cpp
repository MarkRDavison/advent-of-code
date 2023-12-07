#include <2023/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Wait For It", 2023, 6) {
	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef long long RaceNumber;
	struct Race {
		RaceNumber time;
		RaceNumber distance;
	};
	typedef std::vector<Race> RaceVector;

	RaceNumber getRaceWinningCount(const Race& race)
	{
		RaceNumber winningCount = 0;

		for (RaceNumber i = 0; i < race.time; ++i)
		{
			const auto holdTime = i;
			const auto velocity = holdTime;
			const auto distanceTravelled = velocity * (race.time - holdTime);

			if (distanceTravelled > race.distance)
			{
				winningCount++;
			}
		}

		return winningCount;
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		RaceVector races;
		std::string part2Time = "";
		std::string part2Distance = "";
		for (const auto& t : StringExtensions::splitStringByDelimeter(m_InputLines[0], " :"))
		{
			if (t == "Time") { continue; }
			auto& r = races.emplace_back();
			r.time = (RaceNumber)std::stoll(t);
			part2Time += t;
		}
		std::size_t i = 0;
		for (const auto& d : StringExtensions::splitStringByDelimeter(m_InputLines[1], " :"))
		{
			if (d == "Distance") { continue; }
			auto& r = races[i];
			r.distance = (RaceNumber)std::stoll(d);
			i++;
			part2Distance += d;
		}

		Race part2Race{
			.time = (RaceNumber)std::stoll(part2Time),
			.distance = (RaceNumber)std::stoll(part2Distance)
		};

		RaceNumber part1 = 1;

		for (const auto& r : races)
		{
			part1 *= getRaceWinningCount(r);
		}

		RaceNumber part2 = getRaceWinningCount(part2Race);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
