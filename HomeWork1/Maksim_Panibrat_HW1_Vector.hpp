#pragma once

// iostream used only in analize and prints, can be deleted when program will be complited
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(size_t new_size) : capacity_{ new_size }, size_{ capacity_ } {
		data_ = alloc_memory(capacity_);
		new(data_)T[capacity_]{};
	}
	Vector(const size_t new_size, const T value) : capacity_{ new_size }, size_{ capacity_ } {
		data_ = alloc_memory(capacity_);
		new(data_)T[capacity_];

		std::fill_n(data_, capacity_, value);
	}
	Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
		memory_copy(data_, list.begin(), list.size());
		size_ = list.size();
	}
	Vector(const T* rhs_begin, const T* rhs_end) {
		capacity_ = std::distance(rhs_begin, rhs_end);
		size_ = capacity_;
		data_ = alloc_memory(capacity_);
		new(data_)T[capacity_];
		memory_copy(data_, rhs_begin, capacity_);
	}
	Vector(const Vector<T>& rhs) : Vector<T>(rhs.size_) {
		memory_copy(data_, rhs.data_, rhs.size_);
	}
	Vector(Vector<T>&& rhs) noexcept : capacity_{ rhs.capacity_ }, size_{ rhs.size_ }, data_{ rhs.data_ } {
		rhs.data_ = nullptr;
		rhs.size_ = 0;
		rhs.capacity_ = 0;
	}
	~Vector() {
		delete_data();
	}

	Vector& operator=(const Vector<T>& rhs) {
		if (this == &rhs) {
			return *this;
		}
		T* tmp_arr = alloc_memory(rhs.capacity_);
		new(tmp_arr)T[rhs.capacity_];
		memory_copy(tmp_arr, rhs.data_, rhs.size_);
		delete_data();
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

	void push_front(const T value) {
		if (size_ == capacity_) {
			capacity_ *= 2;
		}
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];
		tmp_arr[0] = value;
		memory_copy((tmp_arr + 1), data_, size_);
		delete_data();
		data_ = tmp_arr;
		size_++;
	}

	void push_back(const T value) {
		if (size_ == capacity_) {
			capacity_ *= 2;
		}
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];

		memory_copy(tmp_arr, data_, size_);
		tmp_arr[size_] = value;
		delete_data();
		data_ = tmp_arr;
		size_++;
	}

	template <typename ... Rest>
	void emplace_back(Rest&&... rest) {
		push_back(T{ rest... });
	}

	void insert(size_t pos, const T value) {
		// cause of pos{0} which == data[0] causes error: cant identify which function need to be called
		// then pos{1} = data[0], pos{2} = data[1]  
		pos--;

		if (size_ == capacity_) {
			capacity_ *= 2;
		}
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];
		memory_copy(tmp_arr, data_, pos);
		tmp_arr[pos] = value;
		memory_copy((tmp_arr + pos + 1), (data_ + pos), (size_ - pos));
		delete_data();
		data_ = tmp_arr;
		size_++;
	}

	void erase(size_t pos) {
		pos--;
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];
		memory_copy(tmp_arr, data_, pos);
		memory_copy((tmp_arr + pos), (data_ + pos + 1), (size_ - pos));
		delete_data();
		data_ = tmp_arr;
		size_--;
	}

	void erase(T* pos) {
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];
		size_t distance_to_pos = std::distance(data_, pos);
		memory_copy(tmp_arr, data_, distance_to_pos);
		memory_copy((tmp_arr + distance_to_pos), (data_ + distance_to_pos + 1), (size_ - distance_to_pos));
		delete_data();
		data_ = tmp_arr;
		size_--;
	}

	void erase(T* begin, T* end) {
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];
		size_t erase_distance = std::distance(begin, end);
		size_t pos_start_erase = std::distance(data_, begin);
		memory_copy(tmp_arr, data_, pos_start_erase);
		memory_copy(tmp_arr + pos_start_erase, end, (size_ - erase_distance));
		delete_data();
		data_ = tmp_arr;
		size_ -= erase_distance;
	}

	void reserve(const size_t new_cap) {
		T* tmp_arr = alloc_memory(new_cap);
		new(tmp_arr)T[capacity_];

		if (size_ != 0) {
			memory_copy(tmp_arr, data_, size_);
		}
		delete_data();
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
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_]{};
		if (size_ != 0) {
			memory_copy(tmp_arr, data_, size_);
		}
		delete_data();
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
		T* tmp_arr = alloc_memory(capacity_);
		new(tmp_arr)T[capacity_];

		if (size_ != 0) {
			memory_copy(tmp_arr, data_, size_);
		}
		if (new_size > size_) {
			for (size_t i{ size_ }; i != new_size; i++) {
				tmp_arr[i] = value;
			}
		}

		delete_data();
		data_ = tmp_arr;
		size_ = new_size;
	}

	void clear() {
		size_ = 0;
		delete_data();
	}

	T front() {
		return { *data_ };
	}
	T back() {
		return { *(data_ + size_ - 1) };
	}


	void test_analize() noexcept {
		std::cout << "CHECK: Empty? " << empty() << std::endl;
		std::cout << "Capacity: " << capacity_ << std::endl;
		std::cout << "Size: " << size_ << std::endl;
		if (size_ != 0) {
			std::cout << "Print vector: \n";
			if constexpr (std::is_same<std::pair<bool, const char*>, T>::value) {
				print_pair();
				return;
			}
			else if constexpr (std::is_arithmetic<T>::value) {
				print_arithmetic();
				return;
			}
			else {
				std::cout << "Cant print\n";
			}
		}
	}

private:
	size_t capacity_{ 4 };
	T* data_{};
	size_t size_{};

	void delete_data() {
		if (size_ != 0) {
			if constexpr (std::is_constructible<T>::value) {
				for (size_t i{}; i != size_; i++) {
					data_[i].~T();
				}
			}
			std::free(data_);
		}
	}

	void memory_copy(T* destination, const T* source, const size_t copy_size) {
		if constexpr (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(destination, source, copy_size * sizeof(T));
		}
		else if constexpr (std::is_nothrow_move_constructible<T>::value) {
			for (size_t i{}; i != copy_size;i++) {
				destination[i] = std::move(source[i]);
			}
		}
		else {
			for (size_t i{}; i != copy_size;i++) {
				destination[i] = source[i];
			}
		}
	}

	T* alloc_memory(size_t needed_memory) {
		T* tmp_arr = (T*)std::malloc(needed_memory * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		return tmp_arr;
	}

	void print_pair() {
		for (int i{}; i != size_;i++) {
			std::cout << data_[i].first << data_[i].second << std::endl;
		}
	}
	void print_arithmetic() {
		for (int i{}; i != size_;i++) {
			std::cout << data_[i] << std::endl;
		}
	}
};