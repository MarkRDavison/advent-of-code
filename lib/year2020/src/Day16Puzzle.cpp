#include <2020/Day16Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <numeric>
#include <list>

namespace TwentyTwenty {

	std::vector<std::string> splitStringByLines3(const std::string& _parameter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			result.push_back(line);
		}

		return result;
	}
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("REPLACE NENENENE!?!?!?!?", 2020, 16) {
	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(splitStringByLines3(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		auto parsed = Day16Puzzle::parse(m_InputLines);

		const auto part1 = Day16Puzzle::doPart1(parsed);
		const auto part2 = Day16Puzzle::doPart2(parsed);
		return { part1, part2 };
	}

	ParsedTicketInfo translate(const std::string& _str) {
		ParsedTicketInfo s{};
		return s;
	}

	ParsedTicketInfo Day16Puzzle::parse(const std::vector<std::string>& _inputLines) {
		ParsedTicketInfo s{};

		unsigned index = 0;

		while (!_inputLines[index].empty()) {
			const auto colonLocation = _inputLines[index].find(':');
			assert(colonLocation != std::string::npos);
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(_inputLines[index].substr(colonLocation), ":- or");
			auto& range = s.ticketInfo[_inputLines[index].substr(0, colonLocation)];
			for (unsigned i = 0; i < parts.size(); i += 2) {
				range.emplace_back(std::stoi(parts[i]), std::stoi(parts[i + 1]));
			}

			index++;
		}
		index++;
		index++;

		while (!_inputLines[index].empty()) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(_inputLines[index], ",");
			std::transform(parts.begin(), parts.end(), std::back_inserter(s.myTicket), 
				[](const std::string& _str) -> Day16Number {
					return std::stoi(_str);
				});
			index++;
		}
		index++;
		index++;

		while (index < _inputLines.size() && !_inputLines[index].empty()) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(_inputLines[index], ",");
			auto& nextTicket = s.nearbyTickets.emplace_back();
			std::transform(parts.begin(), parts.end(), std::back_inserter(nextTicket),
				[](const std::string& _str) -> Day16Number {
					return std::stoi(_str);
				});
			index++;
		}


 		return s;
	}

	std::string Day16Puzzle::doPart1(ParsedTicketInfo& _parsed) {

		std::unordered_set<Day16Number> validNumbers;

		for (const auto& [name, range] : _parsed.ticketInfo) {
			for (const auto& [start, end] : range) {
				for (int i = start; i <= end; ++i) {
					validNumbers.insert(i);
				}
			}
		}

		Day16Number invalidSum = 0;
		for (const auto& ticket : _parsed.nearbyTickets) {
			bool valid = true;
			for (const auto num : ticket) {
				if (validNumbers.count(num) == 0) {
					invalidSum += num;
					valid = false;
				}
			}
			if (valid) {
				_parsed.validTickets.push_back(ticket);
			}
		}

		return std::to_string(invalidSum);
	}
	std::string Day16Puzzle::doPart2(const ParsedTicketInfo& _parsed) {

		std::list<Day16Number> l(_parsed.ticketInfo.size());
		std::iota(l.begin(), l.end(), 0);

		do {

		} while (std::next_permutation(l.begin(), l.end()));

		return std::to_string(555);
	}
}
