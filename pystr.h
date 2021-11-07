#pragma once
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

namespace py {
	class pystr;
	pystr py_str(const pystr& str);
#define p py_str("") %

	class pystr {
		friend std::ostream& operator<<(std::ostream& _os, const pystr& _Str);
		friend std::istream& operator>>(std::istream& _is, pystr& _Str);
		friend pystr operator+(const pystr& _Left, const pystr& _Right);
		friend pystr operator%(const pystr& _Left, const pystr& _Right);
	private:
		int size = 0;
		int volume = 1;
		char* data = (char*)calloc(1, sizeof(char));

		void extend_volume();
		void set_volume(const int _Val);

		void set_idx(int* _Idx);
		void check_idx_out_of_range(const int _Idx);

		bool is_over(int _Idx);
	public:

		pystr();		pystr(const char* _Str);		pystr(const char _Str);		pystr(const pystr& _Str);
		~pystr();
		char* begin();
		char* end();
		char* c_str();

		int len();
		int count(const pystr& _Str);
		int find(const pystr& _Str);
		int index(pystr _Str);
		pystr join(pystr _Str);
		pystr join(std::vector<pystr> _List);		pystr join(std::vector<char> _List);
		pystr upper();
		pystr lower();
		pystr strip();					pystr lstrip(); 				pystr rstrip();
		pystr replace(const pystr& _Target, const pystr& _Val);
		std::vector<pystr> split(pystr _Target = ' ');

		char operator[](int _Idx);
		pystr operator()(int _Begin, int _End, const int _Jmp = 1);				pystr operator()(const char* _Begin, int _End, const int _Jmp = 1);		pystr operator()(int _Begin, const char* _End, const int _Jmp = 1);		pystr operator()(const char* _Begin, const char* _End, const int _Jmp = 1);
		pystr& operator=(const pystr& _Right);						pystr& operator=(const char* _Right);					pystr& operator=(const char _Right);
		pystr& operator+=(const pystr& _Right);
		pystr operator*(const int _Val);
		bool operator==(const pystr& _Right);
		bool operator!=(const pystr& _Right);
		bool operator<(const pystr& _Right);
		bool operator<=(const pystr& _Right);
		bool operator>(const pystr& _Right);
		bool operator>=(const pystr& _Right);
	};
	std::ostream& operator<<(std::ostream& _os, const pystr& _Str) {
		_os << _Str.data;
		return _os;
	}
	std::istream& operator>>(std::istream& _is, pystr& _Str) {
		char _Data;
		pystr _List = p" \n" + (char)0;
		_Str = "";
		while (-1 != _List.find(_is.rdbuf()->sgetc())) _is.rdbuf()->snextc();
		while (-1 == _List.find(_Data = _is.rdbuf()->sgetc())) {
			_Str += _Data;
			_is.rdbuf()->snextc();
		}
		return _is;
	}
	pystr operator+(const pystr& _Right, const pystr& _Left) {
		pystr _rStr = _Right;
		_rStr += _Left;
		return _rStr;
	}
	pystr operator%(const pystr& _Right, const pystr& _Left) {
		return operator+(_Right, _Left);
	}

	void pystr::extend_volume() {
		this->set_volume(this->volume * 2);
	}
	void pystr::set_volume(const int _Val) {
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
	void pystr::check_idx_out_of_range(const int _Idx) {
		if (_Idx < 0 || this->size <= _Idx) throw "string index out of range";
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
		return &this->data[this->size - 1]; 
	}
	char* pystr::c_str() {
		return this->data;
	}
	int pystr::len() {
		return this->size;
	}

	int pystr::count(const pystr& _Str) {
		pystr _Scopy = _Str;

		int _Cnt = 0;
		pystr _Cmp = *this;
		int _Ssize = _Scopy.size;
		while (1) {
			int _Res = _Cmp.find(_Scopy);
			if (_Res == -1) return _Cnt;
			_Cnt++;
			if (_Res + _Ssize >= _Scopy.size) return _Cnt;
			_Cmp = _Cmp(_Res + _Ssize, "");
		}
	}
	int pystr::find(const pystr& _Str) {
		//kmp algorithm
		int _Ssize = _Str.size, _piP2 = 0;
		std::vector<int> _kmp_pi(_Ssize, 0); //get pi array
		for (int _piP1 = 0; _piP1 < _Ssize; _piP1++) {
			while (_piP2 > 0 && _Str.data[_piP1] != _Str.data[_piP2]) {
				_piP2 = _kmp_pi[_piP2 - 1];
			}
			if (_Str.data[_piP1] == _Str.data[_piP2] && _piP1 != _piP2) {
				_kmp_pi[_piP1] = ++_piP2;
			}
		}
		//find string
		pystr _Target = *this;
		int _Tsize = _Target.size;
		_piP2 = 0;
		for (int _piP1 = 0; _piP1 < _Tsize; _piP1++) {
			while (_piP2 > 0 && _Target[_piP1] != _Str.data[_piP2]) {
				_piP2 = _kmp_pi[_piP2 - 1];
			}
			if (_Target[_piP1] == _Str.data[_piP2]) {
				if (_piP2 == _Ssize - 1) return _piP1 - _Ssize + 1;
				_piP2++;
			}
		}
		return -1;
	}
	int pystr::index(pystr _Str) {
		int _Res = find(_Str);
		if (_Res == -1) throw "substring not found";
		return _Res;
	}

	pystr pystr::join(pystr _Str) {
		int _Ssize = _Str.size;
		pystr _rStr = _Str[0];
		if (_Ssize == 0) return _rStr;
		for (int _Idx = 1; _Idx < _Ssize; _Idx++) {
			_rStr += this->data;
			_rStr += _Str[_Idx];
		}
		return _rStr;
	}
	pystr pystr::join(std::vector<pystr> _List) {
		int _Lsize = _List.size();
		pystr _rStr;
		if (_Lsize == 0) return _rStr;
		_rStr += _List[0];
		for (int _Idx = 1; _Idx < _Lsize; _Idx++) {
			_rStr += this->data;
			_rStr += _List[_Idx];
		}
		return _rStr;
	}
	pystr pystr::join(std::vector<char> _List) {
		int _Lsize = _List.size();
		pystr _rStr;
		if (_Lsize == 0) return _rStr;
		_rStr = _List[0];
		for (int _Idx = 1; _Idx < _Lsize; _Idx++) {
			_rStr += this->data;
			_rStr += _List[_Idx];
		}
		return _rStr;
	}

	pystr pystr::lower() {
		pystr _rStr = *this;
		int loop = _rStr.size;
		for (int _Idx = 0; _Idx < loop; _Idx++) {
			if ('A' <= _rStr[_Idx] && _rStr[_Idx] <= 'Z') {
				_rStr.data[_Idx] += 'a' - 'A';
			}
		}
		return _rStr;
	}
	pystr pystr::upper() {
		pystr _rStr = *this;
		int loop = _rStr.size;
		for (int _Idx = 0; _Idx < loop; _Idx++) {
			if ('a' <= _rStr[_Idx] && _rStr[_Idx] <= 'z') {
				_rStr.data[_Idx] += 'A' - 'a';
			}
		}
		return _rStr;
	}

	pystr pystr::strip() {
		pystr _rStr = *this;
		return _rStr.lstrip().rstrip();
	}
	pystr pystr::lstrip() {
		pystr _rStr = *this;
		while (_rStr.size > 1 && _rStr[0] == ' ')
			_rStr = _rStr(1, "");
		if (_rStr.size == 1 && _rStr[0] == ' ') _rStr = "";
		return _rStr;
	}
	pystr pystr::rstrip() {
		pystr _rStr = *this;
		while (_rStr.size > 0 && _rStr[-1] == ' ')
			_rStr = _rStr("", -1);
		return _rStr;
	}

	pystr pystr::replace(const pystr& _Target, const pystr& _Val) {
		pystr _rStr;
		pystr _Str = *this;
		int _Tsize = _Target.size;
		while (1) {
			int _Res = _Str.find(_Target);
			if (_Res == -1) return _rStr + _Str;

			_rStr += _Str("", _Res) + _Val;
			_Str = _Str(_Res + _Tsize, "");
		}
	}

	std::vector<pystr> pystr::split(const pystr _Target) {
		std::vector<pystr> _rList;
		pystr _Str = *this;
		int _Tsize = _Target.size;
		if (_Tsize == 0) throw "empty separator";
		while (1) {
			int _Res = _Str.find(_Target);
			if (_Res == -1) {
				_rList.push_back(_Str);
				return _rList;
			}
			_rList.push_back(_Str("", _Res));
			_Str = _Str(_Res + _Tsize, "");
		}
	}

	char pystr::operator[](int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);
		char* _rChar = &(this->data[_Idx]);
		return _rChar[0];
	};
	pystr pystr::operator()(int _Begin, int _End, const int _Jmp) {
		pystr _rStr;
		pystr _Str = *this;
		this->set_idx(&_Begin);
		this->set_idx(&_End);
		this->check_idx_out_of_range(_Begin);
		this->check_idx_out_of_range(_End - ((_End > 0) ? 1 : 0));
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
	pystr pystr::operator*(int _Val) {
		if (_Val <= 0) return py_str("");
		pystr _rStr = *this;
		int _Rest_Cnt = 0;
		while (_Val > 1) {
			_rStr += _rStr;
			if (_Val % 2) _Rest_Cnt++;
			_Val /= 2;
		}
		while(_Rest_Cnt--) _rStr += *this;
		return _rStr;
	}
	bool pystr::operator==(const pystr& _Right) {
		return !std::strcmp(this->data, _Right.data);
	}
	bool pystr::operator!=(const pystr& _Right) {
		return std::strcmp(this->data, _Right.data);
	}
	bool pystr::operator<(const pystr& _Right) {
		return std::strcmp(this->data, _Right.data) < 0;
	}
	bool pystr::operator<=(const pystr& _Right) {
		return std::strcmp(this->data, _Right.data) <= 0;
	}
	bool pystr::operator>(const pystr& _Right) {
		return std::strcmp(this->data, _Right.data) > 0;
	}
	bool pystr::operator>=(const pystr& _Right) {
		return std::strcmp(this->data, _Right.data) >= 0;
	}

	pystr py_str(const pystr& _Str) {
		return _Str;
	}

	std::ostream& operator<<(std::ostream& _os, const std::vector<pystr>& _List) {
		pystr _rStr = '{';
		int _Lsize = _List.size();
		for (int _Idx = 0; _Idx < _Lsize - 1; _Idx++) {
			_rStr += "\"" + _List[_Idx] + "\", ";
		}
		_rStr += "\"" + _List[_Lsize - 1] + "\"}";
		_os << _rStr;
		return _os;
	}
}
