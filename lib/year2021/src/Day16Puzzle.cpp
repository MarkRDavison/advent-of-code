#include <2021/Day16Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>

constexpr DecimalType SUM = 0;
constexpr DecimalType PRODUCT = 1;
constexpr DecimalType MIN = 2;
constexpr DecimalType MAX = 3;
constexpr DecimalType GRT = 5;
constexpr DecimalType LST = 6;
constexpr DecimalType EQL = 7;

namespace TwentyTwentyOne {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Packet Decoder", 2021, 16) {
	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	DecimalType recurseSumVersions(const DecodedPacket& _packet) {
		DecimalType total = _packet.version;
		for (const auto& sp : _packet.subPackets) {
			total += recurseSumVersions(sp);
		}
		return total;
	}
	DecimalType recurseCalculateValue(const DecodedPacket& _packet) {
		if (_packet.typeId == 4) {
			return _packet.number;
		}

		DecimalType value = 0;

		switch (_packet.typeId) {
		case SUM:
			return std::accumulate(_packet.subPackets.begin(), _packet.subPackets.end(), (DecimalType)0,
				[](DecimalType _accumulate, const DecodedPacket& _subPacket) -> DecimalType {
					return _accumulate + recurseCalculateValue(_subPacket);
				});
		case PRODUCT:
			return std::accumulate(_packet.subPackets.begin(), _packet.subPackets.end(), (DecimalType)1,
				[](DecimalType _accumulate, const DecodedPacket& _subPacket) -> DecimalType {
					return _accumulate * recurseCalculateValue(_subPacket);
				});
		case MIN:
			return std::ranges::min(_packet.subPackets
				| std::views::transform(
					[](const DecodedPacket& _subPacket) -> DecimalType {
						return recurseCalculateValue(_subPacket);
					}));
		case MAX:
			return std::ranges::max(_packet.subPackets
				| std::views::transform(
					[](const DecodedPacket& _subPacket) -> DecimalType {
						return recurseCalculateValue(_subPacket);
					}));
		case GRT:
		{
			assert(_packet.subPackets.size() == 2);
			return recurseCalculateValue(_packet.subPackets[0]) > recurseCalculateValue(_packet.subPackets[1]);
		}
		case LST:
		{
			assert(_packet.subPackets.size() == 2);
			return recurseCalculateValue(_packet.subPackets[0]) < recurseCalculateValue(_packet.subPackets[1]);
		}
		case EQL:
		{
			assert(_packet.subPackets.size() == 2);
			return recurseCalculateValue(_packet.subPackets[0]) == recurseCalculateValue(_packet.subPackets[1]);
		}
		}

		return value;
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		const std::string hex = m_InputLines[0];		

		const auto decoded = decode(hexToBin(hex));

		const auto part1 = recurseSumVersions(decoded);
		const auto part2 = recurseCalculateValue(decoded);

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::string Day16Puzzle::hexToBin(const std::string& _hex) {
		const std::unordered_map<char, std::string> hexToBin = {
			{'0', "0000"},
			{'1', "0001"},
			{'2', "0010"},
			{'3', "0011"},
			{'4', "0100"},
			{'5', "0101"},
			{'6', "0110"},
			{'7', "0111"},
			{'8', "1000"},
			{'9', "1001"},
			{'A', "1010"},
			{'B', "1011"},
			{'C', "1100"},
			{'D', "1101"},
			{'E', "1110"},
			{'F', "1111"},
		};
		std::string bits;
		for (const auto& c : _hex) {
			bits += hexToBin.at(c);
		}
		return bits;
	}
	DecodedPacket Day16Puzzle::decode(const std::string& _binary) {
		DecodedPacket packet;
		
		packet.version = std::stoll(_binary.substr(0, 3), nullptr, 2);
		packet.typeId = std::stoll(_binary.substr(3, 3), nullptr, 2);

		if (packet.typeId == 4) {
			// Literal
			std::string number;

			for (std::size_t i = 6; i < _binary.size(); i += 5) {
				const auto control = _binary[i];
				number += _binary.substr(i + 1, 4);
				if (control != '1') {
					packet.bitLength = i + 4 + 1;
					break;
				}
			}

			packet.number = std::stoll(number, nullptr, 2);
		}
		else {
			const std::size_t  lengthType = _binary[6] == '0' ? 15u : 11u;
			std::size_t subPacketIndex = 7 + lengthType;
			if (_binary[6] == '0') {
				const auto subPacketLength = _binary.substr(7, lengthType);
				const auto totalLengthInBitsOfSubPackets = std::stoll(subPacketLength, nullptr, 2);

				while (subPacketIndex < 7 + lengthType + totalLengthInBitsOfSubPackets) {
					const auto subPacket = _binary.substr(subPacketIndex);
					const auto& decoded = packet.subPackets.emplace_back(decode(subPacket));
					subPacketIndex += decoded.bitLength;
				}

				packet.bitLength = subPacketIndex;
			}
			else {
				const auto subPacketCount = _binary.substr(7, lengthType);
				const auto numberOfSubPackets = std::stoll(subPacketCount, nullptr, 2);

				for (int i = 0; i < numberOfSubPackets; ++i) {
					const auto subPacket = _binary.substr(subPacketIndex);
					const auto& decoded = packet.subPackets.emplace_back(decode(subPacket));
					subPacketIndex += decoded.bitLength;
				}

				packet.bitLength = subPacketIndex;
			}

		}

		return packet;
	}
}
