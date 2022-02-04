#include "MyString.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace custom;

std::vector<string> sortRadix(std::vector<string>&, size_t);
std::vector<string> sortVector(std::vector<string>&, size_t);

/* ƒŒ¡¿¬»“‹ Œœ»—¿Õ»≈ */
int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "\nNo main parametres. Program over.\n";
		system("pause");

		return 0;
	}

	std::vector<string> randomOrder;
	string longestWord;
	size_t longestWordLength = 0;
	for (size_t i = 1; i < argc; ++i)
	{
		longestWord = string(argv[i]);
		if (longestWord.length() > longestWordLength)
		{
			longestWordLength = longestWord.length();
		}
		randomOrder.emplace_back(argv[i]);
	}

	std::cout << "Entered words: \n  ";
	for (size_t i = 0, row = 0; i < randomOrder.size(); ++i, ++row)
	{
		std::cout << randomOrder[i];
		if (row > 2)
		{
			std::cout << "\n  ";
			row = 0;
		}
		else
		{
			std::cout << "  ";
		}
	}

	std::vector<string> lexOrder = sortRadix(randomOrder, longestWordLength);
	std::cout << "\n\nWords in reverse lexicographical order: \n  ";
	for (size_t i = lexOrder.size(), row = 0; i > 0; --i, ++row)
	{
		std::cout << lexOrder[i - 1];
		if (row > 2)
		{
			std::cout << "\n  ";
			row = 0;
		}
		else
		{
			std::cout << "  ";
		}
	}

	std::cout << "\n\nSort is over. Program will be shutted down.\n";
	system("pause");

	return 0;
}

std::vector<string> sortRadix(std::vector<string>& randomOrder, size_t longestWordLength)
{
	std::vector<std::vector<string>> bitwise(26);
	std::vector<string> strigsBuffer(0);
	for (size_t i = 0; i < randomOrder.size(); ++i)
	{
		if (randomOrder[i][0] > 64 && randomOrder[i][0] < 91)
		{
			bitwise[static_cast<size_t>(randomOrder[i][0] - 65)].emplace_back(randomOrder[i]);
		}
		if (randomOrder[i][0] > 96 && randomOrder[i][0] < 123)
		{
			bitwise[static_cast<size_t>(randomOrder[i][0] - 97)].emplace_back(randomOrder[i]);
		}
	}
	for (size_t i = 1; i < longestWordLength; ++i)
	{
		if (bitwise[i].empty())
		{
			continue;
		}
		for(size_t j = 0; j < bitwise[j].size(); ++j)
		{
			bitwise[j] = sortVector(bitwise[j], i);
		}
	}
	for (size_t i = 0; i < bitwise.size(); ++i)
	{
		if (bitwise[i].empty())
		{
			continue;
		}
		for (size_t j = 0; j < bitwise[i].size(); ++j)
		{
			strigsBuffer.emplace_back(bitwise[i][j]);
		}
	}
	return strigsBuffer;
}
std::vector<string> sortVector(std::vector<string>& firstSymbolVector, size_t symbolCount)
{
	std::vector<std::vector<string>> vectorsBuffer(26);
	std::vector<string> strigsBuffer;
	for (size_t i = 0; i < firstSymbolVector.size(); ++i)
	{
		if (firstSymbolVector[i][symbolCount] > 64 && firstSymbolVector[i][symbolCount] < 91)
		{
			vectorsBuffer[(size_t)firstSymbolVector[i][symbolCount] - 65].push_back(firstSymbolVector[i]);
		}
		if (firstSymbolVector[i][symbolCount] > 96 && firstSymbolVector[i][symbolCount] < 123)
		{
			vectorsBuffer[(size_t)firstSymbolVector[i][symbolCount] - 97].push_back(firstSymbolVector[i]);
		}
	}
	for (size_t i = 0; i < vectorsBuffer.size(); ++i)
	{
		if (vectorsBuffer[i].empty())
		{
			continue;
		}
		for (size_t j = 0; j < vectorsBuffer[i].size(); ++j)
		{
			strigsBuffer.push_back(vectorsBuffer[i][j]);
		}
	}
	return strigsBuffer;
}