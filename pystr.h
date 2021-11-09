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
#pragma warning(push)
#pragma warning(disable:4455)
		friend pystr operator""p(const char* _Str, size_t len);
#pragma warning(pop)
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

		pystr lower_result();
		pystr upper_result();
		pystr casefold_result();
		bool check_alnum();
		bool check_alpha();
		bool check_Ascii();
		bool check_digit();
		bool check_decimal();
		bool check_numeric();
		bool check_printable();
		bool check_space();
	public:
		pystr();
		pystr(const char* _Str);
		pystr(const char _Str);
		pystr(const wchar_t* _Str);
		pystr(const wchar_t _Str);
		pystr(const int _UniData);
		pystr(const pystr& _Str);
		~pystr();

		pystr* begin();
		pystr* end();
		char* c_str();

		pystr capitalize();
		pystr casefold();
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
		bool isdigit();
		bool isdecimal();
		bool islower();
		bool isnumeric();
		bool isprintable();
		bool isspace();
		bool istitle();
		bool isupper();
		pystr join(const pystr& _Str);
		pystr join(py::pylist<pystr> _List);
		pystr join(py::pylist<char> _List);
		pystr ljust(const int length, const pystr& _Val = ' ');
		pystr lower();
		pystr lstrip();
		//pystr maketrance(const pystr& _Tstr, const pystr& _VStr, const pystr& _RStr = "");
		/**/
		py::pylist<pystr> partition(const pystr& _Str);
		pystr replace(const pystr& _Tstr, const pystr& _Val);
		pystr replace(const pystr& _Tstr, const pystr& _Val, int _Cnt);
		int rfind(const pystr& _Str, int _Begin, int _End);
		int rfind(const pystr& _Str, int _Begin = 0);
		int rindex(const pystr& _Str, int _Begin = 0);
		int rindex(const pystr& _Str, int _Begin, int _End);
		pystr rjust(const int length, const pystr& _Val = ' ');
		py::pylist<pystr> rpartition(const pystr& _Str);
		pystr rstrip();
		py::pylist<pystr> split(const pystr& _Tstr = ' ');
		py::pylist<pystr> splitlines(const bool _keepLineBreak = false);
		bool startwith(const pystr& _Str, int _Begin = 0);
		bool startwith(const pystr& _Str, int _Begin, int _End);
		pystr strip();
		pystr swapcase();
		pystr title();
		//pystr translate(std::map<pystr,pystr> _Dict);
		/**/
		pystr upper();
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
		pystr _End = " \n\t\0";
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
#pragma warning(push)
#pragma warning(disable:4455)
	pystr operator ""p(const char* _Str, size_t len) {
		int nLen = MultiByteToWideChar(CP_ACP, 0, _Str, strlen(_Str), NULL, NULL);
		pystr _rStr;
		_rStr.set_volume(nLen + 1);
		MultiByteToWideChar(CP_ACP, 0, _Str, strlen(_Str), _rStr.data, nLen);
		_rStr.data[nLen] = '\0';
		_rStr.size = nLen;
		return _rStr;
	}
#pragma warning(pop)
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

#pragma warning(push)
#pragma warning(disable: 4466)
#pragma warning(disable: 4566)
	pystr pystr::lower_result() {
		pystr _Chr = (*this)[0];
		if (_Chr == 304) { return "i̇"; }if (65 <= _Chr && _Chr <= 90 || 192 <= _Chr && _Chr <= 214 || 216 <= _Chr && _Chr <= 222 || 913 <= _Chr && _Chr <= 929 || 931 <= _Chr && _Chr <= 939 || 1040 <= _Chr && _Chr <= 1071 || 65313 <= _Chr && _Chr <= 65338 || 71840 <= _Chr && _Chr <= 71871 || 93760 <= _Chr && _Chr <= 93791 || false) { return ord(_Chr) + 32; }if (_Chr == 256 || _Chr == 258 || _Chr == 260 || _Chr == 262 || _Chr == 264 || _Chr == 266 || _Chr == 268 || _Chr == 270 || _Chr == 272 || _Chr == 274 || _Chr == 276 || _Chr == 278 || _Chr == 280 || _Chr == 282 || _Chr == 284 || _Chr == 286 || _Chr == 288 || _Chr == 290 || _Chr == 292 || _Chr == 294 || _Chr == 296 || _Chr == 298 || _Chr == 300 || _Chr == 302 || _Chr == 306 || _Chr == 308 || _Chr == 310 || _Chr == 313 || _Chr == 315 || _Chr == 317 || _Chr == 319 || _Chr == 321 || _Chr == 323 || _Chr == 325 || _Chr == 327 || _Chr == 330 || _Chr == 332 || _Chr == 334 || _Chr == 336 || _Chr == 338 || _Chr == 340 || _Chr == 342 || _Chr == 344 || _Chr == 346 || _Chr == 348 || _Chr == 350 || _Chr == 352 || _Chr == 354 || _Chr == 356 || _Chr == 358 || _Chr == 360 || _Chr == 362 || _Chr == 364 || _Chr == 366 || _Chr == 368 || _Chr == 370 || _Chr == 372 || _Chr == 374 || _Chr == 377 || _Chr == 379 || _Chr == 381 || _Chr == 386 || _Chr == 388 || _Chr == 391 || _Chr == 395 || _Chr == 401 || _Chr == 408 || _Chr == 416 || _Chr == 418 || _Chr == 420 || _Chr == 423 || _Chr == 428 || _Chr == 431 || _Chr == 435 || _Chr == 437 || _Chr == 440 || _Chr == 444 || _Chr == 453 || _Chr == 456 || _Chr == 459 || _Chr == 461 || _Chr == 463 || _Chr == 465 || _Chr == 467 || _Chr == 469 || _Chr == 471 || _Chr == 473 || _Chr == 475 || _Chr == 478 || _Chr == 480 || _Chr == 482 || _Chr == 484 || _Chr == 486 || _Chr == 488 || _Chr == 490 || _Chr == 492 || _Chr == 494 || _Chr == 498 || _Chr == 500 || _Chr == 504 || _Chr == 506 || _Chr == 508 || _Chr == 510 || _Chr == 512 || _Chr == 514 || _Chr == 516 || _Chr == 518 || _Chr == 520 || _Chr == 522 || _Chr == 524 || _Chr == 526 || _Chr == 528 || _Chr == 530 || _Chr == 532 || _Chr == 534 || _Chr == 536 || _Chr == 538 || _Chr == 540 || _Chr == 542 || _Chr == 546 || _Chr == 548 || _Chr == 550 || _Chr == 552 || _Chr == 554 || _Chr == 556 || _Chr == 558 || _Chr == 560 || _Chr == 562 || _Chr == 571 || _Chr == 577 || _Chr == 582 || _Chr == 584 || _Chr == 586 || _Chr == 588 || _Chr == 590 || _Chr == 880 || _Chr == 882 || _Chr == 886 || _Chr == 984 || _Chr == 986 || _Chr == 988 || _Chr == 990 || _Chr == 992 || _Chr == 994 || _Chr == 996 || _Chr == 998 || _Chr == 1000 || _Chr == 1002 || _Chr == 1004 || _Chr == 1006 || _Chr == 1015 || _Chr == 1018 || _Chr == 1120 || _Chr == 1122 || _Chr == 1124 || _Chr == 1126 || _Chr == 1128 || _Chr == 1130 || _Chr == 1132 || _Chr == 1134 || _Chr == 1136 || _Chr == 1138 || _Chr == 1140 || _Chr == 1142 || _Chr == 1144 || _Chr == 1146 || _Chr == 1148 || _Chr == 1150 || _Chr == 1152 || _Chr == 1162 || _Chr == 1164 || _Chr == 1166 || _Chr == 1168 || _Chr == 1170 || _Chr == 1172 || _Chr == 1174 || _Chr == 1176 || _Chr == 1178 || _Chr == 1180 || _Chr == 1182 || _Chr == 1184 || _Chr == 1186 || _Chr == 1188 || _Chr == 1190 || _Chr == 1192 || _Chr == 1194 || _Chr == 1196 || _Chr == 1198 || _Chr == 1200 || _Chr == 1202 || _Chr == 1204 || _Chr == 1206 || _Chr == 1208 || _Chr == 1210 || _Chr == 1212 || _Chr == 1214 || _Chr == 1217 || _Chr == 1219 || _Chr == 1221 || _Chr == 1223 || _Chr == 1225 || _Chr == 1227 || _Chr == 1229 || _Chr == 1232 || _Chr == 1234 || _Chr == 1236 || _Chr == 1238 || _Chr == 1240 || _Chr == 1242 || _Chr == 1244 || _Chr == 1246 || _Chr == 1248 || _Chr == 1250 || _Chr == 1252 || _Chr == 1254 || _Chr == 1256 || _Chr == 1258 || _Chr == 1260 || _Chr == 1262 || _Chr == 1264 || _Chr == 1266 || _Chr == 1268 || _Chr == 1270 || _Chr == 1272 || _Chr == 1274 || _Chr == 1276 || _Chr == 1278 || _Chr == 1280 || _Chr == 1282 || _Chr == 1284 || _Chr == 1286 || _Chr == 1288 || _Chr == 1290 || _Chr == 1292 || _Chr == 1294 || _Chr == 1296 || _Chr == 1298 || _Chr == 1300 || _Chr == 1302 || _Chr == 1304 || _Chr == 1306 || _Chr == 1308 || _Chr == 1310 || _Chr == 1312 || _Chr == 1314 || _Chr == 1316 || _Chr == 1318 || _Chr == 1320 || _Chr == 1322 || _Chr == 1324 || _Chr == 1326 || _Chr == 7680 || _Chr == 7682 || _Chr == 7684 || _Chr == 7686 || _Chr == 7688 || _Chr == 7690 || _Chr == 7692 || _Chr == 7694 || _Chr == 7696 || _Chr == 7698 || _Chr == 7700 || _Chr == 7702 || _Chr == 7704 || _Chr == 7706 || _Chr == 7708 || _Chr == 7710 || _Chr == 7712 || _Chr == 7714 || _Chr == 7716 || _Chr == 7718 || _Chr == 7720 || _Chr == 7722 || _Chr == 7724 || _Chr == 7726 || _Chr == 7728 || _Chr == 7730 || _Chr == 7732 || _Chr == 7734 || _Chr == 7736 || _Chr == 7738 || _Chr == 7740 || _Chr == 7742 || _Chr == 7744 || _Chr == 7746 || _Chr == 7748 || _Chr == 7750 || _Chr == 7752 || _Chr == 7754 || _Chr == 7756 || _Chr == 7758 || _Chr == 7760 || _Chr == 7762 || _Chr == 7764 || _Chr == 7766 || _Chr == 7768 || _Chr == 7770 || _Chr == 7772 || _Chr == 7774 || _Chr == 7776 || _Chr == 7778 || _Chr == 7780 || _Chr == 7782 || _Chr == 7784 || _Chr == 7786 || _Chr == 7788 || _Chr == 7790 || _Chr == 7792 || _Chr == 7794 || _Chr == 7796 || _Chr == 7798 || _Chr == 7800 || _Chr == 7802 || _Chr == 7804 || _Chr == 7806 || _Chr == 7808 || _Chr == 7810 || _Chr == 7812 || _Chr == 7814 || _Chr == 7816 || _Chr == 7818 || _Chr == 7820 || _Chr == 7822 || _Chr == 7824 || _Chr == 7826 || _Chr == 7828 || _Chr == 7840 || _Chr == 7842 || _Chr == 7844 || _Chr == 7846 || _Chr == 7848 || _Chr == 7850 || _Chr == 7852 || _Chr == 7854 || _Chr == 7856 || _Chr == 7858 || _Chr == 7860 || _Chr == 7862 || _Chr == 7864 || _Chr == 7866 || _Chr == 7868 || _Chr == 7870 || _Chr == 7872 || _Chr == 7874 || _Chr == 7876 || _Chr == 7878 || _Chr == 7880 || _Chr == 7882 || _Chr == 7884 || _Chr == 7886 || _Chr == 7888 || _Chr == 7890 || _Chr == 7892 || _Chr == 7894 || _Chr == 7896 || _Chr == 7898 || _Chr == 7900 || _Chr == 7902 || _Chr == 7904 || _Chr == 7906 || _Chr == 7908 || _Chr == 7910 || _Chr == 7912 || _Chr == 7914 || _Chr == 7916 || _Chr == 7918 || _Chr == 7920 || _Chr == 7922 || _Chr == 7924 || _Chr == 7926 || _Chr == 7928 || _Chr == 7930 || _Chr == 7932 || _Chr == 7934 || _Chr == 8579 || _Chr == 11360 || _Chr == 11367 || _Chr == 11369 || _Chr == 11371 || _Chr == 11378 || _Chr == 11381 || _Chr == 11392 || _Chr == 11394 || _Chr == 11396 || _Chr == 11398 || _Chr == 11400 || _Chr == 11402 || _Chr == 11404 || _Chr == 11406 || _Chr == 11408 || _Chr == 11410 || _Chr == 11412 || _Chr == 11414 || _Chr == 11416 || _Chr == 11418 || _Chr == 11420 || _Chr == 11422 || _Chr == 11424 || _Chr == 11426 || _Chr == 11428 || _Chr == 11430 || _Chr == 11432 || _Chr == 11434 || _Chr == 11436 || _Chr == 11438 || _Chr == 11440 || _Chr == 11442 || _Chr == 11444 || _Chr == 11446 || _Chr == 11448 || _Chr == 11450 || _Chr == 11452 || _Chr == 11454 || _Chr == 11456 || _Chr == 11458 || _Chr == 11460 || _Chr == 11462 || _Chr == 11464 || _Chr == 11466 || _Chr == 11468 || _Chr == 11470 || _Chr == 11472 || _Chr == 11474 || _Chr == 11476 || _Chr == 11478 || _Chr == 11480 || _Chr == 11482 || _Chr == 11484 || _Chr == 11486 || _Chr == 11488 || _Chr == 11490 || _Chr == 11499 || _Chr == 11501 || _Chr == 11506 || _Chr == 42560 || _Chr == 42562 || _Chr == 42564 || _Chr == 42566 || _Chr == 42568 || _Chr == 42570 || _Chr == 42572 || _Chr == 42574 || _Chr == 42576 || _Chr == 42578 || _Chr == 42580 || _Chr == 42582 || _Chr == 42584 || _Chr == 42586 || _Chr == 42588 || _Chr == 42590 || _Chr == 42592 || _Chr == 42594 || _Chr == 42596 || _Chr == 42598 || _Chr == 42600 || _Chr == 42602 || _Chr == 42604 || _Chr == 42624 || _Chr == 42626 || _Chr == 42628 || _Chr == 42630 || _Chr == 42632 || _Chr == 42634 || _Chr == 42636 || _Chr == 42638 || _Chr == 42640 || _Chr == 42642 || _Chr == 42644 || _Chr == 42646 || _Chr == 42648 || _Chr == 42650 || _Chr == 42786 || _Chr == 42788 || _Chr == 42790 || _Chr == 42792 || _Chr == 42794 || _Chr == 42796 || _Chr == 42798 || _Chr == 42802 || _Chr == 42804 || _Chr == 42806 || _Chr == 42808 || _Chr == 42810 || _Chr == 42812 || _Chr == 42814 || _Chr == 42816 || _Chr == 42818 || _Chr == 42820 || _Chr == 42822 || _Chr == 42824 || _Chr == 42826 || _Chr == 42828 || _Chr == 42830 || _Chr == 42832 || _Chr == 42834 || _Chr == 42836 || _Chr == 42838 || _Chr == 42840 || _Chr == 42842 || _Chr == 42844 || _Chr == 42846 || _Chr == 42848 || _Chr == 42850 || _Chr == 42852 || _Chr == 42854 || _Chr == 42856 || _Chr == 42858 || _Chr == 42860 || _Chr == 42862 || _Chr == 42873 || _Chr == 42875 || _Chr == 42878 || _Chr == 42880 || _Chr == 42882 || _Chr == 42884 || _Chr == 42886 || _Chr == 42891 || _Chr == 42896 || _Chr == 42898 || _Chr == 42902 || _Chr == 42904 || _Chr == 42906 || _Chr == 42908 || _Chr == 42910 || _Chr == 42912 || _Chr == 42914 || _Chr == 42916 || _Chr == 42918 || _Chr == 42920 || _Chr == 42932 || _Chr == 42934 || _Chr == 42936 || _Chr == 42938 || _Chr == 42940 || _Chr == 42942 || _Chr == 42946 || _Chr == 42951 || _Chr == 42953 || _Chr == 42997 || false) { return ord(_Chr) + 1; }if (_Chr == 376 || false) { return ord(_Chr) + -121; }if (_Chr == 385 || false) { return ord(_Chr) + 210; }if (_Chr == 390 || false) { return ord(_Chr) + 206; }if (393 <= _Chr && _Chr <= 394 || _Chr == 403 || false) { return ord(_Chr) + 205; }if (_Chr == 398 || false) { return ord(_Chr) + 79; }if (_Chr == 399 || false) { return ord(_Chr) + 202; }if (_Chr == 400 || false) { return ord(_Chr) + 203; }if (_Chr == 404 || false) { return ord(_Chr) + 207; }if (_Chr == 406 || _Chr == 412 || false) { return ord(_Chr) + 211; }if (_Chr == 407 || false) { return ord(_Chr) + 209; }if (_Chr == 413 || false) { return ord(_Chr) + 213; }if (_Chr == 415 || false) { return ord(_Chr) + 214; }if (_Chr == 422 || _Chr == 425 || _Chr == 430 || false) { return ord(_Chr) + 218; }if (433 <= _Chr && _Chr <= 434 || false) { return ord(_Chr) + 217; }if (_Chr == 439 || false) { return ord(_Chr) + 219; }if (_Chr == 452 || _Chr == 455 || _Chr == 458 || _Chr == 497 || false) { return ord(_Chr) + 2; }if (_Chr == 502 || false) { return ord(_Chr) + -97; }if (_Chr == 503 || false) { return ord(_Chr) + -56; }if (_Chr == 544 || 1021 <= _Chr && _Chr <= 1023 || false) { return ord(_Chr) + -130; }if (_Chr == 570 || false) { return ord(_Chr) + 10795; }if (_Chr == 573 || false) { return ord(_Chr) + -163; }if (_Chr == 574 || false) { return ord(_Chr) + 10792; }if (_Chr == 579 || false) { return ord(_Chr) + -195; }if (_Chr == 580 || false) { return ord(_Chr) + 69; }if (_Chr == 581 || false) { return ord(_Chr) + 71; }if (_Chr == 895 || false) { return ord(_Chr) + 116; }if (_Chr == 902 || false) { return ord(_Chr) + 38; }if (904 <= _Chr && _Chr <= 906 || false) { return ord(_Chr) + 37; }if (_Chr == 908 || 68736 <= _Chr && _Chr <= 68786 || false) { return ord(_Chr) + 64; }if (910 <= _Chr && _Chr <= 911 || false) { return ord(_Chr) + 63; }if (_Chr == 975 || 5104 <= _Chr && _Chr <= 5109 || false) { return ord(_Chr) + 8; }if (_Chr == 1012 || false) { return ord(_Chr) + -60; }if (_Chr == 1017 || _Chr == 8172 || false) { return ord(_Chr) + -7; }if (1024 <= _Chr && _Chr <= 1039 || false) { return ord(_Chr) + 80; }if (_Chr == 1216 || false) { return ord(_Chr) + 15; }if (1329 <= _Chr && _Chr <= 1366 || 11264 <= _Chr && _Chr <= 11310 || false) { return ord(_Chr) + 48; }if (4256 <= _Chr && _Chr <= 4293 || _Chr == 4295 || _Chr == 4301 || false) { return ord(_Chr) + 7264; }if (5024 <= _Chr && _Chr <= 5103 || false) { return ord(_Chr) + 38864; }if (7312 <= _Chr && _Chr <= 7354 || 7357 <= _Chr && _Chr <= 7359 || false) { return ord(_Chr) + -3008; }if (_Chr == 7838 || false) { return ord(_Chr) + -7615; }if (7944 <= _Chr && _Chr <= 7951 || 7960 <= _Chr && _Chr <= 7965 || 7976 <= _Chr && _Chr <= 7983 || 7992 <= _Chr && _Chr <= 7999 || 8008 <= _Chr && _Chr <= 8013 || _Chr == 8025 || _Chr == 8027 || _Chr == 8029 || _Chr == 8031 || 8040 <= _Chr && _Chr <= 8047 || 8072 <= _Chr && _Chr <= 8079 || 8088 <= _Chr && _Chr <= 8095 || 8104 <= _Chr && _Chr <= 8111 || 8120 <= _Chr && _Chr <= 8121 || 8152 <= _Chr && _Chr <= 8153 || 8168 <= _Chr && _Chr <= 8169 || false) { return ord(_Chr) + -8; }if (8122 <= _Chr && _Chr <= 8123 || false) { return ord(_Chr) + -74; }if (_Chr == 8124 || _Chr == 8140 || _Chr == 8188 || false) { return ord(_Chr) + -9; }if (8136 <= _Chr && _Chr <= 8139 || false) { return ord(_Chr) + -86; }if (8154 <= _Chr && _Chr <= 8155 || false) { return ord(_Chr) + -100; }if (8170 <= _Chr && _Chr <= 8171 || false) { return ord(_Chr) + -112; }if (8184 <= _Chr && _Chr <= 8185 || false) { return ord(_Chr) + -128; }if (8186 <= _Chr && _Chr <= 8187 || false) { return ord(_Chr) + -126; }if (_Chr == 8486 || false) { return ord(_Chr) + -7517; }if (_Chr == 8490 || false) { return ord(_Chr) + -8383; }if (_Chr == 8491 || false) { return ord(_Chr) + -8262; }if (_Chr == 8498 || false) { return ord(_Chr) + 28; }if (8544 <= _Chr && _Chr <= 8559 || false) { return ord(_Chr) + 16; }if (9398 <= _Chr && _Chr <= 9423 || false) { return ord(_Chr) + 26; }if (_Chr == 11362 || false) { return ord(_Chr) + -10743; }if (_Chr == 11363 || false) { return ord(_Chr) + -3814; }if (_Chr == 11364 || false) { return ord(_Chr) + -10727; }if (_Chr == 11373 || false) { return ord(_Chr) + -10780; }if (_Chr == 11374 || false) { return ord(_Chr) + -10749; }if (_Chr == 11375 || false) { return ord(_Chr) + -10783; }if (_Chr == 11376 || false) { return ord(_Chr) + -10782; }if (11390 <= _Chr && _Chr <= 11391 || false) { return ord(_Chr) + -10815; }if (_Chr == 42877 || false) { return ord(_Chr) + -35332; }if (_Chr == 42893 || false) { return ord(_Chr) + -42280; }if (_Chr == 42922 || _Chr == 42926 || false) { return ord(_Chr) + -42308; }if (_Chr == 42923 || false) { return ord(_Chr) + -42319; }if (_Chr == 42924 || false) { return ord(_Chr) + -42315; }if (_Chr == 42925 || false) { return ord(_Chr) + -42305; }if (_Chr == 42928 || false) { return ord(_Chr) + -42258; }if (_Chr == 42929 || false) { return ord(_Chr) + -42282; }if (_Chr == 42930 || false) { return ord(_Chr) + -42261; }if (_Chr == 42931 || false) { return ord(_Chr) + 928; }if (_Chr == 42948 || false) { return ord(_Chr) + -48; }if (_Chr == 42949 || false) { return ord(_Chr) + -42307; }if (_Chr == 42950 || false) { return ord(_Chr) + -35384; }if (66560 <= _Chr && _Chr <= 66599 || 66736 <= _Chr && _Chr <= 66771 || false) { return ord(_Chr) + 40; }if (125184 <= _Chr && _Chr <= 125217 || false) { return ord(_Chr) + 34; }
		return _Chr;
	}
	pystr pystr::upper_result() {
		pystr _Chr = (*this)[0];
		if (_Chr == 223) { return "SS"; }if (_Chr == 329) { return "ʼN"; }if (_Chr == 496) { return "J̌"; }if (_Chr == 912) { return "Ϊ́"; }if (_Chr == 944) { return "Ϋ́"; }if (_Chr == 1415) { return "ԵՒ"; }if (_Chr == 7830) { return "H̱"; }if (_Chr == 7831) { return "T̈"; }if (_Chr == 7832) { return "W̊"; }if (_Chr == 7833) { return "Y̊"; }if (_Chr == 7834) { return "Aʾ"; }if (_Chr == 8016) { return "Υ̓"; }if (_Chr == 8018) { return "Υ̓̀"; }if (_Chr == 8020) { return "Υ̓́"; }if (_Chr == 8022) { return "Υ̓͂"; }if (_Chr == 8064) { return "ἈΙ"; }if (_Chr == 8065) { return "ἉΙ"; }if (_Chr == 8066) { return "ἊΙ"; }if (_Chr == 8067) { return "ἋΙ"; }if (_Chr == 8068) { return "ἌΙ"; }if (_Chr == 8069) { return "ἍΙ"; }if (_Chr == 8070) { return "ἎΙ"; }if (_Chr == 8071) { return "ἏΙ"; }if (_Chr == 8072) { return "ἈΙ"; }if (_Chr == 8073) { return "ἉΙ"; }if (_Chr == 8074) { return "ἊΙ"; }if (_Chr == 8075) { return "ἋΙ"; }if (_Chr == 8076) { return "ἌΙ"; }if (_Chr == 8077) { return "ἍΙ"; }if (_Chr == 8078) { return "ἎΙ"; }if (_Chr == 8079) { return "ἏΙ"; }if (_Chr == 8080) { return "ἨΙ"; }if (_Chr == 8081) { return "ἩΙ"; }if (_Chr == 8082) { return "ἪΙ"; }if (_Chr == 8083) { return "ἫΙ"; }if (_Chr == 8084) { return "ἬΙ"; }if (_Chr == 8085) { return "ἭΙ"; }if (_Chr == 8086) { return "ἮΙ"; }if (_Chr == 8087) { return "ἯΙ"; }if (_Chr == 8088) { return "ἨΙ"; }if (_Chr == 8089) { return "ἩΙ"; }if (_Chr == 8090) { return "ἪΙ"; }if (_Chr == 8091) { return "ἫΙ"; }if (_Chr == 8092) { return "ἬΙ"; }if (_Chr == 8093) { return "ἭΙ"; }if (_Chr == 8094) { return "ἮΙ"; }if (_Chr == 8095) { return "ἯΙ"; }if (_Chr == 8096) { return "ὨΙ"; }if (_Chr == 8097) { return "ὩΙ"; }if (_Chr == 8098) { return "ὪΙ"; }if (_Chr == 8099) { return "ὫΙ"; }if (_Chr == 8100) { return "ὬΙ"; }if (_Chr == 8101) { return "ὭΙ"; }if (_Chr == 8102) { return "ὮΙ"; }if (_Chr == 8103) { return "ὯΙ"; }if (_Chr == 8104) { return "ὨΙ"; }if (_Chr == 8105) { return "ὩΙ"; }if (_Chr == 8106) { return "ὪΙ"; }if (_Chr == 8107) { return "ὫΙ"; }if (_Chr == 8108) { return "ὬΙ"; }if (_Chr == 8109) { return "ὭΙ"; }if (_Chr == 8110) { return "ὮΙ"; }if (_Chr == 8111) { return "ὯΙ"; }if (_Chr == 8114) { return "ᾺΙ"; }if (_Chr == 8115) { return "ΑΙ"; }if (_Chr == 8116) { return "ΆΙ"; }if (_Chr == 8118) { return "Α͂"; }if (_Chr == 8119) { return "Α͂Ι"; }if (_Chr == 8124) { return "ΑΙ"; }if (_Chr == 8130) { return "ῊΙ"; }if (_Chr == 8131) { return "ΗΙ"; }if (_Chr == 8132) { return "ΉΙ"; }if (_Chr == 8134) { return "Η͂"; }if (_Chr == 8135) { return "Η͂Ι"; }if (_Chr == 8140) { return "ΗΙ"; }if (_Chr == 8146) { return "Ϊ̀"; }if (_Chr == 8147) { return "Ϊ́"; }if (_Chr == 8150) { return "Ι͂"; }if (_Chr == 8151) { return "Ϊ͂"; }if (_Chr == 8162) { return "Ϋ̀"; }if (_Chr == 8163) { return "Ϋ́"; }if (_Chr == 8164) { return "Ρ̓"; }if (_Chr == 8166) { return "Υ͂"; }if (_Chr == 8167) { return "Ϋ͂"; }if (_Chr == 8178) { return "ῺΙ"; }if (_Chr == 8179) { return "ΩΙ"; }if (_Chr == 8180) { return "ΏΙ"; }if (_Chr == 8182) { return "Ω͂"; }if (_Chr == 8183) { return "Ω͂Ι"; }if (_Chr == 8188) { return "ΩΙ"; }if (_Chr == 64256) { return "FF"; }if (_Chr == 64257) { return "FI"; }if (_Chr == 64258) { return "FL"; }if (_Chr == 64259) { return "FFI"; }if (_Chr == 64260) { return "FFL"; }if (_Chr == 64261) { return "ST"; }if (_Chr == 64262) { return "ST"; }if (_Chr == 64275) { return "ՄՆ"; }if (_Chr == 64276) { return "ՄԵ"; }if (_Chr == 64277) { return "ՄԻ"; }if (_Chr == 64278) { return "ՎՆ"; }if (_Chr == 64279) { return "ՄԽ"; }if (97 <= _Chr && _Chr <= 122 || 224 <= _Chr && _Chr <= 246 || 248 <= _Chr && _Chr <= 254 || 945 <= _Chr && _Chr <= 961 || 963 <= _Chr && _Chr <= 971 || 1072 <= _Chr && _Chr <= 1103 || 65345 <= _Chr && _Chr <= 65370 || 71872 <= _Chr && _Chr <= 71903 || 93792 <= _Chr && _Chr <= 93823 || false) { return ord(_Chr) + -32; }if (_Chr == 181 || false) { return ord(_Chr) + 743; }if (_Chr == 255 || false) { return ord(_Chr) + 121; }if (_Chr == 257 || _Chr == 259 || _Chr == 261 || _Chr == 263 || _Chr == 265 || _Chr == 267 || _Chr == 269 || _Chr == 271 || _Chr == 273 || _Chr == 275 || _Chr == 277 || _Chr == 279 || _Chr == 281 || _Chr == 283 || _Chr == 285 || _Chr == 287 || _Chr == 289 || _Chr == 291 || _Chr == 293 || _Chr == 295 || _Chr == 297 || _Chr == 299 || _Chr == 301 || _Chr == 303 || _Chr == 307 || _Chr == 309 || _Chr == 311 || _Chr == 314 || _Chr == 316 || _Chr == 318 || _Chr == 320 || _Chr == 322 || _Chr == 324 || _Chr == 326 || _Chr == 328 || _Chr == 331 || _Chr == 333 || _Chr == 335 || _Chr == 337 || _Chr == 339 || _Chr == 341 || _Chr == 343 || _Chr == 345 || _Chr == 347 || _Chr == 349 || _Chr == 351 || _Chr == 353 || _Chr == 355 || _Chr == 357 || _Chr == 359 || _Chr == 361 || _Chr == 363 || _Chr == 365 || _Chr == 367 || _Chr == 369 || _Chr == 371 || _Chr == 373 || _Chr == 375 || _Chr == 378 || _Chr == 380 || _Chr == 382 || _Chr == 387 || _Chr == 389 || _Chr == 392 || _Chr == 396 || _Chr == 402 || _Chr == 409 || _Chr == 417 || _Chr == 419 || _Chr == 421 || _Chr == 424 || _Chr == 429 || _Chr == 432 || _Chr == 436 || _Chr == 438 || _Chr == 441 || _Chr == 445 || _Chr == 453 || _Chr == 456 || _Chr == 459 || _Chr == 462 || _Chr == 464 || _Chr == 466 || _Chr == 468 || _Chr == 470 || _Chr == 472 || _Chr == 474 || _Chr == 476 || _Chr == 479 || _Chr == 481 || _Chr == 483 || _Chr == 485 || _Chr == 487 || _Chr == 489 || _Chr == 491 || _Chr == 493 || _Chr == 495 || _Chr == 498 || _Chr == 501 || _Chr == 505 || _Chr == 507 || _Chr == 509 || _Chr == 511 || _Chr == 513 || _Chr == 515 || _Chr == 517 || _Chr == 519 || _Chr == 521 || _Chr == 523 || _Chr == 525 || _Chr == 527 || _Chr == 529 || _Chr == 531 || _Chr == 533 || _Chr == 535 || _Chr == 537 || _Chr == 539 || _Chr == 541 || _Chr == 543 || _Chr == 547 || _Chr == 549 || _Chr == 551 || _Chr == 553 || _Chr == 555 || _Chr == 557 || _Chr == 559 || _Chr == 561 || _Chr == 563 || _Chr == 572 || _Chr == 578 || _Chr == 583 || _Chr == 585 || _Chr == 587 || _Chr == 589 || _Chr == 591 || _Chr == 881 || _Chr == 883 || _Chr == 887 || _Chr == 985 || _Chr == 987 || _Chr == 989 || _Chr == 991 || _Chr == 993 || _Chr == 995 || _Chr == 997 || _Chr == 999 || _Chr == 1001 || _Chr == 1003 || _Chr == 1005 || _Chr == 1007 || _Chr == 1016 || _Chr == 1019 || _Chr == 1121 || _Chr == 1123 || _Chr == 1125 || _Chr == 1127 || _Chr == 1129 || _Chr == 1131 || _Chr == 1133 || _Chr == 1135 || _Chr == 1137 || _Chr == 1139 || _Chr == 1141 || _Chr == 1143 || _Chr == 1145 || _Chr == 1147 || _Chr == 1149 || _Chr == 1151 || _Chr == 1153 || _Chr == 1163 || _Chr == 1165 || _Chr == 1167 || _Chr == 1169 || _Chr == 1171 || _Chr == 1173 || _Chr == 1175 || _Chr == 1177 || _Chr == 1179 || _Chr == 1181 || _Chr == 1183 || _Chr == 1185 || _Chr == 1187 || _Chr == 1189 || _Chr == 1191 || _Chr == 1193 || _Chr == 1195 || _Chr == 1197 || _Chr == 1199 || _Chr == 1201 || _Chr == 1203 || _Chr == 1205 || _Chr == 1207 || _Chr == 1209 || _Chr == 1211 || _Chr == 1213 || _Chr == 1215 || _Chr == 1218 || _Chr == 1220 || _Chr == 1222 || _Chr == 1224 || _Chr == 1226 || _Chr == 1228 || _Chr == 1230 || _Chr == 1233 || _Chr == 1235 || _Chr == 1237 || _Chr == 1239 || _Chr == 1241 || _Chr == 1243 || _Chr == 1245 || _Chr == 1247 || _Chr == 1249 || _Chr == 1251 || _Chr == 1253 || _Chr == 1255 || _Chr == 1257 || _Chr == 1259 || _Chr == 1261 || _Chr == 1263 || _Chr == 1265 || _Chr == 1267 || _Chr == 1269 || _Chr == 1271 || _Chr == 1273 || _Chr == 1275 || _Chr == 1277 || _Chr == 1279 || _Chr == 1281 || _Chr == 1283 || _Chr == 1285 || _Chr == 1287 || _Chr == 1289 || _Chr == 1291 || _Chr == 1293 || _Chr == 1295 || _Chr == 1297 || _Chr == 1299 || _Chr == 1301 || _Chr == 1303 || _Chr == 1305 || _Chr == 1307 || _Chr == 1309 || _Chr == 1311 || _Chr == 1313 || _Chr == 1315 || _Chr == 1317 || _Chr == 1319 || _Chr == 1321 || _Chr == 1323 || _Chr == 1325 || _Chr == 1327 || _Chr == 7681 || _Chr == 7683 || _Chr == 7685 || _Chr == 7687 || _Chr == 7689 || _Chr == 7691 || _Chr == 7693 || _Chr == 7695 || _Chr == 7697 || _Chr == 7699 || _Chr == 7701 || _Chr == 7703 || _Chr == 7705 || _Chr == 7707 || _Chr == 7709 || _Chr == 7711 || _Chr == 7713 || _Chr == 7715 || _Chr == 7717 || _Chr == 7719 || _Chr == 7721 || _Chr == 7723 || _Chr == 7725 || _Chr == 7727 || _Chr == 7729 || _Chr == 7731 || _Chr == 7733 || _Chr == 7735 || _Chr == 7737 || _Chr == 7739 || _Chr == 7741 || _Chr == 7743 || _Chr == 7745 || _Chr == 7747 || _Chr == 7749 || _Chr == 7751 || _Chr == 7753 || _Chr == 7755 || _Chr == 7757 || _Chr == 7759 || _Chr == 7761 || _Chr == 7763 || _Chr == 7765 || _Chr == 7767 || _Chr == 7769 || _Chr == 7771 || _Chr == 7773 || _Chr == 7775 || _Chr == 7777 || _Chr == 7779 || _Chr == 7781 || _Chr == 7783 || _Chr == 7785 || _Chr == 7787 || _Chr == 7789 || _Chr == 7791 || _Chr == 7793 || _Chr == 7795 || _Chr == 7797 || _Chr == 7799 || _Chr == 7801 || _Chr == 7803 || _Chr == 7805 || _Chr == 7807 || _Chr == 7809 || _Chr == 7811 || _Chr == 7813 || _Chr == 7815 || _Chr == 7817 || _Chr == 7819 || _Chr == 7821 || _Chr == 7823 || _Chr == 7825 || _Chr == 7827 || _Chr == 7829 || _Chr == 7841 || _Chr == 7843 || _Chr == 7845 || _Chr == 7847 || _Chr == 7849 || _Chr == 7851 || _Chr == 7853 || _Chr == 7855 || _Chr == 7857 || _Chr == 7859 || _Chr == 7861 || _Chr == 7863 || _Chr == 7865 || _Chr == 7867 || _Chr == 7869 || _Chr == 7871 || _Chr == 7873 || _Chr == 7875 || _Chr == 7877 || _Chr == 7879 || _Chr == 7881 || _Chr == 7883 || _Chr == 7885 || _Chr == 7887 || _Chr == 7889 || _Chr == 7891 || _Chr == 7893 || _Chr == 7895 || _Chr == 7897 || _Chr == 7899 || _Chr == 7901 || _Chr == 7903 || _Chr == 7905 || _Chr == 7907 || _Chr == 7909 || _Chr == 7911 || _Chr == 7913 || _Chr == 7915 || _Chr == 7917 || _Chr == 7919 || _Chr == 7921 || _Chr == 7923 || _Chr == 7925 || _Chr == 7927 || _Chr == 7929 || _Chr == 7931 || _Chr == 7933 || _Chr == 7935 || _Chr == 8580 || _Chr == 11361 || _Chr == 11368 || _Chr == 11370 || _Chr == 11372 || _Chr == 11379 || _Chr == 11382 || _Chr == 11393 || _Chr == 11395 || _Chr == 11397 || _Chr == 11399 || _Chr == 11401 || _Chr == 11403 || _Chr == 11405 || _Chr == 11407 || _Chr == 11409 || _Chr == 11411 || _Chr == 11413 || _Chr == 11415 || _Chr == 11417 || _Chr == 11419 || _Chr == 11421 || _Chr == 11423 || _Chr == 11425 || _Chr == 11427 || _Chr == 11429 || _Chr == 11431 || _Chr == 11433 || _Chr == 11435 || _Chr == 11437 || _Chr == 11439 || _Chr == 11441 || _Chr == 11443 || _Chr == 11445 || _Chr == 11447 || _Chr == 11449 || _Chr == 11451 || _Chr == 11453 || _Chr == 11455 || _Chr == 11457 || _Chr == 11459 || _Chr == 11461 || _Chr == 11463 || _Chr == 11465 || _Chr == 11467 || _Chr == 11469 || _Chr == 11471 || _Chr == 11473 || _Chr == 11475 || _Chr == 11477 || _Chr == 11479 || _Chr == 11481 || _Chr == 11483 || _Chr == 11485 || _Chr == 11487 || _Chr == 11489 || _Chr == 11491 || _Chr == 11500 || _Chr == 11502 || _Chr == 11507 || _Chr == 42561 || _Chr == 42563 || _Chr == 42565 || _Chr == 42567 || _Chr == 42569 || _Chr == 42571 || _Chr == 42573 || _Chr == 42575 || _Chr == 42577 || _Chr == 42579 || _Chr == 42581 || _Chr == 42583 || _Chr == 42585 || _Chr == 42587 || _Chr == 42589 || _Chr == 42591 || _Chr == 42593 || _Chr == 42595 || _Chr == 42597 || _Chr == 42599 || _Chr == 42601 || _Chr == 42603 || _Chr == 42605 || _Chr == 42625 || _Chr == 42627 || _Chr == 42629 || _Chr == 42631 || _Chr == 42633 || _Chr == 42635 || _Chr == 42637 || _Chr == 42639 || _Chr == 42641 || _Chr == 42643 || _Chr == 42645 || _Chr == 42647 || _Chr == 42649 || _Chr == 42651 || _Chr == 42787 || _Chr == 42789 || _Chr == 42791 || _Chr == 42793 || _Chr == 42795 || _Chr == 42797 || _Chr == 42799 || _Chr == 42803 || _Chr == 42805 || _Chr == 42807 || _Chr == 42809 || _Chr == 42811 || _Chr == 42813 || _Chr == 42815 || _Chr == 42817 || _Chr == 42819 || _Chr == 42821 || _Chr == 42823 || _Chr == 42825 || _Chr == 42827 || _Chr == 42829 || _Chr == 42831 || _Chr == 42833 || _Chr == 42835 || _Chr == 42837 || _Chr == 42839 || _Chr == 42841 || _Chr == 42843 || _Chr == 42845 || _Chr == 42847 || _Chr == 42849 || _Chr == 42851 || _Chr == 42853 || _Chr == 42855 || _Chr == 42857 || _Chr == 42859 || _Chr == 42861 || _Chr == 42863 || _Chr == 42874 || _Chr == 42876 || _Chr == 42879 || _Chr == 42881 || _Chr == 42883 || _Chr == 42885 || _Chr == 42887 || _Chr == 42892 || _Chr == 42897 || _Chr == 42899 || _Chr == 42903 || _Chr == 42905 || _Chr == 42907 || _Chr == 42909 || _Chr == 42911 || _Chr == 42913 || _Chr == 42915 || _Chr == 42917 || _Chr == 42919 || _Chr == 42921 || _Chr == 42933 || _Chr == 42935 || _Chr == 42937 || _Chr == 42939 || _Chr == 42941 || _Chr == 42943 || _Chr == 42947 || _Chr == 42952 || _Chr == 42954 || _Chr == 42998 || false) { return ord(_Chr) + -1; }if (_Chr == 305 || false) { return ord(_Chr) + -232; }if (_Chr == 383 || false) { return ord(_Chr) + -300; }if (_Chr == 384 || false) { return ord(_Chr) + 195; }if (_Chr == 405 || false) { return ord(_Chr) + 97; }if (_Chr == 410 || false) { return ord(_Chr) + 163; }if (_Chr == 414 || 891 <= _Chr && _Chr <= 893 || false) { return ord(_Chr) + 130; }if (_Chr == 447 || false) { return ord(_Chr) + 56; }if (_Chr == 454 || _Chr == 457 || _Chr == 460 || _Chr == 499 || false) { return ord(_Chr) + -2; }if (_Chr == 477 || false) { return ord(_Chr) + -79; }if (575 <= _Chr && _Chr <= 576 || false) { return ord(_Chr) + 10815; }if (_Chr == 592 || false) { return ord(_Chr) + 10783; }if (_Chr == 593 || false) { return ord(_Chr) + 10780; }if (_Chr == 594 || false) { return ord(_Chr) + 10782; }if (_Chr == 595 || false) { return ord(_Chr) + -210; }if (_Chr == 596 || false) { return ord(_Chr) + -206; }if (598 <= _Chr && _Chr <= 599 || _Chr == 608 || false) { return ord(_Chr) + -205; }if (_Chr == 601 || false) { return ord(_Chr) + -202; }if (_Chr == 603 || false) { return ord(_Chr) + -203; }if (_Chr == 604 || false) { return ord(_Chr) + 42319; }if (_Chr == 609 || false) { return ord(_Chr) + 42315; }if (_Chr == 611 || false) { return ord(_Chr) + -207; }if (_Chr == 613 || false) { return ord(_Chr) + 42280; }if (_Chr == 614 || _Chr == 618 || false) { return ord(_Chr) + 42308; }if (_Chr == 616 || false) { return ord(_Chr) + -209; }if (_Chr == 617 || _Chr == 623 || false) { return ord(_Chr) + -211; }if (_Chr == 619 || false) { return ord(_Chr) + 10743; }if (_Chr == 620 || false) { return ord(_Chr) + 42305; }if (_Chr == 625 || false) { return ord(_Chr) + 10749; }if (_Chr == 626 || false) { return ord(_Chr) + -213; }if (_Chr == 629 || false) { return ord(_Chr) + -214; }if (_Chr == 637 || false) { return ord(_Chr) + 10727; }if (_Chr == 640 || _Chr == 643 || _Chr == 648 || false) { return ord(_Chr) + -218; }if (_Chr == 642 || false) { return ord(_Chr) + 42307; }if (_Chr == 647 || false) { return ord(_Chr) + 42282; }if (_Chr == 649 || false) { return ord(_Chr) + -69; }if (650 <= _Chr && _Chr <= 651 || false) { return ord(_Chr) + -217; }if (_Chr == 652 || false) { return ord(_Chr) + -71; }if (_Chr == 658 || false) { return ord(_Chr) + -219; }if (_Chr == 669 || false) { return ord(_Chr) + 42261; }if (_Chr == 670 || false) { return ord(_Chr) + 42258; }if (_Chr == 837 || false) { return ord(_Chr) + 84; }if (_Chr == 940 || false) { return ord(_Chr) + -38; }if (941 <= _Chr && _Chr <= 943 || false) { return ord(_Chr) + -37; }if (_Chr == 962 || false) { return ord(_Chr) + -31; }if (_Chr == 972 || 68800 <= _Chr && _Chr <= 68850 || false) { return ord(_Chr) + -64; }if (973 <= _Chr && _Chr <= 974 || false) { return ord(_Chr) + -63; }if (_Chr == 976 || false) { return ord(_Chr) + -62; }if (_Chr == 977 || false) { return ord(_Chr) + -57; }if (_Chr == 981 || false) { return ord(_Chr) + -47; }if (_Chr == 982 || false) { return ord(_Chr) + -54; }if (_Chr == 983 || 5112 <= _Chr && _Chr <= 5117 || false) { return ord(_Chr) + -8; }if (_Chr == 1008 || false) { return ord(_Chr) + -86; }if (_Chr == 1009 || 1104 <= _Chr && _Chr <= 1119 || false) { return ord(_Chr) + -80; }if (_Chr == 1010 || _Chr == 8165 || false) { return ord(_Chr) + 7; }if (_Chr == 1011 || false) { return ord(_Chr) + -116; }if (_Chr == 1013 || false) { return ord(_Chr) + -96; }if (_Chr == 1231 || false) { return ord(_Chr) + -15; }if (1377 <= _Chr && _Chr <= 1414 || 11312 <= _Chr && _Chr <= 11358 || false) { return ord(_Chr) + -48; }if (4304 <= _Chr && _Chr <= 4346 || 4349 <= _Chr && _Chr <= 4351 || false) { return ord(_Chr) + 3008; }if (_Chr == 7296 || false) { return ord(_Chr) + -6254; }if (_Chr == 7297 || false) { return ord(_Chr) + -6253; }if (_Chr == 7298 || false) { return ord(_Chr) + -6244; }if (7299 <= _Chr && _Chr <= 7300 || false) { return ord(_Chr) + -6242; }if (_Chr == 7301 || false) { return ord(_Chr) + -6243; }if (_Chr == 7302 || false) { return ord(_Chr) + -6236; }if (_Chr == 7303 || false) { return ord(_Chr) + -6181; }if (_Chr == 7304 || false) { return ord(_Chr) + 35266; }if (_Chr == 7545 || false) { return ord(_Chr) + 35332; }if (_Chr == 7549 || false) { return ord(_Chr) + 3814; }if (_Chr == 7566 || false) { return ord(_Chr) + 35384; }if (_Chr == 7835 || false) { return ord(_Chr) + -59; }if (7936 <= _Chr && _Chr <= 7943 || 7952 <= _Chr && _Chr <= 7957 || 7968 <= _Chr && _Chr <= 7975 || 7984 <= _Chr && _Chr <= 7991 || 8000 <= _Chr && _Chr <= 8005 || _Chr == 8017 || _Chr == 8019 || _Chr == 8021 || _Chr == 8023 || 8032 <= _Chr && _Chr <= 8039 || 8112 <= _Chr && _Chr <= 8113 || 8144 <= _Chr && _Chr <= 8145 || 8160 <= _Chr && _Chr <= 8161 || false) { return ord(_Chr) + 8; }if (8048 <= _Chr && _Chr <= 8049 || false) { return ord(_Chr) + 74; }if (8050 <= _Chr && _Chr <= 8053 || false) { return ord(_Chr) + 86; }if (8054 <= _Chr && _Chr <= 8055 || false) { return ord(_Chr) + 100; }if (8056 <= _Chr && _Chr <= 8057 || false) { return ord(_Chr) + 128; }if (8058 <= _Chr && _Chr <= 8059 || false) { return ord(_Chr) + 112; }if (8060 <= _Chr && _Chr <= 8061 || false) { return ord(_Chr) + 126; }if (_Chr == 8126 || false) { return ord(_Chr) + -7205; }if (_Chr == 8526 || false) { return ord(_Chr) + -28; }if (8560 <= _Chr && _Chr <= 8575 || false) { return ord(_Chr) + -16; }if (9424 <= _Chr && _Chr <= 9449 || false) { return ord(_Chr) + -26; }if (_Chr == 11365 || false) { return ord(_Chr) + -10795; }if (_Chr == 11366 || false) { return ord(_Chr) + -10792; }if (11520 <= _Chr && _Chr <= 11557 || _Chr == 11559 || _Chr == 11565 || false) { return ord(_Chr) + -7264; }if (_Chr == 42900 || false) { return ord(_Chr) + 48; }if (_Chr == 43859 || false) { return ord(_Chr) + -928; }if (43888 <= _Chr && _Chr <= 43967 || false) { return ord(_Chr) + -38864; }if (66600 <= _Chr && _Chr <= 66639 || 66776 <= _Chr && _Chr <= 66811 || false) { return ord(_Chr) + -40; }if (125218 <= _Chr && _Chr <= 125251 || false) { return ord(_Chr) + -34; }
		return _Chr;
	}
	pystr pystr::casefold_result() {
		pystr _Chr = (*this)[0];
		if (_Chr == 223) { return "ss"; }if (_Chr == 304) { return "i̇"; }if (_Chr == 329) { return "ʼn"; }if (_Chr == 496) { return "ǰ"; }if (_Chr == 912) { return "ΐ"; }if (_Chr == 944) { return "ΰ"; }if (_Chr == 1415) { return "եւ"; }if (_Chr == 7830) { return "ẖ"; }if (_Chr == 7831) { return "ẗ"; }if (_Chr == 7832) { return "ẘ"; }if (_Chr == 7833) { return "ẙ"; }if (_Chr == 7834) { return "aʾ"; }if (_Chr == 7838) { return "ss"; }if (_Chr == 8016) { return "ὐ"; }if (_Chr == 8018) { return "ὒ"; }if (_Chr == 8020) { return "ὔ"; }if (_Chr == 8022) { return "ὖ"; }if (_Chr == 8064) { return "ἀι"; }if (_Chr == 8065) { return "ἁι"; }if (_Chr == 8066) { return "ἂι"; }if (_Chr == 8067) { return "ἃι"; }if (_Chr == 8068) { return "ἄι"; }if (_Chr == 8069) { return "ἅι"; }if (_Chr == 8070) { return "ἆι"; }if (_Chr == 8071) { return "ἇι"; }if (_Chr == 8072) { return "ἀι"; }if (_Chr == 8073) { return "ἁι"; }if (_Chr == 8074) { return "ἂι"; }if (_Chr == 8075) { return "ἃι"; }if (_Chr == 8076) { return "ἄι"; }if (_Chr == 8077) { return "ἅι"; }if (_Chr == 8078) { return "ἆι"; }if (_Chr == 8079) { return "ἇι"; }if (_Chr == 8080) { return "ἠι"; }if (_Chr == 8081) { return "ἡι"; }if (_Chr == 8082) { return "ἢι"; }if (_Chr == 8083) { return "ἣι"; }if (_Chr == 8084) { return "ἤι"; }if (_Chr == 8085) { return "ἥι"; }if (_Chr == 8086) { return "ἦι"; }if (_Chr == 8087) { return "ἧι"; }if (_Chr == 8088) { return "ἠι"; }if (_Chr == 8089) { return "ἡι"; }if (_Chr == 8090) { return "ἢι"; }if (_Chr == 8091) { return "ἣι"; }if (_Chr == 8092) { return "ἤι"; }if (_Chr == 8093) { return "ἥι"; }if (_Chr == 8094) { return "ἦι"; }if (_Chr == 8095) { return "ἧι"; }if (_Chr == 8096) { return "ὠι"; }if (_Chr == 8097) { return "ὡι"; }if (_Chr == 8098) { return "ὢι"; }if (_Chr == 8099) { return "ὣι"; }if (_Chr == 8100) { return "ὤι"; }if (_Chr == 8101) { return "ὥι"; }if (_Chr == 8102) { return "ὦι"; }if (_Chr == 8103) { return "ὧι"; }if (_Chr == 8104) { return "ὠι"; }if (_Chr == 8105) { return "ὡι"; }if (_Chr == 8106) { return "ὢι"; }if (_Chr == 8107) { return "ὣι"; }if (_Chr == 8108) { return "ὤι"; }if (_Chr == 8109) { return "ὥι"; }if (_Chr == 8110) { return "ὦι"; }if (_Chr == 8111) { return "ὧι"; }if (_Chr == 8114) { return "ὰι"; }if (_Chr == 8115) { return "αι"; }if (_Chr == 8116) { return "άι"; }if (_Chr == 8118) { return "ᾶ"; }if (_Chr == 8119) { return "ᾶι"; }if (_Chr == 8124) { return "αι"; }if (_Chr == 8130) { return "ὴι"; }if (_Chr == 8131) { return "ηι"; }if (_Chr == 8132) { return "ήι"; }if (_Chr == 8134) { return "ῆ"; }if (_Chr == 8135) { return "ῆι"; }if (_Chr == 8140) { return "ηι"; }if (_Chr == 8146) { return "ῒ"; }if (_Chr == 8147) { return "ΐ"; }if (_Chr == 8150) { return "ῖ"; }if (_Chr == 8151) { return "ῗ"; }if (_Chr == 8162) { return "ῢ"; }if (_Chr == 8163) { return "ΰ"; }if (_Chr == 8164) { return "ῤ"; }if (_Chr == 8166) { return "ῦ"; }if (_Chr == 8167) { return "ῧ"; }if (_Chr == 8178) { return "ὼι"; }if (_Chr == 8179) { return "ωι"; }if (_Chr == 8180) { return "ώι"; }if (_Chr == 8182) { return "ῶ"; }if (_Chr == 8183) { return "ῶι"; }if (_Chr == 8188) { return "ωι"; }if (_Chr == 64256) { return "ff"; }if (_Chr == 64257) { return "fi"; }if (_Chr == 64258) { return "fl"; }if (_Chr == 64259) { return "ffi"; }if (_Chr == 64260) { return "ffl"; }if (_Chr == 64261) { return "st"; }if (_Chr == 64262) { return "st"; }if (_Chr == 64275) { return "մն"; }if (_Chr == 64276) { return "մե"; }if (_Chr == 64277) { return "մի"; }if (_Chr == 64278) { return "վն"; }if (_Chr == 64279) { return "մխ"; }if (65 <= _Chr && _Chr <= 90 || 192 <= _Chr && _Chr <= 214 || 216 <= _Chr && _Chr <= 222 || 913 <= _Chr && _Chr <= 929 || 931 <= _Chr && _Chr <= 939 || 1040 <= _Chr && _Chr <= 1071 || 65313 <= _Chr && _Chr <= 65338 || 71840 <= _Chr && _Chr <= 71871 || 93760 <= _Chr && _Chr <= 93791 || false) { return ord(_Chr) + 32; }if (_Chr == 181 || false) { return ord(_Chr) + 775; }if (_Chr == 256 || _Chr == 258 || _Chr == 260 || _Chr == 262 || _Chr == 264 || _Chr == 266 || _Chr == 268 || _Chr == 270 || _Chr == 272 || _Chr == 274 || _Chr == 276 || _Chr == 278 || _Chr == 280 || _Chr == 282 || _Chr == 284 || _Chr == 286 || _Chr == 288 || _Chr == 290 || _Chr == 292 || _Chr == 294 || _Chr == 296 || _Chr == 298 || _Chr == 300 || _Chr == 302 || _Chr == 306 || _Chr == 308 || _Chr == 310 || _Chr == 313 || _Chr == 315 || _Chr == 317 || _Chr == 319 || _Chr == 321 || _Chr == 323 || _Chr == 325 || _Chr == 327 || _Chr == 330 || _Chr == 332 || _Chr == 334 || _Chr == 336 || _Chr == 338 || _Chr == 340 || _Chr == 342 || _Chr == 344 || _Chr == 346 || _Chr == 348 || _Chr == 350 || _Chr == 352 || _Chr == 354 || _Chr == 356 || _Chr == 358 || _Chr == 360 || _Chr == 362 || _Chr == 364 || _Chr == 366 || _Chr == 368 || _Chr == 370 || _Chr == 372 || _Chr == 374 || _Chr == 377 || _Chr == 379 || _Chr == 381 || _Chr == 386 || _Chr == 388 || _Chr == 391 || _Chr == 395 || _Chr == 401 || _Chr == 408 || _Chr == 416 || _Chr == 418 || _Chr == 420 || _Chr == 423 || _Chr == 428 || _Chr == 431 || _Chr == 435 || _Chr == 437 || _Chr == 440 || _Chr == 444 || _Chr == 453 || _Chr == 456 || _Chr == 459 || _Chr == 461 || _Chr == 463 || _Chr == 465 || _Chr == 467 || _Chr == 469 || _Chr == 471 || _Chr == 473 || _Chr == 475 || _Chr == 478 || _Chr == 480 || _Chr == 482 || _Chr == 484 || _Chr == 486 || _Chr == 488 || _Chr == 490 || _Chr == 492 || _Chr == 494 || _Chr == 498 || _Chr == 500 || _Chr == 504 || _Chr == 506 || _Chr == 508 || _Chr == 510 || _Chr == 512 || _Chr == 514 || _Chr == 516 || _Chr == 518 || _Chr == 520 || _Chr == 522 || _Chr == 524 || _Chr == 526 || _Chr == 528 || _Chr == 530 || _Chr == 532 || _Chr == 534 || _Chr == 536 || _Chr == 538 || _Chr == 540 || _Chr == 542 || _Chr == 546 || _Chr == 548 || _Chr == 550 || _Chr == 552 || _Chr == 554 || _Chr == 556 || _Chr == 558 || _Chr == 560 || _Chr == 562 || _Chr == 571 || _Chr == 577 || _Chr == 582 || _Chr == 584 || _Chr == 586 || _Chr == 588 || _Chr == 590 || _Chr == 880 || _Chr == 882 || _Chr == 886 || _Chr == 962 || _Chr == 984 || _Chr == 986 || _Chr == 988 || _Chr == 990 || _Chr == 992 || _Chr == 994 || _Chr == 996 || _Chr == 998 || _Chr == 1000 || _Chr == 1002 || _Chr == 1004 || _Chr == 1006 || _Chr == 1015 || _Chr == 1018 || _Chr == 1120 || _Chr == 1122 || _Chr == 1124 || _Chr == 1126 || _Chr == 1128 || _Chr == 1130 || _Chr == 1132 || _Chr == 1134 || _Chr == 1136 || _Chr == 1138 || _Chr == 1140 || _Chr == 1142 || _Chr == 1144 || _Chr == 1146 || _Chr == 1148 || _Chr == 1150 || _Chr == 1152 || _Chr == 1162 || _Chr == 1164 || _Chr == 1166 || _Chr == 1168 || _Chr == 1170 || _Chr == 1172 || _Chr == 1174 || _Chr == 1176 || _Chr == 1178 || _Chr == 1180 || _Chr == 1182 || _Chr == 1184 || _Chr == 1186 || _Chr == 1188 || _Chr == 1190 || _Chr == 1192 || _Chr == 1194 || _Chr == 1196 || _Chr == 1198 || _Chr == 1200 || _Chr == 1202 || _Chr == 1204 || _Chr == 1206 || _Chr == 1208 || _Chr == 1210 || _Chr == 1212 || _Chr == 1214 || _Chr == 1217 || _Chr == 1219 || _Chr == 1221 || _Chr == 1223 || _Chr == 1225 || _Chr == 1227 || _Chr == 1229 || _Chr == 1232 || _Chr == 1234 || _Chr == 1236 || _Chr == 1238 || _Chr == 1240 || _Chr == 1242 || _Chr == 1244 || _Chr == 1246 || _Chr == 1248 || _Chr == 1250 || _Chr == 1252 || _Chr == 1254 || _Chr == 1256 || _Chr == 1258 || _Chr == 1260 || _Chr == 1262 || _Chr == 1264 || _Chr == 1266 || _Chr == 1268 || _Chr == 1270 || _Chr == 1272 || _Chr == 1274 || _Chr == 1276 || _Chr == 1278 || _Chr == 1280 || _Chr == 1282 || _Chr == 1284 || _Chr == 1286 || _Chr == 1288 || _Chr == 1290 || _Chr == 1292 || _Chr == 1294 || _Chr == 1296 || _Chr == 1298 || _Chr == 1300 || _Chr == 1302 || _Chr == 1304 || _Chr == 1306 || _Chr == 1308 || _Chr == 1310 || _Chr == 1312 || _Chr == 1314 || _Chr == 1316 || _Chr == 1318 || _Chr == 1320 || _Chr == 1322 || _Chr == 1324 || _Chr == 1326 || _Chr == 7680 || _Chr == 7682 || _Chr == 7684 || _Chr == 7686 || _Chr == 7688 || _Chr == 7690 || _Chr == 7692 || _Chr == 7694 || _Chr == 7696 || _Chr == 7698 || _Chr == 7700 || _Chr == 7702 || _Chr == 7704 || _Chr == 7706 || _Chr == 7708 || _Chr == 7710 || _Chr == 7712 || _Chr == 7714 || _Chr == 7716 || _Chr == 7718 || _Chr == 7720 || _Chr == 7722 || _Chr == 7724 || _Chr == 7726 || _Chr == 7728 || _Chr == 7730 || _Chr == 7732 || _Chr == 7734 || _Chr == 7736 || _Chr == 7738 || _Chr == 7740 || _Chr == 7742 || _Chr == 7744 || _Chr == 7746 || _Chr == 7748 || _Chr == 7750 || _Chr == 7752 || _Chr == 7754 || _Chr == 7756 || _Chr == 7758 || _Chr == 7760 || _Chr == 7762 || _Chr == 7764 || _Chr == 7766 || _Chr == 7768 || _Chr == 7770 || _Chr == 7772 || _Chr == 7774 || _Chr == 7776 || _Chr == 7778 || _Chr == 7780 || _Chr == 7782 || _Chr == 7784 || _Chr == 7786 || _Chr == 7788 || _Chr == 7790 || _Chr == 7792 || _Chr == 7794 || _Chr == 7796 || _Chr == 7798 || _Chr == 7800 || _Chr == 7802 || _Chr == 7804 || _Chr == 7806 || _Chr == 7808 || _Chr == 7810 || _Chr == 7812 || _Chr == 7814 || _Chr == 7816 || _Chr == 7818 || _Chr == 7820 || _Chr == 7822 || _Chr == 7824 || _Chr == 7826 || _Chr == 7828 || _Chr == 7840 || _Chr == 7842 || _Chr == 7844 || _Chr == 7846 || _Chr == 7848 || _Chr == 7850 || _Chr == 7852 || _Chr == 7854 || _Chr == 7856 || _Chr == 7858 || _Chr == 7860 || _Chr == 7862 || _Chr == 7864 || _Chr == 7866 || _Chr == 7868 || _Chr == 7870 || _Chr == 7872 || _Chr == 7874 || _Chr == 7876 || _Chr == 7878 || _Chr == 7880 || _Chr == 7882 || _Chr == 7884 || _Chr == 7886 || _Chr == 7888 || _Chr == 7890 || _Chr == 7892 || _Chr == 7894 || _Chr == 7896 || _Chr == 7898 || _Chr == 7900 || _Chr == 7902 || _Chr == 7904 || _Chr == 7906 || _Chr == 7908 || _Chr == 7910 || _Chr == 7912 || _Chr == 7914 || _Chr == 7916 || _Chr == 7918 || _Chr == 7920 || _Chr == 7922 || _Chr == 7924 || _Chr == 7926 || _Chr == 7928 || _Chr == 7930 || _Chr == 7932 || _Chr == 7934 || _Chr == 8579 || _Chr == 11360 || _Chr == 11367 || _Chr == 11369 || _Chr == 11371 || _Chr == 11378 || _Chr == 11381 || _Chr == 11392 || _Chr == 11394 || _Chr == 11396 || _Chr == 11398 || _Chr == 11400 || _Chr == 11402 || _Chr == 11404 || _Chr == 11406 || _Chr == 11408 || _Chr == 11410 || _Chr == 11412 || _Chr == 11414 || _Chr == 11416 || _Chr == 11418 || _Chr == 11420 || _Chr == 11422 || _Chr == 11424 || _Chr == 11426 || _Chr == 11428 || _Chr == 11430 || _Chr == 11432 || _Chr == 11434 || _Chr == 11436 || _Chr == 11438 || _Chr == 11440 || _Chr == 11442 || _Chr == 11444 || _Chr == 11446 || _Chr == 11448 || _Chr == 11450 || _Chr == 11452 || _Chr == 11454 || _Chr == 11456 || _Chr == 11458 || _Chr == 11460 || _Chr == 11462 || _Chr == 11464 || _Chr == 11466 || _Chr == 11468 || _Chr == 11470 || _Chr == 11472 || _Chr == 11474 || _Chr == 11476 || _Chr == 11478 || _Chr == 11480 || _Chr == 11482 || _Chr == 11484 || _Chr == 11486 || _Chr == 11488 || _Chr == 11490 || _Chr == 11499 || _Chr == 11501 || _Chr == 11506 || _Chr == 42560 || _Chr == 42562 || _Chr == 42564 || _Chr == 42566 || _Chr == 42568 || _Chr == 42570 || _Chr == 42572 || _Chr == 42574 || _Chr == 42576 || _Chr == 42578 || _Chr == 42580 || _Chr == 42582 || _Chr == 42584 || _Chr == 42586 || _Chr == 42588 || _Chr == 42590 || _Chr == 42592 || _Chr == 42594 || _Chr == 42596 || _Chr == 42598 || _Chr == 42600 || _Chr == 42602 || _Chr == 42604 || _Chr == 42624 || _Chr == 42626 || _Chr == 42628 || _Chr == 42630 || _Chr == 42632 || _Chr == 42634 || _Chr == 42636 || _Chr == 42638 || _Chr == 42640 || _Chr == 42642 || _Chr == 42644 || _Chr == 42646 || _Chr == 42648 || _Chr == 42650 || _Chr == 42786 || _Chr == 42788 || _Chr == 42790 || _Chr == 42792 || _Chr == 42794 || _Chr == 42796 || _Chr == 42798 || _Chr == 42802 || _Chr == 42804 || _Chr == 42806 || _Chr == 42808 || _Chr == 42810 || _Chr == 42812 || _Chr == 42814 || _Chr == 42816 || _Chr == 42818 || _Chr == 42820 || _Chr == 42822 || _Chr == 42824 || _Chr == 42826 || _Chr == 42828 || _Chr == 42830 || _Chr == 42832 || _Chr == 42834 || _Chr == 42836 || _Chr == 42838 || _Chr == 42840 || _Chr == 42842 || _Chr == 42844 || _Chr == 42846 || _Chr == 42848 || _Chr == 42850 || _Chr == 42852 || _Chr == 42854 || _Chr == 42856 || _Chr == 42858 || _Chr == 42860 || _Chr == 42862 || _Chr == 42873 || _Chr == 42875 || _Chr == 42878 || _Chr == 42880 || _Chr == 42882 || _Chr == 42884 || _Chr == 42886 || _Chr == 42891 || _Chr == 42896 || _Chr == 42898 || _Chr == 42902 || _Chr == 42904 || _Chr == 42906 || _Chr == 42908 || _Chr == 42910 || _Chr == 42912 || _Chr == 42914 || _Chr == 42916 || _Chr == 42918 || _Chr == 42920 || _Chr == 42932 || _Chr == 42934 || _Chr == 42936 || _Chr == 42938 || _Chr == 42940 || _Chr == 42942 || _Chr == 42946 || _Chr == 42951 || _Chr == 42953 || _Chr == 42997 || false) { return ord(_Chr) + 1; }if (_Chr == 376 || false) { return ord(_Chr) + -121; }if (_Chr == 383 || false) { return ord(_Chr) + -268; }if (_Chr == 385 || false) { return ord(_Chr) + 210; }if (_Chr == 390 || false) { return ord(_Chr) + 206; }if (393 <= _Chr && _Chr <= 394 || _Chr == 403 || false) { return ord(_Chr) + 205; }if (_Chr == 398 || false) { return ord(_Chr) + 79; }if (_Chr == 399 || false) { return ord(_Chr) + 202; }if (_Chr == 400 || false) { return ord(_Chr) + 203; }if (_Chr == 404 || false) { return ord(_Chr) + 207; }if (_Chr == 406 || _Chr == 412 || false) { return ord(_Chr) + 211; }if (_Chr == 407 || false) { return ord(_Chr) + 209; }if (_Chr == 413 || false) { return ord(_Chr) + 213; }if (_Chr == 415 || false) { return ord(_Chr) + 214; }if (_Chr == 422 || _Chr == 425 || _Chr == 430 || false) { return ord(_Chr) + 218; }if (433 <= _Chr && _Chr <= 434 || false) { return ord(_Chr) + 217; }if (_Chr == 439 || false) { return ord(_Chr) + 219; }if (_Chr == 452 || _Chr == 455 || _Chr == 458 || _Chr == 497 || false) { return ord(_Chr) + 2; }if (_Chr == 502 || false) { return ord(_Chr) + -97; }if (_Chr == 503 || false) { return ord(_Chr) + -56; }if (_Chr == 544 || 1021 <= _Chr && _Chr <= 1023 || false) { return ord(_Chr) + -130; }if (_Chr == 570 || false) { return ord(_Chr) + 10795; }if (_Chr == 573 || false) { return ord(_Chr) + -163; }if (_Chr == 574 || false) { return ord(_Chr) + 10792; }if (_Chr == 579 || false) { return ord(_Chr) + -195; }if (_Chr == 580 || false) { return ord(_Chr) + 69; }if (_Chr == 581 || false) { return ord(_Chr) + 71; }if (_Chr == 837 || _Chr == 895 || false) { return ord(_Chr) + 116; }if (_Chr == 902 || false) { return ord(_Chr) + 38; }if (904 <= _Chr && _Chr <= 906 || false) { return ord(_Chr) + 37; }if (_Chr == 908 || 68736 <= _Chr && _Chr <= 68786 || false) { return ord(_Chr) + 64; }if (910 <= _Chr && _Chr <= 911 || false) { return ord(_Chr) + 63; }if (_Chr == 975 || false) { return ord(_Chr) + 8; }if (_Chr == 976 || false) { return ord(_Chr) + -30; }if (_Chr == 977 || false) { return ord(_Chr) + -25; }if (_Chr == 981 || false) { return ord(_Chr) + -15; }if (_Chr == 982 || false) { return ord(_Chr) + -22; }if (_Chr == 1008 || false) { return ord(_Chr) + -54; }if (_Chr == 1009 || _Chr == 42948 || false) { return ord(_Chr) + -48; }if (_Chr == 1012 || false) { return ord(_Chr) + -60; }if (_Chr == 1013 || false) { return ord(_Chr) + -64; }if (_Chr == 1017 || _Chr == 8172 || false) { return ord(_Chr) + -7; }if (1024 <= _Chr && _Chr <= 1039 || false) { return ord(_Chr) + 80; }if (_Chr == 1216 || false) { return ord(_Chr) + 15; }if (1329 <= _Chr && _Chr <= 1366 || 11264 <= _Chr && _Chr <= 11310 || false) { return ord(_Chr) + 48; }if (4256 <= _Chr && _Chr <= 4293 || _Chr == 4295 || _Chr == 4301 || false) { return ord(_Chr) + 7264; }if (5112 <= _Chr && _Chr <= 5117 || 7944 <= _Chr && _Chr <= 7951 || 7960 <= _Chr && _Chr <= 7965 || 7976 <= _Chr && _Chr <= 7983 || 7992 <= _Chr && _Chr <= 7999 || 8008 <= _Chr && _Chr <= 8013 || _Chr == 8025 || _Chr == 8027 || _Chr == 8029 || _Chr == 8031 || 8040 <= _Chr && _Chr <= 8047 || 8120 <= _Chr && _Chr <= 8121 || 8152 <= _Chr && _Chr <= 8153 || 8168 <= _Chr && _Chr <= 8169 || false) { return ord(_Chr) + -8; }if (_Chr == 7296 || false) { return ord(_Chr) + -6222; }if (_Chr == 7297 || false) { return ord(_Chr) + -6221; }if (_Chr == 7298 || false) { return ord(_Chr) + -6212; }if (7299 <= _Chr && _Chr <= 7300 || false) { return ord(_Chr) + -6210; }if (_Chr == 7301 || false) { return ord(_Chr) + -6211; }if (_Chr == 7302 || false) { return ord(_Chr) + -6204; }if (_Chr == 7303 || false) { return ord(_Chr) + -6180; }if (_Chr == 7304 || false) { return ord(_Chr) + 35267; }if (7312 <= _Chr && _Chr <= 7354 || 7357 <= _Chr && _Chr <= 7359 || false) { return ord(_Chr) + -3008; }if (_Chr == 7835 || false) { return ord(_Chr) + -58; }if (8122 <= _Chr && _Chr <= 8123 || false) { return ord(_Chr) + -74; }if (_Chr == 8126 || false) { return ord(_Chr) + -7173; }if (8136 <= _Chr && _Chr <= 8139 || false) { return ord(_Chr) + -86; }if (8154 <= _Chr && _Chr <= 8155 || false) { return ord(_Chr) + -100; }if (8170 <= _Chr && _Chr <= 8171 || false) { return ord(_Chr) + -112; }if (8184 <= _Chr && _Chr <= 8185 || false) { return ord(_Chr) + -128; }if (8186 <= _Chr && _Chr <= 8187 || false) { return ord(_Chr) + -126; }if (_Chr == 8486 || false) { return ord(_Chr) + -7517; }if (_Chr == 8490 || false) { return ord(_Chr) + -8383; }if (_Chr == 8491 || false) { return ord(_Chr) + -8262; }if (_Chr == 8498 || false) { return ord(_Chr) + 28; }if (8544 <= _Chr && _Chr <= 8559 || false) { return ord(_Chr) + 16; }if (9398 <= _Chr && _Chr <= 9423 || false) { return ord(_Chr) + 26; }if (_Chr == 11362 || false) { return ord(_Chr) + -10743; }if (_Chr == 11363 || false) { return ord(_Chr) + -3814; }if (_Chr == 11364 || false) { return ord(_Chr) + -10727; }if (_Chr == 11373 || false) { return ord(_Chr) + -10780; }if (_Chr == 11374 || false) { return ord(_Chr) + -10749; }if (_Chr == 11375 || false) { return ord(_Chr) + -10783; }if (_Chr == 11376 || false) { return ord(_Chr) + -10782; }if (11390 <= _Chr && _Chr <= 11391 || false) { return ord(_Chr) + -10815; }if (_Chr == 42877 || false) { return ord(_Chr) + -35332; }if (_Chr == 42893 || false) { return ord(_Chr) + -42280; }if (_Chr == 42922 || _Chr == 42926 || false) { return ord(_Chr) + -42308; }if (_Chr == 42923 || false) { return ord(_Chr) + -42319; }if (_Chr == 42924 || false) { return ord(_Chr) + -42315; }if (_Chr == 42925 || false) { return ord(_Chr) + -42305; }if (_Chr == 42928 || false) { return ord(_Chr) + -42258; }if (_Chr == 42929 || false) { return ord(_Chr) + -42282; }if (_Chr == 42930 || false) { return ord(_Chr) + -42261; }if (_Chr == 42931 || false) { return ord(_Chr) + 928; }if (_Chr == 42949 || false) { return ord(_Chr) + -42307; }if (_Chr == 42950 || false) { return ord(_Chr) + -35384; }if (43888 <= _Chr && _Chr <= 43967 || false) { return ord(_Chr) + -38864; }if (66560 <= _Chr && _Chr <= 66599 || 66736 <= _Chr && _Chr <= 66771 || false) { return ord(_Chr) + 40; }if (125184 <= _Chr && _Chr <= 125217 || false) { return ord(_Chr) + 34; }
		return _Chr;
	}
#pragma warning(pop)
	bool pystr::check_alnum() {
		pystr _Chr = (*this)[0];
		if (48 <= _Chr && _Chr <= 57 || 65 <= _Chr && _Chr <= 90 || 97 <= _Chr && _Chr <= 122 || _Chr == 170 || 178 <= _Chr && _Chr <= 179 || _Chr == 181 || 185 <= _Chr && _Chr <= 186 || 188 <= _Chr && _Chr <= 190 || 192 <= _Chr && _Chr <= 214 || 216 <= _Chr && _Chr <= 246 || 248 <= _Chr && _Chr <= 705 || 710 <= _Chr && _Chr <= 721 || 736 <= _Chr && _Chr <= 740 || _Chr == 748 || _Chr == 750 || 880 <= _Chr && _Chr <= 884 || 886 <= _Chr && _Chr <= 887 || 890 <= _Chr && _Chr <= 893 || _Chr == 895 || _Chr == 902 || 904 <= _Chr && _Chr <= 906 || _Chr == 908 || 910 <= _Chr && _Chr <= 929 || 931 <= _Chr && _Chr <= 1013 || 1015 <= _Chr && _Chr <= 1153 || 1162 <= _Chr && _Chr <= 1327 || 1329 <= _Chr && _Chr <= 1366 || _Chr == 1369 || 1376 <= _Chr && _Chr <= 1416 || 1488 <= _Chr && _Chr <= 1514 || 1519 <= _Chr && _Chr <= 1522 || 1568 <= _Chr && _Chr <= 1610 || 1632 <= _Chr && _Chr <= 1641 || 1646 <= _Chr && _Chr <= 1647 || 1649 <= _Chr && _Chr <= 1747 || _Chr == 1749 || 1765 <= _Chr && _Chr <= 1766 || 1774 <= _Chr && _Chr <= 1788 || _Chr == 1791 || _Chr == 1808 || 1810 <= _Chr && _Chr <= 1839 || 1869 <= _Chr && _Chr <= 1957 || _Chr == 1969 || 1984 <= _Chr && _Chr <= 2026 || 2036 <= _Chr && _Chr <= 2037 || _Chr == 2042 || 2048 <= _Chr && _Chr <= 2069 || _Chr == 2074 || _Chr == 2084 || _Chr == 2088 || 2112 <= _Chr && _Chr <= 2136 || 2144 <= _Chr && _Chr <= 2154 || 2208 <= _Chr && _Chr <= 2228 || 2230 <= _Chr && _Chr <= 2247 || 2308 <= _Chr && _Chr <= 2361 || _Chr == 2365 || _Chr == 2384 || 2392 <= _Chr && _Chr <= 2401 || 2406 <= _Chr && _Chr <= 2415 || 2417 <= _Chr && _Chr <= 2432 || 2437 <= _Chr && _Chr <= 2444 || 2447 <= _Chr && _Chr <= 2448 || 2451 <= _Chr && _Chr <= 2472 || 2474 <= _Chr && _Chr <= 2480 || _Chr == 2482 || 2486 <= _Chr && _Chr <= 2489 || _Chr == 2493 || _Chr == 2510 || 2524 <= _Chr && _Chr <= 2525 || 2527 <= _Chr && _Chr <= 2529 || 2534 <= _Chr && _Chr <= 2545 || 2548 <= _Chr && _Chr <= 2553 || _Chr == 2556 || 2565 <= _Chr && _Chr <= 2570 || 2575 <= _Chr && _Chr <= 2576 || 2579 <= _Chr && _Chr <= 2600 || 2602 <= _Chr && _Chr <= 2608 || 2610 <= _Chr && _Chr <= 2611 || 2613 <= _Chr && _Chr <= 2614 || 2616 <= _Chr && _Chr <= 2617 || 2649 <= _Chr && _Chr <= 2652 || _Chr == 2654 || 2662 <= _Chr && _Chr <= 2671 || 2674 <= _Chr && _Chr <= 2676 || 2693 <= _Chr && _Chr <= 2701 || 2703 <= _Chr && _Chr <= 2705 || 2707 <= _Chr && _Chr <= 2728 || 2730 <= _Chr && _Chr <= 2736 || 2738 <= _Chr && _Chr <= 2739 || 2741 <= _Chr && _Chr <= 2745 || _Chr == 2749 || _Chr == 2768 || 2784 <= _Chr && _Chr <= 2785 || 2790 <= _Chr && _Chr <= 2799 || _Chr == 2809 || 2821 <= _Chr && _Chr <= 2828 || 2831 <= _Chr && _Chr <= 2832 || 2835 <= _Chr && _Chr <= 2856 || 2858 <= _Chr && _Chr <= 2864 || 2866 <= _Chr && _Chr <= 2867 || 2869 <= _Chr && _Chr <= 2873 || _Chr == 2877 || 2908 <= _Chr && _Chr <= 2909 || 2911 <= _Chr && _Chr <= 2913 || 2918 <= _Chr && _Chr <= 2927 || 2929 <= _Chr && _Chr <= 2935 || _Chr == 2947 || 2949 <= _Chr && _Chr <= 2954 || 2958 <= _Chr && _Chr <= 2960 || 2962 <= _Chr && _Chr <= 2965 || 2969 <= _Chr && _Chr <= 2970 || _Chr == 2972 || 2974 <= _Chr && _Chr <= 2975 || 2979 <= _Chr && _Chr <= 2980 || 2984 <= _Chr && _Chr <= 2986 || 2990 <= _Chr && _Chr <= 3001 || _Chr == 3024 || 3046 <= _Chr && _Chr <= 3058 || 3077 <= _Chr && _Chr <= 3084 || 3086 <= _Chr && _Chr <= 3088 || 3090 <= _Chr && _Chr <= 3112 || 3114 <= _Chr && _Chr <= 3129 || _Chr == 3133 || 3160 <= _Chr && _Chr <= 3162 || 3168 <= _Chr && _Chr <= 3169 || 3174 <= _Chr && _Chr <= 3183 || 3192 <= _Chr && _Chr <= 3198 || _Chr == 3200 || 3205 <= _Chr && _Chr <= 3212 || 3214 <= _Chr && _Chr <= 3216 || 3218 <= _Chr && _Chr <= 3240 || 3242 <= _Chr && _Chr <= 3251 || 3253 <= _Chr && _Chr <= 3257 || _Chr == 3261 || _Chr == 3294 || 3296 <= _Chr && _Chr <= 3297 || 3302 <= _Chr && _Chr <= 3311 || 3313 <= _Chr && _Chr <= 3314 || 3332 <= _Chr && _Chr <= 3340 || 3342 <= _Chr && _Chr <= 3344 || 3346 <= _Chr && _Chr <= 3386 || _Chr == 3389 || _Chr == 3406 || 3412 <= _Chr && _Chr <= 3414 || 3416 <= _Chr && _Chr <= 3425 || 3430 <= _Chr && _Chr <= 3448 || 3450 <= _Chr && _Chr <= 3455 || 3461 <= _Chr && _Chr <= 3478 || 3482 <= _Chr && _Chr <= 3505 || 3507 <= _Chr && _Chr <= 3515 || _Chr == 3517 || 3520 <= _Chr && _Chr <= 3526 || 3558 <= _Chr && _Chr <= 3567 || 3585 <= _Chr && _Chr <= 3632 || 3634 <= _Chr && _Chr <= 3635 || 3648 <= _Chr && _Chr <= 3654 || 3664 <= _Chr && _Chr <= 3673 || 3713 <= _Chr && _Chr <= 3714 || _Chr == 3716 || 3718 <= _Chr && _Chr <= 3722 || 3724 <= _Chr && _Chr <= 3747 || _Chr == 3749 || 3751 <= _Chr && _Chr <= 3760 || 3762 <= _Chr && _Chr <= 3763 || _Chr == 3773 || 3776 <= _Chr && _Chr <= 3780 || _Chr == 3782 || 3792 <= _Chr && _Chr <= 3801 || 3804 <= _Chr && _Chr <= 3807 || _Chr == 3840 || 3872 <= _Chr && _Chr <= 3891 || 3904 <= _Chr && _Chr <= 3911 || 3913 <= _Chr && _Chr <= 3948 || 3976 <= _Chr && _Chr <= 3980 || 4096 <= _Chr && _Chr <= 4138 || 4159 <= _Chr && _Chr <= 4169 || 4176 <= _Chr && _Chr <= 4181 || 4186 <= _Chr && _Chr <= 4189 || _Chr == 4193 || 4197 <= _Chr && _Chr <= 4198 || 4206 <= _Chr && _Chr <= 4208 || 4213 <= _Chr && _Chr <= 4225 || _Chr == 4238 || 4240 <= _Chr && _Chr <= 4249 || 4256 <= _Chr && _Chr <= 4293 || _Chr == 4295 || _Chr == 4301 || 4304 <= _Chr && _Chr <= 4346 || 4348 <= _Chr && _Chr <= 4680 || 4682 <= _Chr && _Chr <= 4685 || 4688 <= _Chr && _Chr <= 4694 || _Chr == 4696 || 4698 <= _Chr && _Chr <= 4701 || 4704 <= _Chr && _Chr <= 4744 || 4746 <= _Chr && _Chr <= 4749 || 4752 <= _Chr && _Chr <= 4784 || 4786 <= _Chr && _Chr <= 4789 || 4792 <= _Chr && _Chr <= 4798 || _Chr == 4800 || 4802 <= _Chr && _Chr <= 4805 || 4808 <= _Chr && _Chr <= 4822 || 4824 <= _Chr && _Chr <= 4880 || 4882 <= _Chr && _Chr <= 4885 || 4888 <= _Chr && _Chr <= 4954 || 4969 <= _Chr && _Chr <= 4988 || 4992 <= _Chr && _Chr <= 5007 || 5024 <= _Chr && _Chr <= 5109 || 5112 <= _Chr && _Chr <= 5117 || 5121 <= _Chr && _Chr <= 5740 || 5743 <= _Chr && _Chr <= 5759 || 5761 <= _Chr && _Chr <= 5786 || 5792 <= _Chr && _Chr <= 5866 || 5870 <= _Chr && _Chr <= 5880 || 5888 <= _Chr && _Chr <= 5900 || 5902 <= _Chr && _Chr <= 5905 || 5920 <= _Chr && _Chr <= 5937 || 5952 <= _Chr && _Chr <= 5969 || 5984 <= _Chr && _Chr <= 5996 || 5998 <= _Chr && _Chr <= 6000 || 6016 <= _Chr && _Chr <= 6067 || _Chr == 6103 || _Chr == 6108 || 6112 <= _Chr && _Chr <= 6121 || 6128 <= _Chr && _Chr <= 6137 || 6160 <= _Chr && _Chr <= 6169 || 6176 <= _Chr && _Chr <= 6264 || 6272 <= _Chr && _Chr <= 6276 || 6279 <= _Chr && _Chr <= 6312 || _Chr == 6314 || 6320 <= _Chr && _Chr <= 6389 || 6400 <= _Chr && _Chr <= 6430 || 6470 <= _Chr && _Chr <= 6509 || 6512 <= _Chr && _Chr <= 6516 || 6528 <= _Chr && _Chr <= 6571 || 6576 <= _Chr && _Chr <= 6601 || 6608 <= _Chr && _Chr <= 6618 || 6656 <= _Chr && _Chr <= 6678 || 6688 <= _Chr && _Chr <= 6740 || 6784 <= _Chr && _Chr <= 6793 || 6800 <= _Chr && _Chr <= 6809 || _Chr == 6823 || 6917 <= _Chr && _Chr <= 6963 || 6981 <= _Chr && _Chr <= 6987 || 6992 <= _Chr && _Chr <= 7001 || 7043 <= _Chr && _Chr <= 7072 || 7086 <= _Chr && _Chr <= 7141 || 7168 <= _Chr && _Chr <= 7203 || 7232 <= _Chr && _Chr <= 7241 || 7245 <= _Chr && _Chr <= 7293 || 7296 <= _Chr && _Chr <= 7304 || 7312 <= _Chr && _Chr <= 7354 || 7357 <= _Chr && _Chr <= 7359 || 7401 <= _Chr && _Chr <= 7404 || 7406 <= _Chr && _Chr <= 7411 || 7413 <= _Chr && _Chr <= 7414 || _Chr == 7418 || 7424 <= _Chr && _Chr <= 7615 || 7680 <= _Chr && _Chr <= 7957 || 7960 <= _Chr && _Chr <= 7965 || 7968 <= _Chr && _Chr <= 8005 || 8008 <= _Chr && _Chr <= 8013 || 8016 <= _Chr && _Chr <= 8023 || _Chr == 8025 || _Chr == 8027 || _Chr == 8029 || 8031 <= _Chr && _Chr <= 8061 || 8064 <= _Chr && _Chr <= 8116 || 8118 <= _Chr && _Chr <= 8124 || _Chr == 8126 || 8130 <= _Chr && _Chr <= 8132 || 8134 <= _Chr && _Chr <= 8140 || 8144 <= _Chr && _Chr <= 8147 || 8150 <= _Chr && _Chr <= 8155 || 8160 <= _Chr && _Chr <= 8172 || 8178 <= _Chr && _Chr <= 8180 || 8182 <= _Chr && _Chr <= 8188 || 8304 <= _Chr && _Chr <= 8305 || 8308 <= _Chr && _Chr <= 8313 || 8319 <= _Chr && _Chr <= 8329 || 8336 <= _Chr && _Chr <= 8348 || _Chr == 8450 || _Chr == 8455 || 8458 <= _Chr && _Chr <= 8467 || _Chr == 8469 || 8473 <= _Chr && _Chr <= 8477 || _Chr == 8484 || _Chr == 8486 || _Chr == 8488 || 8490 <= _Chr && _Chr <= 8493 || 8495 <= _Chr && _Chr <= 8505 || 8508 <= _Chr && _Chr <= 8511 || 8517 <= _Chr && _Chr <= 8521 || _Chr == 8526 || 8528 <= _Chr && _Chr <= 8585 || 9312 <= _Chr && _Chr <= 9371 || 9450 <= _Chr && _Chr <= 9471 || 10102 <= _Chr && _Chr <= 10131 || 11264 <= _Chr && _Chr <= 11310 || 11312 <= _Chr && _Chr <= 11358 || 11360 <= _Chr && _Chr <= 11492 || 11499 <= _Chr && _Chr <= 11502 || 11506 <= _Chr && _Chr <= 11507 || _Chr == 11517 || 11520 <= _Chr && _Chr <= 11557 || _Chr == 11559 || _Chr == 11565 || 11568 <= _Chr && _Chr <= 11623 || _Chr == 11631 || 11648 <= _Chr && _Chr <= 11670 || 11680 <= _Chr && _Chr <= 11686 || 11688 <= _Chr && _Chr <= 11694 || 11696 <= _Chr && _Chr <= 11702 || 11704 <= _Chr && _Chr <= 11710 || 11712 <= _Chr && _Chr <= 11718 || 11720 <= _Chr && _Chr <= 11726 || 11728 <= _Chr && _Chr <= 11734 || 11736 <= _Chr && _Chr <= 11742 || _Chr == 11823 || 12293 <= _Chr && _Chr <= 12295 || 12321 <= _Chr && _Chr <= 12329 || 12337 <= _Chr && _Chr <= 12341 || 12344 <= _Chr && _Chr <= 12348 || 12353 <= _Chr && _Chr <= 12438 || 12445 <= _Chr && _Chr <= 12447 || 12449 <= _Chr && _Chr <= 12538 || 12540 <= _Chr && _Chr <= 12543 || 12549 <= _Chr && _Chr <= 12591 || 12593 <= _Chr && _Chr <= 12686 || 12690 <= _Chr && _Chr <= 12693 || 12704 <= _Chr && _Chr <= 12735 || 12784 <= _Chr && _Chr <= 12799 || 12832 <= _Chr && _Chr <= 12841 || 12872 <= _Chr && _Chr <= 12879 || 12881 <= _Chr && _Chr <= 12895 || 12928 <= _Chr && _Chr <= 12937 || 12977 <= _Chr && _Chr <= 12991 || 13312 <= _Chr && _Chr <= 19903 || 19968 <= _Chr && _Chr <= 40956 || 40960 <= _Chr && _Chr <= 42124 || 42192 <= _Chr && _Chr <= 42237 || 42240 <= _Chr && _Chr <= 42508 || 42512 <= _Chr && _Chr <= 42539 || 42560 <= _Chr && _Chr <= 42606 || 42623 <= _Chr && _Chr <= 42653 || 42656 <= _Chr && _Chr <= 42735 || 42775 <= _Chr && _Chr <= 42783 || 42786 <= _Chr && _Chr <= 42888 || 42891 <= _Chr && _Chr <= 42943 || 42946 <= _Chr && _Chr <= 42954 || 42997 <= _Chr && _Chr <= 43009 || 43011 <= _Chr && _Chr <= 43013 || 43015 <= _Chr && _Chr <= 43018 || 43020 <= _Chr && _Chr <= 43042 || 43056 <= _Chr && _Chr <= 43061 || 43072 <= _Chr && _Chr <= 43123 || 43138 <= _Chr && _Chr <= 43187 || 43216 <= _Chr && _Chr <= 43225 || 43250 <= _Chr && _Chr <= 43255 || _Chr == 43259 || 43261 <= _Chr && _Chr <= 43262 || 43264 <= _Chr && _Chr <= 43301 || 43312 <= _Chr && _Chr <= 43334 || 43360 <= _Chr && _Chr <= 43388 || 43396 <= _Chr && _Chr <= 43442 || 43471 <= _Chr && _Chr <= 43481 || 43488 <= _Chr && _Chr <= 43492 || 43494 <= _Chr && _Chr <= 43518 || 43520 <= _Chr && _Chr <= 43560 || 43584 <= _Chr && _Chr <= 43586 || 43588 <= _Chr && _Chr <= 43595 || 43600 <= _Chr && _Chr <= 43609 || 43616 <= _Chr && _Chr <= 43638 || _Chr == 43642 || 43646 <= _Chr && _Chr <= 43695 || _Chr == 43697 || 43701 <= _Chr && _Chr <= 43702 || 43705 <= _Chr && _Chr <= 43709 || _Chr == 43712 || _Chr == 43714 || 43739 <= _Chr && _Chr <= 43741 || 43744 <= _Chr && _Chr <= 43754 || 43762 <= _Chr && _Chr <= 43764 || 43777 <= _Chr && _Chr <= 43782 || 43785 <= _Chr && _Chr <= 43790 || 43793 <= _Chr && _Chr <= 43798 || 43808 <= _Chr && _Chr <= 43814 || 43816 <= _Chr && _Chr <= 43822 || 43824 <= _Chr && _Chr <= 43866 || 43868 <= _Chr && _Chr <= 43881 || 43888 <= _Chr && _Chr <= 44002 || 44016 <= _Chr && _Chr <= 44025 || 44032 <= _Chr && _Chr <= 55203 || 55216 <= _Chr && _Chr <= 55238 || 55243 <= _Chr && _Chr <= 55291 || 63744 <= _Chr && _Chr <= 64109 || 64112 <= _Chr && _Chr <= 64217 || 64256 <= _Chr && _Chr <= 64262 || 64275 <= _Chr && _Chr <= 64279 || _Chr == 64285 || 64287 <= _Chr && _Chr <= 64296 || 64298 <= _Chr && _Chr <= 64310 || 64312 <= _Chr && _Chr <= 64316 || _Chr == 64318 || 64320 <= _Chr && _Chr <= 64321 || 64323 <= _Chr && _Chr <= 64324 || 64326 <= _Chr && _Chr <= 64433 || 64467 <= _Chr && _Chr <= 64829 || 64848 <= _Chr && _Chr <= 64911 || 64914 <= _Chr && _Chr <= 64967 || 65008 <= _Chr && _Chr <= 65019 || 65136 <= _Chr && _Chr <= 65140 || 65142 <= _Chr && _Chr <= 65276 || 65296 <= _Chr && _Chr <= 65305 || 65313 <= _Chr && _Chr <= 65338 || 65345 <= _Chr && _Chr <= 65370 || 65382 <= _Chr && _Chr <= 65470 || 65474 <= _Chr && _Chr <= 65479 || 65482 <= _Chr && _Chr <= 65487 || 65490 <= _Chr && _Chr <= 65495 || 65498 <= _Chr && _Chr <= 65500 || 65536 <= _Chr && _Chr <= 65547 || 65549 <= _Chr && _Chr <= 65574 || 65576 <= _Chr && _Chr <= 65594 || 65596 <= _Chr && _Chr <= 65597 || 65599 <= _Chr && _Chr <= 65613 || 65616 <= _Chr && _Chr <= 65629 || 65664 <= _Chr && _Chr <= 65786 || 65799 <= _Chr && _Chr <= 65843 || 65856 <= _Chr && _Chr <= 65912 || 65930 <= _Chr && _Chr <= 65931 || 66176 <= _Chr && _Chr <= 66204 || 66208 <= _Chr && _Chr <= 66256 || 66273 <= _Chr && _Chr <= 66299 || 66304 <= _Chr && _Chr <= 66339 || 66349 <= _Chr && _Chr <= 66378 || 66384 <= _Chr && _Chr <= 66421 || 66432 <= _Chr && _Chr <= 66461 || 66464 <= _Chr && _Chr <= 66499 || 66504 <= _Chr && _Chr <= 66511 || 66513 <= _Chr && _Chr <= 66517 || 66560 <= _Chr && _Chr <= 66717 || 66720 <= _Chr && _Chr <= 66729 || 66736 <= _Chr && _Chr <= 66771 || 66776 <= _Chr && _Chr <= 66811 || 66816 <= _Chr && _Chr <= 66855 || 66864 <= _Chr && _Chr <= 66915 || 67072 <= _Chr && _Chr <= 67382 || 67392 <= _Chr && _Chr <= 67413 || 67424 <= _Chr && _Chr <= 67431 || 67584 <= _Chr && _Chr <= 67589 || _Chr == 67592 || 67594 <= _Chr && _Chr <= 67637 || 67639 <= _Chr && _Chr <= 67640 || _Chr == 67644 || 67647 <= _Chr && _Chr <= 67669 || 67672 <= _Chr && _Chr <= 67702 || 67705 <= _Chr && _Chr <= 67742 || 67751 <= _Chr && _Chr <= 67759 || 67808 <= _Chr && _Chr <= 67826 || 67828 <= _Chr && _Chr <= 67829 || 67835 <= _Chr && _Chr <= 67867 || 67872 <= _Chr && _Chr <= 67897 || 67968 <= _Chr && _Chr <= 68023 || 68028 <= _Chr && _Chr <= 68047 || 68050 <= _Chr && _Chr <= 68096 || 68112 <= _Chr && _Chr <= 68115 || 68117 <= _Chr && _Chr <= 68119 || 68121 <= _Chr && _Chr <= 68149 || 68160 <= _Chr && _Chr <= 68168 || 68192 <= _Chr && _Chr <= 68222 || 68224 <= _Chr && _Chr <= 68255 || 68288 <= _Chr && _Chr <= 68295 || 68297 <= _Chr && _Chr <= 68324 || 68331 <= _Chr && _Chr <= 68335 || 68352 <= _Chr && _Chr <= 68405 || 68416 <= _Chr && _Chr <= 68437 || 68440 <= _Chr && _Chr <= 68466 || 68472 <= _Chr && _Chr <= 68497 || 68521 <= _Chr && _Chr <= 68527 || 68608 <= _Chr && _Chr <= 68680 || 68736 <= _Chr && _Chr <= 68786 || 68800 <= _Chr && _Chr <= 68850 || 68858 <= _Chr && _Chr <= 68899 || 68912 <= _Chr && _Chr <= 68921 || 69216 <= _Chr && _Chr <= 69246 || 69248 <= _Chr && _Chr <= 69289 || 69296 <= _Chr && _Chr <= 69297 || 69376 <= _Chr && _Chr <= 69415 || 69424 <= _Chr && _Chr <= 69445 || 69457 <= _Chr && _Chr <= 69460 || 69552 <= _Chr && _Chr <= 69579 || 69600 <= _Chr && _Chr <= 69622 || 69635 <= _Chr && _Chr <= 69687 || 69714 <= _Chr && _Chr <= 69743 || 69763 <= _Chr && _Chr <= 69807 || 69840 <= _Chr && _Chr <= 69864 || 69872 <= _Chr && _Chr <= 69881 || 69891 <= _Chr && _Chr <= 69926 || 69942 <= _Chr && _Chr <= 69951 || _Chr == 69956 || _Chr == 69959 || 69968 <= _Chr && _Chr <= 70002 || _Chr == 70006 || 70019 <= _Chr && _Chr <= 70066 || 70081 <= _Chr && _Chr <= 70084 || 70096 <= _Chr && _Chr <= 70106 || _Chr == 70108 || 70113 <= _Chr && _Chr <= 70132 || 70144 <= _Chr && _Chr <= 70161 || 70163 <= _Chr && _Chr <= 70187 || 70272 <= _Chr && _Chr <= 70278 || _Chr == 70280 || 70282 <= _Chr && _Chr <= 70285 || 70287 <= _Chr && _Chr <= 70301 || 70303 <= _Chr && _Chr <= 70312 || 70320 <= _Chr && _Chr <= 70366 || 70384 <= _Chr && _Chr <= 70393 || 70405 <= _Chr && _Chr <= 70412 || 70415 <= _Chr && _Chr <= 70416 || 70419 <= _Chr && _Chr <= 70440 || 70442 <= _Chr && _Chr <= 70448 || 70450 <= _Chr && _Chr <= 70451 || 70453 <= _Chr && _Chr <= 70457 || _Chr == 70461 || _Chr == 70480 || 70493 <= _Chr && _Chr <= 70497 || 70656 <= _Chr && _Chr <= 70708 || 70727 <= _Chr && _Chr <= 70730 || 70736 <= _Chr && _Chr <= 70745 || 70751 <= _Chr && _Chr <= 70753 || 70784 <= _Chr && _Chr <= 70831 || 70852 <= _Chr && _Chr <= 70853 || _Chr == 70855 || 70864 <= _Chr && _Chr <= 70873 || 71040 <= _Chr && _Chr <= 71086 || 71128 <= _Chr && _Chr <= 71131 || 71168 <= _Chr && _Chr <= 71215 || _Chr == 71236 || 71248 <= _Chr && _Chr <= 71257 || 71296 <= _Chr && _Chr <= 71338 || _Chr == 71352 || 71360 <= _Chr && _Chr <= 71369 || 71424 <= _Chr && _Chr <= 71450 || 71472 <= _Chr && _Chr <= 71483 || 71680 <= _Chr && _Chr <= 71723 || 71840 <= _Chr && _Chr <= 71922 || 71935 <= _Chr && _Chr <= 71942 || _Chr == 71945 || 71948 <= _Chr && _Chr <= 71955 || 71957 <= _Chr && _Chr <= 71958 || 71960 <= _Chr && _Chr <= 71983 || _Chr == 71999 || _Chr == 72001 || 72016 <= _Chr && _Chr <= 72025 || 72096 <= _Chr && _Chr <= 72103 || 72106 <= _Chr && _Chr <= 72144 || _Chr == 72161 || _Chr == 72163 || _Chr == 72192 || 72203 <= _Chr && _Chr <= 72242 || _Chr == 72250 || _Chr == 72272 || 72284 <= _Chr && _Chr <= 72329 || _Chr == 72349 || 72384 <= _Chr && _Chr <= 72440 || 72704 <= _Chr && _Chr <= 72712 || 72714 <= _Chr && _Chr <= 72750 || _Chr == 72768 || 72784 <= _Chr && _Chr <= 72812 || 72818 <= _Chr && _Chr <= 72847 || 72960 <= _Chr && _Chr <= 72966 || 72968 <= _Chr && _Chr <= 72969 || 72971 <= _Chr && _Chr <= 73008 || _Chr == 73030 || 73040 <= _Chr && _Chr <= 73049 || 73056 <= _Chr && _Chr <= 73061 || 73063 <= _Chr && _Chr <= 73064 || 73066 <= _Chr && _Chr <= 73097 || _Chr == 73112 || 73120 <= _Chr && _Chr <= 73129 || 73440 <= _Chr && _Chr <= 73458 || _Chr == 73648 || 73664 <= _Chr && _Chr <= 73684 || 73728 <= _Chr && _Chr <= 74649 || 74752 <= _Chr && _Chr <= 74862 || 74880 <= _Chr && _Chr <= 75075 || 77824 <= _Chr && _Chr <= 78894 || 82944 <= _Chr && _Chr <= 83526 || 92160 <= _Chr && _Chr <= 92728 || 92736 <= _Chr && _Chr <= 92766 || 92768 <= _Chr && _Chr <= 92777 || 92880 <= _Chr && _Chr <= 92909 || 92928 <= _Chr && _Chr <= 92975 || 92992 <= _Chr && _Chr <= 92995 || 93008 <= _Chr && _Chr <= 93017 || 93019 <= _Chr && _Chr <= 93025 || 93027 <= _Chr && _Chr <= 93047 || 93053 <= _Chr && _Chr <= 93071 || 93760 <= _Chr && _Chr <= 93846 || 93952 <= _Chr && _Chr <= 94026 || _Chr == 94032 || 94099 <= _Chr && _Chr <= 94111 || 94176 <= _Chr && _Chr <= 94177 || _Chr == 94179 || 94208 <= _Chr && _Chr <= 100343 || 100352 <= _Chr && _Chr <= 101589 || 101632 <= _Chr && _Chr <= 101640 || 110592 <= _Chr && _Chr <= 110878 || 110928 <= _Chr && _Chr <= 110930 || 110948 <= _Chr && _Chr <= 110951 || 110960 <= _Chr && _Chr <= 111355 || 113664 <= _Chr && _Chr <= 113770 || 113776 <= _Chr && _Chr <= 113788 || 113792 <= _Chr && _Chr <= 113800 || 113808 <= _Chr && _Chr <= 113817 || 119520 <= _Chr && _Chr <= 119539 || 119648 <= _Chr && _Chr <= 119672 || 119808 <= _Chr && _Chr <= 119892 || 119894 <= _Chr && _Chr <= 119964 || 119966 <= _Chr && _Chr <= 119967 || _Chr == 119970 || 119973 <= _Chr && _Chr <= 119974 || 119977 <= _Chr && _Chr <= 119980 || 119982 <= _Chr && _Chr <= 119993 || _Chr == 119995 || 119997 <= _Chr && _Chr <= 120003 || 120005 <= _Chr && _Chr <= 120069 || 120071 <= _Chr && _Chr <= 120074 || 120077 <= _Chr && _Chr <= 120084 || 120086 <= _Chr && _Chr <= 120092 || 120094 <= _Chr && _Chr <= 120121 || 120123 <= _Chr && _Chr <= 120126 || 120128 <= _Chr && _Chr <= 120132 || _Chr == 120134 || 120138 <= _Chr && _Chr <= 120144 || 120146 <= _Chr && _Chr <= 120485 || 120488 <= _Chr && _Chr <= 120512 || 120514 <= _Chr && _Chr <= 120538 || 120540 <= _Chr && _Chr <= 120570 || 120572 <= _Chr && _Chr <= 120596 || 120598 <= _Chr && _Chr <= 120628 || 120630 <= _Chr && _Chr <= 120654 || 120656 <= _Chr && _Chr <= 120686 || 120688 <= _Chr && _Chr <= 120712 || 120714 <= _Chr && _Chr <= 120744 || 120746 <= _Chr && _Chr <= 120770 || 120772 <= _Chr && _Chr <= 120779 || 120782 <= _Chr && _Chr <= 120831 || 123136 <= _Chr && _Chr <= 123180 || 123191 <= _Chr && _Chr <= 123197 || 123200 <= _Chr && _Chr <= 123209 || _Chr == 123214 || 123584 <= _Chr && _Chr <= 123627 || 123632 <= _Chr && _Chr <= 123641 || 124928 <= _Chr && _Chr <= 125124 || 125127 <= _Chr && _Chr <= 125135 || 125184 <= _Chr && _Chr <= 125251 || _Chr == 125259 || 125264 <= _Chr && _Chr <= 125273 || 126065 <= _Chr && _Chr <= 126123 || 126125 <= _Chr && _Chr <= 126127 || 126129 <= _Chr && _Chr <= 126132 || 126209 <= _Chr && _Chr <= 126253 || 126255 <= _Chr && _Chr <= 126269 || 126464 <= _Chr && _Chr <= 126467 || 126469 <= _Chr && _Chr <= 126495 || 126497 <= _Chr && _Chr <= 126498 || _Chr == 126500 || _Chr == 126503 || 126505 <= _Chr && _Chr <= 126514 || 126516 <= _Chr && _Chr <= 126519 || _Chr == 126521 || _Chr == 126523 || _Chr == 126530 || _Chr == 126535 || _Chr == 126537 || _Chr == 126539 || 126541 <= _Chr && _Chr <= 126543 || 126545 <= _Chr && _Chr <= 126546 || _Chr == 126548 || _Chr == 126551 || _Chr == 126553 || _Chr == 126555 || _Chr == 126557 || _Chr == 126559 || 126561 <= _Chr && _Chr <= 126562 || _Chr == 126564 || 126567 <= _Chr && _Chr <= 126570 || 126572 <= _Chr && _Chr <= 126578 || 126580 <= _Chr && _Chr <= 126583 || 126585 <= _Chr && _Chr <= 126588 || _Chr == 126590 || 126592 <= _Chr && _Chr <= 126601 || 126603 <= _Chr && _Chr <= 126619 || 126625 <= _Chr && _Chr <= 126627 || 126629 <= _Chr && _Chr <= 126633 || 126635 <= _Chr && _Chr <= 126651 || 127232 <= _Chr && _Chr <= 127244 || 130032 <= _Chr && _Chr <= 130041 || 131072 <= _Chr && _Chr <= 173789 || 173824 <= _Chr && _Chr <= 177972 || 177984 <= _Chr && _Chr <= 178205 || 178208 <= _Chr && _Chr <= 183969 || 183984 <= _Chr && _Chr <= 191456 || 194560 <= _Chr && _Chr <= 195101 || 196608 <= _Chr && _Chr <= 201546 || false) { return true; }
		return false;
	}
	bool pystr::check_alpha() {
		pystr _Chr = (*this)[0];
		if (65 <= _Chr && _Chr <= 90 || 97 <= _Chr && _Chr <= 122 || _Chr == 170 || _Chr == 181 || _Chr == 186 || 192 <= _Chr && _Chr <= 214 || 216 <= _Chr && _Chr <= 246 || 248 <= _Chr && _Chr <= 705 || 710 <= _Chr && _Chr <= 721 || 736 <= _Chr && _Chr <= 740 || _Chr == 748 || _Chr == 750 || 880 <= _Chr && _Chr <= 884 || 886 <= _Chr && _Chr <= 887 || 890 <= _Chr && _Chr <= 893 || _Chr == 895 || _Chr == 902 || 904 <= _Chr && _Chr <= 906 || _Chr == 908 || 910 <= _Chr && _Chr <= 929 || 931 <= _Chr && _Chr <= 1013 || 1015 <= _Chr && _Chr <= 1153 || 1162 <= _Chr && _Chr <= 1327 || 1329 <= _Chr && _Chr <= 1366 || _Chr == 1369 || 1376 <= _Chr && _Chr <= 1416 || 1488 <= _Chr && _Chr <= 1514 || 1519 <= _Chr && _Chr <= 1522 || 1568 <= _Chr && _Chr <= 1610 || 1646 <= _Chr && _Chr <= 1647 || 1649 <= _Chr && _Chr <= 1747 || _Chr == 1749 || 1765 <= _Chr && _Chr <= 1766 || 1774 <= _Chr && _Chr <= 1775 || 1786 <= _Chr && _Chr <= 1788 || _Chr == 1791 || _Chr == 1808 || 1810 <= _Chr && _Chr <= 1839 || 1869 <= _Chr && _Chr <= 1957 || _Chr == 1969 || 1994 <= _Chr && _Chr <= 2026 || 2036 <= _Chr && _Chr <= 2037 || _Chr == 2042 || 2048 <= _Chr && _Chr <= 2069 || _Chr == 2074 || _Chr == 2084 || _Chr == 2088 || 2112 <= _Chr && _Chr <= 2136 || 2144 <= _Chr && _Chr <= 2154 || 2208 <= _Chr && _Chr <= 2228 || 2230 <= _Chr && _Chr <= 2247 || 2308 <= _Chr && _Chr <= 2361 || _Chr == 2365 || _Chr == 2384 || 2392 <= _Chr && _Chr <= 2401 || 2417 <= _Chr && _Chr <= 2432 || 2437 <= _Chr && _Chr <= 2444 || 2447 <= _Chr && _Chr <= 2448 || 2451 <= _Chr && _Chr <= 2472 || 2474 <= _Chr && _Chr <= 2480 || _Chr == 2482 || 2486 <= _Chr && _Chr <= 2489 || _Chr == 2493 || _Chr == 2510 || 2524 <= _Chr && _Chr <= 2525 || 2527 <= _Chr && _Chr <= 2529 || 2544 <= _Chr && _Chr <= 2545 || _Chr == 2556 || 2565 <= _Chr && _Chr <= 2570 || 2575 <= _Chr && _Chr <= 2576 || 2579 <= _Chr && _Chr <= 2600 || 2602 <= _Chr && _Chr <= 2608 || 2610 <= _Chr && _Chr <= 2611 || 2613 <= _Chr && _Chr <= 2614 || 2616 <= _Chr && _Chr <= 2617 || 2649 <= _Chr && _Chr <= 2652 || _Chr == 2654 || 2674 <= _Chr && _Chr <= 2676 || 2693 <= _Chr && _Chr <= 2701 || 2703 <= _Chr && _Chr <= 2705 || 2707 <= _Chr && _Chr <= 2728 || 2730 <= _Chr && _Chr <= 2736 || 2738 <= _Chr && _Chr <= 2739 || 2741 <= _Chr && _Chr <= 2745 || _Chr == 2749 || _Chr == 2768 || 2784 <= _Chr && _Chr <= 2785 || _Chr == 2809 || 2821 <= _Chr && _Chr <= 2828 || 2831 <= _Chr && _Chr <= 2832 || 2835 <= _Chr && _Chr <= 2856 || 2858 <= _Chr && _Chr <= 2864 || 2866 <= _Chr && _Chr <= 2867 || 2869 <= _Chr && _Chr <= 2873 || _Chr == 2877 || 2908 <= _Chr && _Chr <= 2909 || 2911 <= _Chr && _Chr <= 2913 || _Chr == 2929 || _Chr == 2947 || 2949 <= _Chr && _Chr <= 2954 || 2958 <= _Chr && _Chr <= 2960 || 2962 <= _Chr && _Chr <= 2965 || 2969 <= _Chr && _Chr <= 2970 || _Chr == 2972 || 2974 <= _Chr && _Chr <= 2975 || 2979 <= _Chr && _Chr <= 2980 || 2984 <= _Chr && _Chr <= 2986 || 2990 <= _Chr && _Chr <= 3001 || _Chr == 3024 || 3077 <= _Chr && _Chr <= 3084 || 3086 <= _Chr && _Chr <= 3088 || 3090 <= _Chr && _Chr <= 3112 || 3114 <= _Chr && _Chr <= 3129 || _Chr == 3133 || 3160 <= _Chr && _Chr <= 3162 || 3168 <= _Chr && _Chr <= 3169 || _Chr == 3200 || 3205 <= _Chr && _Chr <= 3212 || 3214 <= _Chr && _Chr <= 3216 || 3218 <= _Chr && _Chr <= 3240 || 3242 <= _Chr && _Chr <= 3251 || 3253 <= _Chr && _Chr <= 3257 || _Chr == 3261 || _Chr == 3294 || 3296 <= _Chr && _Chr <= 3297 || 3313 <= _Chr && _Chr <= 3314 || 3332 <= _Chr && _Chr <= 3340 || 3342 <= _Chr && _Chr <= 3344 || 3346 <= _Chr && _Chr <= 3386 || _Chr == 3389 || _Chr == 3406 || 3412 <= _Chr && _Chr <= 3414 || 3423 <= _Chr && _Chr <= 3425 || 3450 <= _Chr && _Chr <= 3455 || 3461 <= _Chr && _Chr <= 3478 || 3482 <= _Chr && _Chr <= 3505 || 3507 <= _Chr && _Chr <= 3515 || _Chr == 3517 || 3520 <= _Chr && _Chr <= 3526 || 3585 <= _Chr && _Chr <= 3632 || 3634 <= _Chr && _Chr <= 3635 || 3648 <= _Chr && _Chr <= 3654 || 3713 <= _Chr && _Chr <= 3714 || _Chr == 3716 || 3718 <= _Chr && _Chr <= 3722 || 3724 <= _Chr && _Chr <= 3747 || _Chr == 3749 || 3751 <= _Chr && _Chr <= 3760 || 3762 <= _Chr && _Chr <= 3763 || _Chr == 3773 || 3776 <= _Chr && _Chr <= 3780 || _Chr == 3782 || 3804 <= _Chr && _Chr <= 3807 || _Chr == 3840 || 3904 <= _Chr && _Chr <= 3911 || 3913 <= _Chr && _Chr <= 3948 || 3976 <= _Chr && _Chr <= 3980 || 4096 <= _Chr && _Chr <= 4138 || _Chr == 4159 || 4176 <= _Chr && _Chr <= 4181 || 4186 <= _Chr && _Chr <= 4189 || _Chr == 4193 || 4197 <= _Chr && _Chr <= 4198 || 4206 <= _Chr && _Chr <= 4208 || 4213 <= _Chr && _Chr <= 4225 || _Chr == 4238 || 4256 <= _Chr && _Chr <= 4293 || _Chr == 4295 || _Chr == 4301 || 4304 <= _Chr && _Chr <= 4346 || 4348 <= _Chr && _Chr <= 4680 || 4682 <= _Chr && _Chr <= 4685 || 4688 <= _Chr && _Chr <= 4694 || _Chr == 4696 || 4698 <= _Chr && _Chr <= 4701 || 4704 <= _Chr && _Chr <= 4744 || 4746 <= _Chr && _Chr <= 4749 || 4752 <= _Chr && _Chr <= 4784 || 4786 <= _Chr && _Chr <= 4789 || 4792 <= _Chr && _Chr <= 4798 || _Chr == 4800 || 4802 <= _Chr && _Chr <= 4805 || 4808 <= _Chr && _Chr <= 4822 || 4824 <= _Chr && _Chr <= 4880 || 4882 <= _Chr && _Chr <= 4885 || 4888 <= _Chr && _Chr <= 4954 || 4992 <= _Chr && _Chr <= 5007 || 5024 <= _Chr && _Chr <= 5109 || 5112 <= _Chr && _Chr <= 5117 || 5121 <= _Chr && _Chr <= 5740 || 5743 <= _Chr && _Chr <= 5759 || 5761 <= _Chr && _Chr <= 5786 || 5792 <= _Chr && _Chr <= 5866 || 5873 <= _Chr && _Chr <= 5880 || 5888 <= _Chr && _Chr <= 5900 || 5902 <= _Chr && _Chr <= 5905 || 5920 <= _Chr && _Chr <= 5937 || 5952 <= _Chr && _Chr <= 5969 || 5984 <= _Chr && _Chr <= 5996 || 5998 <= _Chr && _Chr <= 6000 || 6016 <= _Chr && _Chr <= 6067 || _Chr == 6103 || _Chr == 6108 || 6176 <= _Chr && _Chr <= 6264 || 6272 <= _Chr && _Chr <= 6276 || 6279 <= _Chr && _Chr <= 6312 || _Chr == 6314 || 6320 <= _Chr && _Chr <= 6389 || 6400 <= _Chr && _Chr <= 6430 || 6480 <= _Chr && _Chr <= 6509 || 6512 <= _Chr && _Chr <= 6516 || 6528 <= _Chr && _Chr <= 6571 || 6576 <= _Chr && _Chr <= 6601 || 6656 <= _Chr && _Chr <= 6678 || 6688 <= _Chr && _Chr <= 6740 || _Chr == 6823 || 6917 <= _Chr && _Chr <= 6963 || 6981 <= _Chr && _Chr <= 6987 || 7043 <= _Chr && _Chr <= 7072 || 7086 <= _Chr && _Chr <= 7087 || 7098 <= _Chr && _Chr <= 7141 || 7168 <= _Chr && _Chr <= 7203 || 7245 <= _Chr && _Chr <= 7247 || 7258 <= _Chr && _Chr <= 7293 || 7296 <= _Chr && _Chr <= 7304 || 7312 <= _Chr && _Chr <= 7354 || 7357 <= _Chr && _Chr <= 7359 || 7401 <= _Chr && _Chr <= 7404 || 7406 <= _Chr && _Chr <= 7411 || 7413 <= _Chr && _Chr <= 7414 || _Chr == 7418 || 7424 <= _Chr && _Chr <= 7615 || 7680 <= _Chr && _Chr <= 7957 || 7960 <= _Chr && _Chr <= 7965 || 7968 <= _Chr && _Chr <= 8005 || 8008 <= _Chr && _Chr <= 8013 || 8016 <= _Chr && _Chr <= 8023 || _Chr == 8025 || _Chr == 8027 || _Chr == 8029 || 8031 <= _Chr && _Chr <= 8061 || 8064 <= _Chr && _Chr <= 8116 || 8118 <= _Chr && _Chr <= 8124 || _Chr == 8126 || 8130 <= _Chr && _Chr <= 8132 || 8134 <= _Chr && _Chr <= 8140 || 8144 <= _Chr && _Chr <= 8147 || 8150 <= _Chr && _Chr <= 8155 || 8160 <= _Chr && _Chr <= 8172 || 8178 <= _Chr && _Chr <= 8180 || 8182 <= _Chr && _Chr <= 8188 || _Chr == 8305 || _Chr == 8319 || 8336 <= _Chr && _Chr <= 8348 || _Chr == 8450 || _Chr == 8455 || 8458 <= _Chr && _Chr <= 8467 || _Chr == 8469 || 8473 <= _Chr && _Chr <= 8477 || _Chr == 8484 || _Chr == 8486 || _Chr == 8488 || 8490 <= _Chr && _Chr <= 8493 || 8495 <= _Chr && _Chr <= 8505 || 8508 <= _Chr && _Chr <= 8511 || 8517 <= _Chr && _Chr <= 8521 || _Chr == 8526 || 8579 <= _Chr && _Chr <= 8580 || 11264 <= _Chr && _Chr <= 11310 || 11312 <= _Chr && _Chr <= 11358 || 11360 <= _Chr && _Chr <= 11492 || 11499 <= _Chr && _Chr <= 11502 || 11506 <= _Chr && _Chr <= 11507 || 11520 <= _Chr && _Chr <= 11557 || _Chr == 11559 || _Chr == 11565 || 11568 <= _Chr && _Chr <= 11623 || _Chr == 11631 || 11648 <= _Chr && _Chr <= 11670 || 11680 <= _Chr && _Chr <= 11686 || 11688 <= _Chr && _Chr <= 11694 || 11696 <= _Chr && _Chr <= 11702 || 11704 <= _Chr && _Chr <= 11710 || 11712 <= _Chr && _Chr <= 11718 || 11720 <= _Chr && _Chr <= 11726 || 11728 <= _Chr && _Chr <= 11734 || 11736 <= _Chr && _Chr <= 11742 || _Chr == 11823 || 12293 <= _Chr && _Chr <= 12294 || 12337 <= _Chr && _Chr <= 12341 || 12347 <= _Chr && _Chr <= 12348 || 12353 <= _Chr && _Chr <= 12438 || 12445 <= _Chr && _Chr <= 12447 || 12449 <= _Chr && _Chr <= 12538 || 12540 <= _Chr && _Chr <= 12543 || 12549 <= _Chr && _Chr <= 12591 || 12593 <= _Chr && _Chr <= 12686 || 12704 <= _Chr && _Chr <= 12735 || 12784 <= _Chr && _Chr <= 12799 || 13312 <= _Chr && _Chr <= 19903 || 19968 <= _Chr && _Chr <= 40956 || 40960 <= _Chr && _Chr <= 42124 || 42192 <= _Chr && _Chr <= 42237 || 42240 <= _Chr && _Chr <= 42508 || 42512 <= _Chr && _Chr <= 42527 || 42538 <= _Chr && _Chr <= 42539 || 42560 <= _Chr && _Chr <= 42606 || 42623 <= _Chr && _Chr <= 42653 || 42656 <= _Chr && _Chr <= 42725 || 42775 <= _Chr && _Chr <= 42783 || 42786 <= _Chr && _Chr <= 42888 || 42891 <= _Chr && _Chr <= 42943 || 42946 <= _Chr && _Chr <= 42954 || 42997 <= _Chr && _Chr <= 43009 || 43011 <= _Chr && _Chr <= 43013 || 43015 <= _Chr && _Chr <= 43018 || 43020 <= _Chr && _Chr <= 43042 || 43072 <= _Chr && _Chr <= 43123 || 43138 <= _Chr && _Chr <= 43187 || 43250 <= _Chr && _Chr <= 43255 || _Chr == 43259 || 43261 <= _Chr && _Chr <= 43262 || 43274 <= _Chr && _Chr <= 43301 || 43312 <= _Chr && _Chr <= 43334 || 43360 <= _Chr && _Chr <= 43388 || 43396 <= _Chr && _Chr <= 43442 || _Chr == 43471 || 43488 <= _Chr && _Chr <= 43492 || 43494 <= _Chr && _Chr <= 43503 || 43514 <= _Chr && _Chr <= 43518 || 43520 <= _Chr && _Chr <= 43560 || 43584 <= _Chr && _Chr <= 43586 || 43588 <= _Chr && _Chr <= 43595 || 43616 <= _Chr && _Chr <= 43638 || _Chr == 43642 || 43646 <= _Chr && _Chr <= 43695 || _Chr == 43697 || 43701 <= _Chr && _Chr <= 43702 || 43705 <= _Chr && _Chr <= 43709 || _Chr == 43712 || _Chr == 43714 || 43739 <= _Chr && _Chr <= 43741 || 43744 <= _Chr && _Chr <= 43754 || 43762 <= _Chr && _Chr <= 43764 || 43777 <= _Chr && _Chr <= 43782 || 43785 <= _Chr && _Chr <= 43790 || 43793 <= _Chr && _Chr <= 43798 || 43808 <= _Chr && _Chr <= 43814 || 43816 <= _Chr && _Chr <= 43822 || 43824 <= _Chr && _Chr <= 43866 || 43868 <= _Chr && _Chr <= 43881 || 43888 <= _Chr && _Chr <= 44002 || 44032 <= _Chr && _Chr <= 55203 || 55216 <= _Chr && _Chr <= 55238 || 55243 <= _Chr && _Chr <= 55291 || 63744 <= _Chr && _Chr <= 64109 || 64112 <= _Chr && _Chr <= 64217 || 64256 <= _Chr && _Chr <= 64262 || 64275 <= _Chr && _Chr <= 64279 || _Chr == 64285 || 64287 <= _Chr && _Chr <= 64296 || 64298 <= _Chr && _Chr <= 64310 || 64312 <= _Chr && _Chr <= 64316 || _Chr == 64318 || 64320 <= _Chr && _Chr <= 64321 || 64323 <= _Chr && _Chr <= 64324 || 64326 <= _Chr && _Chr <= 64433 || 64467 <= _Chr && _Chr <= 64829 || 64848 <= _Chr && _Chr <= 64911 || 64914 <= _Chr && _Chr <= 64967 || 65008 <= _Chr && _Chr <= 65019 || 65136 <= _Chr && _Chr <= 65140 || 65142 <= _Chr && _Chr <= 65276 || 65313 <= _Chr && _Chr <= 65338 || 65345 <= _Chr && _Chr <= 65370 || 65382 <= _Chr && _Chr <= 65470 || 65474 <= _Chr && _Chr <= 65479 || 65482 <= _Chr && _Chr <= 65487 || 65490 <= _Chr && _Chr <= 65495 || 65498 <= _Chr && _Chr <= 65500 || 65536 <= _Chr && _Chr <= 65547 || 65549 <= _Chr && _Chr <= 65574 || 65576 <= _Chr && _Chr <= 65594 || 65596 <= _Chr && _Chr <= 65597 || 65599 <= _Chr && _Chr <= 65613 || 65616 <= _Chr && _Chr <= 65629 || 65664 <= _Chr && _Chr <= 65786 || 66176 <= _Chr && _Chr <= 66204 || 66208 <= _Chr && _Chr <= 66256 || 66304 <= _Chr && _Chr <= 66335 || 66349 <= _Chr && _Chr <= 66368 || 66370 <= _Chr && _Chr <= 66377 || 66384 <= _Chr && _Chr <= 66421 || 66432 <= _Chr && _Chr <= 66461 || 66464 <= _Chr && _Chr <= 66499 || 66504 <= _Chr && _Chr <= 66511 || 66560 <= _Chr && _Chr <= 66717 || 66736 <= _Chr && _Chr <= 66771 || 66776 <= _Chr && _Chr <= 66811 || 66816 <= _Chr && _Chr <= 66855 || 66864 <= _Chr && _Chr <= 66915 || 67072 <= _Chr && _Chr <= 67382 || 67392 <= _Chr && _Chr <= 67413 || 67424 <= _Chr && _Chr <= 67431 || 67584 <= _Chr && _Chr <= 67589 || _Chr == 67592 || 67594 <= _Chr && _Chr <= 67637 || 67639 <= _Chr && _Chr <= 67640 || _Chr == 67644 || 67647 <= _Chr && _Chr <= 67669 || 67680 <= _Chr && _Chr <= 67702 || 67712 <= _Chr && _Chr <= 67742 || 67808 <= _Chr && _Chr <= 67826 || 67828 <= _Chr && _Chr <= 67829 || 67840 <= _Chr && _Chr <= 67861 || 67872 <= _Chr && _Chr <= 67897 || 67968 <= _Chr && _Chr <= 68023 || 68030 <= _Chr && _Chr <= 68031 || _Chr == 68096 || 68112 <= _Chr && _Chr <= 68115 || 68117 <= _Chr && _Chr <= 68119 || 68121 <= _Chr && _Chr <= 68149 || 68192 <= _Chr && _Chr <= 68220 || 68224 <= _Chr && _Chr <= 68252 || 68288 <= _Chr && _Chr <= 68295 || 68297 <= _Chr && _Chr <= 68324 || 68352 <= _Chr && _Chr <= 68405 || 68416 <= _Chr && _Chr <= 68437 || 68448 <= _Chr && _Chr <= 68466 || 68480 <= _Chr && _Chr <= 68497 || 68608 <= _Chr && _Chr <= 68680 || 68736 <= _Chr && _Chr <= 68786 || 68800 <= _Chr && _Chr <= 68850 || 68864 <= _Chr && _Chr <= 68899 || 69248 <= _Chr && _Chr <= 69289 || 69296 <= _Chr && _Chr <= 69297 || 69376 <= _Chr && _Chr <= 69404 || _Chr == 69415 || 69424 <= _Chr && _Chr <= 69445 || 69552 <= _Chr && _Chr <= 69572 || 69600 <= _Chr && _Chr <= 69622 || 69635 <= _Chr && _Chr <= 69687 || 69763 <= _Chr && _Chr <= 69807 || 69840 <= _Chr && _Chr <= 69864 || 69891 <= _Chr && _Chr <= 69926 || _Chr == 69956 || _Chr == 69959 || 69968 <= _Chr && _Chr <= 70002 || _Chr == 70006 || 70019 <= _Chr && _Chr <= 70066 || 70081 <= _Chr && _Chr <= 70084 || _Chr == 70106 || _Chr == 70108 || 70144 <= _Chr && _Chr <= 70161 || 70163 <= _Chr && _Chr <= 70187 || 70272 <= _Chr && _Chr <= 70278 || _Chr == 70280 || 70282 <= _Chr && _Chr <= 70285 || 70287 <= _Chr && _Chr <= 70301 || 70303 <= _Chr && _Chr <= 70312 || 70320 <= _Chr && _Chr <= 70366 || 70405 <= _Chr && _Chr <= 70412 || 70415 <= _Chr && _Chr <= 70416 || 70419 <= _Chr && _Chr <= 70440 || 70442 <= _Chr && _Chr <= 70448 || 70450 <= _Chr && _Chr <= 70451 || 70453 <= _Chr && _Chr <= 70457 || _Chr == 70461 || _Chr == 70480 || 70493 <= _Chr && _Chr <= 70497 || 70656 <= _Chr && _Chr <= 70708 || 70727 <= _Chr && _Chr <= 70730 || 70751 <= _Chr && _Chr <= 70753 || 70784 <= _Chr && _Chr <= 70831 || 70852 <= _Chr && _Chr <= 70853 || _Chr == 70855 || 71040 <= _Chr && _Chr <= 71086 || 71128 <= _Chr && _Chr <= 71131 || 71168 <= _Chr && _Chr <= 71215 || _Chr == 71236 || 71296 <= _Chr && _Chr <= 71338 || _Chr == 71352 || 71424 <= _Chr && _Chr <= 71450 || 71680 <= _Chr && _Chr <= 71723 || 71840 <= _Chr && _Chr <= 71903 || 71935 <= _Chr && _Chr <= 71942 || _Chr == 71945 || 71948 <= _Chr && _Chr <= 71955 || 71957 <= _Chr && _Chr <= 71958 || 71960 <= _Chr && _Chr <= 71983 || _Chr == 71999 || _Chr == 72001 || 72096 <= _Chr && _Chr <= 72103 || 72106 <= _Chr && _Chr <= 72144 || _Chr == 72161 || _Chr == 72163 || _Chr == 72192 || 72203 <= _Chr && _Chr <= 72242 || _Chr == 72250 || _Chr == 72272 || 72284 <= _Chr && _Chr <= 72329 || _Chr == 72349 || 72384 <= _Chr && _Chr <= 72440 || 72704 <= _Chr && _Chr <= 72712 || 72714 <= _Chr && _Chr <= 72750 || _Chr == 72768 || 72818 <= _Chr && _Chr <= 72847 || 72960 <= _Chr && _Chr <= 72966 || 72968 <= _Chr && _Chr <= 72969 || 72971 <= _Chr && _Chr <= 73008 || _Chr == 73030 || 73056 <= _Chr && _Chr <= 73061 || 73063 <= _Chr && _Chr <= 73064 || 73066 <= _Chr && _Chr <= 73097 || _Chr == 73112 || 73440 <= _Chr && _Chr <= 73458 || _Chr == 73648 || 73728 <= _Chr && _Chr <= 74649 || 74880 <= _Chr && _Chr <= 75075 || 77824 <= _Chr && _Chr <= 78894 || 82944 <= _Chr && _Chr <= 83526 || 92160 <= _Chr && _Chr <= 92728 || 92736 <= _Chr && _Chr <= 92766 || 92880 <= _Chr && _Chr <= 92909 || 92928 <= _Chr && _Chr <= 92975 || 92992 <= _Chr && _Chr <= 92995 || 93027 <= _Chr && _Chr <= 93047 || 93053 <= _Chr && _Chr <= 93071 || 93760 <= _Chr && _Chr <= 93823 || 93952 <= _Chr && _Chr <= 94026 || _Chr == 94032 || 94099 <= _Chr && _Chr <= 94111 || 94176 <= _Chr && _Chr <= 94177 || _Chr == 94179 || 94208 <= _Chr && _Chr <= 100343 || 100352 <= _Chr && _Chr <= 101589 || 101632 <= _Chr && _Chr <= 101640 || 110592 <= _Chr && _Chr <= 110878 || 110928 <= _Chr && _Chr <= 110930 || 110948 <= _Chr && _Chr <= 110951 || 110960 <= _Chr && _Chr <= 111355 || 113664 <= _Chr && _Chr <= 113770 || 113776 <= _Chr && _Chr <= 113788 || 113792 <= _Chr && _Chr <= 113800 || 113808 <= _Chr && _Chr <= 113817 || 119808 <= _Chr && _Chr <= 119892 || 119894 <= _Chr && _Chr <= 119964 || 119966 <= _Chr && _Chr <= 119967 || _Chr == 119970 || 119973 <= _Chr && _Chr <= 119974 || 119977 <= _Chr && _Chr <= 119980 || 119982 <= _Chr && _Chr <= 119993 || _Chr == 119995 || 119997 <= _Chr && _Chr <= 120003 || 120005 <= _Chr && _Chr <= 120069 || 120071 <= _Chr && _Chr <= 120074 || 120077 <= _Chr && _Chr <= 120084 || 120086 <= _Chr && _Chr <= 120092 || 120094 <= _Chr && _Chr <= 120121 || 120123 <= _Chr && _Chr <= 120126 || 120128 <= _Chr && _Chr <= 120132 || _Chr == 120134 || 120138 <= _Chr && _Chr <= 120144 || 120146 <= _Chr && _Chr <= 120485 || 120488 <= _Chr && _Chr <= 120512 || 120514 <= _Chr && _Chr <= 120538 || 120540 <= _Chr && _Chr <= 120570 || 120572 <= _Chr && _Chr <= 120596 || 120598 <= _Chr && _Chr <= 120628 || 120630 <= _Chr && _Chr <= 120654 || 120656 <= _Chr && _Chr <= 120686 || 120688 <= _Chr && _Chr <= 120712 || 120714 <= _Chr && _Chr <= 120744 || 120746 <= _Chr && _Chr <= 120770 || 120772 <= _Chr && _Chr <= 120779 || 123136 <= _Chr && _Chr <= 123180 || 123191 <= _Chr && _Chr <= 123197 || _Chr == 123214 || 123584 <= _Chr && _Chr <= 123627 || 124928 <= _Chr && _Chr <= 125124 || 125184 <= _Chr && _Chr <= 125251 || _Chr == 125259 || 126464 <= _Chr && _Chr <= 126467 || 126469 <= _Chr && _Chr <= 126495 || 126497 <= _Chr && _Chr <= 126498 || _Chr == 126500 || _Chr == 126503 || 126505 <= _Chr && _Chr <= 126514 || 126516 <= _Chr && _Chr <= 126519 || _Chr == 126521 || _Chr == 126523 || _Chr == 126530 || _Chr == 126535 || _Chr == 126537 || _Chr == 126539 || 126541 <= _Chr && _Chr <= 126543 || 126545 <= _Chr && _Chr <= 126546 || _Chr == 126548 || _Chr == 126551 || _Chr == 126553 || _Chr == 126555 || _Chr == 126557 || _Chr == 126559 || 126561 <= _Chr && _Chr <= 126562 || _Chr == 126564 || 126567 <= _Chr && _Chr <= 126570 || 126572 <= _Chr && _Chr <= 126578 || 126580 <= _Chr && _Chr <= 126583 || 126585 <= _Chr && _Chr <= 126588 || _Chr == 126590 || 126592 <= _Chr && _Chr <= 126601 || 126603 <= _Chr && _Chr <= 126619 || 126625 <= _Chr && _Chr <= 126627 || 126629 <= _Chr && _Chr <= 126633 || 126635 <= _Chr && _Chr <= 126651 || 131072 <= _Chr && _Chr <= 173789 || 173824 <= _Chr && _Chr <= 177972 || 177984 <= _Chr && _Chr <= 178205 || 178208 <= _Chr && _Chr <= 183969 || 183984 <= _Chr && _Chr <= 191456 || 194560 <= _Chr && _Chr <= 195101 || 196608 <= _Chr && _Chr <= 201546 || false) { return true; }
		return false;
	}
	bool pystr::check_Ascii() {
		pystr _Chr = (*this)[0];
		if (0 <= _Chr && _Chr <= 127 || false) { return true; }
		return false;
	}
	bool pystr::check_digit() {
		pystr _Chr = (*this)[0];
		if (48 <= _Chr && _Chr <= 57 || 178 <= _Chr && _Chr <= 179 || _Chr == 185 || 1632 <= _Chr && _Chr <= 1641 || 1776 <= _Chr && _Chr <= 1785 || 1984 <= _Chr && _Chr <= 1993 || 2406 <= _Chr && _Chr <= 2415 || 2534 <= _Chr && _Chr <= 2543 || 2662 <= _Chr && _Chr <= 2671 || 2790 <= _Chr && _Chr <= 2799 || 2918 <= _Chr && _Chr <= 2927 || 3046 <= _Chr && _Chr <= 3055 || 3174 <= _Chr && _Chr <= 3183 || 3302 <= _Chr && _Chr <= 3311 || 3430 <= _Chr && _Chr <= 3439 || 3558 <= _Chr && _Chr <= 3567 || 3664 <= _Chr && _Chr <= 3673 || 3792 <= _Chr && _Chr <= 3801 || 3872 <= _Chr && _Chr <= 3881 || 4160 <= _Chr && _Chr <= 4169 || 4240 <= _Chr && _Chr <= 4249 || 4969 <= _Chr && _Chr <= 4977 || 6112 <= _Chr && _Chr <= 6121 || 6160 <= _Chr && _Chr <= 6169 || 6470 <= _Chr && _Chr <= 6479 || 6608 <= _Chr && _Chr <= 6618 || 6784 <= _Chr && _Chr <= 6793 || 6800 <= _Chr && _Chr <= 6809 || 6992 <= _Chr && _Chr <= 7001 || 7088 <= _Chr && _Chr <= 7097 || 7232 <= _Chr && _Chr <= 7241 || 7248 <= _Chr && _Chr <= 7257 || _Chr == 8304 || 8308 <= _Chr && _Chr <= 8313 || 8320 <= _Chr && _Chr <= 8329 || 9312 <= _Chr && _Chr <= 9320 || 9332 <= _Chr && _Chr <= 9340 || 9352 <= _Chr && _Chr <= 9360 || _Chr == 9450 || 9461 <= _Chr && _Chr <= 9469 || _Chr == 9471 || 10102 <= _Chr && _Chr <= 10110 || 10112 <= _Chr && _Chr <= 10120 || 10122 <= _Chr && _Chr <= 10130 || 42528 <= _Chr && _Chr <= 42537 || 43216 <= _Chr && _Chr <= 43225 || 43264 <= _Chr && _Chr <= 43273 || 43472 <= _Chr && _Chr <= 43481 || 43504 <= _Chr && _Chr <= 43513 || 43600 <= _Chr && _Chr <= 43609 || 44016 <= _Chr && _Chr <= 44025 || 65296 <= _Chr && _Chr <= 65305 || 66720 <= _Chr && _Chr <= 66729 || 68160 <= _Chr && _Chr <= 68163 || 68912 <= _Chr && _Chr <= 68921 || 69216 <= _Chr && _Chr <= 69224 || 69714 <= _Chr && _Chr <= 69722 || 69734 <= _Chr && _Chr <= 69743 || 69872 <= _Chr && _Chr <= 69881 || 69942 <= _Chr && _Chr <= 69951 || 70096 <= _Chr && _Chr <= 70105 || 70384 <= _Chr && _Chr <= 70393 || 70736 <= _Chr && _Chr <= 70745 || 70864 <= _Chr && _Chr <= 70873 || 71248 <= _Chr && _Chr <= 71257 || 71360 <= _Chr && _Chr <= 71369 || 71472 <= _Chr && _Chr <= 71481 || 71904 <= _Chr && _Chr <= 71913 || 72016 <= _Chr && _Chr <= 72025 || 72784 <= _Chr && _Chr <= 72793 || 73040 <= _Chr && _Chr <= 73049 || 73120 <= _Chr && _Chr <= 73129 || 92768 <= _Chr && _Chr <= 92777 || 93008 <= _Chr && _Chr <= 93017 || 120782 <= _Chr && _Chr <= 120831 || 123200 <= _Chr && _Chr <= 123209 || 123632 <= _Chr && _Chr <= 123641 || 125264 <= _Chr && _Chr <= 125273 || 127232 <= _Chr && _Chr <= 127242 || 130032 <= _Chr && _Chr <= 130041 || false) { return true; }
		return false;
	}
	bool pystr::check_decimal() {
		pystr _Chr = (*this)[0];
		if (48 <= _Chr && _Chr <= 57 || 1632 <= _Chr && _Chr <= 1641 || 1776 <= _Chr && _Chr <= 1785 || 1984 <= _Chr && _Chr <= 1993 || 2406 <= _Chr && _Chr <= 2415 || 2534 <= _Chr && _Chr <= 2543 || 2662 <= _Chr && _Chr <= 2671 || 2790 <= _Chr && _Chr <= 2799 || 2918 <= _Chr && _Chr <= 2927 || 3046 <= _Chr && _Chr <= 3055 || 3174 <= _Chr && _Chr <= 3183 || 3302 <= _Chr && _Chr <= 3311 || 3430 <= _Chr && _Chr <= 3439 || 3558 <= _Chr && _Chr <= 3567 || 3664 <= _Chr && _Chr <= 3673 || 3792 <= _Chr && _Chr <= 3801 || 3872 <= _Chr && _Chr <= 3881 || 4160 <= _Chr && _Chr <= 4169 || 4240 <= _Chr && _Chr <= 4249 || 6112 <= _Chr && _Chr <= 6121 || 6160 <= _Chr && _Chr <= 6169 || 6470 <= _Chr && _Chr <= 6479 || 6608 <= _Chr && _Chr <= 6617 || 6784 <= _Chr && _Chr <= 6793 || 6800 <= _Chr && _Chr <= 6809 || 6992 <= _Chr && _Chr <= 7001 || 7088 <= _Chr && _Chr <= 7097 || 7232 <= _Chr && _Chr <= 7241 || 7248 <= _Chr && _Chr <= 7257 || 42528 <= _Chr && _Chr <= 42537 || 43216 <= _Chr && _Chr <= 43225 || 43264 <= _Chr && _Chr <= 43273 || 43472 <= _Chr && _Chr <= 43481 || 43504 <= _Chr && _Chr <= 43513 || 43600 <= _Chr && _Chr <= 43609 || 44016 <= _Chr && _Chr <= 44025 || 65296 <= _Chr && _Chr <= 65305 || 66720 <= _Chr && _Chr <= 66729 || 68912 <= _Chr && _Chr <= 68921 || 69734 <= _Chr && _Chr <= 69743 || 69872 <= _Chr && _Chr <= 69881 || 69942 <= _Chr && _Chr <= 69951 || 70096 <= _Chr && _Chr <= 70105 || 70384 <= _Chr && _Chr <= 70393 || 70736 <= _Chr && _Chr <= 70745 || 70864 <= _Chr && _Chr <= 70873 || 71248 <= _Chr && _Chr <= 71257 || 71360 <= _Chr && _Chr <= 71369 || 71472 <= _Chr && _Chr <= 71481 || 71904 <= _Chr && _Chr <= 71913 || 72016 <= _Chr && _Chr <= 72025 || 72784 <= _Chr && _Chr <= 72793 || 73040 <= _Chr && _Chr <= 73049 || 73120 <= _Chr && _Chr <= 73129 || 92768 <= _Chr && _Chr <= 92777 || 93008 <= _Chr && _Chr <= 93017 || 120782 <= _Chr && _Chr <= 120831 || 123200 <= _Chr && _Chr <= 123209 || 123632 <= _Chr && _Chr <= 123641 || 125264 <= _Chr && _Chr <= 125273 || 130032 <= _Chr && _Chr <= 130041 || false) { return true; }
		return false;
	}
	bool pystr::check_numeric() {
		pystr _Chr = (*this)[0];
		if (48 <= _Chr && _Chr <= 57 || 178 <= _Chr && _Chr <= 179 || _Chr == 185 || 188 <= _Chr && _Chr <= 190 || 1632 <= _Chr && _Chr <= 1641 || 1776 <= _Chr && _Chr <= 1785 || 1984 <= _Chr && _Chr <= 1993 || 2406 <= _Chr && _Chr <= 2415 || 2534 <= _Chr && _Chr <= 2543 || 2548 <= _Chr && _Chr <= 2553 || 2662 <= _Chr && _Chr <= 2671 || 2790 <= _Chr && _Chr <= 2799 || 2918 <= _Chr && _Chr <= 2927 || 2930 <= _Chr && _Chr <= 2935 || 3046 <= _Chr && _Chr <= 3058 || 3174 <= _Chr && _Chr <= 3183 || 3192 <= _Chr && _Chr <= 3198 || 3302 <= _Chr && _Chr <= 3311 || 3416 <= _Chr && _Chr <= 3422 || 3430 <= _Chr && _Chr <= 3448 || 3558 <= _Chr && _Chr <= 3567 || 3664 <= _Chr && _Chr <= 3673 || 3792 <= _Chr && _Chr <= 3801 || 3872 <= _Chr && _Chr <= 3891 || 4160 <= _Chr && _Chr <= 4169 || 4240 <= _Chr && _Chr <= 4249 || 4969 <= _Chr && _Chr <= 4988 || 5870 <= _Chr && _Chr <= 5872 || 6112 <= _Chr && _Chr <= 6121 || 6128 <= _Chr && _Chr <= 6137 || 6160 <= _Chr && _Chr <= 6169 || 6470 <= _Chr && _Chr <= 6479 || 6608 <= _Chr && _Chr <= 6618 || 6784 <= _Chr && _Chr <= 6793 || 6800 <= _Chr && _Chr <= 6809 || 6992 <= _Chr && _Chr <= 7001 || 7088 <= _Chr && _Chr <= 7097 || 7232 <= _Chr && _Chr <= 7241 || 7248 <= _Chr && _Chr <= 7257 || _Chr == 8304 || 8308 <= _Chr && _Chr <= 8313 || 8320 <= _Chr && _Chr <= 8329 || 8528 <= _Chr && _Chr <= 8578 || 8581 <= _Chr && _Chr <= 8585 || 9312 <= _Chr && _Chr <= 9371 || 9450 <= _Chr && _Chr <= 9471 || 10102 <= _Chr && _Chr <= 10131 || _Chr == 11517 || _Chr == 12295 || 12321 <= _Chr && _Chr <= 12329 || 12344 <= _Chr && _Chr <= 12346 || 12690 <= _Chr && _Chr <= 12693 || 12832 <= _Chr && _Chr <= 12841 || 12872 <= _Chr && _Chr <= 12879 || 12881 <= _Chr && _Chr <= 12895 || 12928 <= _Chr && _Chr <= 12937 || 12977 <= _Chr && _Chr <= 12991 || _Chr == 13317 || _Chr == 13443 || _Chr == 14378 || _Chr == 15181 || _Chr == 19968 || _Chr == 19971 || _Chr == 19975 || _Chr == 19977 || _Chr == 20061 || _Chr == 20108 || _Chr == 20116 || _Chr == 20118 || 20159 <= _Chr && _Chr <= 20160 || _Chr == 20191 || _Chr == 20200 || _Chr == 20237 || _Chr == 20336 || _Chr == 20740 || _Chr == 20806 || _Chr == 20841 || _Chr == 20843 || _Chr == 20845 || _Chr == 21313 || 21315 <= _Chr && _Chr <= 21317 || _Chr == 21324 || 21441 <= _Chr && _Chr <= 21444 || _Chr == 22235 || _Chr == 22769 || _Chr == 22777 || _Chr == 24186 || 24318 <= _Chr && _Chr <= 24319 || 24332 <= _Chr && _Chr <= 24334 || _Chr == 24336 || _Chr == 25342 || _Chr == 25420 || _Chr == 26578 || _Chr == 28422 || _Chr == 29590 || _Chr == 30334 || _Chr == 32902 || _Chr == 33836 || _Chr == 36014 || _Chr == 36019 || _Chr == 36144 || _Chr == 38433 || _Chr == 38470 || _Chr == 38476 || _Chr == 38520 || _Chr == 38646 || 42528 <= _Chr && _Chr <= 42537 || 42726 <= _Chr && _Chr <= 42735 || 43056 <= _Chr && _Chr <= 43061 || 43216 <= _Chr && _Chr <= 43225 || 43264 <= _Chr && _Chr <= 43273 || 43472 <= _Chr && _Chr <= 43481 || 43504 <= _Chr && _Chr <= 43513 || 43600 <= _Chr && _Chr <= 43609 || 44016 <= _Chr && _Chr <= 44025 || _Chr == 63851 || _Chr == 63859 || _Chr == 63864 || _Chr == 63922 || _Chr == 63953 || _Chr == 63955 || _Chr == 63997 || 65296 <= _Chr && _Chr <= 65305 || 65799 <= _Chr && _Chr <= 65843 || 65856 <= _Chr && _Chr <= 65912 || 65930 <= _Chr && _Chr <= 65931 || 66273 <= _Chr && _Chr <= 66299 || 66336 <= _Chr && _Chr <= 66339 || _Chr == 66369 || _Chr == 66378 || 66513 <= _Chr && _Chr <= 66517 || 66720 <= _Chr && _Chr <= 66729 || 67672 <= _Chr && _Chr <= 67679 || 67705 <= _Chr && _Chr <= 67711 || 67751 <= _Chr && _Chr <= 67759 || 67835 <= _Chr && _Chr <= 67839 || 67862 <= _Chr && _Chr <= 67867 || 68028 <= _Chr && _Chr <= 68029 || 68032 <= _Chr && _Chr <= 68047 || 68050 <= _Chr && _Chr <= 68095 || 68160 <= _Chr && _Chr <= 68168 || 68221 <= _Chr && _Chr <= 68222 || 68253 <= _Chr && _Chr <= 68255 || 68331 <= _Chr && _Chr <= 68335 || 68440 <= _Chr && _Chr <= 68447 || 68472 <= _Chr && _Chr <= 68479 || 68521 <= _Chr && _Chr <= 68527 || 68858 <= _Chr && _Chr <= 68863 || 68912 <= _Chr && _Chr <= 68921 || 69216 <= _Chr && _Chr <= 69246 || 69405 <= _Chr && _Chr <= 69414 || 69457 <= _Chr && _Chr <= 69460 || 69573 <= _Chr && _Chr <= 69579 || 69714 <= _Chr && _Chr <= 69743 || 69872 <= _Chr && _Chr <= 69881 || 69942 <= _Chr && _Chr <= 69951 || 70096 <= _Chr && _Chr <= 70105 || 70113 <= _Chr && _Chr <= 70132 || 70384 <= _Chr && _Chr <= 70393 || 70736 <= _Chr && _Chr <= 70745 || 70864 <= _Chr && _Chr <= 70873 || 71248 <= _Chr && _Chr <= 71257 || 71360 <= _Chr && _Chr <= 71369 || 71472 <= _Chr && _Chr <= 71483 || 71904 <= _Chr && _Chr <= 71922 || 72016 <= _Chr && _Chr <= 72025 || 72784 <= _Chr && _Chr <= 72812 || 73040 <= _Chr && _Chr <= 73049 || 73120 <= _Chr && _Chr <= 73129 || 73664 <= _Chr && _Chr <= 73684 || 74752 <= _Chr && _Chr <= 74862 || 92768 <= _Chr && _Chr <= 92777 || 93008 <= _Chr && _Chr <= 93017 || 93019 <= _Chr && _Chr <= 93025 || 93824 <= _Chr && _Chr <= 93846 || 119520 <= _Chr && _Chr <= 119539 || 119648 <= _Chr && _Chr <= 119672 || 120782 <= _Chr && _Chr <= 120831 || 123200 <= _Chr && _Chr <= 123209 || 123632 <= _Chr && _Chr <= 123641 || 125127 <= _Chr && _Chr <= 125135 || 125264 <= _Chr && _Chr <= 125273 || 126065 <= _Chr && _Chr <= 126123 || 126125 <= _Chr && _Chr <= 126127 || 126129 <= _Chr && _Chr <= 126132 || 126209 <= _Chr && _Chr <= 126253 || 126255 <= _Chr && _Chr <= 126269 || 127232 <= _Chr && _Chr <= 127244 || 130032 <= _Chr && _Chr <= 130041 || _Chr == 131073 || _Chr == 131172 || _Chr == 131298 || _Chr == 131361 || _Chr == 133418 || _Chr == 133507 || _Chr == 133516 || _Chr == 133532 || _Chr == 133866 || _Chr == 133885 || _Chr == 133913 || _Chr == 140176 || _Chr == 141720 || _Chr == 146203 || _Chr == 156269 || _Chr == 194704 || false) { return true; }
		return false;
	}
	bool pystr::check_printable() {
		pystr _Chr = (*this)[0];
		if (32 <= _Chr && _Chr <= 126 || 161 <= _Chr && _Chr <= 172 || 174 <= _Chr && _Chr <= 887 || 890 <= _Chr && _Chr <= 895 || 900 <= _Chr && _Chr <= 906 || _Chr == 908 || 910 <= _Chr && _Chr <= 929 || 931 <= _Chr && _Chr <= 1327 || 1329 <= _Chr && _Chr <= 1366 || 1369 <= _Chr && _Chr <= 1418 || 1421 <= _Chr && _Chr <= 1423 || 1425 <= _Chr && _Chr <= 1479 || 1488 <= _Chr && _Chr <= 1514 || 1519 <= _Chr && _Chr <= 1524 || 1542 <= _Chr && _Chr <= 1563 || 1566 <= _Chr && _Chr <= 1756 || 1758 <= _Chr && _Chr <= 1805 || 1808 <= _Chr && _Chr <= 1866 || 1869 <= _Chr && _Chr <= 1969 || 1984 <= _Chr && _Chr <= 2042 || 2045 <= _Chr && _Chr <= 2093 || 2096 <= _Chr && _Chr <= 2110 || 2112 <= _Chr && _Chr <= 2139 || _Chr == 2142 || 2144 <= _Chr && _Chr <= 2154 || 2208 <= _Chr && _Chr <= 2228 || 2230 <= _Chr && _Chr <= 2247 || 2259 <= _Chr && _Chr <= 2273 || 2275 <= _Chr && _Chr <= 2435 || 2437 <= _Chr && _Chr <= 2444 || 2447 <= _Chr && _Chr <= 2448 || 2451 <= _Chr && _Chr <= 2472 || 2474 <= _Chr && _Chr <= 2480 || _Chr == 2482 || 2486 <= _Chr && _Chr <= 2489 || 2492 <= _Chr && _Chr <= 2500 || 2503 <= _Chr && _Chr <= 2504 || 2507 <= _Chr && _Chr <= 2510 || _Chr == 2519 || 2524 <= _Chr && _Chr <= 2525 || 2527 <= _Chr && _Chr <= 2531 || 2534 <= _Chr && _Chr <= 2558 || 2561 <= _Chr && _Chr <= 2563 || 2565 <= _Chr && _Chr <= 2570 || 2575 <= _Chr && _Chr <= 2576 || 2579 <= _Chr && _Chr <= 2600 || 2602 <= _Chr && _Chr <= 2608 || 2610 <= _Chr && _Chr <= 2611 || 2613 <= _Chr && _Chr <= 2614 || 2616 <= _Chr && _Chr <= 2617 || _Chr == 2620 || 2622 <= _Chr && _Chr <= 2626 || 2631 <= _Chr && _Chr <= 2632 || 2635 <= _Chr && _Chr <= 2637 || _Chr == 2641 || 2649 <= _Chr && _Chr <= 2652 || _Chr == 2654 || 2662 <= _Chr && _Chr <= 2678 || 2689 <= _Chr && _Chr <= 2691 || 2693 <= _Chr && _Chr <= 2701 || 2703 <= _Chr && _Chr <= 2705 || 2707 <= _Chr && _Chr <= 2728 || 2730 <= _Chr && _Chr <= 2736 || 2738 <= _Chr && _Chr <= 2739 || 2741 <= _Chr && _Chr <= 2745 || 2748 <= _Chr && _Chr <= 2757 || 2759 <= _Chr && _Chr <= 2761 || 2763 <= _Chr && _Chr <= 2765 || _Chr == 2768 || 2784 <= _Chr && _Chr <= 2787 || 2790 <= _Chr && _Chr <= 2801 || 2809 <= _Chr && _Chr <= 2815 || 2817 <= _Chr && _Chr <= 2819 || 2821 <= _Chr && _Chr <= 2828 || 2831 <= _Chr && _Chr <= 2832 || 2835 <= _Chr && _Chr <= 2856 || 2858 <= _Chr && _Chr <= 2864 || 2866 <= _Chr && _Chr <= 2867 || 2869 <= _Chr && _Chr <= 2873 || 2876 <= _Chr && _Chr <= 2884 || 2887 <= _Chr && _Chr <= 2888 || 2891 <= _Chr && _Chr <= 2893 || 2901 <= _Chr && _Chr <= 2903 || 2908 <= _Chr && _Chr <= 2909 || 2911 <= _Chr && _Chr <= 2915 || 2918 <= _Chr && _Chr <= 2935 || 2946 <= _Chr && _Chr <= 2947 || 2949 <= _Chr && _Chr <= 2954 || 2958 <= _Chr && _Chr <= 2960 || 2962 <= _Chr && _Chr <= 2965 || 2969 <= _Chr && _Chr <= 2970 || _Chr == 2972 || 2974 <= _Chr && _Chr <= 2975 || 2979 <= _Chr && _Chr <= 2980 || 2984 <= _Chr && _Chr <= 2986 || 2990 <= _Chr && _Chr <= 3001 || 3006 <= _Chr && _Chr <= 3010 || 3014 <= _Chr && _Chr <= 3016 || 3018 <= _Chr && _Chr <= 3021 || _Chr == 3024 || _Chr == 3031 || 3046 <= _Chr && _Chr <= 3066 || 3072 <= _Chr && _Chr <= 3084 || 3086 <= _Chr && _Chr <= 3088 || 3090 <= _Chr && _Chr <= 3112 || 3114 <= _Chr && _Chr <= 3129 || 3133 <= _Chr && _Chr <= 3140 || 3142 <= _Chr && _Chr <= 3144 || 3146 <= _Chr && _Chr <= 3149 || 3157 <= _Chr && _Chr <= 3158 || 3160 <= _Chr && _Chr <= 3162 || 3168 <= _Chr && _Chr <= 3171 || 3174 <= _Chr && _Chr <= 3183 || 3191 <= _Chr && _Chr <= 3212 || 3214 <= _Chr && _Chr <= 3216 || 3218 <= _Chr && _Chr <= 3240 || 3242 <= _Chr && _Chr <= 3251 || 3253 <= _Chr && _Chr <= 3257 || 3260 <= _Chr && _Chr <= 3268 || 3270 <= _Chr && _Chr <= 3272 || 3274 <= _Chr && _Chr <= 3277 || 3285 <= _Chr && _Chr <= 3286 || _Chr == 3294 || 3296 <= _Chr && _Chr <= 3299 || 3302 <= _Chr && _Chr <= 3311 || 3313 <= _Chr && _Chr <= 3314 || 3328 <= _Chr && _Chr <= 3340 || 3342 <= _Chr && _Chr <= 3344 || 3346 <= _Chr && _Chr <= 3396 || 3398 <= _Chr && _Chr <= 3400 || 3402 <= _Chr && _Chr <= 3407 || 3412 <= _Chr && _Chr <= 3427 || 3430 <= _Chr && _Chr <= 3455 || 3457 <= _Chr && _Chr <= 3459 || 3461 <= _Chr && _Chr <= 3478 || 3482 <= _Chr && _Chr <= 3505 || 3507 <= _Chr && _Chr <= 3515 || _Chr == 3517 || 3520 <= _Chr && _Chr <= 3526 || _Chr == 3530 || 3535 <= _Chr && _Chr <= 3540 || _Chr == 3542 || 3544 <= _Chr && _Chr <= 3551 || 3558 <= _Chr && _Chr <= 3567 || 3570 <= _Chr && _Chr <= 3572 || 3585 <= _Chr && _Chr <= 3642 || 3647 <= _Chr && _Chr <= 3675 || 3713 <= _Chr && _Chr <= 3714 || _Chr == 3716 || 3718 <= _Chr && _Chr <= 3722 || 3724 <= _Chr && _Chr <= 3747 || _Chr == 3749 || 3751 <= _Chr && _Chr <= 3773 || 3776 <= _Chr && _Chr <= 3780 || _Chr == 3782 || 3784 <= _Chr && _Chr <= 3789 || 3792 <= _Chr && _Chr <= 3801 || 3804 <= _Chr && _Chr <= 3807 || 3840 <= _Chr && _Chr <= 3911 || 3913 <= _Chr && _Chr <= 3948 || 3953 <= _Chr && _Chr <= 3991 || 3993 <= _Chr && _Chr <= 4028 || 4030 <= _Chr && _Chr <= 4044 || 4046 <= _Chr && _Chr <= 4058 || 4096 <= _Chr && _Chr <= 4293 || _Chr == 4295 || _Chr == 4301 || 4304 <= _Chr && _Chr <= 4680 || 4682 <= _Chr && _Chr <= 4685 || 4688 <= _Chr && _Chr <= 4694 || _Chr == 4696 || 4698 <= _Chr && _Chr <= 4701 || 4704 <= _Chr && _Chr <= 4744 || 4746 <= _Chr && _Chr <= 4749 || 4752 <= _Chr && _Chr <= 4784 || 4786 <= _Chr && _Chr <= 4789 || 4792 <= _Chr && _Chr <= 4798 || _Chr == 4800 || 4802 <= _Chr && _Chr <= 4805 || 4808 <= _Chr && _Chr <= 4822 || 4824 <= _Chr && _Chr <= 4880 || 4882 <= _Chr && _Chr <= 4885 || 4888 <= _Chr && _Chr <= 4954 || 4957 <= _Chr && _Chr <= 4988 || 4992 <= _Chr && _Chr <= 5017 || 5024 <= _Chr && _Chr <= 5109 || 5112 <= _Chr && _Chr <= 5117 || 5120 <= _Chr && _Chr <= 5759 || 5761 <= _Chr && _Chr <= 5788 || 5792 <= _Chr && _Chr <= 5880 || 5888 <= _Chr && _Chr <= 5900 || 5902 <= _Chr && _Chr <= 5908 || 5920 <= _Chr && _Chr <= 5942 || 5952 <= _Chr && _Chr <= 5971 || 5984 <= _Chr && _Chr <= 5996 || 5998 <= _Chr && _Chr <= 6000 || 6002 <= _Chr && _Chr <= 6003 || 6016 <= _Chr && _Chr <= 6109 || 6112 <= _Chr && _Chr <= 6121 || 6128 <= _Chr && _Chr <= 6137 || 6144 <= _Chr && _Chr <= 6157 || 6160 <= _Chr && _Chr <= 6169 || 6176 <= _Chr && _Chr <= 6264 || 6272 <= _Chr && _Chr <= 6314 || 6320 <= _Chr && _Chr <= 6389 || 6400 <= _Chr && _Chr <= 6430 || 6432 <= _Chr && _Chr <= 6443 || 6448 <= _Chr && _Chr <= 6459 || _Chr == 6464 || 6468 <= _Chr && _Chr <= 6509 || 6512 <= _Chr && _Chr <= 6516 || 6528 <= _Chr && _Chr <= 6571 || 6576 <= _Chr && _Chr <= 6601 || 6608 <= _Chr && _Chr <= 6618 || 6622 <= _Chr && _Chr <= 6683 || 6686 <= _Chr && _Chr <= 6750 || 6752 <= _Chr && _Chr <= 6780 || 6783 <= _Chr && _Chr <= 6793 || 6800 <= _Chr && _Chr <= 6809 || 6816 <= _Chr && _Chr <= 6829 || 6832 <= _Chr && _Chr <= 6848 || 6912 <= _Chr && _Chr <= 6987 || 6992 <= _Chr && _Chr <= 7036 || 7040 <= _Chr && _Chr <= 7155 || 7164 <= _Chr && _Chr <= 7223 || 7227 <= _Chr && _Chr <= 7241 || 7245 <= _Chr && _Chr <= 7304 || 7312 <= _Chr && _Chr <= 7354 || 7357 <= _Chr && _Chr <= 7367 || 7376 <= _Chr && _Chr <= 7418 || 7424 <= _Chr && _Chr <= 7673 || 7675 <= _Chr && _Chr <= 7957 || 7960 <= _Chr && _Chr <= 7965 || 7968 <= _Chr && _Chr <= 8005 || 8008 <= _Chr && _Chr <= 8013 || 8016 <= _Chr && _Chr <= 8023 || _Chr == 8025 || _Chr == 8027 || _Chr == 8029 || 8031 <= _Chr && _Chr <= 8061 || 8064 <= _Chr && _Chr <= 8116 || 8118 <= _Chr && _Chr <= 8132 || 8134 <= _Chr && _Chr <= 8147 || 8150 <= _Chr && _Chr <= 8155 || 8157 <= _Chr && _Chr <= 8175 || 8178 <= _Chr && _Chr <= 8180 || 8182 <= _Chr && _Chr <= 8190 || 8208 <= _Chr && _Chr <= 8231 || 8240 <= _Chr && _Chr <= 8286 || 8304 <= _Chr && _Chr <= 8305 || 8308 <= _Chr && _Chr <= 8334 || 8336 <= _Chr && _Chr <= 8348 || 8352 <= _Chr && _Chr <= 8383 || 8400 <= _Chr && _Chr <= 8432 || 8448 <= _Chr && _Chr <= 8587 || 8592 <= _Chr && _Chr <= 9254 || 9280 <= _Chr && _Chr <= 9290 || 9312 <= _Chr && _Chr <= 11123 || 11126 <= _Chr && _Chr <= 11157 || 11159 <= _Chr && _Chr <= 11310 || 11312 <= _Chr && _Chr <= 11358 || 11360 <= _Chr && _Chr <= 11507 || 11513 <= _Chr && _Chr <= 11557 || _Chr == 11559 || _Chr == 11565 || 11568 <= _Chr && _Chr <= 11623 || 11631 <= _Chr && _Chr <= 11632 || 11647 <= _Chr && _Chr <= 11670 || 11680 <= _Chr && _Chr <= 11686 || 11688 <= _Chr && _Chr <= 11694 || 11696 <= _Chr && _Chr <= 11702 || 11704 <= _Chr && _Chr <= 11710 || 11712 <= _Chr && _Chr <= 11718 || 11720 <= _Chr && _Chr <= 11726 || 11728 <= _Chr && _Chr <= 11734 || 11736 <= _Chr && _Chr <= 11742 || 11744 <= _Chr && _Chr <= 11858 || 11904 <= _Chr && _Chr <= 11929 || 11931 <= _Chr && _Chr <= 12019 || 12032 <= _Chr && _Chr <= 12245 || 12272 <= _Chr && _Chr <= 12283 || 12289 <= _Chr && _Chr <= 12351 || 12353 <= _Chr && _Chr <= 12438 || 12441 <= _Chr && _Chr <= 12543 || 12549 <= _Chr && _Chr <= 12591 || 12593 <= _Chr && _Chr <= 12686 || 12688 <= _Chr && _Chr <= 12771 || 12784 <= _Chr && _Chr <= 12830 || 12832 <= _Chr && _Chr <= 40956 || 40960 <= _Chr && _Chr <= 42124 || 42128 <= _Chr && _Chr <= 42182 || 42192 <= _Chr && _Chr <= 42539 || 42560 <= _Chr && _Chr <= 42743 || 42752 <= _Chr && _Chr <= 42943 || 42946 <= _Chr && _Chr <= 42954 || 42997 <= _Chr && _Chr <= 43052 || 43056 <= _Chr && _Chr <= 43065 || 43072 <= _Chr && _Chr <= 43127 || 43136 <= _Chr && _Chr <= 43205 || 43214 <= _Chr && _Chr <= 43225 || 43232 <= _Chr && _Chr <= 43347 || 43359 <= _Chr && _Chr <= 43388 || 43392 <= _Chr && _Chr <= 43469 || 43471 <= _Chr && _Chr <= 43481 || 43486 <= _Chr && _Chr <= 43518 || 43520 <= _Chr && _Chr <= 43574 || 43584 <= _Chr && _Chr <= 43597 || 43600 <= _Chr && _Chr <= 43609 || 43612 <= _Chr && _Chr <= 43714 || 43739 <= _Chr && _Chr <= 43766 || 43777 <= _Chr && _Chr <= 43782 || 43785 <= _Chr && _Chr <= 43790 || 43793 <= _Chr && _Chr <= 43798 || 43808 <= _Chr && _Chr <= 43814 || 43816 <= _Chr && _Chr <= 43822 || 43824 <= _Chr && _Chr <= 43883 || 43888 <= _Chr && _Chr <= 44013 || 44016 <= _Chr && _Chr <= 44025 || 44032 <= _Chr && _Chr <= 55203 || 55216 <= _Chr && _Chr <= 55238 || 55243 <= _Chr && _Chr <= 55291 || 63744 <= _Chr && _Chr <= 64109 || 64112 <= _Chr && _Chr <= 64217 || 64256 <= _Chr && _Chr <= 64262 || 64275 <= _Chr && _Chr <= 64279 || 64285 <= _Chr && _Chr <= 64310 || 64312 <= _Chr && _Chr <= 64316 || _Chr == 64318 || 64320 <= _Chr && _Chr <= 64321 || 64323 <= _Chr && _Chr <= 64324 || 64326 <= _Chr && _Chr <= 64449 || 64467 <= _Chr && _Chr <= 64831 || 64848 <= _Chr && _Chr <= 64911 || 64914 <= _Chr && _Chr <= 64967 || 65008 <= _Chr && _Chr <= 65021 || 65024 <= _Chr && _Chr <= 65049 || 65056 <= _Chr && _Chr <= 65106 || 65108 <= _Chr && _Chr <= 65126 || 65128 <= _Chr && _Chr <= 65131 || 65136 <= _Chr && _Chr <= 65140 || 65142 <= _Chr && _Chr <= 65276 || 65281 <= _Chr && _Chr <= 65470 || 65474 <= _Chr && _Chr <= 65479 || 65482 <= _Chr && _Chr <= 65487 || 65490 <= _Chr && _Chr <= 65495 || 65498 <= _Chr && _Chr <= 65500 || 65504 <= _Chr && _Chr <= 65510 || 65512 <= _Chr && _Chr <= 65518 || 65532 <= _Chr && _Chr <= 65533 || 65536 <= _Chr && _Chr <= 65547 || 65549 <= _Chr && _Chr <= 65574 || 65576 <= _Chr && _Chr <= 65594 || 65596 <= _Chr && _Chr <= 65597 || 65599 <= _Chr && _Chr <= 65613 || 65616 <= _Chr && _Chr <= 65629 || 65664 <= _Chr && _Chr <= 65786 || 65792 <= _Chr && _Chr <= 65794 || 65799 <= _Chr && _Chr <= 65843 || 65847 <= _Chr && _Chr <= 65934 || 65936 <= _Chr && _Chr <= 65948 || _Chr == 65952 || 66000 <= _Chr && _Chr <= 66045 || 66176 <= _Chr && _Chr <= 66204 || 66208 <= _Chr && _Chr <= 66256 || 66272 <= _Chr && _Chr <= 66299 || 66304 <= _Chr && _Chr <= 66339 || 66349 <= _Chr && _Chr <= 66378 || 66384 <= _Chr && _Chr <= 66426 || 66432 <= _Chr && _Chr <= 66461 || 66463 <= _Chr && _Chr <= 66499 || 66504 <= _Chr && _Chr <= 66517 || 66560 <= _Chr && _Chr <= 66717 || 66720 <= _Chr && _Chr <= 66729 || 66736 <= _Chr && _Chr <= 66771 || 66776 <= _Chr && _Chr <= 66811 || 66816 <= _Chr && _Chr <= 66855 || 66864 <= _Chr && _Chr <= 66915 || _Chr == 66927 || 67072 <= _Chr && _Chr <= 67382 || 67392 <= _Chr && _Chr <= 67413 || 67424 <= _Chr && _Chr <= 67431 || 67584 <= _Chr && _Chr <= 67589 || _Chr == 67592 || 67594 <= _Chr && _Chr <= 67637 || 67639 <= _Chr && _Chr <= 67640 || _Chr == 67644 || 67647 <= _Chr && _Chr <= 67669 || 67671 <= _Chr && _Chr <= 67742 || 67751 <= _Chr && _Chr <= 67759 || 67808 <= _Chr && _Chr <= 67826 || 67828 <= _Chr && _Chr <= 67829 || 67835 <= _Chr && _Chr <= 67867 || 67871 <= _Chr && _Chr <= 67897 || _Chr == 67903 || 67968 <= _Chr && _Chr <= 68023 || 68028 <= _Chr && _Chr <= 68047 || 68050 <= _Chr && _Chr <= 68099 || 68101 <= _Chr && _Chr <= 68102 || 68108 <= _Chr && _Chr <= 68115 || 68117 <= _Chr && _Chr <= 68119 || 68121 <= _Chr && _Chr <= 68149 || 68152 <= _Chr && _Chr <= 68154 || 68159 <= _Chr && _Chr <= 68168 || 68176 <= _Chr && _Chr <= 68184 || 68192 <= _Chr && _Chr <= 68255 || 68288 <= _Chr && _Chr <= 68326 || 68331 <= _Chr && _Chr <= 68342 || 68352 <= _Chr && _Chr <= 68405 || 68409 <= _Chr && _Chr <= 68437 || 68440 <= _Chr && _Chr <= 68466 || 68472 <= _Chr && _Chr <= 68497 || 68505 <= _Chr && _Chr <= 68508 || 68521 <= _Chr && _Chr <= 68527 || 68608 <= _Chr && _Chr <= 68680 || 68736 <= _Chr && _Chr <= 68786 || 68800 <= _Chr && _Chr <= 68850 || 68858 <= _Chr && _Chr <= 68903 || 68912 <= _Chr && _Chr <= 68921 || 69216 <= _Chr && _Chr <= 69246 || 69248 <= _Chr && _Chr <= 69289 || 69291 <= _Chr && _Chr <= 69293 || 69296 <= _Chr && _Chr <= 69297 || 69376 <= _Chr && _Chr <= 69415 || 69424 <= _Chr && _Chr <= 69465 || 69552 <= _Chr && _Chr <= 69579 || 69600 <= _Chr && _Chr <= 69622 || 69632 <= _Chr && _Chr <= 69709 || 69714 <= _Chr && _Chr <= 69743 || 69759 <= _Chr && _Chr <= 69820 || 69822 <= _Chr && _Chr <= 69825 || 69840 <= _Chr && _Chr <= 69864 || 69872 <= _Chr && _Chr <= 69881 || 69888 <= _Chr && _Chr <= 69940 || 69942 <= _Chr && _Chr <= 69959 || 69968 <= _Chr && _Chr <= 70006 || 70016 <= _Chr && _Chr <= 70111 || 70113 <= _Chr && _Chr <= 70132 || 70144 <= _Chr && _Chr <= 70161 || 70163 <= _Chr && _Chr <= 70206 || 70272 <= _Chr && _Chr <= 70278 || _Chr == 70280 || 70282 <= _Chr && _Chr <= 70285 || 70287 <= _Chr && _Chr <= 70301 || 70303 <= _Chr && _Chr <= 70313 || 70320 <= _Chr && _Chr <= 70378 || 70384 <= _Chr && _Chr <= 70393 || 70400 <= _Chr && _Chr <= 70403 || 70405 <= _Chr && _Chr <= 70412 || 70415 <= _Chr && _Chr <= 70416 || 70419 <= _Chr && _Chr <= 70440 || 70442 <= _Chr && _Chr <= 70448 || 70450 <= _Chr && _Chr <= 70451 || 70453 <= _Chr && _Chr <= 70457 || 70459 <= _Chr && _Chr <= 70468 || 70471 <= _Chr && _Chr <= 70472 || 70475 <= _Chr && _Chr <= 70477 || _Chr == 70480 || _Chr == 70487 || 70493 <= _Chr && _Chr <= 70499 || 70502 <= _Chr && _Chr <= 70508 || 70512 <= _Chr && _Chr <= 70516 || 70656 <= _Chr && _Chr <= 70747 || 70749 <= _Chr && _Chr <= 70753 || 70784 <= _Chr && _Chr <= 70855 || 70864 <= _Chr && _Chr <= 70873 || 71040 <= _Chr && _Chr <= 71093 || 71096 <= _Chr && _Chr <= 71133 || 71168 <= _Chr && _Chr <= 71236 || 71248 <= _Chr && _Chr <= 71257 || 71264 <= _Chr && _Chr <= 71276 || 71296 <= _Chr && _Chr <= 71352 || 71360 <= _Chr && _Chr <= 71369 || 71424 <= _Chr && _Chr <= 71450 || 71453 <= _Chr && _Chr <= 71467 || 71472 <= _Chr && _Chr <= 71487 || 71680 <= _Chr && _Chr <= 71739 || 71840 <= _Chr && _Chr <= 71922 || 71935 <= _Chr && _Chr <= 71942 || _Chr == 71945 || 71948 <= _Chr && _Chr <= 71955 || 71957 <= _Chr && _Chr <= 71958 || 71960 <= _Chr && _Chr <= 71989 || 71991 <= _Chr && _Chr <= 71992 || 71995 <= _Chr && _Chr <= 72006 || 72016 <= _Chr && _Chr <= 72025 || 72096 <= _Chr && _Chr <= 72103 || 72106 <= _Chr && _Chr <= 72151 || 72154 <= _Chr && _Chr <= 72164 || 72192 <= _Chr && _Chr <= 72263 || 72272 <= _Chr && _Chr <= 72354 || 72384 <= _Chr && _Chr <= 72440 || 72704 <= _Chr && _Chr <= 72712 || 72714 <= _Chr && _Chr <= 72758 || 72760 <= _Chr && _Chr <= 72773 || 72784 <= _Chr && _Chr <= 72812 || 72816 <= _Chr && _Chr <= 72847 || 72850 <= _Chr && _Chr <= 72871 || 72873 <= _Chr && _Chr <= 72886 || 72960 <= _Chr && _Chr <= 72966 || 72968 <= _Chr && _Chr <= 72969 || 72971 <= _Chr && _Chr <= 73014 || _Chr == 73018 || 73020 <= _Chr && _Chr <= 73021 || 73023 <= _Chr && _Chr <= 73031 || 73040 <= _Chr && _Chr <= 73049 || 73056 <= _Chr && _Chr <= 73061 || 73063 <= _Chr && _Chr <= 73064 || 73066 <= _Chr && _Chr <= 73102 || 73104 <= _Chr && _Chr <= 73105 || 73107 <= _Chr && _Chr <= 73112 || 73120 <= _Chr && _Chr <= 73129 || 73440 <= _Chr && _Chr <= 73464 || _Chr == 73648 || 73664 <= _Chr && _Chr <= 73713 || 73727 <= _Chr && _Chr <= 74649 || 74752 <= _Chr && _Chr <= 74862 || 74864 <= _Chr && _Chr <= 74868 || 74880 <= _Chr && _Chr <= 75075 || 77824 <= _Chr && _Chr <= 78894 || 82944 <= _Chr && _Chr <= 83526 || 92160 <= _Chr && _Chr <= 92728 || 92736 <= _Chr && _Chr <= 92766 || 92768 <= _Chr && _Chr <= 92777 || 92782 <= _Chr && _Chr <= 92783 || 92880 <= _Chr && _Chr <= 92909 || 92912 <= _Chr && _Chr <= 92917 || 92928 <= _Chr && _Chr <= 92997 || 93008 <= _Chr && _Chr <= 93017 || 93019 <= _Chr && _Chr <= 93025 || 93027 <= _Chr && _Chr <= 93047 || 93053 <= _Chr && _Chr <= 93071 || 93760 <= _Chr && _Chr <= 93850 || 93952 <= _Chr && _Chr <= 94026 || 94031 <= _Chr && _Chr <= 94087 || 94095 <= _Chr && _Chr <= 94111 || 94176 <= _Chr && _Chr <= 94180 || 94192 <= _Chr && _Chr <= 94193 || 94208 <= _Chr && _Chr <= 100343 || 100352 <= _Chr && _Chr <= 101589 || 101632 <= _Chr && _Chr <= 101640 || 110592 <= _Chr && _Chr <= 110878 || 110928 <= _Chr && _Chr <= 110930 || 110948 <= _Chr && _Chr <= 110951 || 110960 <= _Chr && _Chr <= 111355 || 113664 <= _Chr && _Chr <= 113770 || 113776 <= _Chr && _Chr <= 113788 || 113792 <= _Chr && _Chr <= 113800 || 113808 <= _Chr && _Chr <= 113817 || 113820 <= _Chr && _Chr <= 113823 || 118784 <= _Chr && _Chr <= 119029 || 119040 <= _Chr && _Chr <= 119078 || 119081 <= _Chr && _Chr <= 119154 || 119163 <= _Chr && _Chr <= 119272 || 119296 <= _Chr && _Chr <= 119365 || 119520 <= _Chr && _Chr <= 119539 || 119552 <= _Chr && _Chr <= 119638 || 119648 <= _Chr && _Chr <= 119672 || 119808 <= _Chr && _Chr <= 119892 || 119894 <= _Chr && _Chr <= 119964 || 119966 <= _Chr && _Chr <= 119967 || _Chr == 119970 || 119973 <= _Chr && _Chr <= 119974 || 119977 <= _Chr && _Chr <= 119980 || 119982 <= _Chr && _Chr <= 119993 || _Chr == 119995 || 119997 <= _Chr && _Chr <= 120003 || 120005 <= _Chr && _Chr <= 120069 || 120071 <= _Chr && _Chr <= 120074 || 120077 <= _Chr && _Chr <= 120084 || 120086 <= _Chr && _Chr <= 120092 || 120094 <= _Chr && _Chr <= 120121 || 120123 <= _Chr && _Chr <= 120126 || 120128 <= _Chr && _Chr <= 120132 || _Chr == 120134 || 120138 <= _Chr && _Chr <= 120144 || 120146 <= _Chr && _Chr <= 120485 || 120488 <= _Chr && _Chr <= 120779 || 120782 <= _Chr && _Chr <= 121483 || 121499 <= _Chr && _Chr <= 121503 || 121505 <= _Chr && _Chr <= 121519 || 122880 <= _Chr && _Chr <= 122886 || 122888 <= _Chr && _Chr <= 122904 || 122907 <= _Chr && _Chr <= 122913 || 122915 <= _Chr && _Chr <= 122916 || 122918 <= _Chr && _Chr <= 122922 || 123136 <= _Chr && _Chr <= 123180 || 123184 <= _Chr && _Chr <= 123197 || 123200 <= _Chr && _Chr <= 123209 || 123214 <= _Chr && _Chr <= 123215 || 123584 <= _Chr && _Chr <= 123641 || _Chr == 123647 || 124928 <= _Chr && _Chr <= 125124 || 125127 <= _Chr && _Chr <= 125142 || 125184 <= _Chr && _Chr <= 125259 || 125264 <= _Chr && _Chr <= 125273 || 125278 <= _Chr && _Chr <= 125279 || 126065 <= _Chr && _Chr <= 126132 || 126209 <= _Chr && _Chr <= 126269 || 126464 <= _Chr && _Chr <= 126467 || 126469 <= _Chr && _Chr <= 126495 || 126497 <= _Chr && _Chr <= 126498 || _Chr == 126500 || _Chr == 126503 || 126505 <= _Chr && _Chr <= 126514 || 126516 <= _Chr && _Chr <= 126519 || _Chr == 126521 || _Chr == 126523 || _Chr == 126530 || _Chr == 126535 || _Chr == 126537 || _Chr == 126539 || 126541 <= _Chr && _Chr <= 126543 || 126545 <= _Chr && _Chr <= 126546 || _Chr == 126548 || _Chr == 126551 || _Chr == 126553 || _Chr == 126555 || _Chr == 126557 || _Chr == 126559 || 126561 <= _Chr && _Chr <= 126562 || _Chr == 126564 || 126567 <= _Chr && _Chr <= 126570 || 126572 <= _Chr && _Chr <= 126578 || 126580 <= _Chr && _Chr <= 126583 || 126585 <= _Chr && _Chr <= 126588 || _Chr == 126590 || 126592 <= _Chr && _Chr <= 126601 || 126603 <= _Chr && _Chr <= 126619 || 126625 <= _Chr && _Chr <= 126627 || 126629 <= _Chr && _Chr <= 126633 || 126635 <= _Chr && _Chr <= 126651 || 126704 <= _Chr && _Chr <= 126705 || 126976 <= _Chr && _Chr <= 127019 || 127024 <= _Chr && _Chr <= 127123 || 127136 <= _Chr && _Chr <= 127150 || 127153 <= _Chr && _Chr <= 127167 || 127169 <= _Chr && _Chr <= 127183 || 127185 <= _Chr && _Chr <= 127221 || 127232 <= _Chr && _Chr <= 127405 || 127462 <= _Chr && _Chr <= 127490 || 127504 <= _Chr && _Chr <= 127547 || 127552 <= _Chr && _Chr <= 127560 || 127568 <= _Chr && _Chr <= 127569 || 127584 <= _Chr && _Chr <= 127589 || 127744 <= _Chr && _Chr <= 128727 || 128736 <= _Chr && _Chr <= 128748 || 128752 <= _Chr && _Chr <= 128764 || 128768 <= _Chr && _Chr <= 128883 || 128896 <= _Chr && _Chr <= 128984 || 128992 <= _Chr && _Chr <= 129003 || 129024 <= _Chr && _Chr <= 129035 || 129040 <= _Chr && _Chr <= 129095 || 129104 <= _Chr && _Chr <= 129113 || 129120 <= _Chr && _Chr <= 129159 || 129168 <= _Chr && _Chr <= 129197 || 129200 <= _Chr && _Chr <= 129201 || 129280 <= _Chr && _Chr <= 129400 || 129402 <= _Chr && _Chr <= 129483 || 129485 <= _Chr && _Chr <= 129619 || 129632 <= _Chr && _Chr <= 129645 || 129648 <= _Chr && _Chr <= 129652 || 129656 <= _Chr && _Chr <= 129658 || 129664 <= _Chr && _Chr <= 129670 || 129680 <= _Chr && _Chr <= 129704 || 129712 <= _Chr && _Chr <= 129718 || 129728 <= _Chr && _Chr <= 129730 || 129744 <= _Chr && _Chr <= 129750 || 129792 <= _Chr && _Chr <= 129938 || 129940 <= _Chr && _Chr <= 129994 || 130032 <= _Chr && _Chr <= 130041 || 131072 <= _Chr && _Chr <= 173789 || 173824 <= _Chr && _Chr <= 177972 || 177984 <= _Chr && _Chr <= 178205 || 178208 <= _Chr && _Chr <= 183969 || 183984 <= _Chr && _Chr <= 191456 || 194560 <= _Chr && _Chr <= 195101 || 196608 <= _Chr && _Chr <= 201546 || 917760 <= _Chr && _Chr <= 917999 || false) { return true; }
		return false;
	}
	bool pystr::check_space() {
		pystr _Chr = (*this)[0];
		if (9 <= _Chr && _Chr <= 13 || 28 <= _Chr && _Chr <= 32 || _Chr == 133 || _Chr == 160 || _Chr == 5760 || 8192 <= _Chr && _Chr <= 8202 || 8232 <= _Chr && _Chr <= 8233 || _Chr == 8239 || _Chr == 8287 || _Chr == 12288 || false) { return true; }
		return false;
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
	pystr::pystr(const int _UniData) {
		this->operator=(chr(_UniData));
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


	pystr pystr::capitalize() {
		return (*this)[0].upper() + (*this)(1,"").lower();
	}
	pystr pystr::casefold() {
		pystr _rStr;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			_rStr += (*this)[_Idx].casefold_result();
		}
		return _rStr;
	}
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
			if ((*this)[_Idx].check_alnum() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isalpha() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_alpha() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isAscii() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_Ascii() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isdigit() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_digit() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isdecimal() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_decimal() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::islower() {
		return *this == this->lower();
	}
	bool pystr::isnumeric() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_numeric() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isprintable() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_printable() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::isspace() {
		if (this->size == 0) return false;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx].check_space() == true) continue;
			return false;
		}
		return true;
	}
	bool pystr::istitle() {
		return *this == this->title();
	}
	bool pystr::isupper() {
		return *this == this->upper();
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
	pystr pystr::join(py::pylist<pystr> _List) {
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
	pystr pystr::join(py::pylist<char> _List) {
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
	pystr pystr::lower() {
		pystr _rStr;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			_rStr += (*this)[_Idx].lower_result();
		}
		return _rStr;
	}
	pystr pystr::lstrip() {
		pystr _Cmp = " \t"p;
		int _Idx = 0, _Ssize = this->size;
		while (_Idx < _Ssize && _Cmp.find(this->data[_Idx]) != -1) _Idx++;
		if (_Idx == _Ssize) return "";
		return this->operator()(_Idx, "");
	}
	//std::map<int, int> pystr::maketrance(const pystr& _Tstr, const pystr& _VStr, const pystr& _RStr);
	/**/
	py::pylist<pystr> pystr::partition(const pystr& _Str) {
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
		py::pylist<int> _kmp_pi(_Ssize, 0); //get pi array
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
	py::pylist<pystr> pystr::rpartition(const pystr& _Str) {
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
	py::pylist<pystr> pystr::split(const pystr& _Tstr) {
		py::pylist<pystr> _rList;
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
	py::pylist<pystr> pystr::splitlines(const bool _keepLineBreak) {
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
	pystr pystr::swapcase() {
		pystr _rStr;
		pystr _Data;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			if ((*this)[_Idx] != (_Data = (*this)[_Idx].lower_result())) {
				_rStr += _Data;
			}
			else _rStr += (_Data = (*this)[_Idx].upper_result());
		}
		return _rStr;
	}
	pystr pystr::title() {
		pystr _rStr, _IdxData;
		pystr _Cmp = " \n\t\0";
		bool _isEnd = true;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			_IdxData = (*this)[_Idx];
			if (_Cmp.find(_IdxData) != -1) {
				_isEnd = true;
			}
			else if (_isEnd == true) {
				_IdxData = _IdxData.upper_result();
				_isEnd = false;
			}
			else {
				_IdxData = _IdxData.lower_result();
			}
			_rStr += _IdxData;
		}
		return _rStr;
	}
	//pystr pystr::translate(std::map<pystr,pystr> _Dict);
	//pystr pystr::translate(std::map<pystr,p> _Dict);
	/**/
	pystr pystr::upper() {
		pystr _rStr;
		int _Ssize = this->size;
		for (int _Idx = 0; _Idx < _Ssize; _Idx++) {
			_rStr += (*this)[_Idx].upper_result();
		}
		return _rStr;
	}
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

#pragma warning(push)
#pragma warning(disable: 4244)
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
	pystr c2py(const pystr& _Str) {
		return _Str;
	}
}
#pragma warning(pop)
