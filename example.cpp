#include <iostream>
#include "python.h"

using namespace std;
using namespace py;

int main() {
	//can make pystr by using ""p
	auto str = "  Life is too\tshort.  "p;
	cout << "pystr = " << "'" + str.replace("\t","\\t") + "'" << endl;
	
	cout << endl << "output"p.center(40, "=") << endl; //function center
	printf("printf(\"%%s\",pystr.c_str()) :             %s\n", str.c_str());
	cout << "for (auto i : pystr) cout << i << endl : ";
	for (auto i : str) cout << i << ",";
	cout << endl;

	cout << endl << "\"function\"p.center(40,\"=\") : " <<			"function"p.center(40, "=") << endl;
	cout << "pystr.count('o') : "p.ljust(32) <<						str.count('o') << endl;
	cout << "pystr.endswith('o') : "p.ljust(32) <<					str.endswith('o') << endl;
	cout << "pystr.expandtabs(3) : "p.ljust(32) <<					str.expandtabs(3) << endl;
	cout << "pystr.find(\"short\") : "p.ljust(32) <<				str.find("short") << endl;
	cout << "pystr.find(\"long\") : "p.ljust(32) <<					str.find("long") << endl;
	cout << "pystr.index(\"short\") : "p.ljust(32) <<				str.index("short") << endl;
	cout << "pystr.index(\"long\") : "p.ljust(32);
	try { cout <<													str.index("long") << endl;
	}																catch (pystr err) {	cout << err << endl; }
	cout << "pystr.isalnum() : "p.ljust(32) <<						str.isalnum() << endl;
	cout << "pystr.isalpha() : "p.ljust(32) <<						str.isalpha() << endl;
	cout << "pystr.isAscii() : "p.ljust(32) <<						str.isAscii() << endl;
	cout << "pystr.isspace() : "p.ljust(32) <<						str.isspace() << endl;
	cout << "pystr.isdecimal() : "p.ljust(32) <<					str.isdecimal() << endl;
	cout << "\"//\"p.join(pystr) : "p.ljust(32) <<					"//"p.join(str) << endl;
	pylist<pystr> list = { "Life", "is", "too", "short." };
	cout << "pylist<pystr> = " << list << endl;
	cout << "\" \"p.join(pylist<pystr>) : "p.ljust(32) <<			" "p.join(list) << endl;
	cout << "pystr.ljust(30,\"_\") : "p.ljust(32) <<				str.ljust(30,"_") << endl;
	cout << "\"pystr.lstrip()\" : "p.ljust(32) << '"' +				str.lstrip() + '"'<< endl;
	cout << "pystr.partition(\"o\") : "p.ljust(32) <<				str.partition("o") << endl;
	cout << "pystr.replace(\"short\",\"long\") : "p.ljust(32) <<	str.replace("short", "long") << endl;
	cout << "pystr.rfind('o') : "p.ljust(32) <<						str.rfind('o') << endl;
	cout << "pystr.rindex('o') : "p.ljust(32) <<					str.rindex('o') << endl;
	cout << "pystr.rjust(30,\"_\") : "p.ljust(32) <<				str.rjust(30, "_") << endl;
	cout << "pystr.rpartition(\"o\") : "p.ljust(32) <<				str.rpartition("o") << endl;
	cout << "\"pystr.rstrip()\" : "p.ljust(32) << '"' +				str.rstrip() + '"' << endl;
	cout << "pystr.split('s') : "p.ljust(32) <<						str.split('s') << endl;
	cout << "\"pystr.strip()\" : "p.ljust(32) << '"' +				str.strip() + '"' << endl;
	cout << "pystr.zfill(30) : "p.ljust(32) <<						str.zfill(30) << endl;

	cout << "len(pystr) : "p.ljust(32) <<		len(str) << endl;
	cout << "ord(\"1\") : "p.ljust(32) <<		ord("1") << endl;
	cout << "chr(49) : "p.ljust(32) <<			chr(49) << endl;
	cout << "str(49) : "p.ljust(32) <<			py::str(49) << endl;

	str = "python1\npython2\npython3\npython1972";
	cout << endl << "pystr = " << str.replace("\n","\\n") << endl;
	cout << "pystr.splitlines() : " <<	str.splitlines() << endl;

	cout << endl << "operator"p.center(40, "=") << endl;
	pystr str1 = "a";
	pystr str2 = "b";
	cout << "str1 = " << str1 << endl 
		 << "str2 = " << str2 << endl;
	cout << "str1 + str2 : "p.ljust(15) <<	 str1 + str2 << endl;
	cout << "str1 += str2 : "p.ljust(15) << (str1 += str2) << endl;
	cout << "str1 : "p.ljust(15) <<			 str1 << endl;
	cout << "str1 * 4 : "p.ljust(15) <<		(str1 * 4) << endl;
	cout << "str1 == str2 : "p.ljust(15) << (str1 == str2) << endl;
	cout << "str1 != str2 : "p.ljust(15) << (str1 != str2) << endl;
	cout << "str1 < str2 : "p.ljust(15) <<	(str1 < str2) << endl;
	cout << "str1 > str2 : "p.ljust(15) <<	(str1 > str2) << endl;

	cout << endl 
		<< "="p*40 << endl
		<< "pylist"p.center(40, "=") << endl
		<< "="p * 40 << endl << endl;
	pylist<int> list1 = { 4,5,6 };
	pylist<int> list2 = { 7,8,9 };
	pylist<int> list3 = { 1,2,3 };
	cout << "list1 = " << list1 << endl
		 << "list2 = " << list2 << endl
		 << "list3 = " << list3 << endl;
	cout << "list1 += list2 + list3 : " <<					(list1 += list2 + list3) << endl;
	cout << "list1 : " << list1 << endl;
	cout << "for (auto ele : list1) cout << ele : "p.ljust(32);
															for (auto ele : list1) cout << ele;
	cout << endl;
	cout << "pylist : "p.ljust(32) <<						list1 << " // (list1)" << endl;
	cout << "pylist.len() : "p.ljust(32) <<					list1.len() << endl;
	cout << "pylist.append(7) : "p.ljust(32) <<				list1.append(7) << endl;
	cout << "pylist.pop(3) : "p.ljust(32) <<				list1.pop(3) << endl;
	cout << "pylist : "p.ljust(32) <<						list1 << endl;
	cout << "pylist.del(2,5) : "p.ljust(32) <<				list1.del(2, 5) << endl;
	cout << "pylist.sort() : "p.ljust(32) <<				list1.sort() << endl;
	cout << "pylist.reverse() : "p.ljust(32) <<				list1.reverse() << endl;
	cout << "pylist.index(5) : "p.ljust(32) <<				list1.index(5) << endl;
	cout << "pylist.index(10) : "p.ljust(32);
	try { cout <<											list1.index(10) << endl;
	}														catch (pystr err) { cout << err << endl; }
	cout << "cout << pylist.insert(5,7) : "p.ljust(32) <<	list1.insert(5, 7) << endl;
	cout << "cout << pylist.remove(5) : "p.ljust(32) <<		list1.remove(5) << endl;
	cout << "cout << pylist.remove(10) : "p.ljust(32);
	try {
		cout << list1.remove(10) << endl;
	}
	catch (pystr err) { cout << err << endl; }
	cout << "cout << pylist.count(7) :  "p.ljust(32) <<		 list1.count(7) << endl;
	cout << "cout << pylist.extend(pylist) : "p.ljust(32) << list1.extend(list1) << endl;
	cout << "cout << pylist.clear() : "p.ljust(32) <<		 list1.clear() << endl;
	cout << "operators"p.center(40, "=") << endl;
	list1 = { 1,3,2,4,5,6,9,7,8 };
	cout << "cout << pylist(\"\", \"\") : "p.ljust(32) <<	 list1("", "") << endl;
	cout << "cout << pylist(1, 5) : "p.ljust(32) <<			 list1(1, 5) << endl;
	cout << "cout << *pylist[3] : "p.ljust(32) <<			*list1[3] << endl;
	cout << "cout << pylist * 3 : "p.ljust(32) <<			 list1 * 2 << endl;
}
