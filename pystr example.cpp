#include <iostream>
#include "python.h"

using namespace std;
using namespace py;

int main() {
	//can make pystr by using ""p
	auto str = "  Life is too\tshort.  "p;
	cout << "pystr = " << "'" + str + "'" << endl;
	
	cout << endl << "output"p.center(40, "=") << endl; //function center
	printf("printf(\"%%s\",pystr.c_str()) : %s\n", str.c_str());
	cout << "for (auto i : pystr) cout << i << endl : ";
	for (auto i : str) cout << i << ",";
	cout << endl;

	cout << endl << "\"function\"p.center(40,\"=\") : " << "function"p.center(40, "=") << endl;
	cout << "pystr.count('o') : " << str.count('o') << endl;
	cout << "pystr.endswith('o') : " << str.endswith('o') << endl;
	cout << "pystr.expandtabs(3) : " << str.expandtabs(3) << endl;
	cout << "pystr.find(\"short\") : " << str.find("short") << endl;
	cout << "pystr.find(\"long\") : " << str.find("long") << endl;
	cout << "pystr.index(\"short\") : " << str.index("short") << endl;
	cout << "pystr.index(\"long\") : ";
	try { cout << str.index("long") << endl; }
	catch (pystr err) { cout << err << endl; }
	cout << "pystr.isalnum() : " << str.isalnum() << endl;
	cout << "pystr.isalpha() : " << str.isalpha() << endl;
	cout << "pystr.isAscii() : " << str.isAscii() << endl;
	cout << "pystr.isdecimal() : " << str.isdecimal() << endl;
	cout << "\"//\"p.join(pystr) : " << "//"p.join(str) << endl;
	pylist<pystr> list = { "Life", "is", "too", "short." };
	cout << "pylist<pystr> = " << list << endl;
	cout << "\" \"p.join(pylist<pystr>) : " << " "p.join(list) << endl;
	cout << "\"pystr.lstrip()\" : " << '"' + str.lstrip() + '"'<< endl;
	cout << "pystr.replace(\"short\",\"long\") : " << str.replace("short", "long") << endl;
	cout << "pystr.rfind('o') : " << str.rfind('o') << endl;
	cout << "\"pystr.rstrip()\" : " << '"' + str.rstrip() + '"' << endl;
	cout << "pystr.split('s') : " << str.split('s') << endl;
	cout << "\"pystr.strip()\" : " << '"' + str.strip() + '"' << endl;
	cout << "len(pystr) : " << len(str) << endl;
	cout << "ord(\"1\") : " << ord("1") << endl;
	cout << "chr(49) : " << chr(49) << endl;
	cout << "str(49) : " << py::str(49) << endl;

	cout << endl << "operator"p.center(40, "=") << endl;
	pystr str1 = "a";
	pystr str2 = "b";
	cout << "str1, str2 = " << str1 << ", " << str2 << endl;
	cout << "str1 + str2 : " << str1 + str2 << endl;
	cout << "str1 += str2 : " << (str1 += str2) << endl;
	cout << "str1 : " << str1 << endl;
	cout << "str1 * 4 : " << (str1 * 4) << endl;
	cout << "str1 == str2 : " << (str1 == str2) << endl;
	cout << "str1 != str2 : " << (str1 != str2) << endl;
	cout << "str1 < str2 : " << (str1 < str2) << endl;
	cout << "str1 > str2 : " << (str1 > str2) << endl;
}
