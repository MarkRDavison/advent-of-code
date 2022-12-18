#include <2022/Day18Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector4.hpp>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyTwo {

	template<typename T>
	struct vector3_hash_fxn_TODO_CORE_ME3 {
		std::size_t operator()(const ze::Vector3<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y) ^ std::hash<T>()(_vec.z);
		}
	};

	template<typename T>
	struct vector4_hash_fxn_TODO_CORE_ME3 {
		std::size_t operator()(const ze::Vector4<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y) ^ std::hash<T>()(_vec.z) ^ std::hash<T>()(_vec.w);
		}
	};
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Boiling Boulders", 2022, 18) {
	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {

		std::unordered_map<std::string, int> faces;

		for (const auto& l : m_InputLines)
		{
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, ",");

			ze::Vector3i coord = {
				std::stoi(p[0]),
				std::stoi(p[1]),
				std::stoi(p[2])
			};

			const auto left =
				std::to_string(coord.x-1) + "-" +
				std::to_string(coord.y) + "-" +
				std::to_string(coord.z) + "-x";

			const auto right =
				std::to_string(coord.x) + "-" +
				std::to_string(coord.y) + "-" +
				std::to_string(coord.z) + "-x";

			const auto up =
				std::to_string(coord.x) + "-" +
				std::to_string(coord.y-1) + "-" +
				std::to_string(coord.z) + "-y";

			const auto down =
				std::to_string(coord.x) + "-" +
				std::to_string(coord.y) + "-" +
				std::to_string(coord.z) + "-y";

			const auto in =
				std::to_string(coord.x) + "-" +
				std::to_string(coord.y) + "-" +
				std::to_string(coord.z-1) + "-z";

			const auto out =
				std::to_string(coord.x) + "-" +
				std::to_string(coord.y) + "-" +
				std::to_string(coord.z) + "-z";

			std::cout << l
				<< "\n\tleft: " << left
				<< "\n\tright: " << right
				<< "\n\tup: " << up
				<< "\n\tdown: " << down
				<< "\n\tin: " << in
				<< "\n\tout: " << out
				<< std::endl;

			faces[left]++;
			faces[right]++;
			faces[up]++;
			faces[down]++;
			faces[in]++;
			faces[out]++;
		}

		int part1 = 0;
		for (const auto& f : faces)
		{
			if (f.second == 1)
			{
				part1++;
			}
		}

		return { std::to_string(part1), "Part 2"};
	}
}
