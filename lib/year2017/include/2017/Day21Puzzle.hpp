#ifndef INCLUDED_ADVENT_OF_CODE_2017_DAY_21_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2017_DAY_21_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <unordered_map>

namespace TwentySeventeen {

	struct Grid : std::vector<std::string> {

		std::string hash() const {
			std::string h;

			for (std::size_t i = 0; i < this->size(); ++i) {
				h += this->at(i) + "/";
			}

			return h.substr(0, h.size() - 1);
		}
	};

	struct Recipe {
		Grid src;
		Grid dst;
	};

	using RecipeBook = std::unordered_map<std::string, std::string>;
	using Art = core::Region<char>;

	class Day21Puzzle : public core::PuzzleBase {
	public:
		Day21Puzzle();
		~Day21Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::string fastSolve(std::size_t _iter);
		void printArt(Art& _art);
		Art solveForIter(std::size_t _iter);

		static Grid flip(const Grid& _grid);
		static Grid mirror(const Grid& _grid);
		static Grid rotate(const Grid& _grid);
		static Grid rotate(const Grid& _grid, std::size_t _iters);


	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2017_DAY_21_PUZZLE_HPP_