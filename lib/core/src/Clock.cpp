#include <Core/Clock.hpp>

Clock::Clock()
{
    m_Start = std::chrono::steady_clock::now();
}