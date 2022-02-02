#include "MyString.h"

#include <iostream>
#include <memory>
#include <vector>

using namespace custom;

int main(int argc, char** argv)
{
	std::vector<string> vec1(argc, argv[0]);
	std::vector<string> vec2(0);
	/*for (unsigned int i = 1; i < argc; ++i)
	{
		strings.push_back(argv[i]);
	}*/
	string a("Hello ");
	char t = a[0];
	string b("World!");
	string c = a + b;
	string z = a + b + c;
	//string z = a + b + "\t" + c;
	string* d = new string("sharedPoinderToString_d");
	std::cout << "StringZ:\n" << "\tsize: " << z.size() << "\tdata: " << z.getString() << std::endl;
	std::cout << "Vec2:\n" << "\tsize: " << vec2.size() << "\tdata: " << ((vec2.size() > 0) ? vec2[0].getString() : "empty") << std::endl;
	std::cout << "StringD:\n" << "\tsize: " << d->size() << "\tdata: " << d->getString() << std::endl;
	
	vec2.emplace(vec2.begin(), std::move(*d));
	std::cout << "Vec2:\n" << "\tsize: " << vec2.size() << "\tdata: " << vec2[0].getString() << std::endl;
	if(d == nullptr)
	{
		std::cout << "String \"d\" does not exist.\n";
	}

	std::cout << "Vec1:\n" << "\tsize: " << vec1[0].size() << "\tdata: " << vec1[0].getString() << std::endl;
	std::cout << "Size:\n\t" << "t: " << sizeof(t) << "\ta: " << a.size() << "\tb: " << b.length() << "\tc: " << c.capacity() << std::endl;
	std::cout << "Data:\n\t" << "t: " << t << "\ta: " << a.getString() << "\tb: " << b.getString() << "\tc: " << c.getString() << std::endl;


	system("pause");

	return 0;
}