#include <2022/Day20Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <unordered_map>

namespace TwentyTwentyTwo {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Grove Positioning System", 2022, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Node {
		int index{ 0 };
		int value{ 0 };

		Node * prev{ nullptr };
		Node * next{ nullptr };

		Node * getValueFurther()
		{
			if (value > 0)
			{
				Node * further = next;
				for (int i = 1; i < value; ++i)
				{
					further = further->next;
				}
				return further;
			}
			else if (value < 0)
			{
				Node * further = prev;
				for (int i = -1; i > value; --i)
				{
					further = further->prev;
				}
				return further;
			}
			else
			{
				assert(false);
			}
		}

		void detach()
		{
			this->prev->next = this->next;
			this->next->prev = this->prev;
			this->prev = nullptr;
			this->next = nullptr;
		}

		void insert(Node * _prev, Node * _next)
		{
			assert(_prev != nullptr);
			assert(_next != nullptr);

			if (this == _prev || this == _next)
			{
				return;
			}

			detach();

			this->prev = _prev;
			this->next = _next;

			_prev->next = this;
			_next->prev = this;

		}
	};

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		std::vector<int> data;
		std::size_t i = 0;
		for (const auto& l : m_InputLines)
		{
			const auto value = std::stoi(l);
			data.push_back(value);
		}

		Node * root = new Node();
		Node * curr = root;

		root->value = data[0];
		root->prev = root;
		root->next = root;

		constexpr bool print = false;

		int zeroIndex = 0;
		std::unordered_map<int, Node *> dataNode;
		bool skip = true;
		{
			int i = 1;
			for (const auto val : data)
			{
				if (skip)
				{
					skip = false;
					continue;
				}

				if (val == 0)
				{
					zeroIndex = i;
				}

				Node* next(new Node());
				next->index = i++;
				next->value = val;

				next->prev = curr;
				next->next = curr->next;
				curr->next = next;
				next->next->prev = next;
				curr = next;
			}
		}

		curr = root;
		do
		{
			if (dataNode.find(curr->index) != dataNode.end())
			{
				throw std::runtime_error("DUPLICATE");
			}
			dataNode[curr->index] = curr;

			curr = curr->next;
		} while (curr != root);

		if (print)
		{
			std::cout << "Initial" << std::endl;
			auto iter = root;
			do
			{
				std::cout << iter->value << ", ";
				iter = iter->next;
			} while (iter != root);
			std::cout << std::endl << std::endl;
		}
		
		for (int index = 0; index < data.size(); ++index)
		{
			const auto node = dataNode[index];

			if (node->value == 0)
			{
				if (print)
				{
					std::cout << "0 does not move" << std::endl;
				}
				continue;
			}

			auto further = node->getValueFurther();

			if (node->value > 0)
			{
				node->insert(further, further->next);
			}
			else if (node->value < 0)
			{
				node->insert(further->prev, further);
			}

			if (print)
			{
				std::cout << "Moving " << node->value << std::endl;
				auto iter = root;
				do
				{
					std::cout << iter->value << ", ";
					iter = iter->next;
				} while (iter != root);
				std::cout << std::endl << std::endl;
			}
		}

		int index1 = 1000;
		int index2 = 2000;
		int index3 = 3000;

		int part1 = 0;

		auto currNode = dataNode[zeroIndex];
		for (int i = 1; i <= index3; ++i)
		{
			currNode = currNode->next;
			if (i == index1)
			{
				part1 += currNode->value;
			}
			if (i == index2)
			{
				part1 += currNode->value;
			}
			if (i == index3)
			{
				part1 += currNode->value;
			}
		}

		return { std::to_string(part1), "Part 2"};
	}
}
