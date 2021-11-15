#include <iostream>
#include "python.h"

using namespace std;
using namespace py;

#define SIZE 49

int main() {
	//can make pystr by using ""p
	auto str = "  Life is too\tshort.  "p;
	cout << "pystr = " << "'" + str.replace("\t", "\\t") + "'" << endl;

	cout << endl << "output"p.center(40, "=") << endl; //function center
	printf("printf(\"%%s\",pystr.c_str()) :             %s\n", str.c_str());
	cout << "for (auto i : pystr) cout << chr(i) << \",\" : ";
	for (auto i : str) cout << chr(i) << ",";
	cout << endl;
	cout << "for (pystr i : pystr) cout << i << \",\" : ";
	for (pystr i : str) cout << i << ",";
	cout << endl;

	cout << endl << "\"function\"p.center(40,\"=\") : " << "function"p.center(40, "=") << endl;
	cout << "(\"py : \" + pystr).capitalize : "p.ljust(SIZE) << ("py : " + str).capitalize() << endl;
	cout << "pystr.casefold : "p.ljust(SIZE) << str.casefold() << endl;
	cout << "pystr.count('o') : "p.ljust(SIZE) << str.count('o') << endl;
	cout << "pystr.endswith('o') : "p.ljust(SIZE) << str.endswith('o') << endl;
	cout << "pystr.expandtabs(3) : "p.ljust(SIZE) << str.expandtabs(3) << endl;
	cout << "pystr.find(\"short\") : "p.ljust(SIZE) << str.find("short") << endl;
	cout << "pystr.find(\"long\") : "p.ljust(SIZE) << str.find("long") << endl;
	cout << "pystr.index(\"short\") : "p.ljust(SIZE) << str.index("short") << endl;
	cout << "pystr.index(\"long\") : "p.ljust(SIZE);
	//cout << str.index("long") << endl;	ValueError: substring not found
	cout << "pystr.isalnum() : "p.ljust(SIZE) << str.isalnum() << endl;
	cout << "pystr.isalpha() : "p.ljust(SIZE) << str.isalpha() << endl;
	cout << "pystr.isAscii() : "p.ljust(SIZE) << str.isAscii() << endl;
	cout << "pystr.isdigit() : "p.ljust(SIZE) << str.isdigit() << endl;
	cout << "pystr.isdecimal() : "p.ljust(SIZE) << str.isdecimal() << endl;
	cout << "pystr.islower() : "p.ljust(SIZE) << str.islower() << endl;
	cout << "pystr.isnumeric() : "p.ljust(SIZE) << str.isnumeric() << endl;
	cout << "pystr.isprintable() : "p.ljust(SIZE) << str.isprintable() << endl;
	cout << "pystr.isspace() : "p.ljust(SIZE) << str.isspace() << endl;
	cout << "pystr.istitle() : "p.ljust(SIZE) << str.istitle() << endl;
	cout << "pystr.isupper() : "p.ljust(SIZE) << str.isupper() << endl;
	cout << "\"//\"p.join(pystr) : "p.ljust(SIZE) << "//"p.join(str) << endl;
	pylist<pystr> list = { "Life", "is", "too", "short." };
	cout << "pylist<pystr> = " << list << endl;
	cout << "\" \"p.join(pylist<pystr>) : "p.ljust(SIZE) << " "p.join(list) << endl;
	cout << "pystr.ljust(30,\"_\") : "p.ljust(SIZE) << str.ljust(30, "_") << endl;
	cout << "pystr.lower() : "p.ljust(SIZE) << str.lower() << endl;
	cout << "\"pystr.lstrip()\" : "p.ljust(SIZE) << '"' + str.lstrip() + '"' << endl;
	cout << "pystr.translate(pystr.maketrance(\"ios\",\"105\")) : "p.ljust(SIZE) << str.translate(str.maketrance("ios","105")) << endl;
	cout << "pystr.partition(\"o\") : "p.ljust(SIZE) << str.partition("o") << endl;
	cout << "pystr.replace(\"short\",\"long\") : "p.ljust(SIZE) << str.replace("short", "long") << endl;
	cout << "pystr.rfind('o') : "p.ljust(SIZE) << str.rfind('o') << endl;
	cout << "pystr.rindex('o') : "p.ljust(SIZE) << str.rindex('o') << endl;
	cout << "pystr.rjust(30,\"_\") : "p.ljust(SIZE) << str.rjust(30, "_") << endl;
	cout << "pystr.rpartition(\"o\") : "p.ljust(SIZE) << str.rpartition("o") << endl;
	cout << "\"pystr.rstrip()\" : "p.ljust(SIZE) << '"' + str.rstrip() + '"' << endl;
	cout << "pystr.split('s') : "p.ljust(SIZE) << str.split('s') << endl;
	cout << "\"pystr.strip()\" : "p.ljust(SIZE) << '"' + str.strip() + '"' << endl;
	cout << "pystr.swapcase() : "p.ljust(SIZE) << str.swapcase() << endl;
	cout << "pystr.title() : "p.ljust(SIZE) << str.title() << endl;
	cout << "pystr.upper() : "p.ljust(SIZE) << str.upper() << endl;
	cout << "pystr.zfill(30) : "p.ljust(SIZE) << str.zfill(30) << endl;

	cout << "len(pystr) : "p.ljust(SIZE) << len(str) << endl;
	cout << "ord(\"1\") : "p.ljust(SIZE) << ord("1") << endl;
	cout << "chr(49) : "p.ljust(SIZE) << chr(49) << endl;
	cout << "str(49) : "p.ljust(SIZE) << py::str(49) << endl;

	str = "python1\npython2\npython3\npython1972";
	cout << endl << "pystr = " << str.replace("\n", "\\n") << endl;
	cout << "pystr.splitlines() : " << str.splitlines() << endl;

	cout << endl << "operator"p.center(40, "=") << endl;
	pystr str1 = "a";
	pystr str2 = "b";
	cout << "str1 = " << str1 << endl
		<< "str2 = " << str2 << endl;
	cout << "str1 + str2 : "p.ljust(15) << str1 + str2 << endl;
	cout << "str1 += str2 : "p.ljust(15) << (str1 += str2) << endl;
	cout << "str1 : "p.ljust(15) << str1 << endl;
	cout << "str1 * 4 : "p.ljust(15) << (str1 * 4) << endl;
	cout << "str1 == str2 : "p.ljust(15) << (str1 == str2) << endl;
	cout << "str1 != str2 : "p.ljust(15) << (str1 != str2) << endl;
	cout << "str1 < str2 : "p.ljust(15) << (str1 < str2) << endl;
	cout << "str1 > str2 : "p.ljust(15) << (str1 > str2) << endl;

	cout << endl
		<< "="p * 40 << endl
		<< "pylist"p.center(40, "=") << endl
		<< "="p * 40 << endl << endl;
	pylist<int> list1 = { 4,5,6 };
	pylist<int> list2 = { 7,8,9 };
	pylist<int> list3 = { 1,2,3 };
	cout << "list1 = " << list1 << endl
		<< "list2 = " << list2 << endl
		<< "list3 = " << list3 << endl;
	cout << "list1 += list2 + list3 : "p.ljust(SIZE) << (list1 += list2 + list3) << endl;
	cout << "list1 : "p.ljust(SIZE) << list1 << endl;
	cout << "for (auto ele : list1) cout << ele : "p.ljust(SIZE);
	for (auto ele : list1) cout << ele;
	cout << endl;
	cout << "pylist : "p.ljust(SIZE) << list1 << " // (list1)" << endl;
	cout << "len(pylist) : "p.ljust(SIZE) << len(list1) << endl;
	cout << "pylist.append(7) : "p.ljust(SIZE) << list1.append(7) << endl;
	cout << "pylist.pop(3) : "p.ljust(SIZE) << list1.pop(3) << endl;
	cout << "pylist : "p.ljust(SIZE) << list1 << endl;
	cout << "pylist.del(2,5) : "p.ljust(SIZE) << list1.del(2, 5) << endl;
	cout << "pylist.sort() : "p.ljust(SIZE) << list1.sort() << endl;
	cout << "pylist.reverse() : "p.ljust(SIZE) << list1.reverse() << endl;
	cout << "pylist.index(5) : "p.ljust(SIZE) << list1.index(5) << endl;
	cout << "pylist.index(10) : "p.ljust(SIZE);
	//cout << list1.index(10) << endl;		ValueError: value not in list
	cout << "cout << pylist.insert(5,7) : "p.ljust(SIZE) << list1.insert(5, 7) << endl;
	cout << "cout << pylist.remove(5) : "p.ljust(SIZE) << list1.remove(5) << endl;
	cout << "cout << pylist.remove(10) : "p.ljust(SIZE);
	//cout << list1.remove(10) << endl;		ValueError: value not in list
	cout << "cout << pylist.count(7) :  "p.ljust(SIZE) << list1.count(7) << endl;
	cout << "cout << pylist.extend(pylist) : "p.ljust(SIZE) << list1.extend(list1) << endl;
	cout << "cout << pylist.clear() : "p.ljust(SIZE) << list1.clear() << endl;
	cout << "operators"p.center(40, "=") << endl;
	list1 = { 1,3,2,4,5,6,9,7,8 };
	cout << "cout << pylist(\"\", \"\") : "p.ljust(SIZE) << list1("", "") << endl;
	cout << "cout << pylist(1, 5) : "p.ljust(SIZE) << list1(1, 5) << endl;
	cout << "cout << *pylist[3] : "p.ljust(SIZE) << *list1[3] << endl;
	cout << "cout << pylist * 3 : "p.ljust(SIZE) << list1 * 2 << endl;
}
