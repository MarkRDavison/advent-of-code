#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_19_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_19_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwenty {

	struct SubRule {
		std::vector<unsigned> ruleIds;
	};

	struct Rule {
		char character{ '?' };

		std::vector<SubRule> subrules;
	};

	struct Message {
		std::string message;
	};

	struct Day19Struct {
		std::unordered_map<unsigned, Rule> rules;
		std::vector<Message> messages;
	};
	
	class Day19Puzzle : public core::PuzzleBase {
	public:
		Day19Puzzle();
		~Day19Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day19Struct parse(const std::vector<std::string>& _inputLines);
		static bool matchRule(const Day19Struct& _parsed, unsigned _ruleId, const std::string& _message);
		static std::string doPart1(const Day19Struct& _parsed);
		static std::string doPart2(const Day19Struct& _parsed);
		static Day19Struct transformPart1ToPart2(const Day19Struct& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_19_PUZZLE_HPP_