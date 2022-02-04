#include "MyString.h"

namespace custom
{
	string::string() : pStr(nullptr), mLength(0), mCapacity(0) //public constructor
	{
	}
	string::string(char* otherStr) : mLength(countLength(otherStr)), mCapacity(mLength + 1)
	{
		this->pStr = new char[mCapacity];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(const char* otherStr) : mLength(string::countLength(otherStr)), mCapacity(mLength + 1)
	{
		this->pStr = new char[mCapacity];
		for (size_t i = 0; i < mLength; ++i)
		{
			this->pStr[i] = otherStr[i];
		}
		this->pStr[mLength] = '\0';
	}
	string::string(const string& other) : mLength(other.mLength), mCapacity(other.mCapacity)
	{
		this->pStr = new char[mCapacity];
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
	string::string(char* otherStr, size_t otherLength) : mLength(otherLength), mCapacity(mLength + 1), pStr(otherStr) //protected constructor
	{
		otherStr = nullptr;
	}
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
		this->mCapacity = (this->mCapacity <= other.mLength + 1) ? other.mLength + 1 : this->mCapacity;
		this->mLength = other.mLength;
		this->pStr = new char[mCapacity];
		std::memcpy(this->pStr, other.pStr, this->mLength);
		return *this;
	}
	void string::operator=(const char* other)
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		this->mLength = string::countLength(other);//1
		this->mCapacity = this->mLength + 1;
		this->pStr = new char[this->mCapacity];
		for (size_t i = 0; i < this->mLength; ++i)
		{
			this->pStr[i] = other[i];
		}
		this->pStr[this->mLength] = '\0';
	}
	void string::operator=(char* other)
	{
		if (this->pStr != nullptr)
		{
			delete[] this->pStr;
		}
		this->mLength = string::countLength(other);//2
		this->mCapacity = this->mLength + 1;
		this->pStr = new char[this->mCapacity];
		for (size_t i = 0; i < this->mLength; ++i)
		{
			this->pStr[i] = other[i];
		}
		this->pStr[this->mLength] = '\0';
	}


	string string::operator+(const string& other)
	{
		size_t newSize = this->mLength + other.mLength;
		char* p = new char[newSize + 1];
		size_t i = 0;
		for (; i < this->mLength; ++i)
		{
			p[i] = this->pStr[i];
		}
		for (size_t j = 0; j < other.mLength; ++j, ++i)
		{
			p[i] = other.pStr[j];
		}
		p[newSize] = '\0';
		return string(p, newSize);
	}
	const string operator+(const string& leftString, const string& righString) // "внешний" бинарный оператор копирования
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
	const string operator+(const string& lstr, const char* rstr)
	{
		return (lstr + string(rstr));
	}
	const string operator+(const char* lstr, const string& rstr)
	{
		return (string(lstr) + rstr);
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


	char& string::operator[](size_t index)
	{
		return this->pStr[index];
	}
	string::operator bool() const
	{
		if (pStr == nullptr || this->mLength < 1)
		{
			return false;
		}
		return true;
	}
	string::operator char* () const
	{
		return this->pStr;
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
	const bool string::operator!=(const string& other)
	{
		return !this->operator==(other);
	}
	const bool string::operator<(const string&& other)
	{
		return (this->mLength < other.mLength) ? true : false;
	}
	const bool string::operator>(const string&& other)
	{
		return (this->mLength > other.mLength) ? true : false;
	}
	const bool string::operator<=(const string&& other)
	{
		return (this->mLength <= other.mLength) ? true : false;
	}
	const bool string::operator>=(const string&& other)
	{
		return (this->mLength >= other.mLength) ? true : false;
	}


	size_t string::length()
	{
		return mLength;
	}
	size_t string::capacity()	// не готово
	{
		return mCapacity;
	}

	/*Moves '\0' to zero index, changes length on 0.
	But keeps capacity unchanged */
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
	void string::push_back(const char c)
	{
		if (mLength >= mCapacity) {
			const size_t newLength = (mLength == 0) ? (mLength + 1) : (mLength * 2);
			reserve(newLength);
		}
		this->pStr[mLength] = c;
		this->mLength++;
		this->pStr[mLength] = '\0';
	}
	void string::reserve(const size_t& size)
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
	void string::resize(const size_t& newLength)
	{
		if (newLength == this->mLength || newLength < 0)
		{
			return;
		}
		if (newLength == 0)
		{
			this->clear();
			return;
		}
		if (newLength > this->mCapacity)
		{
			this->mLength = newLength;
			this->mCapacity = newLength + 1;
			if (this->pStr != nullptr)
			{
				delete[] this->pStr;
			}
			this->pStr = new char[this->mCapacity];
			this->pStr[mLength] = '\0';
			return;
		}
		if (newLength < this->mCapacity)
		{
			this->mLength = newLength;
			this->pStr = new char[newLength + 1];
			this->pStr[mLength] = '\0';
		}
	}
	void string::erase()
	{
		if (this->pStr != nullptr)
		{
			delete[] pStr;
			this->mLength = 0;
			this->mCapacity = 0;
		}
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
	/* "char* string" must be an array of char symbol with '\0'
		or this function provide error */
	size_t string::countLength(char* string)
	{
		const char* end = string;
		while (*end != '\0')
		{
			++end;
		}
		return end - string;
	}
	size_t string::countLength(const char* string)
	{
		size_t tempLength = 0;
		while (string[tempLength] != '\0')
		{
			++tempLength;
		}
		return tempLength;
	}
}

