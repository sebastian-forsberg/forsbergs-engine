#pragma once

// DynArray.h ////////////////////////
// F-25 ENGINE / Core Data Structure |________________________________________.
//   Written as part of an example engine for students attending Forsbergs    |
// school. Optimized for clarity and demonstrative purposes, not performance. |
///////////////////////////////////////// (c)opyright sebastian jensen / 2025 /

#include <stdlib.h>
#include "Result.h"

template <typename T>
class DynArray
{
    T *data;
    int32_t capacity;
    int32_t count;

public:
    int32_t Count() const
    {
        return count;
    }

    int32_t GetIndexOf(const T &item)
    {
        for (int itr = 0; itr < count; itr++)
        {
            if (data[itr] == item)
            {
                return itr;
            }
        }
        return -1;
    }

    Result<T> GetDataAt(int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return Result<T>::Invalid();
        }
        return Result<T>::Ok(data[index]);
    }

    bool ReplaceDataAt(const T &item, int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }
        data[index] = item;
        return true;
    }

    void InsertLast(const T &item)
    {
        if (count == capacity)
        {
            capacity = capacity * 2;
            data = (T *)realloc(data, capacity * sizeof(T));
        }
        data[count] = item;
        count++;
    }

    void InsertAt(const T &item, int32_t index)
    {
        if (count == capacity)
        {
            capacity = capacity * 2;
            data = (T *)realloc(data, capacity);
        }
        for (int32_t itr = count; itr > index; itr--)
        {
            data[itr] = data[itr - 1];
        }
        data[index] = item;
        count++;
    }

    void InsertFirst(const T &item)
    {
        InsertAt(item, 0);
    }

    Result<T> RemoveFirst()
    {
        if (count == 0)
            return Result<T>::Invalid();
        T removed = data[0];
        for (int i = 1; i < count; i++)
        {
            data[i - 1] = data[i];
        }
        count--;
        return Result<T>::Ok(removed);
    }

    Result<T> RemoveLast()
    {
        if (count == 0)
            return Result<T>::Invalid();
        count--;
        return Result<T>::Ok(data[count]);
    }

    void Clear()
    {
        count = 0;
    }

    DynArray(int32_t initialSize = 16) : count{0}, capacity{initialSize}
    {
        data = (T *)malloc(initialSize * sizeof(T));
    }

    ~DynArray()
    {
        free(data);
    }
};