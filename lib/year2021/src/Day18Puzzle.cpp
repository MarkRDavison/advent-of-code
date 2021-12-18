#include <2021/Day18Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <cassert>
#include <stack>

namespace TwentyTwentyOne {

	std::string recurseRender(const SnailFishNumber* _number) {
		if (_number->type == SnailFishNumber::Type::Leaf) {
			return std::to_string(_number->value);
		}

		std::string str;

		str += '[';

		str += recurseRender(_number->left);

		str += ",";

		str += recurseRender(_number->right);

		str += ']';

		return str;
	}

	std::string SnailFishNumber::render() const {
		return recurseRender(this);
	}
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Snailfish", 2021, 18) {
	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {

		SnailFishDecimal part1;
		SnailFishDecimal part2 = 0;
		{
			auto num = Day18Puzzle::parse(m_InputLines[0]);
			for (std::size_t i = 1; i < m_InputLines.size(); ++i) {
				const auto newNum = Day18Puzzle::parse(m_InputLines[i]);
				num = Day18Puzzle::add(num, newNum);
				num = Day18Puzzle::reduce(num);
			}
			part1 = magnitude(num);
		}

		{
			for (unsigned i = 0; i < m_InputLines.size(); ++i) {
				for (unsigned j = 0; j < m_InputLines.size(); ++j) {
					if (i == j) { continue; }

					auto num = Day18Puzzle::add(
						Day18Puzzle::parse(m_InputLines[i]),
						Day18Puzzle::parse(m_InputLines[j]));
					num = Day18Puzzle::reduce(num);
					
					part2 = std::max(part2, magnitude(num));
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
	
	SnailFishNumber *Day18Puzzle::parse(const std::string& _input) {
		SnailFishNumber* root = nullptr;
		std::stack<SnailFishNumber*> stack;

		for (std::size_t i = 0; i < _input.size(); ++i) {
			const char c = _input[i];
			if (c == '[') {
				auto newFish = new SnailFishNumber();
				if (!stack.empty()) {
					auto current = stack.top();
					newFish->parent = current;
					newFish->depth = current->depth + 1;
					current->type = SnailFishNumber::Type::Node;
					if (current->left == nullptr) {
						current->left = newFish;
						newFish->type = SnailFishNumber::Type::Leaf;
					}
					else if (current->right == nullptr) {
						current->right = newFish;
						newFish->type = SnailFishNumber::Type::Leaf;
					}
					else {
						assert(false && "SHOULD NOT GET HERE");
					}
				}
				stack.push(newFish);
				if (root == nullptr) {
					root = newFish;
				}
			}
			else if (c == ']') {
				stack.pop();
			}
			else if (c == ',') {
				auto current = stack.top();

				assert(current->left != nullptr);
				assert(current->right == nullptr);

				const char nextC = _input[i + 1];
				if ('0' <= nextC && nextC <= '9') {
					// right hand side is a value
					const auto closingIndex = _input.find(']', i);
					assert(closingIndex != std::string::npos);

					auto newFishRight = new SnailFishNumber();
					newFishRight->type = SnailFishNumber::Type::Leaf;
					newFishRight->value = std::stol(_input.substr(i + 1, closingIndex - i - 1));
					newFishRight->parent = current;
					current->right = newFishRight;
					i = closingIndex - 1;
				}

			}
			else {
				auto current = stack.top();

				const auto commaIndex = _input.find(',', i);
				assert(commaIndex != std::string::npos);

				auto newFishLeft = new SnailFishNumber();
				newFishLeft->type = SnailFishNumber::Type::Leaf;
				newFishLeft->value = std::stol(_input.substr(i, commaIndex - i));
				newFishLeft->parent = current;
				current->type = SnailFishNumber::Type::Node;
				if (current->left == nullptr) {
					current->left = newFishLeft;
				}
				else {
					current->right = newFishLeft;
				}

				i = commaIndex + 1;

				const char nextC = _input[i];
				if ('0' <= nextC && nextC <= '9') {
					// right hand side is a value
					const auto closingIndex = _input.find(']', i);
					assert(closingIndex != std::string::npos);

					auto newFishRight = new SnailFishNumber();
					newFishRight->type = SnailFishNumber::Type::Leaf;
					newFishRight->value = std::stol(_input.substr(i, closingIndex - i));
					newFishRight->parent = current;
					current->right = newFishRight;
					current->type = SnailFishNumber::Type::Node;
					i = closingIndex - 1;
				}
				else {
					// right hand side is not a value

					i--;
				}
			}
		}


		return root;
	}

	void recurseAssignDepths(SnailFishNumber* _number, SnailFishDecimal _depth) {
		if (_number == nullptr) { return; }
		_number->depth = _depth;

		recurseAssignDepths(_number->left, _depth + 1);
		recurseAssignDepths(_number->right, _depth + 1);
	}

	SnailFishNumber* Day18Puzzle::add(SnailFishNumber* _lhs, SnailFishNumber* _rhs) {
		auto added = new SnailFishNumber();
		added->left = _lhs;
		added->right = _rhs;
		added->type = SnailFishNumber::Type::Node;

		_lhs->parent = added;
		_rhs->parent = added;

		recurseAssignDepths(added, 0);

		return added;
	}

	std::pair<int, int> getChildLeafNodeIndexes(const std::unordered_map<int, SnailFishNumber*>& _indicies, const SnailFishNumber* _parent) {
		int left = -1;
		int right = -1;

		for (const auto& [index, node] : _indicies) {
			if (_parent->left == node) {
				left = index - 1;
			}
			if (_parent->right == node) {
				right = index + 1;
			}
		}

		return { left, right };
	}

	void populateLeafIndicies(std::unordered_map<int, SnailFishNumber*>& _indicies, SnailFishNumber*_current, int& _index) {

		if (_current->type == SnailFishNumber::Type::Leaf) {
			_indicies[_index++] = _current;
			return;
		}

		populateLeafIndicies(_indicies, _current->left, _index);
		populateLeafIndicies(_indicies, _current->right, _index);
	}

	bool recurseExplode(SnailFishNumber* _root, SnailFishNumber* _number) {
		if (_number == nullptr) {
			return false;
		}
		if (_number->depth >= 4 &&
			_number->left != nullptr && _number->left->type == SnailFishNumber::Type::Leaf &&
			_number->right != nullptr && _number->right->type == SnailFishNumber::Type::Leaf) {
			// EXPLODE!
			auto parent = _number->parent;
			std::unordered_map<int, SnailFishNumber*> indicies;
			int index = 0;
			populateLeafIndicies(indicies, _root, index);
			const auto& [leftIndex, rightIndex] = getChildLeafNodeIndexes(indicies, _number);

			if (indicies.count(rightIndex) > 0) {
				auto rightNeighbour = indicies.at(rightIndex);
				rightNeighbour->value += _number->right->value;
			}
			if (indicies.count(leftIndex) > 0) {
				auto leftNeighbour = indicies.at(leftIndex);
				leftNeighbour->value += _number->left->value;
			}
			delete _number->left;
			delete _number->right;
			_number->left = nullptr;
			_number->right = nullptr;
			_number->type = SnailFishNumber::Type::Leaf;
			_number->value = 0;

			return true;
		}
		else {
			if (recurseExplode(_root, _number->left)) {
				return true;
			}
			if (recurseExplode(_root, _number->right)) {
				return true;
			}
		}
		return false;
	}

	bool recurseSplit(const SnailFishNumber* _root, SnailFishNumber* _number) {
		if (_number == nullptr) {
			return false;
		}
		
		if (_number->type == SnailFishNumber::Type::Leaf &&
			_number->value >= 10) {

			auto splitLeft = new SnailFishNumber();
			splitLeft->parent = _number;
			splitLeft->type = SnailFishNumber::Type::Leaf;
			splitLeft->value = _number->value / 2;
			splitLeft->depth = _number->depth + 1;
			auto splitRight = new SnailFishNumber();
			splitRight->parent = _number;
			splitRight->type = SnailFishNumber::Type::Leaf;
			splitRight->value = _number->value / 2;
			splitRight->depth = _number->depth + 1;
			if (splitLeft->value + splitRight->value != _number->value) {
				splitRight->value++;
			}
			assert(splitLeft->value + splitRight->value == _number->value);
			_number->type = SnailFishNumber::Type::Node;
			_number->left = splitLeft;
			_number->right = splitRight;

			return true;
		}
		if (recurseSplit(_root, _number->left)) {
			return true;
		}
		if (recurseSplit(_root, _number->right)) {
			return true;
		}
		return false;
	}

	std::pair<bool, SnailFishNumber*> Day18Puzzle::explode(SnailFishNumber* _number) {
		SnailFishNumber* root = _number;

		bool exploded = recurseExplode(root, _number);

		return { exploded ,root };
	}

	std::pair<bool, SnailFishNumber*> Day18Puzzle::split(SnailFishNumber* _number) {
		SnailFishNumber* root = _number;

		bool split = recurseSplit(root, _number);

		return { split, root };
	}

	SnailFishDecimal Day18Puzzle::magnitude(SnailFishNumber* _number) {
		if (_number->type == SnailFishNumber::Type::Leaf) {
			return _number->value;
		}

		return 3 * magnitude(_number->left) + 2 * magnitude(_number->right);
	}

	SnailFishNumber* Day18Puzzle::reduce(SnailFishNumber* _number) {

		SnailFishNumber* current = _number;
		while (true) {
			std::string rendered = current->render();
			auto [exploded, explodedNumber] = explode(current);
			if (exploded) {
				//std::cout << "x " << explodedNumber->render() << std::endl;
				current = explodedNumber;
				recurseAssignDepths(current, 0);
				continue;
			}
			auto [splitted, splitNumber] = split(current);
			if (splitted) {
				//std::cout << "s " << splitNumber->render() << std::endl;
				recurseAssignDepths(current, 0);
				return reduce(splitNumber);
			}
			if (!splitted) {
				break;
			}
		}

		return current;
	}
}
