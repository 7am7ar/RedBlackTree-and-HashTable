#include "RedBlackTree.h"

#include <iostream>
#include <fstream>
#include <algorithm>

RedBlackTree::RedBlackTree()
{
	m_nodeQuantity = 0;
	m_crown = nullptr;
}

bool RedBlackTree::LoadText(std::string fileName)
{
	std::ifstream fin(fileName);

	if (fin.is_open())
	{
		std::string currentWord;
		while (!fin.eof())
		{
			fin >> currentWord;
			currentWord.erase(std::remove_if(currentWord.begin(), currentWord.end(), ispunct), currentWord.end());
			AddNode(currentWord);
		}

		fin.close();
		return true;
	}
	else return false;
}

bool RedBlackTree::AddNode(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);

	if (m_nodeQuantity == 0)
	{
		m_nodeQuantity++;
		m_crown = new Node(word);
	}
	else
	{
		Node * currentNode = m_crown;
		bool isAdded = false;

		while (!isAdded)
		{
			// If current node is leaf
			if (currentNode->GetWord().empty())
			{
				// Define color
				Color color = Red;

				Node * left = new Node(currentNode, "Left");
				Node * right = new Node(currentNode, "Right");

				currentNode->SetWord(word);
				currentNode->SetColor(color);

				m_nodeQuantity++;
				BalanceTree(currentNode->GetPrevious());

				return true;
			}
			// If current node is not leaf
			else
			{
				if (word == currentNode->GetWord()) return false;

				if (word < currentNode->GetWord()) currentNode = currentNode->GetNextLeft();
				else currentNode = currentNode->GetNextRight();
			}
		}
	}
}

void RedBlackTree::BalanceTree(Node* parent)
{
	
	if (parent->GetColor() == Black) return;

	//Case 1 or 2
	int caseBalance = -1;

	if (parent->GetParentBrunchDirection() == "Left")
	{
		if (parent->GetPrevious()->GetNextRight()->GetColor() == Red) caseBalance = 1;
		else caseBalance = 2;
	}
	if (parent->GetParentBrunchDirection() == "Right")
	{
		if (parent->GetPrevious()->GetNextLeft()->GetColor() == Red) caseBalance = 1;
		else caseBalance = 2;
	}

	switch (caseBalance)
	{
	case 1:
		parent->GetPrevious()->GetNextLeft()->SetColor(Black);
		parent->GetPrevious()->GetNextRight()->SetColor(Black);
		if (parent->GetPrevious()->GetPrevious() == nullptr)
		{
			parent->GetPrevious()->SetColor(Black);
			return;
		}
		
		parent->GetPrevious()->SetColor(Red);
		BalanceTree(parent->GetPrevious()->GetPrevious());
		break;
	case 2:
	{
		int hasToBeSwapped = -1;

		if (parent->GetParentBrunchDirection() == "Left")
		{
			if (parent->GetNextRight()->GetColor() == Red) hasToBeSwapped = 0;
		}
		if (parent->GetParentBrunchDirection() == "Right")
		{
			if (parent->GetNextLeft()->GetColor() == Red) hasToBeSwapped = 1;
		}

		if (hasToBeSwapped != -1)
		{
			// Added is on the right
			if (hasToBeSwapped == 0)
			{
				Node* temp = parent->GetNextRight()->GetNextLeft();

				parent->GetNextRight()->SetPrevious(parent->GetPrevious());
				parent->SetPrevious(parent->GetNextRight());
				parent->GetPrevious()->SetNextLeft(parent);
				parent = parent->GetPrevious();
				parent->SetParentBrunchDirection("Left");

				parent->GetNextLeft()->SetNextRight(temp);
				temp->SetPrevious(parent->GetNextLeft());
			}
			// Added is on the left
			if (hasToBeSwapped == 1)
			{
				Node* temp = parent->GetNextLeft()->GetNextRight();

				parent->GetNextLeft()->SetPrevious(parent->GetPrevious());
				parent->SetPrevious(parent->GetNextLeft());
				parent->GetPrevious()->SetNextRight(parent);
				parent = parent->GetPrevious();
				parent->SetParentBrunchDirection("Right");

				parent->GetNextRight()->SetNextLeft(temp);
				temp->SetPrevious(parent->GetNextRight());
			}
		}
	}
	// Continue with case 3
	case 3:
	{
		// Left case
		if (parent->GetNextLeft()->GetColor() == Red)
		{
			Node* temp = parent->GetNextRight();
			temp->SetParentBrunchDirection("Left");

			parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
			parent->SetNextRight(parent->GetPrevious());
			parent->SetPrevious(parent->GetPrevious()->GetPrevious());
			parent->GetNextRight()->SetPrevious(parent);
			parent->GetNextRight()->SetNextLeft(temp);
			temp->SetPrevious(parent->GetNextRight());
			parent->GetNextRight()->SetParentBrunchDirection("Right");

			parent->SetColor(Black);
			parent->GetNextRight()->SetColor(Red);
		}
		// Right case
		else
		{
			Node* temp = parent->GetNextLeft();
			temp->SetParentBrunchDirection("Right");

			parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
			parent->SetNextLeft(parent->GetPrevious());
			parent->SetPrevious(parent->GetPrevious()->GetPrevious());
			parent->GetNextLeft()->SetPrevious(parent);
			parent->GetNextLeft()->SetNextRight(temp);
			temp->SetPrevious(parent->GetNextLeft());
			parent->GetNextLeft()->SetParentBrunchDirection("Left");


			parent->SetColor(Black);
			parent->GetNextLeft()->SetColor(Red);
		}

		if (parent->GetPrevious() == nullptr) m_crown = parent;
		else
		{
			if (parent->GetParentBrunchDirection() == "Left")
				parent->GetPrevious()->SetNextLeft(parent);
			else 
				parent->GetPrevious()->SetNextRight(parent);
		}
	}
		break;
	}
}

bool RedBlackTree::Search(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);

	if (m_nodeQuantity == 0)
	{
		return false;
	}
	else
	{
		Node * currentNode = m_crown;
		bool isFound = false;

		while (!isFound)
		{
			// If current node is leaf
			if (currentNode->GetWord().empty())
			{
				return false;
			}
			// If current node is not leaf
			else
			{
				if (word == currentNode->GetWord())
				{
					return true;
				}
				else
				{
					if (word < currentNode->GetWord()) currentNode = currentNode->GetNextLeft();
					else currentNode = currentNode->GetNextRight();
				}
			}
		}
	}
}

void RedBlackTree::Clean()
{
	if (m_nodeQuantity == 0) return;
	m_crown->CleanBrunch();
	m_nodeQuantity = 0;
}

void RedBlackTree::Show()
{
	if (m_nodeQuantity == 0)
	{
		std::cout << "Dictionary is empty.\n";
		return;
	}
	int count = 0;
	m_crown->ShowBrunch(0, count);
}

bool RedBlackTree::RemoveNode(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);

	// Find node if it is in the tree
	if (m_nodeQuantity == 0)
	{
		return false;
	}
	else
	{
		if (m_nodeQuantity == 1)
		{
			delete m_crown;
			m_nodeQuantity--;
			return true;
		}

		Node * currentNode = m_crown;
		bool isFound = false;

		while (!isFound)
		{
			// If current node is leaf
			if (currentNode->GetWord().empty())
			{
				return false;
			}
			// If current node is not leaf
			else
			{
				if (word == currentNode->GetWord())
				{
					isFound = true;
				}
				else
				{
					if (word < currentNode->GetWord()) currentNode = currentNode->GetNextLeft();
					else currentNode = currentNode->GetNextRight();
				}
			}
		}

		// If node was found, delete it
		DeleteNode(currentNode);
		m_nodeQuantity--;
		return true;
	}
}

void RedBlackTree::DeleteNode(Node * nodeToRemove)
{
	int childrenNumber = 0;
	if (!(nodeToRemove->GetNextLeft()->GetWord().empty())) childrenNumber++;
	if (!(nodeToRemove->GetNextRight()->GetWord().empty())) childrenNumber++;

	if (nodeToRemove->GetColor() == Red)
	{
		switch (childrenNumber)
		{
		case 0:
		{
			// Just remove node, no balance needed
			Node * parent = nodeToRemove->GetPrevious();
			std::string direction = nodeToRemove->GetParentBrunchDirection();
			delete nodeToRemove;
			Node * nil = new Node(parent, direction);
			break;
		}
		case 2:
		{
			// Find min on the right, swap and call again for new place
			bool isFound = false;
			Node * currentNode = nodeToRemove->GetNextRight();

			while (!isFound)
			{
				if (currentNode->GetWord().empty())
				{
					currentNode = currentNode->GetPrevious();
					isFound = true;
				}
				else currentNode = currentNode->GetNextLeft();
			}

			// Swap
			std::string word = nodeToRemove->GetWord();
			nodeToRemove->SetWord(currentNode->GetWord());
			currentNode->SetWord(word);

			DeleteNode(currentNode);
			break;
		}
		}
	}
	else
	{
		switch (childrenNumber)
		{
		case 0:
		{
			// Remove and balance
			Node * parent = nodeToRemove->GetPrevious();
			std::string direction = nodeToRemove->GetParentBrunchDirection();
			delete nodeToRemove;
			Node * nil = new Node(parent, direction);

			RemoveBalance(nil);

			break;
		}
		case 1:
		{
			// Move red child without childs on place of nodeToRemove
			if (nodeToRemove->GetNextLeft()->GetWord().empty())
			{
				std::string word = nodeToRemove->GetNextRight()->GetWord();
				nodeToRemove->SetWord(word);

				Node * parent = nodeToRemove->GetNextRight()->GetPrevious();
				std::string direction = nodeToRemove->GetNextRight()->GetParentBrunchDirection();
				delete nodeToRemove->GetNextRight();
				Node * nil = new Node(parent, direction);
			}
			else
			{
				std::string word = nodeToRemove->GetNextLeft()->GetWord();
				nodeToRemove->SetWord(word);

				Node * parent = nodeToRemove->GetNextLeft()->GetPrevious();
				std::string direction = nodeToRemove->GetNextLeft()->GetParentBrunchDirection();
				delete nodeToRemove->GetNextLeft();
				Node * nil = new Node(parent, direction);
			}

			break;
		}
		case 2:
		{
			// Find min on the right, swap and call again for new place
			bool isFound = false;
			Node * currentNode = nodeToRemove->GetNextRight();

			while (!isFound)
			{
				if (currentNode->GetWord().empty())
				{
					currentNode = currentNode->GetPrevious();
					isFound = true;
				}
				else currentNode = currentNode->GetNextLeft();
			}

			// Swap
			std::string word = nodeToRemove->GetWord();
			nodeToRemove->SetWord(currentNode->GetWord());
			currentNode->SetWord(word);

			DeleteNode(currentNode);
			break;
		}
		}
	}
}


void RedBlackTree::RemoveBalance(Node* deleted)
{
	if (deleted->GetPrevious() == nullptr) return;

	Node* parent = deleted->GetPrevious();
	// Deleted is on the right
	if (deleted->GetParentBrunchDirection() == "Right")
	{
		// Parent is red
		if (parent->GetColor() == Red)
		{
			// Left child is black
			if (parent->GetNextLeft()->GetColor() == Black)
			{
				// Left child has left black child
				if (parent->GetNextLeft()->GetNextLeft()->GetColor() == Black)
				{
					// Left child has right black child
					if (parent->GetNextLeft()->GetNextRight()->GetColor() == Black)
					{
						parent->SetColor(Black);
						parent->GetNextLeft()->SetColor(Red);
					}
					// Left child has right red child
					else
					{
						parent->SetColor(Black);
						RemoveBalance(deleted);
						parent->GetPrevious()->SetColor(Red);
					}
				}
				// Left child has left red child
				else
				{
					parent = parent->GetNextLeft(); // To not change working code))))
					Node* temp = parent->GetNextRight();
					temp->SetParentBrunchDirection("Left");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextRight(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextRight()->SetPrevious(parent);
					parent->GetNextRight()->SetNextLeft(temp);
					temp->SetPrevious(parent->GetNextRight());
					parent->GetNextRight()->SetParentBrunchDirection("Right");

					parent->SetColor(Red);
					parent->GetNextRight()->SetColor(Black);
					parent->GetNextLeft()->SetColor(Black);

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
			}
		}
		// Parent is black
		else
		{
			// Left child is red
			if (parent->GetNextLeft()->GetColor() == Red)
			{
				parent = parent->GetNextLeft();

				// Left grandgrandchild is black
				if (parent->GetNextRight()->GetNextLeft()->GetColor() == Black)
				{
					// Right grandgrandchild is black
					if (parent->GetNextRight()->GetNextRight()->GetColor() == Black)
					{
						Node* temp = parent->GetNextRight();
						temp->SetParentBrunchDirection("Left");

						parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
						parent->SetNextRight(parent->GetPrevious());
						parent->SetPrevious(parent->GetPrevious()->GetPrevious());
						parent->GetNextRight()->SetPrevious(parent);
						parent->GetNextRight()->SetNextLeft(temp);
						temp->SetPrevious(parent->GetNextRight());
						parent->GetNextRight()->SetParentBrunchDirection("Right");

						parent->SetColor(Black);
						parent->GetNextRight()->GetNextLeft()->SetColor(Red);

						if (parent->GetPrevious() == nullptr) m_crown = parent;
						else
						{
							if (parent->GetParentBrunchDirection() == "Left")
								parent->GetPrevious()->SetNextLeft(parent);
							else
								parent->GetPrevious()->SetNextRight(parent);
						}
					}
				}
				else
				{
					//Big rotation
					parent->GetNextRight()->GetNextLeft()->SetColor(Black);
					parent = parent->GetNextRight();

					Node* temp = parent->GetNextLeft();
					temp->SetParentBrunchDirection("Right");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextLeft(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextLeft()->SetPrevious(parent);
					parent->GetNextLeft()->SetNextRight(temp);
					temp->SetPrevious(parent->GetNextLeft());
					parent->GetNextLeft()->SetParentBrunchDirection("Left");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}

					temp = parent->GetNextRight();
					temp->SetParentBrunchDirection("Left");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextRight(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextRight()->SetPrevious(parent);
					parent->GetNextRight()->SetNextLeft(temp);
					temp->SetPrevious(parent->GetNextRight());
					parent->GetNextRight()->SetParentBrunchDirection("Right");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
			}
			//Left child is black
			else
			{
				parent = parent->GetNextLeft();

				// Right grandchild is red
				if (parent->GetNextRight()->GetColor() == Red)
				{
					//Big rotation
					parent->GetNextRight()->SetColor(Black);
					parent = parent->GetNextRight();

					Node* temp = parent->GetNextLeft();
					temp->SetParentBrunchDirection("Right");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextLeft(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextLeft()->SetPrevious(parent);
					parent->GetNextLeft()->SetNextRight(temp);
					temp->SetPrevious(parent->GetNextLeft());
					parent->GetNextLeft()->SetParentBrunchDirection("Left");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}

					temp = parent->GetNextRight();
					temp->SetParentBrunchDirection("Left");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextRight(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextRight()->SetPrevious(parent);
					parent->GetNextRight()->SetNextLeft(temp);
					temp->SetPrevious(parent->GetNextRight());
					parent->GetNextRight()->SetParentBrunchDirection("Right");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
				else
				{
					// Left grandchild is black
					if (parent->GetNextLeft()->GetColor() == Black)
					{
						parent->SetColor(Red);
						RemoveBalance(parent->GetPrevious());
					}
					// Left grandchild is red
					else
					{
						parent->GetNextLeft()->SetColor(Red);
						parent->GetPrevious()->SetColor(Red);

						Node* temp = parent->GetNextRight();
						temp->SetParentBrunchDirection("Left");

						parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
						parent->SetNextRight(parent->GetPrevious());
						parent->SetPrevious(parent->GetPrevious()->GetPrevious());
						parent->GetNextRight()->SetPrevious(parent);
						parent->GetNextRight()->SetNextLeft(temp);
						temp->SetPrevious(parent->GetNextRight());
						parent->GetNextRight()->SetParentBrunchDirection("Right");

						if (parent->GetPrevious() == nullptr) m_crown = parent;
						else
						{
							if (parent->GetParentBrunchDirection() == "Left")
								parent->GetPrevious()->SetNextLeft(parent);
							else
								parent->GetPrevious()->SetNextRight(parent);
						}

						RemoveBalance(parent);
					}
				}
			}
		}
	}
	// Deleted is on the left
	else
	{
		// Parent is red
		if (parent->GetColor() == Red)
		{
			// Right child is black
			if (parent->GetNextRight()->GetColor() == Black)
			{
				// Right child has Right black child
				if (parent->GetNextRight()->GetNextRight()->GetColor() == Black)
				{
					// Right child has left black child
					if (parent->GetNextRight()->GetNextLeft()->GetColor() == Black)
					{
						parent->SetColor(Black);
						parent->GetNextRight()->SetColor(Red);
					}
					// Right child has left red child
					else
					{
						parent->SetColor(Black);
						RemoveBalance(deleted);
						parent->GetPrevious()->SetColor(Red);
					}
				}
				// Right child has Right red child
				else
				{
					parent = parent->GetNextRight(); // To not change working code))))

					Node* temp = parent->GetNextLeft();
					temp->SetParentBrunchDirection("Right");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextLeft(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextLeft()->SetPrevious(parent);
					parent->GetNextLeft()->SetNextRight(temp);
					temp->SetPrevious(parent->GetNextLeft());
					parent->GetNextLeft()->SetParentBrunchDirection("Left");

					parent->SetColor(Red);
					parent->GetNextLeft()->SetColor(Black);
					parent->GetNextRight()->SetColor(Black);

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
			}
		}
		// Parent is black
		else
		{
			// Right child is red
			if (parent->GetNextRight()->GetColor() == Red)
			{
				parent = parent->GetNextRight();

				// Right grandgrandchild is black
				if (parent->GetNextLeft()->GetNextRight()->GetColor() == Black)
				{
					// Left grandgrandchild is black
					if (parent->GetNextLeft()->GetNextLeft()->GetColor() == Black)
					{
						Node* temp = parent->GetNextLeft();
						temp->SetParentBrunchDirection("Right");

						parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
						parent->SetNextLeft(parent->GetPrevious());
						parent->SetPrevious(parent->GetPrevious()->GetPrevious());
						parent->GetNextLeft()->SetPrevious(parent);
						parent->GetNextLeft()->SetNextRight(temp);
						temp->SetPrevious(parent->GetNextLeft());
						parent->GetNextLeft()->SetParentBrunchDirection("Left");

						parent->SetColor(Black);
						parent->GetNextLeft()->GetNextRight()->SetColor(Red);

						if (parent->GetPrevious() == nullptr) m_crown = parent;
						else
						{
							if (parent->GetParentBrunchDirection() == "Left")
								parent->GetPrevious()->SetNextLeft(parent);
							else
								parent->GetPrevious()->SetNextRight(parent);
						}
					}
				}
				else
				{
					//Big rotation
					parent->GetNextLeft()->GetNextRight()->SetColor(Black);
					parent = parent->GetNextLeft();

					Node* temp = parent->GetNextRight();
					temp->SetParentBrunchDirection("Left");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextRight(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextRight()->SetPrevious(parent);
					parent->GetNextRight()->SetNextLeft(temp);
					temp->SetPrevious(parent->GetNextRight());
					parent->GetNextRight()->SetParentBrunchDirection("Right");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}

					temp = parent->GetNextLeft();
					temp->SetParentBrunchDirection("Right");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextLeft(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextLeft()->SetPrevious(parent);
					parent->GetNextLeft()->SetNextRight(temp);
					temp->SetPrevious(parent->GetNextLeft());
					parent->GetNextLeft()->SetParentBrunchDirection("Left");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
			}
			//Right child is black
			else
			{
				parent = parent->GetNextRight();

				// Left grandchild is red
				if (parent->GetNextLeft()->GetColor() == Red)
				{
					//Big rotation
					parent->GetNextLeft()->SetColor(Black);
					parent = parent->GetNextLeft();

					Node* temp = parent->GetNextRight();
					temp->SetParentBrunchDirection("Left");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextRight(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextRight()->SetPrevious(parent);
					parent->GetNextRight()->SetNextLeft(temp);
					temp->SetPrevious(parent->GetNextRight());
					parent->GetNextRight()->SetParentBrunchDirection("Right");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}

					temp = parent->GetNextLeft();
					temp->SetParentBrunchDirection("Right");

					parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
					parent->SetNextLeft(parent->GetPrevious());
					parent->SetPrevious(parent->GetPrevious()->GetPrevious());
					parent->GetNextLeft()->SetPrevious(parent);
					parent->GetNextLeft()->SetNextRight(temp);
					temp->SetPrevious(parent->GetNextLeft());
					parent->GetNextLeft()->SetParentBrunchDirection("Left");

					if (parent->GetPrevious() == nullptr) m_crown = parent;
					else
					{
						if (parent->GetParentBrunchDirection() == "Left")
							parent->GetPrevious()->SetNextLeft(parent);
						else
							parent->GetPrevious()->SetNextRight(parent);
					}
				}
				else
				{
					// Right grandchild is black
					if (parent->GetNextRight()->GetColor() == Black)
					{
						parent->SetColor(Red);
						RemoveBalance(parent->GetPrevious());
					}
					// Right grandchild is red
					else
					{
						parent->GetPrevious()->SetColor(Red);
						parent->GetNextRight()->SetColor(Red);

						Node* temp = parent->GetNextLeft();
						temp->SetParentBrunchDirection("Right");

						parent->SetParentBrunchDirection(parent->GetPrevious()->GetParentBrunchDirection());
						parent->SetNextLeft(parent->GetPrevious());
						parent->SetPrevious(parent->GetPrevious()->GetPrevious());
						parent->GetNextLeft()->SetPrevious(parent);
						parent->GetNextLeft()->SetNextRight(temp);
						temp->SetPrevious(parent->GetNextLeft());
						parent->GetNextLeft()->SetParentBrunchDirection("Left");

						if (parent->GetPrevious() == nullptr) m_crown = parent;
						else
						{
							if (parent->GetParentBrunchDirection() == "Left")
								parent->GetPrevious()->SetNextLeft(parent);
							else
								parent->GetPrevious()->SetNextRight(parent);
						}

						RemoveBalance(parent);
					}
				}
			}
		}
	}
}