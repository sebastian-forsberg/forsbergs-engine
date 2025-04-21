#pragma once

// ProfileTimer.h /////////////////
// F-25 ENGINE / Simple Timer     |___________________________________________.
//   A simple timer for automated instrumentation based profiling.            |
///////////////////////////////////////////////////////////////////////////////

#include "Common.h"
#include "Logger.h"

class ProfileTimer
{
    double started;
    const char *label;
    Logger *logger;

public:
    ProfileTimer(Logger *logger, const char *label) : started{GetTime()}, label{label}, logger{logger}
    {
        char msg[64];
        snprintf(msg, 64, "%s started at %f", label, started);
        logger->Log(INFO, msg);
    }

    ~ProfileTimer()
    {
        char msg[64];
        snprintf(msg, 64, "%s terminated: took %f", label, GetTime() - started);
        logger->Log(INFO, msg);
    }
};