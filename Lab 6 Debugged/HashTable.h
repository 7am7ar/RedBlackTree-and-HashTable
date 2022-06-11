#pragma once

#include "Element.h"
#include "Globals.h"

#include <string>

class HashTable
{
public:
	HashTable();
	void Update(Mode mode);
	bool Add(std::string word);
	int AddInto(std::string word, Element* table);
	bool Remove(std::string word);
	int Search(std::string word);
	void Show();
	bool LoadText(std::string fileName);
	void Clean();
	int Hash(std::string word, int size, int key);
private:
	Element* m_table;
	int m_deletedSize;
	int m_size;
	int m_capacity;
};