#include <2017/Day07Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentySeventeen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Recursive Circus", 2017, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct TowerNode {
		TowerNode(const std::string& _parentName, const std::string& _name, int _weight) : parentName(_parentName), name(_name), weight(_weight) {}

		const std::string parentName;
		const std::string name;
		const int weight;

		int getTotalWeight() const {
			int sum = weight;

			for (const auto& c : children) {
				sum += c.getTotalWeight();
			}

			return sum;
		}

		std::vector<TowerNode> children;
	};

	TowerNode createRecurse(
		const std::string& _parentName,
		const std::string& _name,
		const std::unordered_map<std::string, std::unordered_set<std::string>>& _relationships,
		const std::unordered_map<std::string, int>& _weights) {

		TowerNode node(_parentName, _name, _weights.at(_name));

		for (const auto& c : _relationships.at(_name)) {
			node.children.emplace_back(createRecurse(node.name, c, _relationships, _weights));
		}

		return node;
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {

		std::unordered_map<std::string, std::unordered_set<std::string>> relationships;
		std::unordered_map<std::string, TowerNode*> towersByName;
		std::unordered_set<std::string> nonRoot;
		std::unordered_map<std::string, int> weights;

		for (const auto& l : m_InputLines) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(l, " ()->,");
			
			auto& relations = relationships[parts[0]];
			weights[parts[0]] = std::stoi(parts[1]);
			for (std::size_t i = 2; i < parts.size(); ++i) {
				relations.insert(parts[i]);
				nonRoot.insert(parts[i]);
				
			}
		}

		std::string part1;

		for (const auto& [k, v] : relationships) {
			if (nonRoot.count(k) == 0) {
				part1 = k;
				break;
			}
		}

		auto root = createRecurse({}, part1, relationships, weights);

		int part2 = 0;

		int siblingWeight = 0;
		auto curr = &root;

		while (true) {
			std::unordered_map<int, int> childrenWeights;
			for (const auto& c : curr->children) {
				childrenWeights[c.getTotalWeight()]++;
			}

			if (childrenWeights.size() == 1) {
				part2 = curr->weight - (curr->getTotalWeight() - siblingWeight);
				break;
			}

			for (auto& c : curr->children) {
				const auto cWeight = c.getTotalWeight();
				if (childrenWeights[cWeight] == 1) {
					curr = &c;
				}
				else {
					siblingWeight = cWeight;
				}
			}

		}


		return { part1, std::to_string(part2)};
	}
}
