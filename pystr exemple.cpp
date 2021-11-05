#include <iostream>
#include <vector>
#include "pystr.h"

using namespace std;
using namespace py;

int main() {
	pystr python = "Python";
	
	printf("printf(\"%%s\",pystr.c_str()) : %s\n", python.c_str());
	cout << "pystr.len() : " << python.len() << endl;

	pystr var1 = "aaabbc";
	cout << "pystr.count() : " << var1.count("a") << endl;

	cout << "pystr.find() : " << python.find("Py") << endl;
	cout << "pystr.find() : " << python.find('x') << endl;

	cout << "pystr.index() : " << python.index('n') << endl;
	try { cout << python.index('x') << endl; }
	catch (const char* res) { cout << "pystr.index() : " << res << endl; }

	cout << "pystr.join(pystr) : " << py_str(",").join(python) << endl;
	vector<pystr> list(5,python);
	cout << "vector<pystr> : " << list << endl;
	cout << "pystr.join(vector<pystr>) : "  << py_str("//").join(list) << endl;

	cout << "pystr.upper() : " << python.upper() << endl;
	cout << "pystr.lower() : " << python.lower() << endl;

	pystr var2 = "   aaabbc   ";
	cout << "pystr.lstrip() : \"" << var2.lstrip() << "\"" << endl;
	cout << "pystr.rstrip() : \"" << var2.rstrip() << "\"" << endl;
	cout << "pystr.strip() : \"" << var2.strip() << "\"" << endl;

	cout << "pystr.replace(\"Pyth\",\"System \") : " << python.replace("Pyth", "System ") << endl;

	pystr var3 = "life is too short. so we need Python";
	cout << "pystr.split(\" \") : " << var3.split(" ") << endl;

	cout << "pystr[2] : " << python[2] << endl;
	cout << "pystr(2, 4) : " << python(2, 5) << endl;
	cout << "pystr(2, \"\") : " << python(2, "") << endl;
	cout << "pystr(\"\", 4) : " << python("", 5) << endl;
	cout << "pystr(\"\", \"\", 2) : " << python("", "", 2) << endl;

	cout << endl << p"="*20 + "operators" + p"="*20<< endl;
	
	cout << "py_str(\"Py\") + \"thon\" : " << py_str("Py") + "thon" << endl;
	cout << "\"Py\" + py_str(\"thon\") : " << "Py" + py_str("thon") << endl;
	cout << "p\"Py\" + \"thon\" : " << p"Py" + "thon" << endl;
	cout << "\"Py\" + p\"thon\" : " << "Py" + p"thon" << endl;
	cout << "p\"Py\" + p\"thon\" * 2 : " << p"Py" + p"thon" * 2 << endl;
	cout << "p\"Py\" % p\"thon\" * 2 : " << p"Py" % p"thon" * 2 << endl;

	pystr var4 = "I hate";
	var4 += p" " + "Cpp";
	cout << "p\"I hate\" += p\" \"+ \"Cpp\" : " << var4 << endl;
	cout << "p\"Python\" == p\"Cpp\" : " << (p"Python" == p"Cpp") << endl;
	cout << "p\"Python\" != p\"Cpp\" : " << (p"Python" != p"Cpp") << endl;

	cout << endl << p"=" * 20 + "input" + p"=" * 20 << endl;
	pystr a,b,c,d;
	cin >> a >> b >> c >> d;
	cout << a + b + c + d;
}
