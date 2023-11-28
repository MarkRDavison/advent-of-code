#include <2020/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <cassert>
#include <unordered_map>

namespace TwentyTwenty {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Crab Cups", 2020, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		const auto& parsed = Day23Puzzle::parse(m_InputLines);

		const auto part1 = Day23Puzzle::doPart1(parsed, 100);
		const auto part2 = Day23Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Day23Parsed Day23Puzzle::parse(const std::vector<std::string>& _inputLines) {
		Day23Parsed parsed;

		parsed.label = _inputLines[0];

		return parsed;
	}

	std::string Day23Puzzle::doPart1(const Day23Parsed& _parsed, unsigned _moves) {

		struct CupNode {
			CupNode(Day23Number _number) : number(_number) {}
			Day23Number number;

			CupNode* next{ nullptr };
		};

		CupNode* first = new CupNode(std::stol(_parsed.label.substr(0, 1)));
		CupNode* curr = first;
		for (unsigned i = 1; i < _parsed.label.size(); ++i) {
			CupNode* newCup = new CupNode(std::stol(_parsed.label.substr(i, 1)));
			curr->next = newCup;
			curr = newCup;
		}
		curr->next = first;
		curr = first;

		for (unsigned i = 1; i <= _moves; ++i) {
			std::cout << "-- move " << i << " --" << std::endl;
			{
				CupNode* iter = curr->next;
				std::cout << "cups: (" << curr->number << ")";
				while (iter != curr) {
					std::cout << " " << iter->number;
					iter = iter->next;
				}
				std::cout << std::endl;
			}

			{
				auto first_of_three = curr->next;
				auto second_of_three = first_of_three->next;
				auto third_of_three = second_of_three->next;
				std::cout << "pick up: " << first_of_three->number
					<< ", " << second_of_three->number
					<< ", " << third_of_three->number
					<< std::endl;

				auto destinationNumber = curr->number;
				do {
					destinationNumber--;
					if (destinationNumber < 1) {
						destinationNumber += 9;
					}
				} while (
					destinationNumber == first_of_three->number ||
					destinationNumber == second_of_three->number ||
					destinationNumber == third_of_three->number);

				std::cout << "destination: " << destinationNumber << std::endl;

				auto dest = curr;
				while (dest->number != destinationNumber) {
					dest = dest->next;
				}

				auto beforePickup = curr;
				auto afterPickup = third_of_three->next;
				beforePickup->next = afterPickup;

				auto beforePlace = dest;
				auto afterPlace = dest->next;

				beforePlace->next = first_of_three;
				third_of_three->next = afterPlace;

				curr = curr->next;
			}
		}

		std::cout << "-- final --" << std::endl;
		CupNode* iter = curr->next;
		CupNode* one{ curr };
		std::cout << "cups: (" << curr->number << ")";
		while (iter != curr) {
			if (iter->number == 1) {
				one = iter;
			}
			std::cout << " " << iter->number;
			iter = iter->next;
		}
		std::cout << std::endl;

		assert(one != nullptr);
		std::string result;
		iter = one->next;
		while (iter != one) {
			result += std::to_string(iter->number);
			iter = iter->next;
		}

		return result;
	}
	std::string Day23Puzzle::doPart2(const Day23Parsed& _parsed) {
		struct CupNode {
			CupNode(Day23Number _number) : number(_number) {}
			Day23Number number;

			CupNode* next{ nullptr };
		};
		std::unordered_map<Day23Number, CupNode*> nodes;
		CupNode* first = new CupNode(std::stol(_parsed.label.substr(0, 1)));
		CupNode* curr = first;
		nodes[first->number] = first;
		for (unsigned i = 1; i <= 1000000; ++i) {
			const Day23Number number = i >= _parsed.label.size()
				? i
				: std::stol(_parsed.label.substr(i, 1));
			CupNode* newCup = new CupNode(number);
			nodes[number] = newCup;
			curr->next = newCup;
			curr = newCup;
		}
		curr->next = first;
		curr = first;

		for (unsigned i = 1; i <= 10000000; ++i) {
			{
				auto first_of_three = curr->next;
				auto second_of_three = first_of_three->next;
				auto third_of_three = second_of_three->next;

				auto destinationNumber = curr->number;
				do {
					destinationNumber--;
					if (destinationNumber < 1) {
						destinationNumber += 1000000;
					}
				} while (
					destinationNumber == first_of_three->number ||
					destinationNumber == second_of_three->number ||
					destinationNumber == third_of_three->number);

				auto dest = nodes[destinationNumber];

				auto beforePickup = curr;
				auto afterPickup = third_of_three->next;
				beforePickup->next = afterPickup;

				auto beforePlace = dest;
				auto afterPlace = dest->next;

				beforePlace->next = first_of_three;
				third_of_three->next = afterPlace;

				curr = curr->next;
			}
		}

		CupNode* one = nodes[1];

		return std::to_string(one->next->number * one->next->next->number);
	}
}
