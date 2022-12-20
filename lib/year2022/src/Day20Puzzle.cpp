#include <2022/Day20Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <iterator>
#include <algorithm>

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
        int64_t index;
        int64_t value;

        bool operator==(const Node& _rhs) const {
            return this->index == _rhs.index && this->value == _rhs.value;
        }
    };

    using NodeList = std::vector<Node>;

    int64_t safeModulus(int64_t _a, int64_t _b) { return (_a % _b + _b) % _b; }

    void moveNode(NodeList& _nodeList, const Node& _node) {
        auto it = std::find(_nodeList.begin(), _nodeList.end(), _node);
        auto value = std::distance(_nodeList.begin(), it) + _node.value;
        auto size = _nodeList.size() - 1;
        auto pos = safeModulus(value, size);

        _nodeList.erase(it);
        _nodeList.insert(_nodeList.begin() + pos, _node);
    }

    int64_t getNthFromZero(const NodeList& _nodeList, int64_t _zeroIndex, int64_t _index) {
        return _nodeList[(_index + _zeroIndex) % _nodeList.size()].value;
    };

    int64_t getThousandsSum(const NodeList& _nodeList) {
        auto zeroLocation = std::find_if(_nodeList.begin(), _nodeList.end(),
            [](auto& num) {
                return num.value == 0;
            });

        auto zero_pos = std::distance(_nodeList.begin(), zeroLocation);

        return
            getNthFromZero(_nodeList, zero_pos, 1000) +
            getNthFromZero(_nodeList, zero_pos, 2000) +
            getNthFromZero(_nodeList, zero_pos, 3000);
    }

    NodeList applyMixing(const NodeList& _nodeList, const NodeList& _unmixedNodeList)
    {
        auto mixed(_nodeList);

        for (auto& num : _unmixedNodeList) {
            moveNode(mixed, num);
        }

        return mixed;
    }


	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
        constexpr int64_t DecryptionKey = 811589153;

        NodeList nodeList;

        int i = 0;
        std::string line;
        for (const auto& l : m_InputLines)
        {
            nodeList.push_back(Node
            { 
                .index = i++, 
                .value = std::stoi(l) 
            });
        }

        auto part_1 = getThousandsSum(applyMixing(nodeList, nodeList));

        for (auto& num : nodeList) {
            num.value *= DecryptionKey;
        }

        auto part2Mixed(nodeList);
        for (int i = 0; i < 10; ++i) {
            part2Mixed = applyMixing(part2Mixed, nodeList);
        }

        auto part_2 = getThousandsSum(part2Mixed);

		return { std::to_string(part_1), std::to_string(part_2) };
	}
}
