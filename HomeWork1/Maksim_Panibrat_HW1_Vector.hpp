#pragma once
#include <exception>
#include <cstring>
#include <iterator>
#include <initializer_list>
#include <algorithm>
#include <type_traits>
#include <utility> // for std::forward

template <typename T>
class Vector {
public:
	Vector() {
		data_ = create_array(capacity_);
	}
	Vector(const size_t new_size) : capacity_{ new_size }, size_{ capacity_ } {
		data_ = create_array(capacity_);
	}
	Vector(const size_t new_size, const T value) : Vector(new_size) {
		std::fill_n(data_, capacity_, value);
	}
	Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
		memory_copy(data_, list.begin(), list.end());
	}
	Vector(const T* rhs_begin, const T* rhs_end) : Vector(std::distance(rhs_begin, rhs_end)) {
		memory_copy(data_, rhs_begin, rhs_end);
	}
	Vector(const Vector<T>& rhs) : Vector<T>(rhs.size_) {
		memory_copy(data_, rhs.begin(), rhs.end());
	}
	Vector(Vector<T>&& rhs) noexcept : capacity_{ rhs.capacity_ }, size_{ rhs.size_ }, data_{ rhs.data_ } {
		rhs.data_ = nullptr;
		rhs.size_ = 0;
		rhs.capacity_ = 0;
	}
	~Vector() {
		free_data();
	}

	Vector& operator=(const Vector<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		T* tmp_arr = create_array(rhs.capacity_);
		memory_copy(tmp_arr, rhs.begin(), rhs.end());
		free_data();
		capacity_ = rhs.capacity_;
		size_ = rhs.size_;
		data_ = tmp_arr;
		return *this;
	}

	Vector& operator=(Vector<T>&& rhs) noexcept {
		if (this == &rhs) {
			return *this;
		}
		capacity_ = rhs.capacity_;
		size_ = rhs.size_;
		data_ = rhs.data_;
		rhs.data_ = nullptr;
		rhs.size_ = 0;
		rhs.capacity_ = 0;
		return *this;
	}

	const T& operator[](const size_t pos) const {
		return data_[pos];
	}
	T& operator[](const size_t pos) {
		return data_[pos];
	}

	size_t capacity() const noexcept {
		return this->capacity_;
	}
	size_t size() const noexcept {
		return this->size_;
	}
	bool empty() const noexcept {
		return size_ == 0;
	}

	T* begin() {
		return { data_ };
	}
	T* end() {
		return { data_ + size_ };
	}
	T* begin() const {
		return { data_ };
	}
	T* end() const {
		return { data_ + size_ };
	}

	void push_front(T value) {
		if (size_ == capacity_) {
			reserve(capacity_ * 2);
		}
		free_space_for_element(data_, end());
		place_element(0, value);
		++size_;
	}

	void push_back(T value) {
		if (size_ == capacity_) {
			reserve(capacity_ * 2);
		}
		place_element(size_, value);
		++size_;
	}

	template <typename ... Rest>
	void emplace_back(Rest&&... rest) {
		push_back({ std::forward<Rest>(rest)... });
	}

	void insert(const size_t pos, T value) {
		if (size_ == capacity_) {
			reserve(capacity_ * 2);
		}
		free_space_for_element(data_ + pos, end());
		place_element(pos, value);
		++size_;
	}

	void erase(size_t pos) {
		if constexpr (std::is_constructible<T>::value) {
			data_[pos].~T();
		}
		if (pos != size_) {
			memory_copy(data_ + pos, data_ + pos + 1, end());
		}
		--size_;
	}

	void erase(T* pos) {
		if constexpr (std::is_constructible<T>::value) {
			pos->~T();
		}
		if (pos != end()) {
			memory_copy(pos, pos + 1, end());
		}
		--size_;
	}

	void erase(T* begin, T* end) {
		if constexpr (std::is_constructible<T>::value) {
			for (T* delete_begin{ begin }; delete_begin != end; delete_begin++) {
				delete_begin->~T();
			}
		}
		if (end != this->end()) {
			memory_copy(begin, end, this->end());
		}
		size_ -= std::distance(begin, end);;
	}

	void reserve(const size_t new_cap) {
		if (new_cap <= capacity_) {
			return;
		}
		T* tmp_arr = create_array(new_cap);
		if (size_ != 0) {
			memory_copy(tmp_arr, data_, end());
		}
		free_data();
		data_ = tmp_arr;
		capacity_ = new_cap;
	}

	void resize(const size_t new_size) {
		if (new_size < size_) {
			if (std::is_constructible<T>::value) {
				for (size_t i{ new_size }; i != size_; i++) {
					data_[i].~T();
				}
			}
			size_ = new_size;
		}

		capacity_ = new_size;
		T* tmp_arr = create_array(capacity_);
		if (size_ != 0) {
			memory_copy(tmp_arr, data_, end());
		}
		free_data();
		data_ = tmp_arr;
		size_ = new_size;
	}

	void resize(const size_t new_size, const T value) {
		if (new_size < size_) {
			if (std::is_constructible<T>::value) {
				for (size_t i{ new_size }; i != size_; i++) {
					data_[i].~T();
				}
			}
			size_ = new_size;
		}
		capacity_ = new_size;
		T* tmp_arr = create_array(capacity_);
		if (size_ != 0) {
			memory_copy(tmp_arr, data_, end());
		}
		if (new_size > size_) {
			for (size_t i{ size_ }; i != new_size; i++) {
				tmp_arr[i] = value;
			}
		}

		free_data();
		data_ = tmp_arr;
		size_ = new_size;
	}

	void clear() {
		free_data();
		size_ = 0;
	}

	T front() {
		return { *data_ };
	}
	T back() {
		return { *(data_ + size_ - 1) };
	}

private:
	size_t capacity_{ 1 };
	T* data_{};
	size_t size_{};

	void free_data() {
		if (size_ != 0) {
			if constexpr (std::is_constructible<T>::value) {
				for (size_t i{}; i != size_; i++) {
					data_[i].~T();
				}
			}
			std::free(data_);
		}
	}

	void place_element(const size_t pos, T value) noexcept {
		if constexpr (std::is_nothrow_move_constructible<T>::value) {
			data_[pos] = std::move(value);
		}
		else {
			data_[pos] = value;
		}
	}

	void memory_copy(T* destination, T* source_begin, T* source_end) noexcept {
		if constexpr (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(destination, source_begin, std::distance(source_begin, source_end) * sizeof(T));
		}
		else if constexpr (std::is_nothrow_move_constructible<T>::value) {
			for (; source_begin != source_end; destination++, source_begin++) {
				*destination = std::move(*source_begin);
			}
		}
		else {
			for (; source_begin != source_end; destination++, source_begin++) {
				*destination = *source_begin;
			}
		}
	}

	void memory_copy(T* destination, const T* source_begin, const T* source_end) noexcept {
		if constexpr (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(destination, source_begin, std::distance(source_begin, source_end) * sizeof(T));
		}
		else if constexpr (std::is_nothrow_move_constructible<T>::value) {
			for (; source_begin != source_end; destination++, source_begin++) {
				*destination = std::move(*source_begin);
			}
		}
		else {
			for (; source_begin != source_end; destination++, source_begin++) {
				*destination = *source_begin;
			}
		}
	}

	void free_space_for_element(T* begin, T* end) noexcept {
		if constexpr (std::is_nothrow_move_constructible<T>::value) {
			for (; end != begin; end--) {
				*end = std::move(*(end - 1));
			}
		}
		else {
			for (; end != begin; end--) {
				*end = *(end - 1);
			}
		}
	}

	T* create_array(size_t needed_memory) {
		T* tmp_arr = (T*)std::malloc(needed_memory * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[needed_memory]{};
		return tmp_arr;
	}
};
