#include "MyString.h"

namespace custom
{
	string::string() : pStr(nullptr), mLength(0)
	{
	}
	string::string(char* otherStr) : mLength(countLength(otherStr))
	{
		this->pStr = new char[mLength + 1];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(const char* otherStr) : mLength(string::countLength(otherStr))
	{
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

	/*void memcpy(char* dest, char* source, size_t length)
	{
		if (dest != nullptr)
		{
			delete[] dest;
		}
		dest = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			dest[i] = source[i];
		}
		dest[length] = '\0';
	}*/


	string::~string()
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
	}
	string& string::operator=(string&& other) noexcept
	{
		move(other);
		return *this;
	}
	std::ostream& operator<<(std::ostream& outStream, const string& str)
	{
		std::copy(str.pStr, str.pStr + str.mLength, std::ostream_iterator<char>(outStream));
		return outStream;
	}
	std::istream& operator>>(std::istream& inputStream, string& str)
	{
		str.clear();
		do {
			const char c = inputStream.get();
			if (!std::isgraph(c)) {
				break;
			}
			str.push_back(c);
		} while (true);
		return inputStream;
	}
	string& string::operator=(const string& other)
	{
		if (this == &other)
		{
			return *this;
		}
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		std::memcpy(this->pStr, other.pStr, this->mLength);
		return *this;
	}
	void string::operator=(const char* other)
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		size_t length = string::countLength(other);
		this->pStr = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			this->pStr[i] = other[i];
		}
		this->pStr[length] = '\0';
	}
	void string::operator=(char* other)
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		size_t length = string::countLength(other);
		this->pStr = new char[length + 1];
		for (size_t i = 0; i < length; ++i)
		{
			this->pStr[i] = other[i];
		}
		this->pStr[length] = '\0';
	}
	char& string::operator[](size_t index)
	{
		return this->pStr[index];
	}
	void string::push_back(const char c)
	{
		if (mLength >= mCapacity) {
			const size_t new_sz = (mLength == 0) ? (mLength + 1) : (mLength * 2);
			reserve(new_sz);
		}
		this->pStr[mLength] = c;
		this->mLength++;
		this->pStr[mLength] = '\0';
	}
	void string::reserve(const size_t size)
	{
		if (mCapacity >= size) {
			return;
		}
		mCapacity = size;

		if (pStr == nullptr) {
			pStr = new char[mCapacity];
			return;
		}

		char* p = new char[mCapacity];
		std::memcpy(p, pStr, mLength + 1);
		delete[] pStr;
		pStr = p;
	}
	string string::operator+(const string& other)
	{
		size_t newSize = this->mLength + other.mLength + 1;
		char* p = new char[newSize];
		size_t i = 0;
		for (; i < this->mLength; ++i)
		{
			p[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mLength; ++j, ++i)
		{
			p[i] = other.pStr[j];
		}
		return string(p, newSize);
	}

	string::operator bool() const
	{
		if (pStr == nullptr || this->mLength < 1)
		{
			return false;
		}
		return true;
	}

	string::operator char*() const
	{
		return this->pStr;
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

	void string::clear()
	{
		this->pStr[0] = '\0';
		size_t mLength = 0;
	}

	const char* string::getString()
	{
		if (mLength == 0)
		{
			return "";
		}
		const char* p = pStr;
		return p;
	}

	/* "char* string" must be an array of char symbol with '\0'
		or this function provide error */
	size_t string::countLength(char* string)	// времено
	{
		const char* end = string;
		while (*end != '\0')
		{
			++end;
		}
		return end - string;
	}
	size_t string::countLength(const char* string)	// времено
	{
		size_t tempLength = 0;
		while (string[tempLength] != '\0')
		{
			++tempLength;
		}
		return tempLength;
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
	const string operator+(const string& leftString, const string& righString)
	{
		string str;
		str.mLength = leftString.mLength + righString.mLength;
		str.mCapacity = str.mLength + 1;
		str.pStr = new char[str.mCapacity];
		std::memcpy(str.pStr, leftString.pStr, leftString.mLength);
		std::memcpy(str.pStr + leftString.mLength, righString.pStr, righString.mLength);
		str.pStr[str.mLength] = '\0';
		return str;
	}
	/*const string operator+(const string& leftString, const string& righString)
	{
		size_t newLength = leftString.mLength + righString.mLength + 1;
		char* p = new char[newLength];

		size_t i = 0;
		while (i < leftString.mLength)
		{
			p[i] = leftString.pStr[i];
			++i;
		}
		for (size_t j = 0; j < righString.mLength; ++i, ++j)
		{
			p[i] = righString.pStr[j];
		}
		p[i] = '\0';

		return string(p, newLength);
	}*/

	const string operator+(const string& lstr, const char* rstr)
	{
		return (lstr + string(rstr));
	}

	const string operator+(const char* lstr, const string& rstr)
	{
		return (string(lstr) + rstr);
	}
}

