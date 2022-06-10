#include "Node.h"

Node::Node(std::string word) : m_word(word), m_parentBrunchDirection()
{
	m_previous = nullptr;
	m_nextLeft = new Node(this, "Left");
	m_nextRight = new Node(this, "Right");
	m_color = Black;
}

Node::Node(Node* previous, std::string direction) : m_word(), m_parentBrunchDirection(direction)
{
	if (direction == "Left") previous->SetNextLeft(this);
	else previous->SetNextRight(this);
	m_previous = previous;
	m_nextLeft = nullptr;
	m_nextRight = nullptr;
	m_color = Black;
}

std::string Node::GetWord()
{
	return m_word;
}

Node* Node::GetNextLeft()
{
	return m_nextLeft;
}

Node* Node::GetNextRight()
{
	return m_nextRight;
}

Node* Node::GetPrevious()
{
	return m_previous;
}
Color Node::GetColor()
{
	return m_color;
}

void Node::SetWord(std::string word)
{
	m_word = word;
}

void Node::SetNextLeft(Node* nextLeft)
{
	m_nextLeft = nextLeft;
	m_nextLeft->SetParentBrunchDirection("Left");
}

void Node::SetNextRight(Node* nextRight)
{
	m_nextRight = nextRight;
	m_nextRight->SetParentBrunchDirection("Right");
}

void Node::SetPrevious(Node* previous)
{
	m_previous = previous;
}

void Node::SetColor(Color color)
{
	m_color = color;
}

void Node::CleanBrunch()
{
	if (m_word.empty())
	{
		delete this;
		return;
	}
	else
	{
		m_nextLeft->CleanBrunch();
		m_nextRight->CleanBrunch();
	}
	delete this;
}

void Node::ShowBrunch(int number, int& count)
{
	if (m_word.empty())
	{
		return;
	}
	else
	{
		std::cout << '#' << count << " \"" << m_word;
		if(m_word.size() > 8) std::cout << "\" \t";
		else std::cout << "\" \t\t";
		if (count != 0) std::cout << m_parentBrunchDirection << " from #" << number << '.' ;
		else std::cout << "Does not have parent.";
		std::cout << " Color: ";
		if (m_color == Black) std::cout << "Black";
		else std::cout << "Red";
		std::cout << '\n';
		number = count;
		count++;
		m_nextLeft->ShowBrunch(number, count);
		m_nextRight->ShowBrunch(number, count);
	}
	return;
}



std::string Node::GetParentBrunchDirection()
{
	return m_parentBrunchDirection;
}

void Node::SetParentBrunchDirection(std::string direction)
{
	m_parentBrunchDirection = direction;
}