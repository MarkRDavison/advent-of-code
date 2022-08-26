#ifndef INCLUDED_ADVENT_OF_CODE_2016_DAY_22_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_DAY_22_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <unordered_set>

namespace TwentySixteen {

	struct NodeCell {
		bool open{ false };

		bool valid() {
			return open;
		}
		float costTo(const NodeCell& _target) const {
			return 1.0f;
		}
	};

	struct Node {
		int x;
		int y;
		int size;
		int used;
		int avail;
		int usePerc;
	};

	template<typename T>
	struct vector2_hash_fxn {
		std::size_t operator()(const ze::Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};
	
	class Day22Puzzle : public core::PuzzleBase {
	public:
		Day22Puzzle();
		~Day22Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<
			core::Region<Node>, 
			std::unordered_set<ze::Vector2i, vector2_hash_fxn<int>>
		> parse(const std::vector<std::string>& _inputLines);

		static bool viablePair(const Node& _lhs, const Node& _rhs);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_DAY_22_PUZZLE_HPP_