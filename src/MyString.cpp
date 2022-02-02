#include "MyString.h"

namespace custom
{
	string::string() : pStr(nullptr), mSize(0)
	{
	}
	string::string(char* otherStr) : mSize(string::countSize(otherStr))
	{
		this->pStr = new char[mSize + 1];
		for (size_t i = 0; i < mSize; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mSize] = '\0';
	}
	string::string(const char* otherStr) : mSize(0)
	{
		while (otherStr[mSize])
		{
			++mSize;
			if (otherStr[mSize] == '\0')
			{
				break;
			}
		}
		this->pStr = new char[mSize + 1];
		for (size_t i = 0; i < mSize; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mSize] = '\0';
	}
	string::string(char* otherStr, size_t otherSize) : mSize(otherSize)
	{
		this->pStr = new char[mSize];
		for (size_t i = 0; i < mSize; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mSize] = '\0';
		delete[] otherStr;
	}
	string::string(const string& other) : mSize(other.mSize)
	{
		this->pStr = new char[mSize + 1];
		for (size_t i = 0; i < mSize; ++i)
		{
			this->pStr[i] = other.pStr[i];
		}
		this->pStr[mSize] = '\0';
	}

	string::string(string&& other) noexcept : mSize(other.mSize), pStr(other.pStr)
	{
		other.pStr = nullptr;
	}

	string::~string()
	{
		delete[] this->pStr;
	}
	/*string& string::operator=(const string& other)
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		size_t length = string::countSize(pStr);
		this->pStr = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			this->pStr[i] = other.pStr[i];
		}
		this->pStr[length] = '\0';
		return *this;
	}*/
	void string::operator=(const string& other)
	{
		if (this == &other)
		{
			return;
		}
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		size_t length = string::countSize(pStr);
		this->pStr = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			this->pStr[i] = other.pStr[i];
		}
		this->pStr[length] = '\0';
	}

	char& string::operator[](size_t index)
	{
		return this->pStr[index];
	}

	char* string::operator<<(string const& other)
	{
		return other.pStr;
	}

	string& string::operator+(const string&& other)&&
	{
		string newStr;
		newStr.mSize = this->mSize + other.mSize;
		newStr.pStr = new char[newStr.mSize + 1];
		size_t i = 0;
		for (; i < this->mSize; ++i)
		{
			newStr.pStr[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mSize; ++j, ++i)
		{
			newStr.pStr[i] = other.pStr[j];
		}
		newStr.pStr[this->mSize + other.mSize] = '\0';
		return newStr;
	}

	/*string&& string::operator+(const string& other)
	{
		string newStr;
		newStr.mSize = this->mSize + other.mSize;
		newStr.pStr = new char[newStr.mSize + 1];
		size_t i = 0;
		for (; i < this->mSize; ++i)
		{
			newStr.pStr[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mSize; ++j, ++i)
		{
			newStr.pStr[i] = other.pStr[j];
		}
		newStr.pStr[this->mSize + other.mSize] = '\0';
		return newStr;
	}*/
	/*string string::operator+(const string& other)
	{
		size_t newSize = this->mSize + other.mSize + 1;
		char* p = new char[newSize];
		size_t i = 0;
		for (; i < this->mSize; ++i)
		{
			p[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mSize; ++j, ++i)
		{
			p[i] = other.pStr[j];
		}
		return string(p, newSize);
	}*/

	string::operator bool() const
	{
		if (this->mSize < 1)
		{
			return false;
		}
		return true;
	}

	const bool string::operator!=(const string& other)
	{
		return !this->operator==(other);
	}

	const bool string::operator==(const string& other)
	{
		if (this->mSize != other.mSize)
		{
			return false;
		}
		for (size_t i = 0; i < this->mSize; ++i)
		{
			if (this->pStr[i] != other.pStr[i])
			{
				return false;
			}
		}
		return true;
	}

	size_t string::size()		// не готово
	{
		return mSize;
	}

	size_t string::length()		// не готово
	{
		return mSize;
	}

	size_t string::capacity()	// не готово
	{
		return mCapacity;
	}

	char* string::getString()
	{
		if (mSize == 0)
		{
			return nullptr;
		}
		return pStr;
	}

	size_t string::countSize(char* string)	// времено
	{
		const char* end = string;
		while (*end != '\0')
		{
			++end;
		}
		return end - string;
		/*while (pStr[mSize])
		{
			++mSize;
			if (pStr[mSize] == '\0')
			{
				break;
			}
		}
		return mSize;*/
	}
	string operator+(const string & str1, const string & str2)
	{
		size_t newSize = str1.mSize + str2.mSize + 1;
		char* p = new char(newSize);
		size_t i = 0;
		while (i < str1.mSize)
		{
			p[i] = str1.pStr[i];
			++i;
		}
		for (size_t j = 0; j < str2.mSize; ++i, ++j)
		{
			p[i] = str2.pStr[j];
		}
		p[i] = '\0';
		return string(p, newSize);
	}
	/*string append(string& other, ...)
	{
		for (string* ptr = &other; other > 0; other--)
		{
			size_t newSize = str1.mSize + str2.mSize + 1;
			char* p = new char(newSize);
			size_t i = 0;
			while (i < str1.mSize)
			{
				p[i] = str1.pStr[i];
				++i;
			}
			for (size_t j = 0; j < str2.mSize; ++i, ++j)
			{
				p[i] = str2.pStr[j];
			}
			p[i] = '\0';
		}
		return string(p, newSize);
	}*/
}

