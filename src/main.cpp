#include <iostream>
#include <zeno-engine/Core/zeno-engine.h>
#include <zeno-engine/Core/Logger.hpp>
#include <zeno-engine/Core/Vector2.hpp>

int main()
{
    auto logger = ze::Logger(ze::Severity::Info);
    zeno_engine();

    auto vec = ze::Vector2f(25.3f, 1111.1f);

    logger.log(ze::Severity::Info, std::to_string(vec.x) + "/" + std::to_string(vec.y));
    return 0;
}