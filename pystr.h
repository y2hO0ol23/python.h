#pragma once
#include <cstdlib> 
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

namespace py {
	class pystr;
	pystr py_str(const pystr& str);
#define p py_str("") %

	class pystr {
		friend std::ostream& operator<<(std::ostream& ret, const pystr& str);
		friend std::istream& operator>>(std::istream& ret, pystr& str);
		friend pystr operator+(const pystr& str1, const pystr& str2);
		friend pystr operator%(const pystr& str1, const pystr& str2);
	private:
		int size = 0;
		int volume = 1;
		char* data = (char*)calloc(1, sizeof(char));

		void extend_volume();
		void set_volume(const int value);

		void set_idx(int* idx);
		void check_idx_out_of_range(const int idx);

		bool is_over(int idx);
	public:
		pystr();		pystr(const char* str);		pystr(const char str);		pystr(const pystr& str);
		~pystr();
		char* begin();
		char* end();
		char* c_str();

		int len();
		int count(const pystr& str);
		int find(const pystr& str);
		int index(pystr str);
		pystr join(pystr str);
		pystr join(std::vector<pystr> list);		pystr join(std::vector<char> list);
		pystr upper();
		pystr lower();
		pystr strip();					pystr lstrip(); 				pystr rstrip();
		pystr replace(const pystr& target, const pystr& value);
		std::vector<pystr> split(pystr target);		std::vector<pystr> split();

		char operator[](int idx);
		pystr operator()(int idx1, int idx2, const int jump);				pystr operator()(const char* idx1, int idx2, const int jump);		pystr operator()(int idx1, const char* idx2, const int jump);		pystr operator()(const char* idx1, const char* idx2, const int jump);
		pystr operator()(int idx1, int idx2);						pystr operator()(const char* idx1, int idx2);				pystr operator()(int idx1, const char* idx2);				pystr operator()(const char* idx1, const char* idx2);
		pystr& operator=(const pystr& str);						pystr& operator=(const char* str);					pystr& operator=(const char str);
		pystr& operator+=(const pystr& str);
		pystr operator*(const int value);
		bool operator==(const pystr& str);
		bool operator!=(const pystr& str);
		bool operator<(const pystr& str);
		bool operator<=(const pystr& str);
		bool operator>(const pystr& str);
		bool operator>=(const pystr& str);
		pystr operator%(const pystr& str);
	};
	std::ostream& operator<<(std::ostream& ret, const pystr& str) {
		ret << str.data;
		return ret;
	}
	std::istream& operator>>(std::istream& ret, pystr& str) {
		char data;
		pystr list = p" \n" + (char)0;
		str = "";
		while (-1 != list.find(ret.rdbuf()->sgetc())) ret.rdbuf()->snextc();
		while (-1 == list.find(data = ret.rdbuf()->sgetc())) {
			str += data;
			ret.rdbuf()->snextc();
		}
		return ret;
	}
	pystr operator+(const pystr& str1, const pystr& str2) {
		pystr ret = str1;
		ret += str2;
		return ret;
	}
	pystr operator%(const pystr& str1, const pystr& str2) {
		return operator+(str1, str2);
	}

	void pystr::extend_volume() {
		this->set_volume(this->volume * 2);
	}
	void pystr::set_volume(const int value) {
		while (1) {
			char* temp = (char*)realloc(this->data, sizeof(char) * value);
			if (temp != NULL) {
				this->data = temp;
				this->volume = value;
				break;
			}
		}
	}

	void pystr::set_idx(int* idx) {
		if (*idx < 0) *idx += this->size;
	}
	void pystr::check_idx_out_of_range(const int idx) {
		if (idx < 0 || this->size <= idx) throw "string index out of range";
	}

	bool pystr::is_over(int idx) {
		return this->volume <= idx + 1;
	}

	pystr::pystr() {
		this->operator=("");
	}
	pystr::pystr(const char* str) {
		this->operator=(str);
	}
	pystr::pystr(const char str) {
		this->operator=(str);
	}
	pystr::pystr(const pystr& str) {
		//same as pystr::operator=(str)
		int loop = str.size;
		for (int i = 0; i < loop; i++) {
			if (this->volume <= i) this->extend_volume();
			this->data[i] = str.data[i];
		}
		if (this->volume <= loop) this->extend_volume();
		this->data[loop] = '\0';
		this->size = loop;
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

	int pystr::count(const pystr& str) {
		pystr temp = str;

		int cnt = 0;
		pystr cmp = *this;
		int str_size = temp.size;
		while (1) {
			int res = cmp.find(temp);
			if (res == -1) return cnt;
			cnt++;
			if (res + str_size >= cmp.size) return cnt;
			cmp = cmp(res + str_size, "");
		}
	}
	int pystr::find(const pystr& str) {
		pystr temp = str;
		//kmp algorithm
		int str_size = temp.size, j = 0;
		std::vector<int> pi(str_size, 0); //get pi array
		for (int i = 0; i < str_size; i++) {
			while (j > 0 && temp[i] != temp[j]) j = pi[j - 1];
			if (temp[i] == temp[j] && i != j) pi[i] = ++j;
		}
		//find string
		pystr target_str = *this;
		int target_str_size = target_str.size;
		j = 0;
		for (int i = 0; i < target_str_size; i++) {
			while (j > 0 && target_str[i] != temp[j]) j = pi[j - 1];
			if (target_str[i] == temp[j]) {
				if (j == str_size - 1) return (i - str_size + 1);
				j++;
			}
		}
		return -1;
	}
	int pystr::index(pystr str) {
		int res = find(str);
		if (res == -1) throw "substring not found";
		return res;
	}

	pystr pystr::join(pystr str) {
		int loop = str.size;
		pystr ret = str[0];
		if (loop == 0) return ret;
		for (int i = 1; i < loop; i++) {
			ret += this->data;
			ret += str[i];
		}
		return ret;
	}
	pystr pystr::join(std::vector<pystr> list) {
		int loop = list.size();
		pystr ret;
		if (loop == 0) return ret;
		ret += list[0];
		for (int i = 1; i < loop; i++) {
			ret += this->data;
			ret += list[i];
		}
		return ret;
	}
	pystr pystr::join(std::vector<char> list) {
		int loop = list.size();
		pystr ret;
		if (loop == 0) return ret;
		ret = list[0];
		for (int i = 1; i < loop; i++) {
			ret += this->data;
			ret += list[i];
		}
		return ret;
	}

	pystr pystr::lower() {
		pystr ret = *this;
		int loop = ret.size;
		for (int i = 0; i < loop; i++) {
			if ('A' <= ret.data[i] && ret.data[i] <= 'Z') {
				ret.data[i] += 'a' - 'A';
			}
		}
		return ret;
	}
	pystr pystr::upper() {
		pystr ret = *this;
		int loop = ret.size;
		for (int i = 0; i < loop; i++) {
			if ('a' <= ret.data[i] && ret.data[i] <= 'z') {
				ret.data[i] += 'A' - 'a';
			}
		}
		return ret;
	}

	pystr pystr::strip() {
		pystr ret = *this;
		return ret.lstrip().rstrip();
	}
	pystr pystr::lstrip() {
		pystr ret = *this;
		while (ret.size > 1 && ret[0] == ' ')
			ret = ret(1, "");
		if (ret.size == 1 && ret[0] == ' ') ret = "";
		return ret;
	}
	pystr pystr::rstrip() {
		pystr ret = *this;
		while (ret.size > 0 && ret[-1] == ' ')
			ret = ret("", -1);
		return ret;
	}

	pystr pystr::replace(const pystr& target, const pystr& value) {
		pystr ret;
		pystr str = *this;
		int target_size = target.size;
		while (1) {
			int res = str.find(target);
			if (res == -1) return ret + str;

			ret += str("", res) + value;
			str = str(res + target_size, "");
		}
	}

	std::vector<pystr> pystr::split(const pystr target) {
		std::vector<pystr> ret;
		pystr str = *this;
		int target_size = target.size;
		if (target_size == 0) throw "empty separator";
		while (1) {
			int res = str.find(target);
			if (res == -1) {
				ret.push_back(str);
				return ret;
			}
			ret.push_back(str("", res));
			str = str(res + target_size, "");
		}
	}
	std::vector<pystr> pystr::split() {
		return this->split(' ');
	}

	char pystr::operator[](int idx) {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx);
		char* ret = &(this->data[idx]);
		return ret[0];
	};
	pystr pystr::operator()(int idx1, int idx2, const int jump) {
		pystr ret;
		pystr temp = *this;
		this->set_idx(&idx1);
		this->set_idx(&idx2);
		this->check_idx_out_of_range(idx1);
		this->check_idx_out_of_range(idx2 - ((idx2 > 0) ? 1 : 0));
		for (int i = idx1; i < idx2; i += jump) ret += temp[i];
		return ret;
	};
	pystr pystr::operator()(const char* idx1, int idx2, const int jump) {
		return this->operator()(0, idx2, jump);
	}
	pystr pystr::operator()(int idx1, const char* idx2, const int jump) {
		return this->operator()(idx1, this->size, jump);
	}
	pystr pystr::operator()(const char* idx1, const char* idx2, const int jump) {
		return this->operator()(0, this->size, jump);
	}
	pystr pystr::operator()(int idx1, int idx2) {
		return this->operator()(idx1, idx2, 1);
	}
	pystr pystr::operator()(const char* idx1, int idx2) {
		return this->operator()(0, idx2, 1);
	}
	pystr pystr::operator()(int idx1, const char* idx2) {
		return this->operator()(idx1, this->size, 1);
	}
	pystr pystr::operator()(const char* idx1, const char* idx2) {
		return this->operator()(0, this->size, 1);
	}

	pystr& pystr::operator=(const pystr& str) {
		int loop = str.size;
		for (int i = 0; i < loop; i++) {
			if (this->is_over(i)) this->extend_volume();
			this->data[i] = str.data[i];
		}
		if (this->is_over(loop)) this->extend_volume();
		this->data[loop] = '\0';
		this->size = loop;
		return *this;
	}
	pystr& pystr::operator=(const char* str) {
		int loop = strlen(str);
		for (int i = 0; i < loop; i++) {
			if (this->is_over(i)) this->extend_volume();
			this->data[i] = str[i];
		}
		if (this->is_over(loop)) this->extend_volume();
		this->data[loop] = '\0';
		this->size = loop;
		return *this;
	}
	pystr& pystr::operator=(const char str) {
		int point = this->size;
		if (this->is_over(point)) this->extend_volume();
		this->data[point] = str;
		this->data[point + 1] = '\0';
		this->size = point + 1;
		return *this;
	}

	pystr& pystr::operator+=(const pystr& str) {
		int loop = str.size;
		int point = this->size;
		for (int i = 0; i < loop; i++) {
			if (this->is_over(point)) this->extend_volume();
			this->data[point] = str.data[i];
			point++;
		}
		if (this->is_over(point)) this->extend_volume();
		this->data[point] = '\0';
		this->size = point;
		return *this;
	}
	pystr pystr::operator*(int value) {
		if (value <= 0) return py_str("");
		pystr ret = *this;
		int dcnt = 0;
		while (value > 1) {
			ret += ret;
			if (value % 2) dcnt++;
			value /= 2;
		}
		for (int i = 0; i < dcnt; i++) ret += *this;
		return ret;
	}
	bool pystr::operator==(const pystr& str) {
		return !std::strcmp(this->data, str.data);
	}
	bool pystr::operator!=(const pystr& str) {
		return std::strcmp(this->data, str.data);
	}
	bool pystr::operator<(const pystr& str) {
		return std::strcmp(this->data, str.data) < 0;
	}
	bool pystr::operator<=(const pystr& str) {
		return std::strcmp(this->data, str.data) <= 0;
	}
	bool pystr::operator>(const pystr& str) {
		return std::strcmp(this->data, str.data) > 0;
	}
	bool pystr::operator>=(const pystr& str) {
		return std::strcmp(this->data, str.data) >= 0;
	}
	pystr pystr::operator%(const pystr& str) {
		return operator+(*this, str);
	}

	pystr py_str(const pystr& str) {
		return str;
	}

	std::ostream& operator<<(std::ostream& ret, const std::vector<pystr>& data) {
		pystr res = '{';
		int loop = data.size();
		for (int i = 0; i < loop - 1; i++) {
			res += "\"" + data[i] + "\", ";
		}
		res += "\"" + data[loop - 1] + "\"}";
		ret << res;
		return ret;
	}
}
