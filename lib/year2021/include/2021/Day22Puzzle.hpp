#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_22_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_22_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector3.hpp>

namespace TwentyTwentyOne {

	using ReactorNumber = long long;
	using ReactorVector = Vector3<ReactorNumber>;


	struct Cube {
		Cube() {}
		Cube(const ReactorVector& _start, const ReactorVector& _end) : start(_start), end(_end) {

		}
		bool operator==(const Cube& _other) const {
			return start == _other.start && end == _other.end;
		}

		ReactorNumber volume() const {
			return (end.x - start.x + 1) * (end.y - start.y + 1) * (end.z - start.z + 1);
		}

		void sort() {
			if (start.x < end.x) {
				std::swap(start.x, end.x);
			}
			if (start.y < end.y) {
				std::swap(start.y, end.y);
			}
			if (start.z < end.z) {
				std::swap(start.z, end.z);
			}
		}

		ReactorVector start;
		ReactorVector end;
		enum class Action {
			ON, OFF
		} action;
	};


	class Day22Puzzle : public core::PuzzleBase {
	public:
		Day22Puzzle();
		~Day22Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Cube> parse(const std::vector<std::string>& _inputLines);
		static bool cubesIntersect(const Cube& _lhs, const Cube& _rhs, Cube& _intersection);
		static bool cubeInside(const Cube& _lhs, const Cube& _rhs, Cube& _intersection);
		static std::pair<bool, std::vector<Cube>> split(const Cube& _lhs, const Cube& _rhs);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_22_PUZZLE_HPP_