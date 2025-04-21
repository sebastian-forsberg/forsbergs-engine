#pragma once

// LinkedList.h //////////////////////
// F-25 ENGINE / Core Data Structure |________________________________________.
//   Written as part of an example engine for students attending Forsbergs    |
// school. Optimized for clarity and demonstrative purposes, not performance. |
///////////////////////////////////////////////////////////////////////////////

#include "Result.h"

template <typename T>
struct Node
{
    T data;
    Node<T> *next;
};

template <typename T>
class LinkedList
{
    Node<T> *head;
    int32_t count;

public:
    int32_t Count() const
    {
        return count;
    }

    // Get the index of the node that contains the provided data.
    // T must either be a primitive or implement == operator.
    int32_t GetIndexOf(const T &item)
    {
        Node<T> *itr = head;
        int32_t index = 0;
        while (itr != nullptr)
        {
            if (itr->data == item)
            {
                return index;
            }
            itr = itr->next;
            index++;
        }
        return -1;
    }

    // Return the data at the index wrapped in a Result.
    Result<T> GetDataAt(int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return Result<T>::Invalid();
        }
        Node<T> *itr = head;
        for (int i = 0; i < index; i++)
        {
            itr = itr->next;
        }
        return Result<T>::Ok(itr->data);
    }

    // Replaces the data at the provided index.
    // Returns false if provided index is out of bounds. [DESTRUCTIVE]
    bool ReplaceDataAt(const T &item, int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }
        Node<T> *itr = head;
        for (int i = 0; i < index; i++)
        {
            itr = itr->next;
        }
        itr->data = item;
        return true;
    }

    // Insert node at the head of list. [DESTRUCTIVE]
    void InsertFirst(const T &item)
    {
        head = new Node<T>{item, head};
        count++;
    }

    // Insert node at tail of list. [DESTRUCTIVE]
    void InsertLast(const T &item)
    {
        if (head == nullptr)
        {
            InsertFirst(item);
            return;
        }
        Node<T> *tail = head;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }
        tail->next = new Node<T>{item, nullptr};
        count++;
    }

    // Insert node after provided index. [DESTRUCTIVE]
    bool InsertAfter(const T &item, int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return false;
        }
        if (index == count - 1)
        {
            InsertLast(item);
            return true;
        }
        Node<T> *target = head;
        for (int i = 0; i < index; i++)
        {
            target = target->next;
        }
        target->next = new Node<T>{item, target->next};
        count++;
        return true;
    }

    // Insert node before provided index. [DESTRUCTIVE]
    bool InsertBefore(const T &item, int32_t index)
    {
        if (index == 0)
        {
            InsertFirst(item);
            return true;
        }
        return InsertAfter(item, index - 1);
    }

    // Removes the head of the list (index 0).
    // Returns the removed data wrapped in a result so you can use
    // it like a stack. [DESTRUCTIVE]
    Result<T> RemoveFirst()
    {
        if (head == nullptr)
        {
            return Result<T>::Invalid();
        }
        Node<T> *oldHead = head;
        T data = oldHead->data;
        head = head->next;
        delete oldHead;
        count--;
        return Result<T>::Ok(data);
    }

    // Removes the tail of the list (index count).
    // Returns the removed data wrapped in a result so you can use
    // it like a queue. [DESTRUCTIVE]
    Result<T> RemoveLast()
    {
        if (head == nullptr)
        {
            return Result<T>::Invalid();
        }
        if (head->next == nullptr)
        {
            return RemoveFirst(); // Only one element
        }

        Node<T> *prev = head;
        while (prev->next->next != nullptr)
        {
            prev = prev->next;
        }
        T data = prev->next->data;
        delete prev->next;
        prev->next = nullptr;
        count--;
        return Result<T>::Ok(data);
    }

    // Removes the node at the provided index.
    // Returns the removed data wrapped in a result. [DESTRUCTIVE]
    Result<T> RemoveAt(int32_t index)
    {
        if (index < 0 || index >= count)
        {
            return Result<T>::Invalid();
        }
        if (index == 0)
        {
            return RemoveFirst();
        }

        Node<T> *prev = head;
        for (int i = 0; i < index - 1; i++)
        {
            prev = prev->next;
        }

        Node<T> *target = prev->next;
        T data = target->data;
        prev->next = target->next;
        delete target;
        count--;
        return Result<T>::Ok(data);
    }

    // Remove all nodes. [DESTRUCTIVE]
    void Clear()
    {
        while (head != nullptr)
        {
            Node<T> *next = head->next;
            delete head;
            head = next;
        }
        count = 0;
    }

    LinkedList<T>() : head{nullptr}, count{0} {}

    ~LinkedList<T>()
    {
        Clear();
    }
};