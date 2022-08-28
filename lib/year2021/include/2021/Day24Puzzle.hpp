#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_24_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_24_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwentyOne {

	using AluNumber = long;

	struct Instruction {
		enum class Type {
			inp,
			add,
			mul,
			div,
			mod,
			eql
		} type;

		bool is1Var{ false };
		bool is2Var{ false };

		char var1 = {'?'};
		char var2 = { '?' };

		AluNumber val1 = { -1 };
		AluNumber val2 = { -1 };
	};

	class ArithmeticLogicUnit {
	public:
		ArithmeticLogicUnit(const std::vector<std::string>& _input);
		ArithmeticLogicUnit(const std::vector<std::string>& _input, const std::vector<AluNumber>& _inputValues);

		void run();
		void reset(const std::vector<AluNumber>& _inputValues);

		AluNumber get(char _name) const;

	protected:
		void runInp(const Instruction& _instruction);
		void runAdd(const Instruction& _instruction);
		void runMul(const Instruction& _instruction);
		void runDiv(const Instruction& _instruction);
		void runMod(const Instruction& _instruction);
		void runEql(const Instruction& _instruction);

		AluNumber get1(const Instruction& _instruction) const;
		AluNumber get2(const Instruction& _instruction) const;
	private:
		std::vector<AluNumber> m_InputValues;
		std::vector<Instruction> m_Instructions;

		std::unordered_map<char, AluNumber> m_Values;

	};

	class Day24Puzzle : public core::PuzzleBase {
	public:
		Day24Puzzle();
		~Day24Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_24_PUZZLE_HPP_