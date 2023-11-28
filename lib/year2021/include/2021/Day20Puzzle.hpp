#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_20_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_20_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector2.hpp>
#include <unordered_set>

namespace TwentyTwentyOne {	

	template<typename T>
	struct vector2_hash_fxn {
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};

	class Day20Puzzle : public core::PuzzleBase {
	public:
		Day20Puzzle();
		~Day20Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<std::vector<int>, std::vector<std::vector<int>>> parse(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_20_PUZZLE_HPP_