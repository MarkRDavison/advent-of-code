#include <iostream>
#include <nlohmann/json.hpp>
#include <zeno-engine/Core/zeno-engine.h>
#include <zeno-engine/Core/Logger.hpp>
#include <zeno-engine/Core/Vector2.hpp>

int main()
{
    nlohmann::json json = {
        {"pi", 3.14},
        {"happy", true},
        {"name", "Kuba"},
        {"nothing", nullptr},
        {"answer", {
            {"everything", 42}
        }},
        {"list", {1, 2, 3}},
        {"object", {
            {"currency", "PLN"},
            {"value", 100.0}
        }}
    };

    auto logger = ze::Logger(ze::Severity::Info);
    logger.log(ze::Severity::Info, json.dump());
    zeno_engine();

    auto vec = ze::Vector2f(25.3f, 1111.1f);

    logger.log(ze::Severity::Info, std::to_string(vec.x) + "/" + std::to_string(vec.y));
    return 0;
}