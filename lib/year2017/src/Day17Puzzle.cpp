#include <2017/Day17Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Spinlock", 2017, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Node {
		Node* left{ nullptr };
		Node* right{ nullptr };
		int value;
	};

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		const int step = std::stoi(m_InputLines[0]);

		Node* root = new Node();

		root->left = root;
		root->right = root;
		root->value = 0;

		Node* curr = root;
		int currentValue = 0;

		for (std::size_t iter = 0; iter < 2017; ++iter) {
			for (int i = 0; i < step; ++i) {
				curr = curr->right;
			}

			Node* next = curr->right;

			Node* newNode = new Node();
			newNode->value = ++currentValue;

			curr->right = newNode;
			newNode->left = curr;

			newNode->right = next;
			next->left = next;

			curr = newNode;
		}

		const auto part1 = curr->right->value;

		int i = 0;
		int part2 = 0;
		for (int t = 1; t < 50000000 + 1; ++t) {
			i = (i + step) % t + 1;
			if (i == 1) {
				part2 = t;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
