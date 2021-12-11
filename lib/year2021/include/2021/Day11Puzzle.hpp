#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>

namespace TwentyTwentyOne {

	struct Octopus {
		int energy;
		bool flashed{ false };
		bool valid{ false };
	};

	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static core::Region<Octopus> parse(const std::vector<std::string>& _inputLines);
		static long iterate(core::Region<Octopus>& _region);
		static bool validate(core::Region<Octopus>& _region, const std::vector<std::string>& _desired);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_11_PUZZLE_HPP_