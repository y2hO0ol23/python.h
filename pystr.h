#pragma once
#include <iostream>
#include <algorithm>
#include <windows.h>
#include "pylist.h"
#include <map>

namespace py {
	class pystr;
	int len(const pystr& _Str);
	int ord(const pystr& _Str);
	pystr chr(const int& _Val);
	pystr str(const double& _Val);
	
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
		friend int len(const pystr& _Str);
		friend int ord(const pystr& _Str);
	private:
		int size = 0;
		int volume = 0;
		wchar_t* data;
		pystr* is_range_base = nullptr;

		struct range_base {
			range_base() {}
			~range_base() { free(this->data); }
			pystr* data = nullptr;
			int volume = 0;
			bool flag = true;
		} _RB;

		void volume_setup();
		void extend_volume();
		void set_volume(const int _Val);
		void set_idx(int* _Idx);
		void set_large_idx(int* _Idx);
		void check_idx_out_of_range(const int _Idx);
		bool is_over(int _Idx);
		void set_size(int _Val);
		char* data_to_char();
		void set_range_base_data();
	public:
		pystr();
		pystr(const char* _Str);
		pystr(const char _Str);
		pystr(const wchar_t* _Str);
		pystr(const wchar_t _Str);
		pystr(const pystr& _Str);
		~pystr();

		pystr* begin();
		pystr* end();
		char* c_str();

		//pystr capitalize();
		//pystr casefold();
		/**/
		pystr center(const int _Length, const pystr& _Val = ' ');
		int count(const pystr& _Str, int _Begin = 0);
		int count(const pystr& _Str, int _Begin, int _End);
		bool endswith(const pystr& _Str, int _Begin = 0);
		bool endswith(const pystr& _Str, int _Begin, int _End);
		pystr expandtabs(int _Val = 8);
		int find(const pystr& _Str, int _Begin, int _End);
		int find(const pystr& _Str, int _Begin = 0);
		int index(const pystr& _Str, int _Begin, int _End);
		int index(const pystr& _Str, int _Begin = 0);
		bool isalnum();
		bool isalpha();
		bool isAscii();
		//bool isdigit();
		/**/
		bool isdecimal();
		//bool islower();
		//bool isnumeric();
		//bool isprintable();
		/**/
		bool isspace();
		//bool istitle();
		//bool isupper();
		/**/
		pystr join(const pystr& _Str);
		pystr join(pylist<pystr> _List);
		pystr join(pylist<char> _List);
		pystr ljust(const int length, const pystr& _Val = ' ');
		//pystr lower();
		/**/
		pystr lstrip();
		//pystr maketrance(const pystr& _Tstr, const pystr& _VStr, const pystr& _RStr = "");
		/**/
		pylist<pystr> partition(const pystr& _Str);
		pystr replace(const pystr& _Tstr, const pystr& _Val);
		pystr replace(const pystr& _Tstr, const pystr& _Val, int _Cnt);
		int rfind(const pystr& _Str, int _Begin, int _End);
		int rfind(const pystr& _Str, int _Begin = 0);
		int rindex(const pystr& _Str, int _Begin = 0);
		int rindex(const pystr& _Str, int _Begin, int _End);
		pystr rjust(const int length, const pystr& _Val = ' ');
		pylist<pystr> rpartition(const pystr& _Str);
		pystr rstrip();
		pylist<pystr> split(const pystr& _Tstr = ' ');
		pylist<pystr> splitlines(const bool _keepLineBreak = false);
		bool startwith(const pystr& _Str, int _Begin = 0);
		bool startwith(const pystr& _Str, int _Begin, int _End);
		pystr strip();
		//pystr swapcase();
		//pystr title();
		//pystr translate(std::map<pystr,pystr> _Dict);
		//pystr upper();
		/**/
		pystr zfill(const int _Cnt);

		pystr operator[](int _Idx);
		pystr operator()(int _Begin, int _End, const int _Jmp = 1);
		pystr operator()(const char* _Begin, int _End, const int _Jmp = 1);
		pystr operator()(int _Begin, const char* _End, const int _Jmp = 1);
		pystr operator()(const char* _Begin, const char* _End, const int _Jmp = 1);
		pystr& operator=(const pystr& _Right);
		pystr& operator=(const char* _Right);
		pystr& operator=(const char _Right);
		pystr& operator=(const wchar_t* _Right);
		pystr& operator=(const wchar_t _Right);
		pystr& operator+=(const pystr& _Right);
	};
	std::ostream& operator<<(std::ostream& _os, const pystr& _Str) {
		int nLen = WideCharToMultiByte(CP_ACP, 0, _Str.data, -1, NULL, 0, NULL, NULL);
		char* _W2B = (char*)calloc(nLen, sizeof(char) * nLen);
		WideCharToMultiByte(CP_ACP, 0, _Str.data, -1, _W2B, nLen, NULL, NULL);
		_os << _W2B;
		free(_W2B);
		return _os;
	}
	std::istream& operator>>(std::istream& _is, pystr& _Str) {
		char _Data;
		pystr _End = " \n" + (char)0;
		char *_rStr = (char*)calloc(1,sizeof(char));
		int _rStrVolume = 1;
		int _Idx = 0;
		while (-1 != _End.find(_Data = _is.rdbuf()->sgetc())) _is.rdbuf()->snextc();
		while (-1 == _End.find(_Data = _is.rdbuf()->sgetc())) {
			if (_Idx + 1 >= _rStrVolume) {
				_rStrVolume *= 2;
				while (1) {
					char* _Temp = (char*)realloc(_rStr, sizeof(char) * _rStrVolume);
					if (_Temp != NULL) {
						_rStr = _Temp;
						break;
					}
				}
			}
			_rStr[_Idx] = _Data;
			_Idx++;
			_is.rdbuf()->snextc();
		}
		_rStr[_Idx] = NULL;
		_Str = _rStr;
		free(_rStr);
		return _is;
	}
	pystr operator ""p(const char* _Str, size_t len) {
		int nLen = MultiByteToWideChar(CP_ACP, 0, _Str, strlen(_Str), NULL, NULL);
		pystr _rStr;
		_rStr.set_volume(nLen + 1);
		MultiByteToWideChar(CP_ACP, 0, _Str, strlen(_Str), _rStr.data, nLen);
		_rStr.data[nLen] = '\0';
		_rStr.size = nLen;
		return _rStr;
	}
	pystr operator+(const pystr& _Left, const pystr& _Right) {
		pystr _rStr = _Left;
		return _rStr += _Right;
	}
	bool operator==(const pystr& _Left, const pystr& _Right) {
		return !std::wcscmp(_Left.data, _Right.data);
	}
	bool operator!=(const pystr& _Left, const pystr& _Right) {
		return std::wcscmp(_Left.data, _Right.data);
	}
	bool operator<(const pystr& _Left, const pystr& _Right) {
		return std::wcscmp(_Left.data, _Right.data) < 0;
	}
	bool operator<=(const pystr& _Left, const pystr& _Right) {
		return std::wcscmp(_Left.data, _Right.data) <= 0;
	}
	bool operator>(const pystr& _Left, const pystr& _Right) {
		return std::wcscmp(_Left.data, _Right.data) > 0;
	}
	bool operator>=(const pystr& _Left, const pystr& _Right) {
		return std::wcscmp(_Left.data, _Right.data) >= 0;
	}
	pystr operator*(const pystr& _Str, int _Val) {
		if (_Val <= 0) return ""p;
		if (_Val == 1) return _Str;
		return _Str * (_Val / 2) + _Str * (_Val / 2) + _Str * (_Val % 2);
	}
	void pystr::volume_setup() {
		if (this->volume == 0) {
			this->data = (wchar_t*)calloc(1, sizeof(wchar_t) * 1);
			this->volume = 1;
		}
	}
	void pystr::extend_volume() {
		if (this->volume == 0) volume_setup();
		this->set_volume(this->volume * 2);
	}
	void pystr::set_volume(const int _Val) {
		while (1) {
			wchar_t* _Temp = (wchar_t*)realloc(this->data, sizeof(wchar_t) * _Val);
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
		if (*_Idx < 0) *_Idx = 0;
		int _Ssize = this->size;
		if (*_Idx >= _Ssize) *_Idx = _Ssize;
	}
	void pystr::check_idx_out_of_range(const int _Idx) {
		if (_Idx < 0 || this->size <= _Idx) throw "IndexError: string index out of range"p;
	}
	bool pystr::is_over(int _Idx) {
		return this->volume <= _Idx + 1;
	}
	void pystr::set_size(int _Val) {
		this->size = _Val;
		this->_RB.flag = true;
		if(is_range_base != nullptr) this->is_range_base->_RB.flag = true;
	}

	char* pystr::data_to_char() {
		pystr _Str = *this;
		int nLen = WideCharToMultiByte(CP_ACP, 0, _Str.data, -1, NULL, 0, NULL, NULL);
		char* _W2B = new char[nLen];
		WideCharToMultiByte(CP_ACP, 0, _Str.data, -1, _W2B, nLen, NULL, NULL);
		return _W2B;
	}
	void pystr::set_range_base_data() {
		int _Size = this->size;
		if (this->_RB.volume == 0) {
			this->_RB.data = (pystr*)calloc(_Size, sizeof(pystr) * _Size);
			this->_RB.volume = _Size;
		}
		else {
			while (this->_RB.volume < _Size) this->_RB.volume *= 2;
			while (1) {
				pystr* _Temp = (pystr*)realloc(this->_RB.data, sizeof(pystr) * this->_RB.volume);
				if (_Temp != NULL) {
					this->_RB.data = _Temp;
					break;
				}
			}
		}
		for (int _Idx = 0; _Idx < _Size; _Idx++) {
			this->_RB.data[_Idx] = this->data[_Idx];
			this->_RB.data[_Idx].is_range_base = this;
		}
		this->_RB.flag = false;
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
	pystr::pystr(const wchar_t* _Str) {
		this->operator=(_Str);
	}
	pystr::pystr(const wchar_t _Str) {
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
		this->set_size(_Ssize);
	}
	pystr::~pystr() {
		free(this->data);
	}

	pystr* pystr::begin() {
		if (this->_RB.flag) this->set_range_base_data();
		return &(this->_RB.data[0]);
	}
	pystr* pystr::end() {
		if (this->_RB.flag) this->set_range_base_data();
		return &(this->_RB.data[this->size]);
	}
	char* pystr::c_str() {
		return this->data_to_char();
	}


	//pystr pystr::capitalize();
	//pystr pystr::casefold();
	/**/
	pystr pystr::center(const int _Length, const pystr& _Val) {
		if (_Val.size != 1) throw "TypeError: The fill character must be exactly one character long"p;
		int _Ssize = this->size;
		pystr _rStr = (_Val * (((_Length + 1) / 2) - ((_Ssize + 1) / 2))) + *this;

		_rStr += _Val * (_Length - _rStr.size);
		return _rStr;
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
	bool pystr::endswith(const pystr& _Str, int _Begin) {
		return this->endswith(_Str, _Begin, this->size);
	}
	bool pystr::endswith(const pystr& _Str, int _Begin, int _End) {
		return (*this)[_End - 1] == _Str;
	}
	pystr pystr::expandtabs(int _Val) {
		if (_Val > 1) _Val -= 1;
		return this->replace("\t", " "p * _Val);
	}
	int pystr::find(const pystr& _Str, int _Begin) {
		return this->find(_Str, _Begin, this->size);
	}
	int pystr::find(const pystr& _Str, int _Begin, int _End) {
		pystr _Tstr = (*(this))(_Begin, _End);
		wchar_t* _Ptr = wcsstr(_Tstr.data, _Str.data);
		if (_Ptr == nullptr) return -1;
		return (_Ptr - _Tstr.data) + _Begin;
	}
	int pystr::index(const pystr& _Str, int _Begin) {
		return this->index(_Str, _Begin, this->size);
	}
	int pystr::index(const pystr& _Str, int _Begin, int _End) {
		int _Res = this->find(_Str, _Begin, _End);
		if (_Res == -1) throw "ValueError: substring not found"p;
		return _Res;
	}
	bool pystr::isalnum() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('0' < (*this)[_Idx] && (*this)[_Idx] < '9') ||
				('a' < (*this)[_Idx] && (*this)[_Idx] < 'z') ||
				('A' < (*this)[_Idx] && (*this)[_Idx] < 'Z')) continue;
			return false;
		}
		return true;
	}
	bool pystr::isalpha() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('a' < (*this)[_Idx] && (*this)[_Idx] < 'z') ||
				('A' < (*this)[_Idx] && (*this)[_Idx] < 'Z')) continue;
			return false;
		}
		return true;
	}
	bool pystr::isAscii() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((char(0x0) <= (*this)[_Idx] && (*this)[_Idx] <= char(0x7f))) continue;
			return false;
		}
		return true;
	}
	//bool pystr::isdigit();
	/**/
	bool pystr::isdecimal() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (('0' < (*this)[_Idx] && (*this)[_Idx] < '9')) continue;
			return false;
		}
		return true;
	}
	//bool pystr::islower();
	//bool pystr::isnumeric();
	//bool pystr::isprintable();
	/**/
	bool pystr::isspace() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if (this->data[0] != ' ') return false;
		}
		return true;
	}
	//bool pystr::istitle();
	//bool pystr::isupper();
	/**/
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
	pystr pystr::ljust(const int length, const pystr& _Val) {
		if (_Val.size != 1) throw "TypeError: The fill character must be exactly one character long"p;
		return this->data + _Val * (length - this->size);
	}
	//pystr pystr::lower();
	/**/
	pystr pystr::lstrip() {
		pystr _Cmp = " \t"p;
		int _Idx = 0, _Ssize = this->size;
		while (_Idx < _Ssize && _Cmp.find(this->data[_Idx]) != -1) _Idx++;
		if (_Idx == _Ssize) return "";
		return this->operator()(_Idx, "");
	}
	//std::map<int, int> pystr::maketrance(const pystr& _Tstr, const pystr& _VStr, const pystr& _RStr);
	/**/
	pylist<pystr> pystr::partition(const pystr& _Str) {
		int _Idx = this->find(_Str);
		if (_Idx == -1) _Idx = this->size;
		return { (*this)("",_Idx), _Str, (*this)(_Idx + _Str.size,"") };
	}
	pystr pystr::replace(const pystr& _Tstr, const pystr& _Val) {
		return this->replace(_Tstr, _Val, this->size);
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
	int pystr::rfind(const pystr& _Str, int _Begin) {
		return this->rfind(_Str, _Begin, this->size);
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
	int pystr::rindex(const pystr& _Str, int _Begin) {
		return this->rindex(_Str, _Begin, this->size);
	}
	int pystr::rindex(const pystr& _Str, int _Begin, int _End) {
		int _Res = this->rfind(_Str, _Begin, _End);
		if (_Res == -1) throw "ValueError: substring not found"p;
		return _Res;
	}
	pystr pystr::rjust(const int length, const pystr& _Val) {
		if (_Val.size != 1) throw "TypeError: The fill character must be exactly one character long"p;
		return _Val * (length - this->size) + this->data;
	}
	pylist<pystr> pystr::rpartition(const pystr& _Str) {
		int _Idx = this->rfind(_Str);
		if (_Idx == -1) _Idx = this->size;
		return { (*this)("",_Idx), _Str, (*this)(_Idx + _Str.size,"") };
	}
	pystr pystr::rstrip() {
		pystr _Str = *this, _Cmp = " \t"p;
		int _Idx = _Str.size;
		while (_Idx > 0 && _Cmp.find(_Str[_Idx - 1]) != -1) _Idx--;
		if (_Idx == 0) return _Str = "";
		return _Str(0, _Idx);
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
	pylist<pystr> pystr::splitlines(const bool _keepLineBreak) {
		pystr _Str = *this;
		if (_keepLineBreak == true) _Str = _Str.replace('\n', "@\n\n");
		else						_Str = _Str.replace('\n', "@\n");
		return _Str.split("@\n");
	}
	bool pystr::startwith(const pystr& _Str, int _Begin) {
		return this->startwith(_Str, _Begin, this->size);
	}
	bool pystr::startwith(const pystr& _Str, int _Begin, int _End) {
		return (*this)[_Begin] == _Str;
	}
	pystr pystr::strip() {
		pystr _rStr = *this;
		return _rStr.lstrip().rstrip();
	}
	//pystr pystr::swapcase();
	//pystr pystr::title();
	//pystr pystr::translate(std::map<pystr,pystr> _Dict);
	//pystr pystr::translate(std::map<pystr,pystr> _Dict);
	//pystr pystr::upper();
	/**/
	pystr pystr::zfill(const int _Cnt) {
		return this->rjust(_Cnt, "0");
	}

	pystr pystr::operator[](int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);
		wchar_t* _rChar = &(this->data[_Idx]);
		return _rChar[0];
	};
	pystr pystr::operator()(int _Begin, int _End, const int _Jmp) {
		this->set_large_idx(&_Begin);
		this->set_large_idx(&_End);

		pystr _rStr;
		for (int _Idx = _Begin; _Idx < _End; _Idx += _Jmp) _rStr += this->data[_Idx];
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

#pragma warning(push)
#pragma warning(disable: 4996)
	pystr& pystr::operator=(const pystr& _Right) {
		int _Null_Idx = _Right.size;
		while (this->is_over(_Null_Idx)) this->extend_volume();
		wcscpy(this->data, _Right.data);
		this->data[_Null_Idx] = '\0';
		this->set_size(_Null_Idx);
		return *this;
	}
	pystr& pystr::operator=(const char* _Right) {
		int nLen = MultiByteToWideChar(CP_ACP, 0, _Right, strlen(_Right), NULL, NULL);
		while (this->is_over(nLen)) this->extend_volume();
		MultiByteToWideChar(CP_ACP, 0, _Right, strlen(_Right), this->data, nLen);
		this->data[nLen] = '\0';
		this->set_size(nLen);
		return *this;
	}
	pystr& pystr::operator=(const char _Right) {
		char _Char2Str[2] = { _Right, '\0' };
		return this->operator=(_Char2Str);
	}
	pystr& pystr::operator=(const wchar_t* _Right) {
		int _Idx = 0;
		int _Null_Idx = this->size + wcslen(_Right);
		while (this->is_over(_Null_Idx)) this->extend_volume();
		wcscpy(this->data, _Right);
		this->data[_Null_Idx] = '\0';
		this->set_size(_Null_Idx);
		return *this;
	}
	pystr& pystr::operator=(const wchar_t _Right) {
		if (this->is_over(0)) this->extend_volume();
		this->data[0] = _Right;
		this->data[1] = '\0';
		this->set_size(1);
		return *this;
	}
	pystr& pystr::operator+=(const pystr& _Right) {
		int _Null_Idx = this->size + _Right.size;
		while (this->is_over(_Null_Idx)) this->extend_volume();
		wcscat(this->data, _Right.data);
		this->data[_Null_Idx] = '\0';
		this->set_size(_Null_Idx);
		return *this;
	}
#pragma warning(pop)

	int len(const pystr& _Str) {
		return _Str.size;
	}
	int ord(const pystr& _Str) {
		pystr _Scopy = _Str;
		if (len(_Scopy) > 1) throw "ord() expected a character, but string of length "p + str(len(_Scopy)) + " found"p;
		return (int)(_Scopy.data[0]);
	}
	pystr chr(const int& _Val) {
		if (!(0 <= _Val && _Val <= 0x10FFFF)) throw "chr() arg not in range("p + str(_Val) + ")"p;
		return (wchar_t)_Val;
	}
	pystr str(const double& _Val) {
		pystr _rStr;
		int _IntVal = (_Val + 0.00000000005);
		double _DotVal = (_Val + 0.00000000005) - _IntVal;
		while (_IntVal > 0) {
			_rStr = chr((_IntVal % 10) + ord("0")) + _rStr;
			_IntVal /= 10;
		}
		int _Time = 10;
		//              1234567890
		double _Cmp = 0.0000000001;
		if (_DotVal > _Cmp) _rStr += ".";
		while (_Time-- && _DotVal > _Cmp) {
			_DotVal *= 10;
			_rStr += chr((int)_DotVal + ord("0"));
			_DotVal -= (int)_DotVal;
			_Cmp *= 10;
		}
		return _rStr;
	}
}
