#pragma once

// Logger.h ///////////////////////
// F-25 ENGINE / Logging system   |___________________________________________.
//   Example of an object oriented logging system.                            |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

#include "Common.h"

enum LogLevel
{
    TRACE,
    INFO,
    ERROR,
    WARNING,
    FATAL,
    NUM_LEVELS
};

class Logger
{
    FILE *logs[NUM_LEVELS];

public:
    bool filter[NUM_LEVELS];
    bool logToConsole;
    bool logToFile;

    Logger()
    {
        static const char *logPaths[] = {
            "logs/trace.log",
            "logs/info.log",
            "logs/error.log",
            "logs/warning.log",
            "logs/fatal.log"};

        for (int32_t i = 0; i < LogLevel::NUM_LEVELS; i++)
        {
            errno = 0;
            logs[i] = fopen(logPaths[i], "w");
            if (logs[i] == nullptr)
            {
                printf("Failed opening file %s : errno=%d\n", logPaths[i], errno);
            }
        }

        logToConsole = true;
        logToFile = true;
    }

    void Log(LogLevel level, const char *msg)
    {
        if (filter[level])
        {
            return;
        }
        if (logToFile)
        {
            if (logs[level] != nullptr)
            {
                fprintf(logs[level], "[%4f]> %s \n", GetTime(), msg);
            }
        }
        if (logToConsole)
        {
            printf("[%4f]> %s \n", GetTime(), msg);
        }
    }

    ~Logger()
    {
        for (int32_t i = 0; i < LogLevel::NUM_LEVELS; i++)
        {
            if (logs[i] != nullptr)
            {
                fclose(logs[i]);
            }
            logs[i] = nullptr;
        }
    }
};