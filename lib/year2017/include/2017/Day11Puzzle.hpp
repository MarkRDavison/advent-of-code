#ifndef INCLUDED_ADVENT_OF_CODE_2017_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2017_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySeventeen {

	struct Hex {
		int q, r, s;
		Hex(int q_, int r_) : q(q_), r(r_), s(-q_ - r_) {}


		void operator+=(const Hex& _b);
		Hex& operator=(const Hex& _b);

		int length() const;
	};

	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<Hex, int> apply(const std::string& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2017_DAY_11_PUZZLE_HPP_