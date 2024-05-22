
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

	BTree(const T& aKey = T{}) noexcept;
	BTree( T&& aKey ) noexcept;
    
	~BTree()
	{
		std::cout << "Delete " << fKey << std::endl;
	}
	
	template<typename... Args>
	static Node makeNode(Args&&... args);

	// copy semantics
	BTree(const BTree& aOther);
	BTree& operator=(const BTree& aOther);

	// move semantics
	BTree(BTree&& aOther) noexcept;
	BTree& operator=(BTree&& aOther) noexcept;

	void swap(BTree& aOther) noexcept;

	const T& operator*() const noexcept;
	bool hasLeft() const noexcept;
	BTree& left() const;
	bool hasRight() const noexcept;
	BTree& right() const;

	void attachLeft(Node& aNode);
	void attachRight(Node& aNode);

	Node detachLeft();
	Node detachRight();
    
	bool leaf() const noexcept;
	size_t height() const noexcept;

	const T& findMax() const noexcept;
	const T& findMin() const noexcept;
    
	void doDepthFirstSearch(const TreeVisitor<T>& aVisitor) const noexcept;

private:
	T fKey;
	Node fLeft;
	Node fRight;
};
