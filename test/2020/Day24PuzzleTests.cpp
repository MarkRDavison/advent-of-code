#include <catch/catch.hpp>
#include <2020/Day24Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 24 Examples work", "[2020][Day24]") {
	    const std::vector<std::string> input = {
			"sesenwnenenewseeswwswswwnenewsewsw",
			"neeenesenwnwwswnenewnwwsewnenwseswesw",
			"seswneswswsenwwnwse",
			"nwnwneseeswswnenewneswwnewseswneseene",
			"swweswneswnenwsewnwneneseenw",
			"eesenwseswswnenwswnwnwsewwnwsene",
			"sewnenenenesenwsewnenwwwse",
			"wenwwweseeeweswwwnwwe",
			"wsweesenenewnwwnwsenewsenwwsesesenwne",
			"neeswseenwwswnwswswnw",
			"nenwswwsewswnenenewsenwsenwnesesenew",
			"enewnwewneswsewnwswenweswnenwsenwsw",
			"sweneswneswneneenwnewenewwneswswnese",
			"swwesenesewenwneswnwwneseswwne",
			"enesenwswwswneneswsenwnewswseenwsese",
			"wnwnesenesenenwwnenwsewesewsesesew",
			"nenewswnwewswnenesenwnesewesw",
			"eneswnwswnwsenenwnwnwwseeswneewsenese",
			"neswnwewnwnwseenwseesewsenwsweewe",
			"wseweeenwnesenwwwswnew"
		};

	    Day24Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("10" == answers.first);
		REQUIRE("2208" == answers.second);
	}

}
