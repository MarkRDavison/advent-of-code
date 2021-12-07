#include <2021/Day04Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <sstream>
#include <algorithm>

namespace TwentyTwentyOne {

	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Giant Squid", 2021, 4) {
	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		auto [numbers, boards] = parseInput(m_InputLines);

		std::string part1;
		std::string part2;

		for (const auto& n : numbers) {
			bool boardWon = false;
			for (auto& b : boards) {
				if (hasBoardWon(b)) {
					boardWon = true;
					continue;
				}
				if (applyNumber(b, n)) {
					if (hasBoardWon(b)) {
						const auto& sum = sumUnmarkedNumbers(b);
						const auto& total = n * sum;
						if (part1.empty()) {
							part1 = std::to_string(total);
						}
						part2 = std::to_string(total);
					}
				}
			}
			if (boardWon) {
				boards.erase(std::remove_if(boards.begin(), boards.end(), 
					[](const Day4BingoBoard& _board) -> bool {
						return hasBoardWon(_board);
					}));
			}
		}



		return { part1, part2 };
	}

	std::pair<std::vector<int>, std::vector<Day4BingoBoard>> Day04Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<int> numbers;
		std::vector<Day4BingoBoard> boards;

		for (const auto& n : ze::StringExtensions::splitStringByDelimeter(_inputLines[0], ",")) {
			numbers.push_back(std::stoi(n));
		}

		unsigned boardIndex = -1;
		unsigned boardRowIndex = 0;
		const unsigned indexOffset = 1;
		for (unsigned i = indexOffset; i < _inputLines.size(); ++i) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(_inputLines[i], " ");
			if (parts.empty()) {
				boards.emplace_back();
				boardRowIndex = 0;
				continue;
			}

			assert(parts.size() == 5);

			for (unsigned j = 0; j < 5; ++j) {
				boards.back().number[boardRowIndex][j].first = std::stoi(parts[j]);
				boards.back().number[boardRowIndex][j].second = true;
			}
			boardRowIndex++;
		}

		return { numbers, boards };
	}

	bool Day04Puzzle::hasBoardWon(const Day4BingoBoard& _board) {

		bool rowWon;
		for (unsigned row = 0; row < 5; ++row) {
			rowWon = true;
			for (unsigned column = 0; column < 5; ++column) {
				if (_board.number[row][column].second) {
					rowWon = false;
					break;
				}
			}
			if (rowWon) {
				return true;
			}
		}


		bool columnWon;
		for (unsigned column = 0; column < 5; ++column) {
			columnWon = true;
			for (unsigned row = 0; row < 5; ++row) {
				if (_board.number[row][column].second) {
					columnWon = false;
					break;
				}
			}
			if (columnWon) {
				return true;
			}
		}

		return false;
	}
	
	bool Day04Puzzle::applyNumber(Day4BingoBoard& _board, int _number) {
		for (unsigned row = 0; row < 5; ++row) {
			for (unsigned column = 0; column < 5; ++column) {
				auto& number = _board.number[row][column];
				if (number.first == _number) {
					number.second = false;
					return true;
				}
			}
		}
		return false;
	}
	
	int Day04Puzzle::sumUnmarkedNumbers(const Day4BingoBoard& _board) {
		int sum = 0;
		for (unsigned row = 0; row < 5; ++row) {
			for (unsigned column = 0; column < 5; ++column) {
				auto& number = _board.number[row][column];
				if (number.second) {
					sum += number.first;
				}
			}
		}
		return sum;
	}
}
