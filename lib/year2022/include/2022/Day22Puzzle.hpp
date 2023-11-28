#ifndef INCLUDED_ADVENT_OF_CODE_2022_DAY_22_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2022_DAY_22_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Orientation.hpp>
#include <unordered_map>

namespace TwentyTwentyTwo {

	template<typename T>
	struct vector2_hash_fxn_TODO_CORE_ME4 {
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};

	using Map = std::vector<std::string>;
	using Adjacency = std::unordered_map<Vector2i, std::unordered_map<core::Orientation, Vector2i>, vector2_hash_fxn_TODO_CORE_ME4<int>>;
	using OrientationAdjacency = std::unordered_map<Vector2i, std::unordered_map<core::Orientation, core::Orientation>, vector2_hash_fxn_TODO_CORE_ME4<int>>;

	class Day22Puzzle : public core::PuzzleBase {
	public:
		Day22Puzzle();
		~Day22Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve(int _cubeSize);
		std::pair<std::string, std::string> fastSolve() override;

		static Adjacency processAdjacency2D(const Map& _map);
		static std::pair<Adjacency, OrientationAdjacency> processAdjacency3D(const Map& _map, int _cubeSize, const Vector2i& _startingLocation);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2022_DAY_22_PUZZLE_HPP_