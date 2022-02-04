#include "MyString.h"

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace custom;

std::vector<string> sortRadix(std::vector<string>&, size_t);
//void sortVector(std::vector<string>&);
std::vector<string> sortVector(std::vector<string>&, size_t);
short int symbolCompare(char, char);
short int stringCompare(string, string);

int main(int argc, char** argv)
{
	std::vector<string> randomOrder;
	string longestWord;
	size_t longestWordLength = 0;
	if (argc > 1)
	{
		for (size_t i = 1; i < argc; ++i)
		{
			longestWord = string(argv[i]);
			std::cout << "argv: " << argv[i] << " string length: " << longestWord.length() << " string: " << longestWord.getString() << "\n";
			if (longestWord.length() > longestWordLength)
			{
				longestWordLength = longestWord.length();
			}
			randomOrder.push_back(string(argv[i]));
		}
		std::cout << "\n";
		for (size_t i = 0; i < randomOrder.size(); ++i)
		{
			std::cout << randomOrder[i].getString() << "\n";
		}
		std::vector<string> lexOrder = sortRadix(randomOrder, longestWordLength);
		for (size_t i = lexOrder.size() - 1; i > 0 ; --i)
		{
			for (size_t j = 0; j < lexOrder[i].length(); ++j)
			{
				std::cout << (int)lexOrder[i][j] << ".";
			}
			std::cout << "\n";
			std::cout << lexOrder[i].getString() << "\n";
		}
		for (size_t j = 0; j < lexOrder[0].length(); ++j)
		{
			std::cout << (int)lexOrder[0][j] << ".";
		}
		std::cout << lexOrder[0].getString() << "\n";
	}
	
	//std::vector<string> vec1(argc, argv[0]);
	//std::vector<string> vec2(0);
	string a("Hello ");
	char t = a[0];
	string b("World!");
	string c = a + b;
	std::cout << "c = a + b = " << c << std::endl;
	string z = a + b + c;
	std::cout << "z = a + b + c = " << z << std::endl;
	//string z = a + b + "\t" + c;
	//string* d = new string("sharedPoinderToString_d");
	//std::cout << "StringZ:\n" << "\tsize: " << z.length() << "\tdata: " << z.getString() << std::endl;
	//std::cout << "Vec2:\n" << "\tsize: " << vec2.size() << "\tdata: " << ((vec2.size() > 0) ? vec2[0].getString() : "empty") << std::endl;
	//std::cout << "StringD:\n" << "\tsize: " << d->length() << "\tdata: " << d->getString() << std::endl;
	
	//vec2.emplace(vec2.begin(), std::move(*d));
	//std::cout << "Vec2:\n" << "\tsize: " << vec2.size() << "\tdata: " << vec2[0].getString() << std::endl;
	//if(d == nullptr)
	//{
	//	std::cout << "String \"d\" does not exist.\n";
	//}

	//std::cout << "Vec1:\n" << "\tsize: " << vec1[0].length() << "\tdata: " << vec1[0].getString() << std::endl;
	//std::cout << "Size:\n\t" << "t: " << sizeof(t) << "\ta: " << a.length() << "\tb: " << b.length() << "\tc: " << c.capacity() << std::endl;
	//std::cout << "Data:\n\t" << "t: " << t << "\ta: " << a.getString() << "\tb: " << b.getString() << "\tc: " << c.getString() << std::endl;


	std::cout << "Barier 5" << std::endl;
	system("pause");

	return 0;
}

std::vector<string> sortRadix(std::vector<string>& randomOrder, size_t longestWordLength)
{
	std::vector<std::vector<string>> bitwise(256);
	std::vector<string> strigsBuffer(0);
	for (size_t i = 0; i < randomOrder.size(); ++i)
	{
		bitwise[static_cast<size_t>(randomOrder[i][0])].push_back(randomOrder[i]);
	}
	std::cout << "The longest word length: " << longestWordLength << std::endl;
	for (size_t i = 1; i < longestWordLength; ++i)
	{
		if (bitwise[i].empty())
		{
			std::cout << "_";
			continue;
		}
		std::cout << std::endl;
		for(size_t j = 0; j < bitwise[j].size(); ++j)
		{
			bitwise[j] = sortVector(bitwise[j], i);
		}
	}
	for (size_t i = 0; i < bitwise.size(); ++i)
	{
		if (bitwise[i].empty())
		{
			std::cout << "_";
			continue;
		}
		std::cout << std::endl;
		for (size_t j = 0; j < bitwise[i].size(); ++j)
		{
			strigsBuffer.push_back(bitwise[i][j]);
		}
	}
	return strigsBuffer;
}
std::vector<string> sortVector(std::vector<string>& firstSymbolVector, size_t symbolCount)
{
	std::vector<std::vector<string>> vectorsBuffer(256);
	std::vector<string> strigsBuffer;
	for (size_t i = 0; i < firstSymbolVector.size(); ++i)
	{
		vectorsBuffer[firstSymbolVector[i][symbolCount]].push_back(firstSymbolVector[i]);
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
/*void sortVector(std::vector<stdstring>& firstSymbolVector)
{
	if (firstSymbolVector.empty() || firstSymbolVector.size() == 1)
	{
		return;
	}
	std::vector<stdstring> bufferVector;
	string bufferString;
	for (size_t i = firstSymbolVector.size() - 1; i > 0; --i)
	{
		switch (stringCompare(firstSymbolVector[i], firstSymbolVector[i - 1]))
		{
		case -1:
			bufferString = firstSymbolVector[i - 1];
			firstSymbolVector[i - 1] = firstSymbolVector[i];
			firstSymbolVector[i] = bufferString;
			break;
		case 0:
			break;
		case 1:
			break;
		}
	}
}*/
short int stringCompare(string first, string second)
{
	bool compare = first.length() <= second.length();
	size_t length = (compare) ? first.length() : second.length();
	short int iflongerbutsame = (compare) ? iflongerbutsame = -1 : iflongerbutsame = 1;
	for (size_t i = 0; i < length; ++i)
	{
		switch (symbolCompare(first[i], second[i]))
		{
		case -1:
			return -1;
		case 0:
			break;
		case 1:
			return 1;
		}
	}
	if (first.length() == second.length())
	{
		return 0;
	}
	return iflongerbutsame;
}
short int symbolCompare(char first, char second)
{
	if (first < second)
	{
		return -1;
	}
	if (first == second)
	{
		return 0;
	}
	return 1;
}