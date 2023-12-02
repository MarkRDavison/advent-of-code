#include <2018/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>

namespace TwentyEighteen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Marble Mania", 2018, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		const auto& p = StringExtensions::splitStringByDelimeter(m_InputLines[0], " ");

		const long long players = std::stoi(p[0]);
		const long long marbles = std::stoi(p[6]);

		const auto part1 = solve(players, marbles);
		const auto part2 = solve(players, marbles * 100);

		return { std::to_string(part1), std::to_string(part2) };
	}

	long long Day09Puzzle::solve(long long _players, long long _marbles)
	{
		struct Node {
			Node* left{ nullptr };
			Node* right{ nullptr };
			long long value{ 0 };
		};

		Node* root = new Node();
		root->value = 0;
		root->left = root;
		root->right = root;

		Node* curr = root;

		long long player = 1;

		std::unordered_map<long long, long long> scores;

		for (long long i = 1; i <= _marbles; ++i)
		{
			Node* newMarble = new Node();
			newMarble->value = i;

			if (i % 23 == 0)
			{
				scores[player] += i;

				auto off7 = curr->left->left->left->left->left->left->left;
				scores[player] += off7->value;

				auto off7L = off7->left;
				auto off7R = off7->right;

				delete off7;

				off7L->right = off7R;
				off7R->left = off7L;

				delete newMarble;

				newMarble = off7R;
			}
			else
			{
				auto marble1 = curr->right;
				auto marble2 = marble1->right;

				newMarble->left = marble1;
				marble1->right = newMarble;
				newMarble->right = marble2;
				marble2->left = newMarble;
			}

			player += 1;
			if (player > _players)
			{
				player = 1;
			}
			curr = newMarble;
		}

		const auto max = *std::max_element(
			scores.begin(), 
			scores.end(),
			[](const std::pair<long long, long long>& lhs, const std::pair<long long, long long>& rhs) -> bool
			{
				return lhs.second < rhs.second;
			});

		return max.second;
	}
}
