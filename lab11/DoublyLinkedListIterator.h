
// COS30008, Tutorial 11, 2024

#pragma once

#include <cassert>
#include <stdexcept>

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
public:
    using Iterator = DoublyLinkedListIterator<T>;
    using Node = typename DoublyLinkedList<T>::Node;

    enum class States
    {
        BEFORE,
        DATA,
        AFTER
    };
    
    DoublyLinkedListIterator( const Node& aHead, const Node& aTail ) noexcept :
        fHead(aHead),
        fTail(aTail),
        fCurrent(aHead), // put first element in the list
        fState(States::DATA)
    {
        assert (!fHead == !fTail);

        if (!fHead)
        {
            fState = States::AFTER;
        }
    }
    
    const T& operator*() const noexcept
    {
        return fCurrent->fData;
    }
    
    Iterator& operator++() noexcept
    {
        switch (fState)
        {
            case States::BEFORE: 
                fCurrent = fHead;

                if (fCurrent)
                {
                    fState = States::DATA;
                }
                else
                {
                    fState = States::AFTER;
                }

                break;

            case States::DATA:
                fCurrent = fCurrent->fNext;

                if (fCurrent)
                {
                    fState = States::AFTER;
                }
                break;

            case States::AFTER:
                fCurrent = fHead;

                if (fCurrent)
                {
                    fState = States::DATA;
                }
                else 
                {
                    fState = States::BEFORE;
                }

                break;
        }

    }
    
    Iterator operator++(int) noexcept
    {
        Iterator old = *this;

        ++(*this);

        return old;
    }
    
    Iterator& operator--() noexcept
    { }
    
    Iterator operator--(int) noexcept
    {
        Iterator old = *this;

        --(*this);

        return old;
    }

    bool operator==( const Iterator& aOther ) const noexcept
    {
        return 
        fHead == aOther.fHead &&
        fTail == aOther.fTail &&
        fState == aOther.fState &&
        fCurrent == aOther.fCurrent;
    }

    bool operator!=( const Iterator& aOther ) const noexcept
    {
        return !(*this == aOther);
    }
    
    Iterator begin() const noexcept
    {
        return ++(rend());
    }

    Iterator end() const noexcept
    {
        Iterator iter = *this;

        iter.fCurrent = nullptr;
        iter.fState = States::AFTER;

        return iter;
    }
    
    Iterator rbegin() const noexcept
    {
        return --(rend());
    }
    
    Iterator rend() const noexcept
    {
        Iterator iter = *this;

        iter.fCurrent = nullptr;
        iter.fState = States::AFTER;

        return iter;
    }

private:
    Node fHead;
    Node fTail;
    Node fCurrent;
    States fState;
};
