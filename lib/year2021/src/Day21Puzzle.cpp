#include <2021/Day21Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>

namespace TwentyTwentyOne {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Dirac Dice", 2021, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::size_t solvePart1(int _player1, int _player2) {
		std::size_t p1 = (std::size_t)_player1;
		std::size_t p2 = (std::size_t)_player2;
		std::size_t p1Score = 0;
		std::size_t p2Score = 0;

		std::size_t diceRolls = 0;
		std::size_t dice = 1;
		bool p1Turn = true;
		while (p1Score < 1000 && p2Score < 1000) {
			if (p1Turn) {
				p1 += dice++;
				p1 += dice++;
				p1 += dice++;
				diceRolls += 3;
				while (p1 > 10) {
					p1 -= 10;
				}
				p1Score += p1;
			} else {
				p2 += dice++;
				p2 += dice++;
				p2 += dice++;
				diceRolls += 3;
				while (p2 > 10) {
					p2 -= 10;
				}
				p2Score += p2;
			}
			p1Turn = !p1Turn;
		}

		const auto min = std::min(p1Score, p2Score);
		return min * diceRolls;
	}
	//                             p1 position  p1 score     p2 position  p2 score
	using ScorePlaces = std::tuple<std::size_t, std::size_t, std::size_t, std::size_t>;

	template<typename T>
	struct tuple_hash_fxn {
		std::size_t operator()(const ScorePlaces& _score) const {
			return  
				std::hash<T>()(std::get<0>(_score)) ^ 
				std::hash<T>()(std::get<1>(_score)) ^
				std::hash<T>()(std::get<2>(_score)) ^
				std::hash<T>()(std::get<3>(_score));
		}
	};
	std::pair<std::size_t, std::size_t> recurseSolve(const ScorePlaces& _scorePlaces, std::unordered_map<ScorePlaces, std::pair<std::size_t, std::size_t>, tuple_hash_fxn<std::size_t>>& _memoizer, std::size_t _depth) {
		std::size_t p1Wins = 0; std::size_t p2Wins = 0;

		const auto [p1Position, p1Score, p2Position, p2Score] = _scorePlaces;

		if (p1Score >= 21) {
			return { 1, 0 };
		}
		else if (p2Score >= 21) {
			return { 0, 1 };
		}

		if (_memoizer.count(_scorePlaces) > 0) {
			return _memoizer[_scorePlaces];
		}

		for (std::size_t i = 1; i <= 3; ++i) {
			for (std::size_t j= 1; j <= 3; ++j) {
				for (std::size_t k = 1; k <= 3; ++k) {
					const auto move = i + j + k;
					const auto newP1Position = (p1Position + move) % 10;
					const auto newP1Score = p1Score + newP1Position + 1;

					const auto& [p2Win, p1Win] = recurseSolve({ p2Position, p2Score, newP1Position, newP1Score }, _memoizer, _depth + 1);
					p1Wins += p1Win;
					p2Wins += p2Win;
				}
			}
		}
		_memoizer[_scorePlaces] = { p1Wins, p2Wins };
		return { p1Wins, p2Wins };
	}

	std::size_t solvePart2(int _player1, int _player2) {
		std::unordered_map<ScorePlaces, std::pair<std::size_t, std::size_t>, tuple_hash_fxn<std::size_t>> memoizer;

		const auto& [p1W, p2W] = recurseSolve({_player1 - 1, 0, _player2 - 1, 0}, memoizer, 0);

		return std::max(p1W, p2W);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		const int player1 = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " :").back());
		const int player2 = std::stoi(ze::StringExtensions::splitStringByDelimeter(m_InputLines[1], " :").back());

		const auto part1 = solvePart1(player1, player2);
		const auto part2 = solvePart2(player1, player2);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
