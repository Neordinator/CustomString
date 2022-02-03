#include "MyString.h"

namespace custom
{
	string::string() : pStr(nullptr), mLength(0)
	{
	}
	string::string(char* otherStr) : mLength(string::countSize(otherStr))
	{
		this->pStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(const char* otherStr) : mLength(0)
	{
		while (otherStr[mLength])
		{
			++mLength;
			if (otherStr[mLength] == '\0')
			{
				break;
			}
		}
		this->pStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(const string& other) : mLength(other.mLength)
	{
		this->pStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = other.pStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(string&& other) noexcept : mLength(other.mLength), pStr(other.pStr), mCapacity(other.mCapacity)
	{
		other.pStr = nullptr;
		other.mCapacity = 0;
		other.mLength = 0;
	}
	void string::move(string& other)
	{
		this->mLength = other.mLength;
		this->pStr = other.pStr;
		this->mCapacity = other.mCapacity;
		other.pStr = nullptr;
		other.mCapacity = 0;
		other.mLength = 0;
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

	string& string::operator+(const string&& other)&
	{
		string newStr;
		newStr.mLength = this->mLength + other.mLength;
		newStr.pStr = new char[newStr.mLength + 1];
		size_t i = 0;
		for (; i < this->mLength; ++i)
		{
			newStr.pStr[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mLength; ++j, ++i)
		{
			newStr.pStr[i] = other.pStr[j];
		}
		newStr.pStr[this->mLength + other.mLength] = '\0';
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
		if (this->mLength < 1)
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
		if (this->mLength != other.mLength)
		{
			return false;
		}
		for (size_t i = 0; i < this->mLength; ++i)
		{
			if (this->pStr[i] != other.pStr[i])
			{
				return false;
			}
		}
		return true;
	}

	size_t string::length()		// не готово
	{
		return mLength;
	}

	size_t string::capacity()	// не готово
	{
		return mCapacity;
	}

	char* string::getString()
	{
		if (mLength == 0)
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
	string::string(char* otherStr, size_t otherLength) : mLength(otherLength)
	{
		this->pStr = new char[mLength];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
		delete[] otherStr;
	}
	string operator+(const string & str1, const string & str2)
	{
		size_t newSize = str1.mLength + str2.mLength + 1;
		char* p = new char(newSize);
		size_t i = 0;
		while (i < str1.mLength)
		{
			p[i] = str1.pStr[i];
			++i;
		}
		for (size_t j = 0; j < str2.mLength; ++i, ++j)
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

