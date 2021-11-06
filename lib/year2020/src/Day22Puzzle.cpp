#include <2020/Day22Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <cassert>

namespace TwentyTwenty {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Crab Combat", 2020, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		const auto& parsed = Day22Puzzle::parse(m_InputLines);

		const auto part1 = Day22Puzzle::doPart1(parsed);
		const auto part2 = Day22Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Day22Struct Day22Puzzle::parse(const std::vector<std::string>& _inputLines) {
		Day22Struct parsed;

		bool player1 = true;

		for (const auto& str : _inputLines) {
			if (str.empty()) {
				continue;
			}
			else if (str.find("Player 1") == 0) {
				player1 = true;
			}
			else if (str.find("Player 2") == 0) {
				player1 = false;
			}
			else {
				if (player1) {
					parsed.player1.emplace_back(std::stol(str));
				} else {
					parsed.player2.emplace_back(std::stol(str));
				}
			}
		}

		return parsed;
	}

	std::string Day22Puzzle::doPart1(const Day22Struct& _parsed) {

		struct CardNode {

			CardNode(Day22Number _value) : value(_value) {

			}

			CardNode* prev{ nullptr };
			CardNode* next{ nullptr };

			Day22Number value;
		};

		struct Player {
			CardNode* top{ nullptr };
			CardNode* bot{ nullptr };

			void printDeck(int _number) const {
				std::cout << "Player " << _number << "'s deck: ";
				CardNode* current = top;
				while (current != nullptr) {
					std::cout << current->value << ", ";
					current = current->next;
				}
				std::cout << std::endl;
			}

			CardNode* popTop() {
				CardNode* current = top;
				top = top->next;
				current->next = nullptr;
				current->prev = nullptr;
				return  current;
			}
		};

		Player p1;
		Player p2;

		{
			p1.top = new CardNode(_parsed.player1[0]);
			p1.bot = p1.top;
			for (unsigned i = 1; i < _parsed.player1.size(); ++i) {
				CardNode* newNode = new CardNode(_parsed.player1[i]);
				p1.bot->next = newNode;
				newNode->prev = p1.bot;
				p1.bot = newNode;
			}
		}
		{
			p2.top = new CardNode(_parsed.player2[0]);
			p2.bot = p2.top;
			for (unsigned i = 1; i < _parsed.player2.size(); ++i) {
				CardNode* newNode = new CardNode(_parsed.player2[i]);
				p2.bot->next = newNode;
				newNode->prev = p2.bot;
				p2.bot = newNode;
			}
		}

		unsigned round = 1;
		while (p1.top != nullptr && p2.top != nullptr) {
			std::cout << "-- Round " << round << " --" << std::endl;
			p1.printDeck(1);
			p2.printDeck(2);
			auto player1Card = p1.popTop();
			auto player2Card = p2.popTop();
			std::cout << "Player 1 plays: " << player1Card->value << std::endl;
			std::cout << "Player 2 plays: " << player2Card->value << std::endl;

			assert(player1Card->value != player2Card->value);
			if (player1Card->value > player2Card->value) {
				std::cout << "Player 1 wins the round!" << std::endl << std::endl;
				p1.bot->next = player1Card;
				player1Card->prev = p1.bot;

				p1.bot = player2Card;
				player2Card->prev = player1Card;
				player1Card->next = player2Card;
			}
			else {
				std::cout << "Player 2 wins the round!" << std::endl << std::endl;
				p2.bot->next = player2Card;
				player2Card->prev = p2.bot;

				p2.bot = player1Card;
				player1Card->prev = player2Card;
				player2Card->next = player1Card;
			}

			round++;
		}

		std::cout << "== Post-game results ==" << std::endl;		
		p1.printDeck(1);
		p2.printDeck(2);

		Player* winningPlayer = p1.top != nullptr
			? &p2
			: &p1;
		CardNode* current = winningPlayer->bot;
		Day22Number multiplier = 1;
		Day22Number score = 0;
		while (multiplier <= _parsed.player1.size() + _parsed.player2.size()) {
			score += multiplier * current->value;
			std::cout << current->value << " x " << multiplier << std::endl;
			multiplier++;
			current = current->prev;
		}

		return std::to_string(score);
	}
	std::string Day22Puzzle::doPart2(const Day22Struct& _parsed) {
		return "";
	}
}
