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

		const int players = std::stoi(p[0]);
		const int marbles = std::stoi(p[6]);

		return { std::to_string(solve(players, marbles)), "Part 2"};
	}

	int Day09Puzzle::solve(int _players, int _marbles)
	{
		struct Node {
			Node* left{ nullptr };
			Node* right{ nullptr };
			int value;
		};

		Node* root = new Node();
		root->value = 0;
		root->left = root;
		root->right = root;

		Node* curr = root;

		int player = 1;

		std::unordered_map<int, int> scores;

		for (int i = 1; i <= _marbles; ++i) 
		{
			auto next = curr->right;
			auto nextNext = next->right;

			if (i % 23 == 0)
			{
				scores[player] += i;
				Node* spec = curr;
				for (int j = 0; j < 7; ++j) {
					spec = spec->left;
				}

				auto specPrev = spec->left;
				auto specNext = spec->right;

				specPrev->right = specNext;
				specNext->left = specPrev;

				scores[player] += spec->value;
				delete spec;
				curr = specNext;
			}
			else
			{
				auto newNode = new Node();
				newNode->value = i;

				next->right = newNode;
				newNode->left = next;

				nextNext->left = newNode;
				newNode->right = nextNext;

				curr = newNode;

				// std::cout << next->value << " (" << newNode->value << ") " << nextNext->value << std::endl;
			}

			player++;

			if (player > _players)
			{
				player -= _players;
			}
		}

		curr = root->right;
		while (curr != root)
		{
			auto next = curr->right;
			delete curr;
			curr = next;
		}
		delete root;

		const auto max = *std::max_element(scores.begin(), scores.end());

		return max.second;
	}
}
