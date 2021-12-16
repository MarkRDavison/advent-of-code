#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

using DecimalType = long long;

struct DecodedPacket {
	DecimalType version;
	DecimalType typeId;
	DecimalType bitLength;
	DecimalType number;

	std::vector<DecodedPacket> subPackets;
};

namespace TwentyTwentyOne {
	
	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::string hexToBin(const std::string& _hex);
		static DecodedPacket decode(const std::string& _binary);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_16_PUZZLE_HPP_