#pragma once

namespace custom
{
	class string
	{
	public:
		string();
		string(char*);
		string(const char*);
		string(string const&); //lvalue - reference
		string(string&&) noexcept;//rvalue - reference
		~string();
		//string& operator=(string const&&);
		//string& operator=(const string&);
		void operator=(const string&);

		char& operator[](size_t);
		//string	operator[](size_t);

		char* operator<<(string const&);
		//string operator+(string const&);
		//string& operator+(string const&&)&&; // "&& в конце" - ссылочный пурификатор, чтобы функция вызывалось только для rvalue
		string& operator+(string const&&)&; // "& в конце" - ссылочный пурификатор, чтобы функция вызывалось только для lvalue
		friend string operator+(string const&, string const&);
		//friend string append(string&, ...);

		operator bool() const;

		const bool operator!=(string const&);

		const bool operator==(string const&);

		size_t length();
		size_t capacity();

		char* getString();
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

	protected:
		string(char*, size_t);

		void move(string&);//rvalue - reference
		size_t countSize(char*);


	protected:
		char* pStr;
		size_t mLength;
		size_t mCapacity{0};
	};
}

