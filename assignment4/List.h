
// COS30008, Problem Set 4, 2024
// Utkarsh Ranjan - 102874485

#pragma once

#include <cassert>

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class List
{
    private:
        using Node = typename DoublyLinkedList<T>::Node;

        Node fHead;		// first element
        Node fTail;		// last element
        size_t fSize;	// number of elements

    public:
        using Iterator = DoublyLinkedListIterator<T>;

        List() noexcept :							// default constructor	 (2)
            fHead(nullptr),
            fTail(nullptr),
            fSize(0)
        { }


        // copy semantics ---------------------------------------------------///

        List( const List& aOther ):					// copy constructor		(10)
            fHead(nullptr),
            fTail(nullptr),
            fSize(0)
        { 
            Node lCurrent = aOther.fHead;
            while (lCurrent)
            {
                push_back(lCurrent->fData);
                lCurrent = lCurrent->fNext;
            }
        }

        List& operator=( const List& aOther ) 		// copy assignment      (14)
        {
            if (this != &aOther)
            {
                List buffer(aOther);
                swap(buffer);
            }
            return *this;
        }


        // move semantics ---------------------------------------------------///

        List( List&& aOther ) noexcept :			// move constructor	 	 (4)
            fHead(std::move(aOther.fHead)),
            fTail(std::move(aOther.fTail)),
            fSize(std::move(aOther.fSize))
        { 
            aOther.fHead = nullptr;
            aOther.fTail = nullptr;
            aOther.fSize = 0;
        }

        List& operator=( List&& aOther ) noexcept 	// move assignment		 (8)
        {
            if (this != &aOther)
            {
                swap(aOther);
                aOther.fHead = nullptr;
                aOther.fTail = nullptr;
                aOther.fSize = 0;
            }

            return *this;
        }

        void swap( List& aOther ) noexcept 			// swap elements		 (9)
        {
            std::swap(aOther.fHead, fHead);
            std::swap(aOther.fTail, fTail);
            std::swap(aOther.fSize, fSize);
        }


        // basic operations -------------------------------------------------///

        size_t size() const noexcept 				// list size			 (2)
        {
            return fSize;
        }

        template<typename U>
        void push_front( U&& aData ) 			    // add element at front	(24)
        {
            Node lNew = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
            lNew->fNext = fHead;

            if (fHead)
                fHead->fPrevious = lNew;

            fHead = lNew;
            if (!fTail)
                fTail = lNew;

            ++fSize;
        }

        template<typename U>
        void push_back( U&& aData ) 				// add element at back	(24)
        {
            Node lNew = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));
            lNew->fPrevious = fTail;

            if (fTail)
                fTail->fNext = lNew;

            fTail = lNew;
            if (!fHead)
                fHead = lNew;

            ++fSize;
        }

        void remove( const T& aElement ) noexcept 	// remove element		(36)
        {
            Node lCurrent = fHead;

            while (lCurrent) 
            {
                if (lCurrent->fData == aElement)
                {
                    if (lCurrent == fHead) 
                    {
                        fHead = lCurrent->fNext;
                        if (fHead)
                            fHead->fPrevious.reset();
                    }
                    else if (lCurrent == fTail)
                    {
                        fTail = lCurrent->fPrevious.lock();
                        if (fTail) 
                            fTail->fNext.reset();
                    }
                    else 
                    {
                        lCurrent->isolate();
                    }

                    --fSize;
                    return;
                }
                lCurrent = lCurrent->fNext;
            }
        }

        const T& operator[]( size_t aIndex ) const 	// list indexer			(14)
        {
            assert(aIndex < fSize);

            Node lCurrent = fHead;
            for (size_t i = 0; i < aIndex; ++i)
            {
                lCurrent = lCurrent->fNext;
            }

            return lCurrent->fData;
        }


        // iterator interface -----------------------------------------------///

        Iterator begin() const noexcept 			//						 (4)
        {
            return Iterator(fHead, fTail);
        }

        Iterator end() const noexcept 				//						 (4)
        {
            Iterator iter(fHead, fTail);
            return ++iter.end();
        }

        Iterator rbegin() const noexcept 			//						 (4)
        {
            return Iterator(fHead, fTail).rbegin();
        }

        Iterator rend() const noexcept 				//						 (4)
        {
            Iterator iter(fHead, fTail);
            return --iter.rend();
        }
};

