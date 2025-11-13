#pragma once
#include <string>
#include <vector>

class Logger
{
private:
    std::vector<std::string> historia;

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger& GetInstance();

    void Log(const std::string& wpis);
    void PrintHistory() const;
};
#pragma once
