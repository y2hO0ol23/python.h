#pragma once
#ifndef _PYTHONLIST_
#define _PYTHONLIST_
#include <iostream>
#include <algorithm>
#include "pystr.h"

namespace py {
	template <class T> class pylist;
	template <class T> class node;

	template <class T>
	class node {
		friend class pylist<T>;
	private:
		T data;
		node<T>* next; // 다음
		node<T>* prev; // 이전
	};

	template <class T>
	class pylist {
		template <class opT> friend std::ostream& operator<<(std::ostream& _os, const pylist<opT>& _List);
		template <class opT> friend pylist<opT> operator+(const pylist<opT>& _Left, const pylist<opT>& _Right);
	private:
		node<T>* head = nullptr; // 시작
		node<T>* tail = nullptr; // 끝
		int size = 0;

		void set_idx(int* _Idx);
		void check_idx_out_of_range(const int _Idx);

		node<T>* make_new_node(const T& _Val);
		node<T>* found_node(int _Idx);
		void remove_node(node<T>* _Ptr);

		T* data;
		int volume = 0;
		bool flag = false;
		void set_data();
	public:
		pylist();
		pylist(int _Size, T _Val);
		pylist(std::initializer_list<T> _List);
		pylist(const pylist<T>& _List);
		~pylist();
		int len();

		T* begin();
		T* end();

		pylist<T>& append(const T& _Val);
		T pop(int _Idx = -1);
		pylist<T>& del(int _Idx);
		pylist<T>& del(int _Begin, int _End, int _Jmp = 1);
		pylist<T>& del(const char* _Begin, int _End, int _Jmp = 1);
		pylist<T>& del(int _Begin, const char* _End, int _Jmp = 1);
		pylist<T>& del(const char* _Begin, const char* _End, int _Jmp = 1);
		pylist<T>& sort();
		pylist<T>& reverse();
		int index(T _Val);
		pylist<T>& insert(int _Idx, T _Val);
		pylist<T>& remove(T _Val);
		int count(T _Val);
		pylist<T>& extend(pylist<T> _List);
		pylist<T> copy();
		pylist<T>& clear();

		T* operator[](int _Idx);
		pylist<T>& operator=(std::initializer_list<T> _Right);
		pylist<T>& operator=(const pylist<T>& _Right);
		pylist<T>& operator+=(const pylist<T>& _Right);
		pylist<T> operator*(int _Val);
		pylist<T> operator()(int _Begin, int _End, const int _Jmp = 1);
		pylist<T> operator()(const char* _Begin, int _End, const int _Jmp = 1);
		pylist<T> operator()(int _Begin, const char* _End, const int _Jmp = 1);
		pylist<T> operator()(const char* _Begin, const char* _End, const int _Jmp = 1);
	};
	template <class opT> std::ostream& operator<<(std::ostream& _os, const pylist<opT>& _List) {
		_os << "{";
		pylist<opT> _rList = _List;
		int _Lsize = _rList.len();
		for (int _Idx = 0; _Idx < _Lsize - 1; _Idx++) {
			_os << *_rList[_Idx] << ", ";
		}
		if (_Lsize) _os << *_rList[_Lsize - 1];
		_os << "}";
		return _os;
	}
	template <class opT> pylist<opT> operator+(const pylist<opT>& _Left, const pylist<opT>& _Right) {
		pylist<opT> _rList = _Left;
		return _rList += _Right;
	}

	template <class T> void pylist<T>::set_idx(int* _Idx) {
		if (*_Idx < 0) *_Idx += this->size;
	}
	template <class T> void pylist<T>::check_idx_out_of_range(const int _Idx) {
		if (_Idx < 0 || this->size <= _Idx) throw py::c2py("IndexError: list index out of range");
	}

	template <class T> node<T>* pylist<T>::make_new_node(const T& _Val) {
		node<T>* _New_Node = (node<T>*)calloc(1, sizeof(node<T>));
		_New_Node->data = _Val;
		_New_Node->next = nullptr;
		_New_Node->prev = nullptr;
		this->size++;
		this->flag = true;
		return _New_Node;
	}
	template <class T> node<T>* pylist<T>::found_node(int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);

		node<T>* _rNode;
		if (_Idx < (this->size / 2)) {
			_rNode = this->head;
			int _Idx_Cnt = 0;
			while (_Idx_Cnt != _Idx) {
				_rNode = _rNode->next;
				_Idx_Cnt++;
			}
		}
		else {
			_rNode = this->tail;
			int _Idx_Cnt = this->size - 1;
			while (_Idx_Cnt != _Idx) {
				_rNode = _rNode->prev;
				_Idx_Cnt--;
			}
		}
		return _rNode;
	}

	template <class T> void pylist<T>::remove_node(node<T>* _Node_Ptr) {
		if (_Node_Ptr->prev == nullptr)	this->head = _Node_Ptr->next;
		else								_Node_Ptr->prev->next = _Node_Ptr->next;
		if (_Node_Ptr->next == nullptr)	this->tail = _Node_Ptr->prev;
		else								_Node_Ptr->next->prev = _Node_Ptr->prev;
		
		free(_Node_Ptr);
		this->size--;
		this->flag = true;
	}

	template <class T> void pylist<T>::set_data() {
		int _Size = this->size;
		if (this->volume == 0) {
			this->data = (T*)calloc(_Size, sizeof(T) * _Size);
			this->volume = _Size;
		}
		else {
			while (this->volume < _Size) this->volume *= 2;
			while (1) {
				T* _Temp = (T*)realloc(this->data, sizeof(T) * this->volume);
				if (_Temp != NULL) {
					this->data = _Temp;
					break;
				}
			}
		}

		node<T>* _Node = this->head;
		int _Idx = 0;
		while(_Node != nullptr) {
			this->data[_Idx] = _Node->data;
			_Node = _Node->next;
			_Idx++;
		}
		this->flag = false;
	}

	template <class T> pylist<T>::pylist() {}
	template <class T> pylist<T>::pylist(int _Size, T _Val) {
		if (_Size < 0) return;
		while (_Size--) {
			this->append(_Val);
		}
	}
	template <class T> pylist<T>::pylist(std::initializer_list<T> _List) {
		*this = _List;
	}
	template <class T> pylist<T>::pylist(const pylist<T>& _List) {
		*this = _List;
	}

	template <class T> pylist<T>::~pylist() {
		this->clear();
	}
	template <class T> int pylist<T>::len() {
		if (this->flag) this->set_data();
		return this->size;
	}

	template <class T> T* pylist<T>::begin() {
		if (this->flag) this->set_data();
		return &this->data[0];
	}
	template <class T> T* pylist<T>::end() {
		if (this->flag) this->set_data();
		return &this->data[this->size];
	}

	template <class T> pylist<T>& pylist<T>::append(const T& _Val) {
		node<T>* _New_Node = this->make_new_node(_Val);
		_New_Node->prev = this->tail;
		if (this->tail != nullptr) this->tail->next = _New_Node;
		this->tail = _New_Node;
		if (this->head == nullptr) this->head = _New_Node;
		return *this;
	}
	template <class T> T pylist<T>::pop(int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);

		node<T>* _rData_Node = this->found_node(_Idx);
		T _rData = _rData_Node->data;
		this->remove_node(_rData_Node);

		return _rData;
	}
	template <class T> pylist<T>& pylist<T>::del(int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);

		return *this = this->operator()("", _Idx) + this->operator()(_Idx + 1, "");
	}
	template <class T> pylist<T>& pylist<T>::del(int _Begin, int _End, int _Jmp) {
		this->set_idx(&_Begin);
		this->set_idx(&_End);
		this->check_idx_out_of_range(_Begin);
		this->check_idx_out_of_range(_End - ((_End > 0) ? 1 : 0));

		int _Cnt = 0;
		node<T>* _Node = this->found_node(_Begin);
		int Idx = _Begin; _Jmp--;
		if (!(Idx < _End)) return *this;
		while (1) {
			node<T>* _Next_Node = _Node->next;
			this->remove_node(_Node); _End--;
			_Node = _Next_Node;
			Idx += _Jmp;
			if (!(Idx < _End)) return *this;
			if (this->size - Idx > _Jmp) {
				int _Jmp_Cnt = _Jmp;
				while (_Jmp_Cnt--) _Node = _Node->next;
			}
			else _Node = this->found_node(Idx);
		}
	}
	template <class T> pylist<T>& pylist<T>::del(const char* _Begin, int _End, int _Jmp) {
		return this->del(0, _End, _Jmp);
	}
	template <class T> pylist<T>& pylist<T>::del(int _Begin, const char* _End, int _Jmp) {
		return this->del(_Begin, this->size, _Jmp);
	}
	template <class T> pylist<T>& pylist<T>::del(const char* _Begin, const char* _End, int _Jmp) {
		return this->del(0, this->size, _Jmp);
	}
	template <class T> pylist<T>& pylist<T>::sort() {
		int _Size = this->size;
		T* _SortList = (T*)calloc(_Size, sizeof(T) * _Size);
		for (int _Idx = 0; _Idx < _Size; _Idx++) {
			_SortList[_Idx] = this->pop(0);
		}
		std::sort(_SortList, _SortList + _Size);
		for (int _Idx = 0; _Idx < _Size; _Idx++) {
			this->append(_SortList[_Idx]);
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::reverse() {
		pylist<T> _rList;
		while (this->size) {
			_rList.append(this->pop());
		}
		return *this = _rList;
	}
	template <class T> int pylist<T>::index(T _Val) {
		int _Idx = 0;
		node<T>* _Node = this->head;
		while (_Node != nullptr) {
			if (_Node->data == _Val) return _Idx;
			_Node = _Node->next;
			_Idx++;
		}
		throw py::c2py("ValueError: value not in list");
	}
	template <class T> pylist<T>& pylist<T>::insert(int _Idx, T _Val) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx - ((_Idx > 0) ? 1 : 0));

		if (_Idx == this->size) {
			this->append(_Val);
		}
		else {
			node<T>* _Node = this->found_node(_Idx);
			node<T>* _New_Node = this->make_new_node(_Val);
			_New_Node->next = _Node;
			_New_Node->prev = _Node->prev;
			if (_Node->prev != nullptr) _Node->prev->next = _New_Node;
			else this->head = _New_Node;
			_Node->prev = _New_Node;
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::remove(T _Val) {
		this->pop(this->index(_Val));
		return *this;
	}
	template <class T> int pylist<T>::count(T _Val) {
		int _Cnt = 0;
		node<T>* _Node = this->head;
		while (_Node != nullptr) {
			if (_Node->data == _Val) _Cnt++;
			_Node = _Node->next;
		}
		return _Cnt;
	}
	template <class T> pylist<T>& pylist<T>::extend(pylist<T> _List) {
		return this->operator+=(_List);
	}
	template <class T> pylist<T> pylist<T>::copy() {
		pylist<T> _rList = *this;
		return _rList;
	}
	template <class T> pylist<T>& pylist<T>::clear() {
		while (this->size) this->pop();
		return *this;
	}

	template <class T> T* pylist<T>::operator[](int _Idx) {
		this->set_idx(&_Idx);
		this->check_idx_out_of_range(_Idx);

		return &(this->found_node(_Idx)->data);
	}
	template <class T> pylist<T>& pylist<T>::operator=(std::initializer_list<T> _Right) {
		this->clear();
		for (T _Ele : _Right) {
			this->append(_Ele);
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::operator=(const pylist<T>& _Right) {
		this->clear();
		node<T>* _rNode = _Right.head;
		while(_rNode != nullptr) {
			this->append(_rNode->data);
			_rNode = _rNode->next;
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::operator+=(const pylist<T>& _Right) {
		pylist<T> _Rcopy = _Right;
		this->tail->next = _Rcopy.head;
		_Rcopy.head->prev = this->tail;
		this->tail = _Rcopy.tail;
		_Rcopy.head = nullptr; _Rcopy.tail = nullptr;

		this->size += _Rcopy.size;
		this->flag = true;
		_Rcopy.size = 0;
		return *this;
	}
	template <class T> pylist<T> pylist<T>::operator*(int _Val) {
		if (_Val <= 0) return {};
		pylist<T> _rList = *this;
		int _Rest_Cnt = 0;
		while (_Val > 1) {
			_rList += _rList;
			if (_Val % 2) _Rest_Cnt++;
			_Val /= 2;
		}
		while (_Rest_Cnt--) _rList += *this;
		return _rList;
	}

	template <class T> pylist<T> pylist<T>::operator()(int _Begin, int _End, const int _Jmp) {
		this->set_idx(&_Begin);
		this->set_idx(&_End);
		this->check_idx_out_of_range(_Begin);
		this->check_idx_out_of_range(_End - ((_End > 0) ? 1 : 0));

		pylist<T> _rList;
		int _Lsize = this->size;
		node<T>* _Node = this->found_node(_Begin);
		int Idx = _Begin;
		if (!(Idx < _End)) return _rList;
		while (1) {
			_rList.append(_Node->data);
			
			Idx += _Jmp;
			if (!(Idx < _End)) return _rList;
			if (_Lsize - Idx > _Jmp) {
				int _Jmp_Cnt = _Jmp;
				while (_Jmp_Cnt--) _Node = _Node->next;
			}
			else _Node = this->found_node(Idx);
		}
	}
	template <class T> pylist<T> pylist<T>::operator()(const char* _Begin, int _End, const int _Jmp) {
		return this->operator()(0, _End, _Jmp);
	}
	template <class T> pylist<T> pylist<T>::operator()(int _Begin, const char* _End, const int _Jmp) {
		return this->operator()(_Begin, this->size, _Jmp);
	}
	template <class T> pylist<T> pylist<T>::operator()(const char* _Begin, const char* _End, const int _Jmp) {
		return this->operator()(0, this->size, _Jmp);
	}
}
#endif
