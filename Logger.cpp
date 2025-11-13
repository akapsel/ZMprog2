#include "Logger.h"
#include <iostream>

Logger& Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string& wpis)
{
    historia.push_back(wpis);
}

void Logger::PrintHistory() const
{
    std::cout << "\n=== Historia dzialan ===\n";

    if (historia.empty())
    {
        std::cout << "Brak wpisow w historii.\n";
        return;
    }

    for (const auto& w : historia)
        std::cout << w << "\n";
}
