#include "HashTable.h"

#include <iostream>
#include <fstream>
#include <algorithm>

HashTable::HashTable() : m_table()
{
	m_deleted = 0;
	m_hashKey = 8;
}

int HashTable::Search(std::string word)
{
	int hashOne = Hash(word, m_hashKey, m_hashKey + 1);
	int hashTwo = Hash(word, m_hashKey, m_hashKey - 1);

	for (int i = 0; i < m_hashKey; i++)
	{
		if (hashOne < m_table.size())
		{
			if (m_table[hashOne].first)
			{
				if (m_table[hashOne].second == word) return hashOne;
			}
		}
		hashOne = (hashOne + hashTwo) % m_hashKey;
	}

	return -1;
}

bool HashTable::Remove(std::string word)
{
	int position = Search(word);

	if (position == -1) return false;
	else
	{
		m_table[position].first = false;
		m_deleted++;
		if (m_deleted > m_table.size() / 2) Rehash();
	}
}

bool HashTable::Add(std::string word)
{
	int result = AddInto(word, m_table);
	
	if (result == -1) return false;
	else
	{
		if (result == 1) m_deleted--;
		return true;
	}
}

int HashTable::AddInto(std::string word, std::vector<std::pair<bool, std::string>>& table)
{
	if (0.75 * m_hashKey < m_table.size()) m_hashKey *= 2;

	int hashOne = Hash(word, m_hashKey, m_hashKey + 1);
	int hashTwo = Hash(word, m_hashKey, m_hashKey - 1);
	int appropriatePosition = -1;

	for (int i = 0; i < m_hashKey; i++)
	{
		if (hashOne < table.size())
		{
			if (table[hashOne].first)
			{
				if (table[hashOne].second == word) return -1;
			}
			else
			{
				if (appropriatePosition == -1) appropriatePosition = hashOne;
			}
		}

		hashOne = (hashOne + hashTwo) % m_hashKey;
	}

	if (appropriatePosition == -1)
	{
		table.push_back(std::make_pair(true, word));
		return 0;
	}
	else
	{
		table[appropriatePosition].first = true;
		table[appropriatePosition].second = word;
		return 1;
	}
}

void HashTable::Rehash()
{
	std::vector<std::pair<bool, std::string>> table;

	for (int i = 0; i < m_table.size(); i++)
	{
		if (m_table[i].first)
		{
			AddInto(table[i].second, table);
		}
	}

	m_table.clear();
	m_table = table;
	m_deleted = 0;
}

void HashTable::Show()
{
	if (m_table.size() == 0)
	{
		std::cout << "Dictionary is empty\n";
	}

	int counter = 0;

	for (int i = 0; i < m_table.size(); i++)
	{
		if (m_table[i].first)
		{
			std::cout << "#" << i - counter << ' ' << m_table[i].second << '\n';
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
	m_deleted = 0;
	m_hashKey = 8;
	m_table.clear();
}

int HashTable::Hash(std::string word, int size, int key)
{
	int result = 0;

	if (size == 0)
	{
		size++;
		key++;
	}
	for (int i = 0; i < word.size(); i++)
		result = (key * result + word[i]) % size;

	result = (2 * result + 1) % size;
	return result;
}