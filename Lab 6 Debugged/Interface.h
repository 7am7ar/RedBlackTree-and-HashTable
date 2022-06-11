#pragma once

#include "HashTable.h"
#include "RedBlackTree.h"

bool IsOnlyDigits(const std::string s)
{
	return s.find_first_not_of("0123456789") == std::string::npos;
}

void Start()
{
	HashTable hashTable;
	RedBlackTree redBlackTree;

	while (true)
	{
		std::cout << "0. Show the Red-Black Tree.\n";
		std::cout << "1. Load text in the Red-Black Tree.\n";
		std::cout << "2. Add word to the Red-Black Tree.\n";
		std::cout << "3. Remove word from the Red-Black Tree.\n";
		std::cout << "4. Find word in the Red-Black Tree.\n";
		std::cout << "5. Clean the Red-Black Tree.\n";
		std::cout << "6. Show the Hash-table.\n";
		std::cout << "7. Load text in the Hash-table.\n";
		std::cout << "8. Add word to the Hash-table.\n";
		std::cout << "9. Remove word from the Hash-table.\n";
		std::cout << "10. Find word in the Hash-table.\n";
		std::cout << "11. Clean the Hash-table.\n";
		std::cout << "12. End the programm.\n";

		std::string input;
		int operationNumber;
		bool isAssigned = false;

		while (!isAssigned)
		{
			std::cout << "Enter the operation number:\n";
			std::cin >> input;
			if (IsOnlyDigits(input) && std::stoi(input) >= 0 && std::stoi(input) <= 12)
			{
				operationNumber = std::stoi(input);
				isAssigned = true;
			}
			else std::cout << "Number is incorrect.\n";
		}

		switch (operationNumber)
		{
		case 0:
			std::cout << "\nDictionary in Red-Black tree:\n";
			redBlackTree.Show();
			break;
		case 1:
			std::cout << "\nEnter file name:\n";
			std::cin >> input;
			{
				bool result = redBlackTree.LoadText(input);
				if (result) std::cout << "\nText was loaded.\n";
				else std::cout << "File name is incorrect.\n";
			}
			break;
		case 2:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = redBlackTree.AddNode(input);
				if (result) std::cout << "\nWord was added in the dictionary.\n";
				else std::cout << "\nDictionary already contains this word.\n";
			}
			break;
		case 3:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = redBlackTree.RemoveNode(input);
				if (result) std::cout << "\nWord was removed from the dictionary.\n";
				else std::cout << "\nDictionary does not contain this word.\n";
			}
			break;
		case 4:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = redBlackTree.Search(input);
				if (result) std::cout << "\nDictionary contans this word.\n";
				else std::cout << "\nDictionary does not contain this word.\n";
			}
			break;
		case 5:
			redBlackTree.Clean();
			std::cout << "\nDictionary in Red-Black tree was cleaned.\n";
			break;
		case 6:
			std::cout << "\nDictionary in Hash-table:\n";
			hashTable.Show();
			break;
		case 7:
			std::cout << "\nEnter file name:\n";
			std::cin >> input;
			{
				bool result = hashTable.LoadText(input);
				if (result) std::cout << "\nText was loaded.\n";
				else std::cout << "File name is incorrect.\n";
			}
			break;
		case 8:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = hashTable.Add(input);
				if (result) std::cout << "\nWord was added in the dictionary.\n";
				else std::cout << "\nDictionary already contains this word.\n";
			}
			break;
		case 9:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = hashTable.Remove(input);
				if (result) std::cout << "\nWord was removed from the dictionary.\n";
				else std::cout << "\nDictionary does not contain this word.\n";
			}
			break;
		case 10:
			std::cout << "\nEnter word:\n";
			std::cin >> input;
			{
				bool result = hashTable.Search(input);
				if (result) std::cout << "\nDictionary contans this word.\n";
				else std::cout << "\nDictionary does not contain this word.\n";
			}
			break;
		case 11:
			hashTable.Clean();
			std::cout << "\nDictionary in Hash-table was cleaned.\n";
			break;
		case 12:
			return;
		}
		std::cout << '\n';
	}
}