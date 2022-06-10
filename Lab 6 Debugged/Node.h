#pragma once

#include <string>
#include <iostream>

#include "Globals.h"

class Node
{
public:
	Node(std::string m_word);
	Node(Node* previous, std::string direction);
	std::string GetWord();
	std::string GetParentBrunchDirection();
	Node* GetNextLeft();
	Node* GetNextRight();
	Node* GetPrevious();
	Color GetColor();
	void SetParentBrunchDirection(std::string direction);
	void SetWord(std::string word);
	void SetNextLeft(Node* nextLeft);
	void SetNextRight(Node* nextRight);
	void SetPrevious(Node* previous);
	void SetColor(Color color);
	void CleanBrunch();
	void ShowBrunch(int number, int& count);
private:
	Node* m_previous;
	Node* m_nextLeft;
	Node* m_nextRight;
	Color m_color;
	std::string m_word;
	std::string m_parentBrunchDirection;
};