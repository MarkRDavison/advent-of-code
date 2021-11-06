#include <iostream>
#include <zeno-engine/Core/zeno-engine.h>
#include <zeno-engine/Core/Logger.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <Core/InitialisationInfo.hpp>
#include <Core/PuzzleConstructor.hpp>

int main(int _argc, char** _argv) {
    auto logger = ze::Logger(ze::Severity::Info);
    zeno_engine();

    auto vec = ze::Vector2f(25.3f, 1111.1f);

    logger.log(ze::Severity::Info, std::to_string(vec.x) + "/" + std::to_string(vec.y));



    core::IPuzzleBase* puzzle = core::PuzzleConstructor::createPuzzle(core::InitialisationInfo::parseArguments(_argc, _argv));

    if (puzzle == nullptr) {
        return EXIT_FAILURE;
    }

    //ze::Clock clock;
    std::cout << "Puzzle " << puzzle->getPuzzleYear() << " - Day " << puzzle->getPuzzleDay() << " - " << puzzle->getPuzzleName() << std::endl;

    const std::pair<std::string, std::string>& solution = puzzle->fastSolve();

    std::cout << "Part 1: " << solution.first << std::endl << "Part 2: " << solution.second << std::endl;

    //std::cout << "In " << clock.getElapsedTime() << "s." << std::endl;
    delete puzzle;

    return EXIT_SUCCESS;
}