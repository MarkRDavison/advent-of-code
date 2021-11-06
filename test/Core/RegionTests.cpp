#include <catch/catch.hpp>
#include <catch/CatchToString.hpp>
#include <iostream>

namespace core {

	TEST_CASE("ASLKJDHASKJDHASJOHIDA", "[Core][Region]") {
		REQUIRE(1 == 2);
	}

	TEST_CASE("ASLKJDHASKJDHASJOHIDAasdasdsa", "[Core][Region]") {
		ze::Vector2f vec(1.3f, 22.f);
		REQUIRE(ze::Vector2f(1.2f, 22.f) == vec);
	}

}