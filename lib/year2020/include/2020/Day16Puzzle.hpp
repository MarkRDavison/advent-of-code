#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwenty {

	using Day16Number = int;
	using Ticket = std::vector<Day16Number>;
	using Range = std::vector<std::pair<Day16Number, Day16Number>>;
	

	struct ParsedTicketInfo {
		std::unordered_map<std::string, Range> ticketInfo;
		Ticket myTicket;
		std::vector<Ticket> nearbyTickets;
		std::vector<Ticket> validTickets;
	};
	
	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		
		static ParsedTicketInfo parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(ParsedTicketInfo& _parsed);
		static std::string doPart2(const ParsedTicketInfo& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_16_PUZZLE_HPP_