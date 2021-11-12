#pragma once
#ifndef _PYTHONLIST_
#define _PYTHONLIST_
#include <iostream>
#include <algorithm>
#include "pystr.h"

namespace py {
	template <class T> class pylist;
	template <class T> class pylist_node;
	template <class T> int len(pylist<T> value);

	template <class T>
	class pylist_node {
		friend class pylist<T>;
	private:
		T data_;
		pylist_node<T>* next_;
		pylist_node<T>* prev_;
	};

	template <class T>
	class pylist {
		template <class T> friend std::ostream& operator<<(std::ostream& os, const pylist<T>& value);
		template <class T> friend pylist<T> operator+(const pylist<T>& left, const pylist<T>& right);
		template <class T> friend int len(const pylist<T> value);
	private:
		pylist_node<T>* head_ = nullptr;
		pylist_node<T>* tail_ = nullptr;
		int size_ = 0;

		void set_idx(int* idx) const;
		void check_idx_out_of_range(const int idx) const;

		pylist_node<T>* make_new_node(const T& value);
		pylist_node<T>* found_node(const int idx) const;
		void remove_node(pylist_node<T>* node_ptr);

		T* data_;
		int volume_ = 0;
		bool flag_ = false;
		void set_data();
	public:
		pylist();
		pylist(int count, T value);
		pylist(std::initializer_list<T> value);
		pylist(const pylist<T>& value);
		~pylist();

		T* begin();
		T* end();

		pylist<T>& append(const T& value);
		T pop(const int idx = -1);
		pylist<T>& del(const int idx);
		pylist<T>& del(const int start, const int end, const int distance = 1);
		pylist<T>& del(const char* start, const int end, const int distance = 1);
		pylist<T>& del(const int start, const char* end, const int distance = 1);
		pylist<T>& del(const char* start, const char* end, const int distance = 1);
		pylist<T>& sort();
		pylist<T>& reverse();
		int index(const T value);
		pylist<T>& insert(const int idx, T value);
		pylist<T>& remove(const T value);
		int count(const T value);
		pylist<T>& extend(const pylist<T> _List);
		pylist<T> copy() const;
		pylist<T>& clear();

		T* operator[](int idx) const;
		pylist<T>& operator=(std::initializer_list<T> right);
		pylist<T>& operator=(const pylist<T>& right);
		pylist<T>& operator+=(const pylist<T>& right);
		pylist<T> operator*(const int value) const;
		pylist<T> operator()(const int start, const int end, const int distance = 1) const;
		pylist<T> operator()(const char* start, const int end, const int distance = 1) const;
		pylist<T> operator()(const int start, const char* end, const int distance = 1) const;
		pylist<T> operator()(const char* start, const char* end, const int distance = 1) const;
	};
	template <class T> std::ostream& operator<<(std::ostream& os, const pylist<T>& value) {
		os << "{";
		int size = value.size_;
		for (int idx = 0; idx < size - 1; idx++) {
			os << *value[idx] << ", ";
		}
		if (size) os << *value[size - 1];
		os << "}";
		return os;
	}
	template <class T> pylist<T> operator+(const pylist<T>& left, const pylist<T>& right) {
		pylist<T> ret_value = left;
		return ret_value += right;
	}

	template <class T> void pylist<T>::set_idx(int* idx) const {
		if (*idx < 0) *idx += this->size_;
	}
	template <class T> void pylist<T>::check_idx_out_of_range(const int idx)  const {
		if (idx < 0 || this->size_ <= idx) throw py::to_py("IndexError: list index out of range");
	}

	template <class T> pylist_node<T>* pylist<T>::make_new_node(const T& value) {
		pylist_node<T>* new_node = (pylist_node<T>*)calloc(1, sizeof(pylist_node<T>));
		new_node->data_ = value;
		new_node->next_ = nullptr;
		new_node->prev_ = nullptr;
		this->size_++;
		this->flag_ = true;
		return new_node;
	}
	template <class T> pylist_node<T>* pylist<T>::found_node(int idx) const {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx);

		pylist_node<T>* ret_value;
		if (idx < (this->size_ / 2)) {
			ret_value = this->head_;
			int idx_cnt = 0;
			while (idx_cnt != idx) {
				ret_value = ret_value->next_;
				idx_cnt++;
			}
		}
		else {
			ret_value = this->tail_;
			int idx_cnt = this->size_ - 1;
			while (idx_cnt != idx) {
				ret_value = ret_value->prev_;
				idx_cnt--;
			}
		}
		return ret_value;
	}

	template <class T> void pylist<T>::remove_node(pylist_node<T>* node_ptr) {
		if (node_ptr->prev_ == nullptr)	this->head_ = node_ptr->next_;
		else								node_ptr->prev_->next_ = node_ptr->next_;
		if (node_ptr->next_ == nullptr)	this->tail_ = node_ptr->prev_;
		else								node_ptr->next_->prev_ = node_ptr->prev_;
		
		free(node_ptr);
		this->size_--;
		this->flag_ = true;
	}

	template <class T> void pylist<T>::set_data() {
		int size = this->size_;
		if (this->volume_ == 0) {
			this->data_ = (T*)calloc(size, sizeof(T) * size);
			this->volume_ = size;
		}
		else {
			while (this->volume_ < size) this->volume_ *= 2;
			while (1) {
				T* temp = (T*)realloc(this->data_, sizeof(T) * this->volume_);
				if (temp != NULL) {
					this->data_ = temp;
					break;
				}
			}
		}

		pylist_node<T>* node = this->head_;
		int idx = 0;
		while(node != nullptr) {
			this->data_[idx] = node->data_;
			node = node->next_;
			idx++;
		}
		this->flag_ = false;
	}

	template <class T> pylist<T>::pylist() {}
	template <class T> pylist<T>::pylist(int count, T value) {
		if (count < 0) return;
		while (count--) {
			this->append(value);
		}
	}
	template <class T> pylist<T>::pylist(std::initializer_list<T> value) {
		*this = value;
	}
	template <class T> pylist<T>::pylist(const pylist<T>& value) {
		*this = value;
	}

	template <class T> pylist<T>::~pylist() {
		this->clear();
	}

	template <class T> T* pylist<T>::begin() {
		if (this->flag_) this->set_data();
		return &this->data_[0];
	}
	template <class T> T* pylist<T>::end() {
		if (this->flag_) this->set_data();
		return &this->data_[this->size_];
	}

	template <class T> pylist<T>& pylist<T>::append(const T& value) {
		pylist_node<T>* new_node = this->make_new_node(value);
		new_node->prev_ = this->tail_;
		if (this->tail_ != nullptr) this->tail_->next_ = new_node;
		this->tail_ = new_node;
		if (this->head_ == nullptr) this->head_ = new_node;
		return *this;
	}
	template <class T> T pylist<T>::pop(int idx) {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx);

		pylist_node<T>* node = this->found_node(idx);
		T ret_value = node->data_;
		this->remove_node(node);

		return ret_value;
	}
	template <class T> pylist<T>& pylist<T>::del(int idx) {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx);

		return *this = (*this)("", idx) + (*this)(idx + 1, "");
	}
	template <class T> pylist<T>& pylist<T>::del(const int start, const int end, const int distance) {
		int idx = start, idx_end = end;
		this->set_idx(&idx);
		this->set_idx(&idx_end);
		this->check_idx_out_of_range(idx);
		this->check_idx_out_of_range(idx_end - ((idx_end > 0) ? 1 : 0));

		pylist_node<T>* node = this->found_node(idx);
		if (!(idx < idx_end)) return *this;
		while (1) {
			pylist_node<T>* next = node->next_;
			this->remove_node(node); idx_end--;
			node = next;
			idx += distance - 1;
			if (!(idx < idx_end)) return *this;
			if (this->size_ - idx > distance - 1) {
				int distance_cnt = distance - 1;
				while (distance_cnt--) node = node->next_;
			}
			else node = this->found_node(idx);
		}
	}
	template <class T> pylist<T>& pylist<T>::del(const char* start, const int end, const int distance) {
		return this->del(0, end, distance);
	}
	template <class T> pylist<T>& pylist<T>::del(const int start, const char* end, const int distance) {
		return this->del(start, this->size_, distance);
	}
	template <class T> pylist<T>& pylist<T>::del(const char* start, const char* end, const int distance) {
		return this->del(0, this->size_, distance);
	}
	template <class T> pylist<T>& pylist<T>::sort() {
		int size = this->size_;
		T* sorted_list = (T*)calloc(size, sizeof(T) * size);
		for (int idx = 0; idx < size; idx++) {
			sorted_list[idx] = this->pop(0);
		}
		std::sort(sorted_list, sorted_list + size);
		for (int idx = 0; idx < size; idx++) {
			this->append(sorted_list[idx]);
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::reverse() {
		pylist<T> ret_value;
		while (this->size_) {
			ret_value.append(this->pop());
		}
		return *this = ret_value;
	}
	template <class T> int pylist<T>::index(T value) {
		int idx = 0;
		pylist_node<T>* node = this->head_;
		while (node != nullptr) {
			if (node->data_ == value) return idx;
			node = node->next_;
			idx++;
		}
		throw py::to_py("ValueError: value not in list");
	}
	template <class T> pylist<T>& pylist<T>::insert(int idx, T value) {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx - ((idx > 0) ? 1 : 0));

		if (idx == this->size_) {
			this->append(value);
		}
		else {
			pylist_node<T>* node = this->found_node(idx);
			pylist_node<T>* new_node = this->make_new_node(value);
			new_node->next_ = node;
			new_node->prev_ = node->prev_;
			if (node->prev_ != nullptr) node->prev_->next_ = new_node;
			else this->head_ = new_node;
			node->prev_ = new_node;
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::remove(T value) {
		this->pop(this->index(value));
		return *this;
	}
	template <class T> int pylist<T>::count(T value) {
		int count = 0;
		pylist_node<T>* node = this->head_;
		while (node != nullptr) {
			if (node->data_ == value) count++;
			node = node->next_;
		}
		return count;
	}
	template <class T> pylist<T>& pylist<T>::extend(pylist<T> _List) {
		return (*this) += _List;
	}
	template <class T> pylist<T> pylist<T>::copy() const {
		pylist<T> ret_value = *this;
		return ret_value;
	}
	template <class T> pylist<T>& pylist<T>::clear() {
		while (this->size_) this->pop();
		return *this;
	}

	template <class T> T* pylist<T>::operator[](int idx) const {
		this->set_idx(&idx);
		this->check_idx_out_of_range(idx);

		return &(this->found_node(idx)->data_);
	}
	template <class T> pylist<T>& pylist<T>::operator=(std::initializer_list<T> right) {
		this->clear();
		for (T element : right) {
			this->append(element);
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::operator=(const pylist<T>& right) {
		this->clear();
		pylist_node<T>* node = right.head_;
		while(node != nullptr) {
			this->append(node->data_);
			node = node->next_;
		}
		return *this;
	}
	template <class T> pylist<T>& pylist<T>::operator+=(const pylist<T>& right) {
		pylist<T> temp = right;
		this->tail_->next_ = temp.head_;
		temp.head_->prev_ = this->tail_;
		this->tail_ = temp.tail_;

		this->size_ += temp.size_;
		this->flag_ = true;
		
		temp.head_ = nullptr; temp.tail_ = nullptr;
		temp.size_ = 0;
		return *this;
	}
	template <class T> pylist<T> pylist<T>::operator*(int value) const {
		if (value <= 0) return {};
		pylist<T> ret_value = *this;
		int rest_count = 0;
		while (value > 1) {
			ret_value += ret_value;
			if (value % 2) rest_count++;
			value /= 2;
		}
		while (rest_count--) ret_value += *this;
		return ret_value;
	}

	template <class T> pylist<T> pylist<T>::operator()(const int start, const int end, const int distance) const {
		int idx = start, idx_end = end;
		this->set_idx(&idx);
		this->set_idx(&idx_end);
		this->check_idx_out_of_range(idx);
		this->check_idx_out_of_range(idx_end - ((idx_end > 0) ? 1 : 0));

		pylist<T> ret_value;
		int size = this->size_;
		pylist_node<T>* node = this->found_node(idx);
		if (!(idx < idx_end)) return ret_value;
		while (1) {
			ret_value.append(node->data_);
			
			idx += distance;
			if (!(idx < idx_end)) return ret_value;
			if (size - idx > distance) {
				int distancecount = distance;
				while (distancecount--) node = node->next_;
			}
			else node = this->found_node(idx);
		}
	}
	template <class T> pylist<T> pylist<T>::operator()(const char* start, const int end, const int distance) const {
		return (*this)(0, end, distance);
	}
	template <class T> pylist<T> pylist<T>::operator()(const int start, const char* end, const int distance) const {
		return (*this)(start, this->size_, distance);
	}
	template <class T> pylist<T> pylist<T>::operator()(const char* start, const char* end, const int distance) const {
		return (*this)(0, this->size_, distance);
	}

	template <class T> int len(const pylist<T> value) {
		return value.size_;
	}
}
#endif
