#pragma once
#include "pystr.h"
#include "pylist.h"

namespace py {
#define in :
#define lamda [&]

	template <class T> py::pylist<std::pair<int, T>> enumerate(py::pylist<T> _List) {
		py::pylist<std::pair<int, T>> _rList;
		int _Lsize = _List.size();
		for (int _Idx = 0; _Idx < _Lsize; _Idx++) {
			_rList.append(std::make_pair(_Idx, _List[_Idx]));
		}
		return _rList;
	}
	py::pylist<pystr> list(pystr _Str) {
		py::pylist<pystr> _rList;
		int size = len(_Str);
		for (int _Idx = 0; _Idx < size; _Idx++) {
			_rList.append(_Str[_Idx]);
		}
		return _rList;
	}
	//has err
	/*template <typename T, typename K> py::pylist<K> map(std::function<K> _Func, py::pylist<T> _List) {
		py::pylist<T> _rList;
		int _Lsize = _List.len();
		for (int _Idx = 0; _Idx < _Lsize; _Idx++) {
			_rList.append(_Func(_List[_Idx]));
		}
		return _rList;
	}*/
	/**/
	py::pylist<int> range(int _Begin, int _End, int _Jmp = 1) {
		py::pylist<int> _rList;
		if ((_End - _Begin) * _Jmp < 0) return _rList;
		if (_Jmp == 0) throw "range() arg 3 must not be zero"p;

		int _Flag = 1;
		if (_Jmp < 0) {
			_Flag *= -1;
			_Begin *= -1;
			_End *= -1;
			_Jmp *= -1;
		}
		for (int _Val = _Begin; _Val < _End; _Val += _Jmp) {
			_rList.append(_Val * _Flag);
		}
		return _rList;
	}
	py::pylist<int> range(const int _End) {
		return range(0, _End);
	}
}
