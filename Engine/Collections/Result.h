#pragma once

// Result.h //////////////////////////
// F-25 ENGINE / Core Data Structure |________________________________________.
//   Written as part of an example engine for students attending Forsbergs    |
// school. Optimized for clarity and demonstrative purposes, not performance. |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

template <typename T>
struct Result
{
    T data;
    bool valid;

    static Result<T> Ok(const T &val)
    {
        return {val, true};
    }

    static Result<T> Invalid()
    {
        return {T(), false};
    }
};