#include <2022/Day18Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector4.hpp>
#include <cassert>
#include <queue>
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

	using CoordSet = std::unordered_set<ze::Vector3i, vector3_hash_fxn_TODO_CORE_ME3<int>>;
	using CoordSet4 = std::unordered_set<ze::Vector4i, vector4_hash_fxn_TODO_CORE_ME3<int>>;

	std::vector<ze::Vector3i> neighbours(const ze::Vector3i& _c)
	{
		std::vector<ze::Vector3i> n;
		n.push_back(_c + ze::Vector3i(+1, +0, +0));
		n.push_back(_c + ze::Vector3i(-1, +0, +0));
		n.push_back(_c + ze::Vector3i(+0, +1, +0));
		n.push_back(_c + ze::Vector3i(+0, -1, +0));
		n.push_back(_c + ze::Vector3i(+0, +0, +1));
		n.push_back(_c + ze::Vector3i(+0, +0, -1));
		return n;
	}

	bool inRange(const ze::Vector3i& _c, const ze::Vector3i& _min, const ze::Vector3i& _max)
	{
		return !(
			_c.x < _min.x || _max.x < _c.x ||
			_c.y < _min.y || _max.y < _c.y ||
			_c.z < _min.z || _max.z < _c.z
		);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {

		std::unordered_map<std::string, int> faces;
		CoordSet coordsSet;
		std::vector<ze::Vector3i> coords;

		ze::Vector3i min;
		ze::Vector3i max;

		for (const auto& l : m_InputLines)
		{
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, ",");

			ze::Vector3i coord = {
				std::stoi(p[0]),
				std::stoi(p[1]),
				std::stoi(p[2])
			};
			coords.push_back(coord);
			coordsSet.insert(coord);

			min.x = std::min(min.x, coord.x);
			max.x = std::max(max.x, coord.x);
			min.y = std::min(min.y, coord.y);
			max.y = std::max(max.y, coord.y);
			min.z = std::min(min.z, coord.z);
			max.z = std::max(max.z, coord.z);

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


		constexpr const int MARGIN = 2;

		int part2 = 0;

		ze::Vector3i start = { min.x - 1, min.y - 1, min.z - 1 };

		ze::Vector3i minimumRange = min - ze::Vector3i(MARGIN, MARGIN, MARGIN);
		ze::Vector3i maximumRange = max + ze::Vector3i(MARGIN, MARGIN, MARGIN);

		CoordSet seen;
		std::queue<ze::Vector3i> queue;
		queue.push(start);

		CoordSet4 surface;
		while (!queue.empty())
		{
			const auto current = queue.front();
			queue.pop();

			{	// TOP
				const auto n = current + ze::Vector3i(+0, +1, +0);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 0));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
			{	// BOTTOM
				const auto n = current + ze::Vector3i(+0, -1, +0);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 1));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
			{	// LEFT
				const auto n = current + ze::Vector3i(-1, +0, +0);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 2));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
			{	// RIGHT
				const auto n = current + ze::Vector3i(+1, +0, +0);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 3));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
			{	// IN
				const auto n = current + ze::Vector3i(+0, +0, -1);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 4));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
			{	// OUT
				const auto n = current + ze::Vector3i(+0, +0, +1);
				if (coordsSet.contains(n))
				{
					surface.insert(ze::Vector4i(n, 5));
				}
				else {
					if (!seen.contains(n) && inRange(n, minimumRange, maximumRange))
					{
						seen.insert(n);
						queue.push(n);
					}
				}
			}
		}

		return { std::to_string(part1), std::to_string(surface.size()) };
	}
}
