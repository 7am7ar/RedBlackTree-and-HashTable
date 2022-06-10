#pragma once

#include <list>

#include "Node.h"

class RedBlackTree
{
public:
	RedBlackTree();
	bool LoadText(std::string fileName);
	bool AddNode(std::string word);
	void BalanceTree(Node* parent);
	void RemoveBalance(Node* deleted);
	bool RemoveNode(std::string word);
	void DeleteNode(Node* nodeToRemove);
	bool Search(std::string word);
	void Clean();
	void Show();
private:
	Node* m_crown;
	int m_nodeQuantity;
};

