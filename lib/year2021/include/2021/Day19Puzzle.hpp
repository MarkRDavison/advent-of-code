#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_19_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_19_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector3.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentyTwentyOne {
	using BeaconDecimal = long;

	template<typename T>
	struct vector3_hash_fxn {
		std::size_t operator()(const Vector3<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y) ^ std::hash<T>()(_vec.z);
		}
	};

	struct ParsedBeaconData {
		BeaconDecimal scannerNumber{ 0 };
		std::vector<Vector3<BeaconDecimal>> beacons;
	};

	struct FixedBeaconData {
		std::unordered_set<Vector3<BeaconDecimal>, vector3_hash_fxn<BeaconDecimal>> beacons;
		std::unordered_map<BeaconDecimal, std::vector<Vector3<BeaconDecimal>>> beaconsFixedPerScanner;
		std::unordered_map<BeaconDecimal, Vector3<BeaconDecimal>> scanners;
	};

	class Day19Puzzle : public core::PuzzleBase {
	public:
		Day19Puzzle();
		~Day19Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<ParsedBeaconData> parse(const std::vector<std::string>& _inputLines);

		static bool areRelativelySame(BeaconDecimal _scannerNumber, BeaconDecimal _threshold, FixedBeaconData& _data, const std::vector<Vector3<BeaconDecimal>>& _lhs, const std::vector<Vector3<BeaconDecimal>>& _tester);


	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_19_PUZZLE_HPP_