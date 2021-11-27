#pragma once
#ifndef _PYTHONMAIN_
#define _PYTHOMMAIN_
#include "pyerr.h"
#include "pylist.h"
#include "pystr.h"
#include <map>

namespace py {
#include <iostream>
#define in :
#define lamda [&]
	using std::pair;
	using std::map;

	template <class K, class V> std::ostream& operator<<(std::ostream& os, const map<K, V>& value) {
		os << "{";
		pylist<pystr> list;
		for (typename map<K, V>::const_iterator iter = value.begin(); iter != value.end(); iter++) {
			list.append(py::str(iter->first) + ":" + py::str(iter->second));
		}
		int length = py::len(list);
		if(length > 0) os << *list[0];
		for (int idx = 1; idx < length; idx++) {
			os << ", " << *list[idx];
		}
		return os << "}";
	}
	//has err
	/*template <typename T, typename K> pylist<K> map(std::function<K> _Func, pylist<T> _List) {
		pylist<T> _rList;
		int _Lsize = _List.len();
		for (int _Idx = 0; _Idx < _Lsize; _Idx++) {
			_rList.append(_Func(_List[_Idx]));
		}
		return _rList;
	}*/
	/**/
	/*template<class T>
	void print(T argc, ...) {
		va_list ap;

		va_start(ap, argc);
		for (int _ = 0; _ < argc; _++) {
			auto num = va_arg(ap, auto);    
			std::cout << str(num);
		}
		va_end(ap);
	}*/

	template <class T> pylist<pair<int, T>> enumerate(pylist<T> value) {
		pylist<pair<int, T>> ret_value;
		int size = py::len(value);
		for (int idx = 0; idx < size; idx++) {
			ret_value.append(std::make_pair(idx, value[idx]));
		}
		return ret_value;
	}
	pylist<pystr> list(pystr value) {
		pylist<pystr> ret_value;
		int size = py::len(value);
		for (int _Idx = 0; _Idx < size; _Idx++) {
			ret_value.append(value[_Idx]);
		}
		return ret_value;
	}
	pylist<int> range(const int start, const int stop, const int step = 1) {
		if (step == 0) ValueError("range() arg 3 must not be zero");
		pylist<int> ret_value;
		if ((stop - start) * step < 0) return ret_value;

		int s = 1;
		int value = start;
		if (step < 0) {
			s *= -1;
			value *= -1;
		}
		while (value < stop * s) {
			ret_value.append(value * s);
			value += step * s;
		}
		return ret_value;
	}
	pylist<int> range(const int stop) {
		return range(0, stop);
	}
}
#endif
