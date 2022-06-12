#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <algorithm>

HashTable::HashTable() : m_table()
{
	m_capacity = standartSize;
	m_deletedSize = 0;
	m_size = 0;
	m_table = new Element[m_capacity];
}

int HashTable::Hash(std::string word, int size, int key)
{
	int result = 0;

	for (int i = 0; i < word.size(); i++)
	{
		result = (key * result + word[i]) % size;
	}
	result = (result * 2 + 1) % size;

	if (result < 0) result *= -1;

	return result;
}

int HashTable::Search(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);

	int hashOne = Hash(word, m_capacity, m_capacity + 1);
	int hashTwo = Hash(word, m_capacity, m_capacity - 1);

	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[hashOne].GetState() == Actual && m_table[hashOne].GetData() == word) return hashOne;

		hashOne = (hashOne + hashTwo) % m_capacity;
	}

	return -1;
}

bool HashTable::Remove(std::string word)
{
	int position = Search(word);

	if (position == -1) return false;
	else
	{
		m_table[position].SetState(Deleted);
		m_deletedSize++;
		m_size--;

		if (m_deletedSize > (m_capacity / 2)) Update(Rehash);
	}
}

void HashTable::Update(Mode mode)
{
	int previousCapacity = m_capacity;

	if (mode == Resize) m_capacity *= 2;

	Element* newTable = new Element[m_capacity];

	for (int i = 0; i < previousCapacity; i++)
	{
		if (m_table[i].GetState() == Actual)
		{
			AddInto(m_table[i].GetData(), newTable);
		}
	}

	delete[] m_table;
	m_table = newTable;
	m_deletedSize = 0;
}

bool HashTable::Add(std::string word)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);

	int result = AddInto(word, m_table);
	
	if (result == 0) return false;
	else
	{
		if (result == 1) m_deletedSize--;
		else m_size++;
		
		return true;
	}
}

int HashTable::AddInto(std::string word, Element* table)
{
	int hashOne = Hash(word, m_capacity, m_capacity + 1);
	int hashTwo = Hash(word, m_capacity, m_capacity - 1);

	int appropriatePosition = -1;
	int result = -1;

	for (int i = 0; i < m_capacity; i++)
	{
		if (table[hashOne].GetState() == Actual)
		{
			if (table[hashOne].GetData() == word) return 0;
		}
		else
		{
			if (appropriatePosition == -1)
			{
				if (table[hashOne].GetState() == Deleted) result = 1;
				else result = 2;
				appropriatePosition = hashOne;
			}
		}

		hashOne = (hashOne + hashTwo) % m_capacity;
	}

	if (appropriatePosition == -1)
	{
		std::cout << "FUCK YEAH";
		return 0;
	}

	table[appropriatePosition].SetState(Actual);
	table[appropriatePosition].SetData(word);

	if (resizeValue * m_capacity < m_size)
	{
		Update(Resize);
	}

	return result;
}

void HashTable::Show()
{
	if (m_size == 0)
	{
		std::cout << "Dictionary is empty\n";
	}

	int counter = 0;

	for (int i = 0; i < m_capacity; i++)
	{
		if (m_table[i].GetState() == Actual)
		{
			std::cout << "#" << i - counter << " \"" << m_table[i].GetData() << "\"\n";
		}
		else counter++;
	}
}

bool HashTable::LoadText(std::string fileName)
{
	std::ifstream fin(fileName);
	if (fin.is_open())
	{
		std::string currentWord;
		while (!fin.eof())
		{
			fin >> currentWord;
			currentWord.erase(std::remove_if(currentWord.begin(), currentWord.end(), ispunct), currentWord.end());
			Add(currentWord);
		}

		fin.close();
		return true;
	}
	else return false;
}

void HashTable::Clean()
{
	m_capacity = standartSize;
	m_deletedSize = 0;
	m_size = 0;
	delete[] m_table;
	m_table = new Element[m_capacity];
}