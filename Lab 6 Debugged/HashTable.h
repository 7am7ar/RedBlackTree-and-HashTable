#pragma once

#include <vector>
#include <utility>
#include <string>

class HashTable
{
public:
	HashTable();
	void Rehash();
	bool Add(std::string word);
	int AddInto(std::string word, std::vector<std::pair<bool, std::string>>& table);
	bool Remove(std::string word);
	int Search(std::string word);
	void Show();
	bool LoadText(std::string fileName);
	void Clean();
	int Hash(std::string word, int size, int key);
private:
	std::vector<std::pair<bool, std::string>> m_table;
	int m_deleted;
	int m_hashKey;
};

