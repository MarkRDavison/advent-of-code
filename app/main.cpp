#include <iostream>
#include <Core/Clock.hpp>
#include <Core/Vector2.hpp>
#include <Core/InitialisationInfo.hpp>
#include <Core/PuzzleConstructor.hpp>
#include <Puzzles2015.hpp>
#include <Puzzles2016.hpp>
#include <Puzzles2017.hpp>
#include <Puzzles2018.hpp>
#include <Puzzles2019.hpp>
#include <Puzzles2020.hpp>
#include <Puzzles2021.hpp>
#include <Puzzles2022.hpp>
#include <Puzzles2023.hpp>

int main(int _argc, char** _argv) {
    REGISTER_YEAR(TwentyFifteen,     2015);
    REGISTER_YEAR(TwentySixteen,     2016);
    REGISTER_YEAR(TwentySeventeen,   2017);
    REGISTER_YEAR(TwentyEighteen,    2018);
    REGISTER_YEAR(TwentyNineteen,    2019);
    REGISTER_YEAR(TwentyTwenty,      2020);
    REGISTER_YEAR(TwentyTwentyOne,   2021);
    REGISTER_YEAR(TwentyTwentyTwo,   2022);
    REGISTER_YEAR(TwentyTwentyThree, 2023);

    std::cout << "2015 - Day 19 DOES NOT WORK" << std::endl;

    core::IPuzzleBase* puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

    if (puzzle == nullptr) {
        return EXIT_FAILURE;
    }

    Clock clock;
    std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

    const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

    std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

    std::cout << "In " << clock.getElapsedTime() << "s." << std::endl;
    delete puzzle;

    getchar();

    return EXIT_SUCCESS;
}