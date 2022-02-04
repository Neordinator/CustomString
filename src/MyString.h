#pragma once

#include <iostream>

namespace custom
{
	class string
	{
	public:
		string();
		string(char*);
		string(const char*);
		string(string const&);
		string(string&&) noexcept;
		~string();

		string& operator=(string&&) noexcept;
		string& operator=(const string&);
		void operator=(const char*);
		void operator=(char*);

		string operator+(string const&);
		friend const string operator+(const string&, const string&);
		friend const string operator+(const string&, const char*);
		friend const string operator+(const char*, const string&);

		friend std::ostream& operator<<(std::ostream&, const string&);
		friend std::istream& operator>>(std::istream&, const string&);

		char& operator[](size_t);
		operator char*	() const;
		operator bool	() const;

		const bool operator!=(string const&);

		const bool operator==(string const&);

		/*const bool operator<(string const&&);
		friend const bool operator<(string const&, string const&);

		const bool operator>(string const&&);
		friend const bool operator>(string const&, string const&);

		const bool operator<=(string const&&);
		friend const bool operator<=(string const&, string const&);

		const bool operator>=(string const&&);
		friend const bool operator>=(string const&, string const&);*/
		//string& operator<<(string const&&);
		/*string& operator>>(string const&);
		string& operator>>(string const&&);
		ostream& operator<<(ostream&, string const&);
		istream& operator>>(istream&, string const&);*/

		//string operator+(const string&);
	public:
		size_t length();
		size_t capacity();
		void clear();
		const char* getString();
		void push_back(const char c);
		void reserve(const size_t size);

	protected:
		string(char*, size_t);

		void move(string&);
		//friend void memcpy(char*, char*, size_t);
		size_t countLength(char*);
		size_t countLength(const char*);


	protected:
		char* pStr;
		size_t mLength;
		size_t mCapacity{0};
	};
}

