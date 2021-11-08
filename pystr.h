#pragma once
#include <cstring>
#include <iostream>
#include <algorithm>
#include "pylist.h"

namespace py {
	class pystr;

	class pystr {
		friend pystr operator""p(const char* _Str, size_t len);
		friend std::ostream& operator<<(std::ostream& _os, const pystr& _Str);
		friend std::istream& operator>>(std::istream& _is, pystr& _Str);
		friend pystr operator+(const pystr& _Left, const pystr& _Right);
		friend bool operator==(const pystr& _Left, const pystr& _Right);
		friend bool operator!=(const pystr& _Left, const pystr& _Right);
		friend bool operator<(const pystr& _Left, const pystr& _Right);
		friend bool operator<=(const pystr& _Left, const pystr& _Right);
		friend bool operator>(const pystr& _Left, const pystr& _Right);
		friend bool operator>=(const pystr& _Left, const pystr& _Right);
		friend pystr operator*(const pystr& _Str, int _Val);
	private:
		int size = 0;
		int volume = 0;
		char* data;

		void volume_setup();
		void extend_volume();
		void set_volume(const int _Val);

		void set_idx(int* _Idx);
		void set_large_idx(int* _Idx);
		void check_idx_out_of_range(const int _Idx);

		bool is_over(int _Idx);
	public:
		pystr();
		pystr(const char* _Str);
		pystr(const char _Str);
		pystr(const pystr& _Str);
		~pystr();

		char* begin();
		char* end();
		char* c_str();

		int len();
		int count(const pystr& _Str, int _Begin = 0);
		int count(const pystr& _Str, int _Begin, int _End);
		int find(const pystr& _Str, int _Begin, int _End);
		int find(const pystr& _Str, int _Begin = 0);
		int rfind(const pystr& _Str, int _Begin, int _End);
		int rfind(const pystr& _Str, int _Begin = 0);
		int index(const pystr& _Str);
		pystr join(const pystr& _Str);
		pystr join(py::pylist<pystr> _List);
		pystr join(py::pylist<char> _List);
		pystr upper();
		pystr lower(); pystr casefold();
		pystr swapcase();
		pystr capitalize();
		pystr title();
		pystr strip();
		pystr lstrip();
		pystr rstrip();
		pystr replace(const pystr& _Tstr, const pystr& _Val);
		pystr replace(const pystr& _Tstr, const pystr& _Val, int _Cnt);
		py::pylist<pystr> split(const pystr& _Tstr = ' ');
		pystr center(const int _Length, const pystr& _Val = ' ');
		bool endswith(const pystr& _Str, int _Begin = 0);
		bool endswith(const pystr& _Str, int _Begin, int _End); 
		pystr expandtabs(int _Val = 8);
		bool isalnum();
		bool isalpa();
		bool isASCII();
		bool isdecimal();


		pystr operator[](int _Idx);
		pystr operator()(int _Begin, int _End, const int _Jmp = 1);
		pystr operator()(const char* _Begin, int _End, const int _Jmp = 1);
		pystr operator()(int _Begin, const char* _End, const int _Jmp = 1);
		pystr operator()(const char* _Begin, const char* _End, const int _Jmp = 1);
		pystr& operator=(const pystr& _Right);
		pystr& operator=(const char* _Right);
		pystr& operator=(const char _Right);
		pystr& operator+=(const pystr& _Right);
	};
	std::ostream& operator<<(std::ostream& _os, const pystr& _Str) {
		_os << _Str.data;
		return _os;
	}
	std::istream& operator>>(std::istream& _is, pystr& _Str) {
		char _Data;
		pystr _List = " \n" + (char)0;
		_Str = "";
		while (-1 != _List.find(_is.rdbuf()->sgetc())) _is.rdbuf()->snextc();
		while (-1 == _List.find(_Data = _is.rdbuf()->sgetc())) {
			_Str += _Data;
			_is.rdbuf()->snextc();
		}
		return _is;
	}
	pystr operator ""p(const char* _Str, size_t len) {
		pystr _rStr = _Str;
		return _rStr;
	}
	pystr operator+(const pystr& _Left, const pystr& _Right) {
		pystr _rStr = _Left;
		return _rStr += _Right;
	}
	bool operator==(const pystr& _Left, const pystr& _Right) {
		return !std::strcmp(_Left.data, _Right.data);
	}
	bool operator!=(const pystr& _Left, const pystr& _Right) {
		return std::strcmp(_Left.data, _Right.data);
	}
	bool operator<(const pystr& _Left, const pystr& _Right) {
		return std::strcmp(_Left.data, _Right.data) < 0;
	}
	bool operator<=(const pystr& _Left, const pystr& _Right) {
		return std::strcmp(_Left.data, _Right.data) <= 0;
	}
	bool operator>(const pystr& _Left, const pystr& _Right) {
		return std::strcmp(_Left.data, _Right.data) > 0;
	}
	bool operator>=(const pystr& _Left, const pystr& _Right) {
		return std::strcmp(_Left.data, _Right.data) >= 0;
	}
	pystr operator*(const pystr& _Str, int _Val) {
		if (_Val <= 0) return ""p;
		if (_Val == 1) return _Str;
		return _Str * (_Val / 2) + _Str * (_Val / 2) + _Str * (_Val % 2);
	}
	void pystr::volume_setup() {
		if (this->volume == 0) {
			this->data = (char*)calloc(1, sizeof(char) * 1);
			this->volume = 1;
		}
	}
	void pystr::extend_volume() {
		if (this->volume == 0) volume_setup();
		this->set_volume(this->volume * 2);
	}
	void pystr::set_volume(const int _Val) {
		if (this->volume == 0) return volume_setup();
		while (1) {
			char* _Temp = (char*)realloc(this->data, sizeof(char) * _Val);
			if (_Temp != NULL) {
				this->data = _Temp;
				this->volume = _Val;
				break;
			}
		}
	}

	void pystr::set_idx(int* _Idx) {
		if (*_Idx < 0) *_Idx += this->size;
	}
	void pystr::set_large_idx(int* _Idx) {
		this->set_idx(_Idx);
		if (*_Idx < 0) _Idx = 0;
		if (*_Idx > (this->size)) *_Idx = this->size;
	}
	void pystr::check_idx_out_of_range(const int _Idx) {
		if (_Idx < 0 || this->size <= _Idx) throw "IndexError: string index out of range"p;
	}

	bool pystr::is_over(int _Idx) {
		return this->volume <= _Idx + 1;
	}

	pystr::pystr() {
		this->operator=("");
	}
	pystr::pystr(const char* _Str) {
		this->operator=(_Str);
	}
	pystr::pystr(const char _Str) {
		this->operator=(_Str);
	}
	pystr::pystr(const pystr& _Str) {
		//same as pystr::operator=(str)
		int _Ssize = _Str.size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (this->volume <= _Idx) this->extend_volume();
			this->data[_Idx] = _Str.data[_Idx];
		}
		if (this->volume <= _Ssize) this->extend_volume();
		this->data[_Ssize] = '\0';
		this->size = _Ssize;
	}
	pystr::~pystr() {
		free(this->data);
	}

	char* pystr::begin() {
		return &this->data[0];
	}
	char* pystr::end() {
		return &this->data[this->size];
	}
	char* pystr::c_str() {
		return this->data;
	}

	int pystr::len() {
		return this->size;
	}
	int pystr::count(const pystr& _Str, int _Begin) {
		return this->count(_Str, _Begin, this->size);
	}
	int pystr::count(const pystr& _Str, int _Begin, int _End) {
		this->set_large_idx(&_Begin); this->set_large_idx(&_End);
		pystr _Scopy = _Str;

		int _Cnt = 0;
		pystr _Tstr = this->operator()(_Begin, _End);
		int _Ssize = _Scopy.size;
		while (1) {
			int _Res = _Tstr.find(_Scopy);
			if (_Res == -1) return _Cnt;
			_Cnt++;
			if (_Res + _Ssize >= _Tstr.size) return _Cnt;
			_Tstr = _Tstr(_Res + _Ssize, "");
		}
	}
	
	int pystr::find(const pystr& _Str, int _Begin) {
		return this->find(_Str, _Begin, this->size);
	}
	int pystr::find(const pystr& _Str, int _Begin, int _End) {
		this->set_large_idx(&_Begin); this->set_large_idx(&_End);
		//kmp algorithm
		pystr _Scopy = _Str;
		int _Ssize = _Scopy.size, _piP2 = 0;
		pylist<int> _kmp_pi(_Ssize, 0); //get pi array
		for (int _piP1 = 0; _piP1 < _Ssize; _piP1++) {
			while (_piP2 > 0 && _Scopy[_piP1] != _Scopy[_piP2]) {
				_piP2 = *_kmp_pi[_piP2 - 1];
			}
			if (_Scopy[_piP1] == _Scopy[_piP2] && _piP1 != _piP2) {
				*_kmp_pi[_piP1] = ++_piP2;
			}
		}

		//find string
		pystr _Target = this->operator()(_Begin, _End);
		int _Tsize = _Target.size;
		_piP2 = 0;
		for (int _piP1 = 0; _piP1 < _Tsize; _piP1++) {
			while (_piP2 > 0 && _Target[_piP1] != _Scopy[_piP2]) {
				_piP2 = *_kmp_pi[_piP2 - 1];
			}
			if (_Target[_piP1] == _Scopy[_piP2]) {
				if (_piP2 == _Ssize - 1) return _piP1 - _Ssize + 1 + _Begin;
				_piP2++;
			}
		}
		return -1;
	}
	
	int pystr::rfind(const pystr& _Str, int _Begin) {
		return this->rfind(_Str, _Begin,this->size);
	}
	int pystr::rfind(const pystr& _Str, int _Begin, int _End) {
		this->set_idx(&_Begin); this->set_idx(&_End);
		if (_Begin < 0) _Begin = 0;
		if (_End > this->size) _End = this->size;
		//kmp algorithm
		pystr _Scopy = _Str;
		int _Ssize = _Scopy.size, _piP2 = 0;
		pylist<int> _kmp_pi(_Ssize, 0); //get pi array
		for (int _piP1 = _Ssize - 1; _piP1 >= 0; _piP1--) {
			while (_piP2 > 0 && _Scopy[_piP1] != _Scopy[_piP2]) {
				_piP2 = *_kmp_pi[_piP2 - 1];
			}
			if (_Scopy[_piP1] == _Scopy[_piP2] && _piP1 != _piP2) {
				*_kmp_pi[_piP1] = ++_piP2;
			}
		}

		//find string
		pystr _Tstr = this->operator()(_Begin, _End);
		std::cout << _Tstr;
		int _Tsize = _Tstr.size;
		_piP2 = 0;
		for (int _piP1 = _Tsize - 1; _piP1 >= 0; _piP1--) {
			while (_piP2 > 0 && _Tstr[_piP1] != _Scopy[_piP2]) {
				_piP2 = *_kmp_pi[_piP2 - 1];
			}
			if (_Tstr[_piP1] == _Scopy[_piP2]) {
				if (_piP2 == _Ssize - 1) return _piP1 + _Begin;
				_piP2++;
			}
		}
		return -1;
	}
	
	int pystr::index(const pystr& _Str) {
		int _Res = find(_Str);
		if (_Res == -1) throw "ValueError: substring not found"p;
		return _Res;
	}

	pystr pystr::join(const pystr& _Str) {
		int _Ssize = _Str.size;
		pystr _Scopy = _Str;
		pystr _rStr = _Scopy[0];
		if (_Ssize == 0) return _rStr;
		for (int _Idx = 1; _Idx < _Ssize; _Idx++) {
			_rStr += this->data;
			_rStr += _Scopy[_Idx];
		}
		return _rStr;
	}
	pystr pystr::join(pylist<pystr> _List) {
		int _Lsize = _List.len();
		pystr _rStr;
		if (_Lsize == 0) return _rStr;
		_rStr += *_List[0];
		for (int _Idx = 1; _Idx < _Lsize; _Idx++) {
			_rStr += this->data;
			_rStr += *_List[_Idx];
		}
		return _rStr;
	}
	pystr pystr::join(pylist<char> _List) {
		int _Lsize = _List.len();
		pystr _rStr;
		if (_Lsize == 0) return _rStr;
		_rStr = *_List[0];
		for (int _Idx = 1; _Idx < _Lsize; _Idx++) {
			_rStr += this->data;
			_rStr += *_List[_Idx];
		}
		return _rStr;
	}

	pystr pystr::lower() {
		pystr _rStr = *this;
		int _Ssize = _rStr.size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ('A' <= _rStr[_Idx] && _rStr[_Idx] <= 'Z') {
				_rStr.data[_Idx] += 'a' - 'A';
			}
		}
		return _rStr;
	}
	pystr pystr::casefold() {
		return this->lower();
	}
	pystr pystr::upper() {
		pystr _rStr = *this;
		int _Ssize = _rStr.size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ('a' <= _rStr[_Idx] && _rStr[_Idx] <= 'z') {
				_rStr.data[_Idx] += 'A' - 'a';
			}
		}
		return _rStr;
	}
	pystr pystr::swapcase() {
		pystr _rStr = *this;
		int _Ssize = _rStr.size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ('a' <= _rStr[_Idx] && _rStr[_Idx] <= 'z') {
				_rStr.data[_Idx] = toupper(_rStr.data[_Idx]);
			}
			else if ('A' <= _rStr[_Idx] && _rStr[_Idx] <= 'Z') {
				_rStr.data[_Idx] = tolower(_rStr.data[_Idx]);
			}
		}
		return _rStr;
	}
	pystr pystr::capitalize() {
		pystr _rStr = *this;
		int _Ssize = _rStr.size;
		bool _isUpper = true;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (_isUpper == true) {
				if ('a' <= _rStr[_Idx] && _rStr[_Idx] <= 'z') {
					_rStr.data[_Idx] = toupper(_rStr.data[_Idx]);
				}
				_isUpper = false;
			}
			else if (_isUpper == false && 'A' <= _rStr[_Idx] && _rStr[_Idx] <= 'Z') {
				_rStr.data[_Idx] = tolower(_rStr.data[_Idx]);
			}
		}
		return _rStr;
	}
	pystr pystr::title() {
		pystr _rStr = *this;
		int _Ssize = _rStr.size;
		bool _isUpper = true;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (_isUpper == true) {
				if ('a' <= _rStr[_Idx] && _rStr[_Idx] <= 'z') {
					_rStr.data[_Idx] = toupper(_rStr.data[_Idx]);
				}
				_isUpper = false;
			}
			else if (_isUpper == false && 'A' <= _rStr[_Idx] && _rStr[_Idx] <= 'Z') {
				_rStr.data[_Idx] = tolower(_rStr.data[_Idx]);
			}
			else if (_rStr[_Idx] == " " || _rStr[_Idx] == "\n") {
				_isUpper = true;
			}
		}
		return _rStr;
	}
	pystr pystr::strip() {
		pystr _rStr = *this;
		return _rStr.lstrip().rstrip();
	}
	pystr pystr::lstrip() {
		pystr _Str = *this;
		int _Idx = 0, _Ssize = _Str.size;
		while (_Idx < _Ssize && _Str[_Idx] == ' ') _Idx++;
		if (_Idx == _Ssize) return _Str = "";
		return _Str(_Idx, "");
	}
	pystr pystr::rstrip() {
		pystr _Str = *this;
		int _Idx = _Str.size;
		while (_Idx > 0 && _Str[_Idx - 1] == ' ') _Idx--;
		if (_Idx == 0) return _Str = "";
		return _Str(0, _Idx);
	}
	pystr pystr::replace(const pystr& _Tstr, const pystr& _Val) {
		return this->replace(_Tstr, _Val, this->count(_Tstr));
	}
	pystr pystr::replace(const pystr& _Tstr, const pystr& _Val, int _Cnt) {
		pystr _rStr;
		pystr _Str = *this;
		int _Tsize = _Tstr.size;
		while (1) {
			int _Res = _Str.find(_Tstr);
			if (_Res == -1 || _Cnt <= 0) return _rStr + _Str;

			_rStr += _Str("", _Res) + _Val;
			_Str = _Str(_Res + _Tsize, "");
			_Cnt--;
		}
	}
	pylist<pystr> pystr::split(const pystr& _Tstr) {
		pylist<pystr> _rList;
		pystr _Str = *this;
		int _Tsize = _Tstr.size;
		if (_Tsize == 0) throw "ValueError: empty separator"p;
		while (1) {
			int _Res = _Str.find(_Tstr);
			if (_Res == -1) {
				_rList.append(_Str);
				return _rList;
			}
			_rList.append(_Str("", _Res));
			_Str = _Str(_Res + _Tsize, "");
		}
	}
	pystr pystr::center(const int _Length, const pystr& _Val) {
		if (_Val.size != 1) throw "TypeError: The fill character must be exactly one character long"p;
		int _Ssize = this->size;
		pystr _rStr = (_Val * (((_Length + 1) / 2) - ((_Ssize + 1) / 2))) + *this;

		_rStr += _Val * (_Length - _rStr.size);
		return _rStr;
	}
	bool pystr::endswith(const pystr& _Str, int _Begin) {
		return this->endswith(_Str, _Begin, this->size);
	}
	bool pystr::endswith(const pystr& _Str, int _Begin, int _End) {
		return (*this)(_Begin, _End)(-_Str.size, "") == _Str;
	}
	pystr pystr::expandtabs(int _Val) {
		if (_Val > 1) _Val -= 1;
		return this->replace("\t", " "p * _Val);
	}
	bool pystr::isalnum() {
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('0' < (*this)[_Idx] && (*this)[_Idx] < '9') ||
				('a' < (*this)[_Idx] && (*this)[_Idx] < 'z') ||
				('A' < (*this)[_Idx] && (*this)[_Idx] < 'Z')) continue;
			return false;
		}
		return true;
	}
	bool pystr::isalpa() {
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('a' < (*this)[_Idx] && (*this)[_Idx] < 'z') ||
				('A' < (*this)[_Idx] && (*this)[_Idx] < 'Z')) continue;
			return false;
		}
		return true;
	}
	bool pystr::isASCII() {
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((char(0x0) <= (*this)[_Idx] && (*this)[_Idx] <= char(0x7f))) continue;
			return false;
		}
		return true;
	}
	bool pystr::isdecimal() {
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('0' < (*this)[_Idx] && (*this)[_Idx] < '9')) continue;
			return false;
		}
		return true;
	}

	pystr pystr::operator[](int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);
		char* _rChar = &(this->data[_Idx]);
		return _rChar[0];
	};
	pystr pystr::operator()(int _Begin, int _End, const int _Jmp) {
		this->set_idx(&_Begin);
		this->set_idx(&_End);
		this->check_idx_out_of_range(_Begin);
		this->check_idx_out_of_range(_End - ((_End > 0) ? 1 : 0));

		pystr _rStr;
		pystr _Str = *this;
		for (int _Idx = _Begin; _Idx < _End; _Idx += _Jmp) _rStr += _Str[_Idx];
		return _rStr;
	};
	pystr pystr::operator()(const char* _Begin, int _End, const int _Jmp) {
		return this->operator()(0, _End, _Jmp);
	}
	pystr pystr::operator()(int _Begin, const char* _End, const int _Jmp) {
		return this->operator()(_Begin, this->size, _Jmp);
	}
	pystr pystr::operator()(const char* _Begin, const char* _End, const int _Jmp) {
		return this->operator()(0, this->size, _Jmp);
	}

	pystr& pystr::operator=(const pystr& _Right) {
		int _Rsize = _Right.size;
		for (int i = 0; i < _Rsize; i++) {
			if (this->is_over(i)) this->extend_volume();
			this->data[i] = _Right.data[i];
		}
		if (this->is_over(_Rsize)) this->extend_volume();
		this->data[_Rsize] = '\0';
		this->size = _Rsize;
		return *this;
	}
	pystr& pystr::operator=(const char* _Right) {
		int _Rsize = strlen(_Right);
		for (int i = 0; i < _Rsize; i++) {
			if (this->is_over(i)) this->extend_volume();
			this->data[i] = _Right[i];
		}
		if (this->is_over(_Rsize)) this->extend_volume();
		this->data[_Rsize] = '\0';
		this->size = _Rsize;
		return *this;
	}
	pystr& pystr::operator=(const char _Right) {
		if (this->is_over(0)) this->extend_volume();
		this->data[0] = _Right;
		this->data[1] = '\0';
		this->size = 1;
		return *this;
	}

	pystr& pystr::operator+=(const pystr& _Right) {
		int _Rsize = _Right.size;
		int _Ssize = this->size;
		int _Null_Idx = _Ssize + _Rsize;
		for (int _Idx = _Ssize; _Idx < _Null_Idx; _Idx++) {
			if (this->is_over(_Idx)) this->extend_volume();
			this->data[_Idx] = _Right.data[_Idx - _Ssize];
		}
		if (this->is_over(_Null_Idx)) this->extend_volume();
		this->data[_Null_Idx] = '\0';
		this->size = _Null_Idx;
		return *this;
	}
}
