#include <catch/catch.hpp>
#include <2021/Day16Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 16 decoding packets works", "[2021][Day16]") {
		SECTION("Basic literal packet works") {
			const auto packet = Day16Puzzle::decode(Day16Puzzle::hexToBin("D2FE28"));

			REQUIRE(6 == packet.version);
			REQUIRE(4 == packet.typeId);
			REQUIRE(2021 == packet.number);
			REQUIRE(21 == packet.bitLength);
			REQUIRE(packet.subPackets.empty());
		}
		SECTION("Operator length type id = 0 works") {
			const auto packet = Day16Puzzle::decode(Day16Puzzle::hexToBin("38006F45291200"));

			REQUIRE(1 == packet.version);
			REQUIRE(6 == packet.typeId);
			REQUIRE(49 == packet.bitLength);
			REQUIRE(2 == packet.subPackets.size());
			REQUIRE(10 == packet.subPackets[0].number);
			REQUIRE(20 == packet.subPackets[1].number);
		}
		SECTION("Operator length type id = 1 works") {
			const auto packet = Day16Puzzle::decode(Day16Puzzle::hexToBin("EE00D40C823060"));

			REQUIRE(7 == packet.version);
			REQUIRE(3 == packet.typeId);
			REQUIRE(51 == packet.bitLength);
			REQUIRE(3 == packet.subPackets.size());
			REQUIRE(1 == packet.subPackets[0].number);
			REQUIRE(2 == packet.subPackets[1].number);
			REQUIRE(3 == packet.subPackets[2].number);
		}
	}

	TEST_CASE("Day 16 Examples part 1 work", "[2021][Day16]") {
		const std::vector<std::pair<std::string, int>> part1 = {
			{"8A004A801A8002F478", 16},
			{"620080001611562C8802118E34", 12},
			{"C0015000016115A2E0802F182340", 23},
			{"A0016C880162017C3686B18A3D4780", 31},
		};

		for (const auto& [i, a] : part1) {
			SECTION(i + " works as expected") {
				Day16Puzzle puzzle{};
				puzzle.setVerbose(true);
				puzzle.setInputLines({ i });

				auto answers = puzzle.fastSolve();

				REQUIRE(std::to_string(a) == answers.first);
			}
		}
	}

	TEST_CASE("Day 16 Examples part 2 work", "[2021][Day16]") {
		const std::vector<std::pair<std::string, int>> part2 = {
			{"C200B40A82", 3},
			{"04005AC33890", 54},
			{"880086C3E88112", 7},
			{"CE00C43D881120", 9},
			{"D8005AC2A8F0", 1},
			{"F600BC2D8F", 0},
			{"9C005AC2F8F0", 0},
			{"9C0141080250320F1802104A08", 1},
		};

		for (const auto& [i, a] : part2) {
			SECTION(i + " works as expected") {
				Day16Puzzle puzzle{};
				puzzle.setVerbose(true);
				puzzle.setInputLines({ i });

				auto answers = puzzle.fastSolve();

				REQUIRE(std::to_string(a) == answers.second);
			}
		}
	}

}