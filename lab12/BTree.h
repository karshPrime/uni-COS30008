
// COS30008, Tutorial 12, 2024

#pragma once

#include <memory>
#include <cassert>
#include <iostream>

#include "Visitors.h"

template<typename T>
class BTree
{
public:
    using Node = std::unique_ptr<BTree>;

    BTree(const T& aKey = T{}) noexcept:
        fKey(aKey)
    {}

    BTree( T&& aKey ) noexcept:
        fKey(std::move(aKey))
    {}
    
    ~BTree()
    {
        std::cout << "Delete " << fKey << std::endl;
    }
    
    template<typename... Args>
    static Node makeNode(Args&&... args)
    // has to return aNode
    // makeNode -> create a heap object
    // use the argument with proper consutructure
    // we will use 'make_unique' method
    // we use the templateT explicitly
    {
        return std::make_unique<BTree>(std::forward<Args>(args)...);
    }

    // copy semantics
    BTree(const BTree& aOther) :
        fKey(aOther.fKey)
    {
        if (aOther.fLeft)
        {
            fLeft = std::move(makeNode(*aOther.fLeft));
        }

        if (aOther.fRight)
        {
            fRight = std::move(makeNode(*aOther.fRight));
        }
    }

    BTree& operator=(const BTree& aOther)
    {
        if ( this != &aOther )
        {
            this->BTree();

            new (this) BTree (aOther);
        }
        return *this;
    }

    // move semantics
    BTree(BTree&& aOther) noexcept
    {
        //
    }

    BTree& operator=(BTree&& aOther) noexcept;

    void swap(BTree& aOther) noexcept
    {
        std::swap(fLeft, aOther.fLeft);
        std::swap(fKey, aOther.fKey);
        std::swap(fRight, aOther.fRight);
    }

    const T& operator*() const noexcept
    {
        return fKey;
    }

    bool hasLeft() const noexcept
    {
        return fLeft ? true : false;
    }

    BTree& left() const
    {
        assert(fLeft);
        return *fLeft;
    }

    bool hasRight() const noexcept
    {
        return fRight ? true : false;
    }

    BTree& right() const
    {
        assert(fRight);
        return *fRight;
    }

    void attachLeft(Node& aNode)
    {
        assert(!fLeft);

        fLeft = std::move(aNode);
    }

    void attachRight(Node& aNode)
    {
        assert(!fRight);
        fRight = std::move(aNode);
    }

    Node detachLeft()
    {
        assert(fLeft);
        return std::move(fLeft);
    }

    Node detachRight()
    {
        assert(fRight);
        return std::move(fRight);
    }
    
    bool leaf() const noexcept
    {
        // no subtress; the sub-nodes = leaf
        return !fLeft && !fRight;
    }

    size_t height() const noexcept
    {
        size_t Result = 0;

        if (!leaf())
        {
            Result = std::max(fLeft ? fLeft->height() + 1 : 0),
                             (fRight ? fRight->height() + 1 : 0);
        }
    }

    const T& findMax() const noexcept;

    const T& findMin() const noexcept;
    
    void doDepthFirstSearch(const TreeVisitor<T>& aVisitor) const noexcept
    {
        aVisitor.preVisit(**this);

        if (hasLeft())
        {
            left().doDepthFirstSearch(aVisitor);
        }

        aVisitor.inVisit(**this);

        if (hasRight())
        {
            right().doDepthFirstSearch(aVisitor);
        }

        aVisitor.postVisit(**this);
    }

private:
    T fKey;
    Node fLeft;
    Node fRight;
};
