#pragma once

// iostream used only in analize and prints, can be deleted when program will be complited
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(size_t new_size) : capacity{ new_size }, size{ capacity } {
		data = alloc_memory(capacity);
		new(data)T[capacity]{};
	}
	Vector(const size_t new_size, const T value) : capacity{ new_size }, size{ capacity } {
		data = alloc_memory(capacity);
		new(data)T[capacity];

		std::fill_n(data, capacity, value);
	}
	Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
		memory_copy(data, list.begin(), list.size());
		size = list.size();
	}
	Vector(const T* rhs_begin, const T* rhs_end) {
		capacity = std::distance(rhs_begin, rhs_end);
		size = capacity;
		data = alloc_memory(capacity);
		new(data)T[capacity];
		memory_copy(data, rhs_begin, capacity);
	}
	Vector(const Vector& rhs) : Vector(rhs.size) {
		memory_copy(data, rhs.data, rhs.size);
	}
	Vector(Vector&& rhs) noexcept : capacity{ rhs.capacity }, size{ rhs.size }, data{ rhs.data } {
		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
	}
	~Vector() {
		delete_data();
	}

	Vector& operator=(const Vector& rhs) {
		if (this == &rhs) {
			return *this;
		}
		T* tmp_arr = alloc_memory(rhs.capacity);
		new(tmp_arr)T[rhs.capacity];
		memory_copy(tmp_arr, rhs.data, rhs.size);
		delete_data();
		capacity = rhs.capacity;
		size = rhs.size;
		data = tmp_arr;
		return *this;
	}

	Vector& operator=(Vector&& rhs) noexcept {
		if (this == &rhs) {
			return *this;
		}
		capacity = rhs.capacity;
		size = rhs.size;
		data = rhs.data;
		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
		return *this;
	}

	const T& operator[](const size_t pos) const {
		return data[pos];
	}
	T& operator[](const size_t pos) {
		return data[pos];
	}

	size_t capacity_() const noexcept {
		return this->capacity;
	}
	size_t size_() const noexcept {
		return this->size;
	}
	bool empty() const noexcept {
		if (size == 0) {
			return true;
		}
		return false;
	}

	T* begin() {
		return { data };
	}
	T* end() {
		return { data + size };
	}

	void push_front(const T value) {
		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];
		tmp_arr[0] = value;
		memory_copy((tmp_arr + 1), data, size);
		delete_data();
		data = tmp_arr;
		size++;
	}

	void push_back(const T value) {
		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];

		memory_copy(tmp_arr, data, size);
		tmp_arr[size] = value;
		delete_data();
		data = tmp_arr;
		size++;
	}

	template <typename ... Rest>
	void emplace_back(Rest&&... rest) {
		push_back(T{ rest... });
	}

	void insert(size_t pos, const T value) {
		// cause of pos{0} which == data[0] causes error: cant identify which function need to be called
		// then pos{1} = data[0], pos{2} = data[1]  
		pos--;

		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];
		memory_copy(tmp_arr, data, pos);
		tmp_arr[pos] = value;
		memory_copy((tmp_arr + pos + 1), (data + pos), (size - pos));
		delete_data();
		data = tmp_arr;
		size++;
	}

	void erase(size_t pos) {
		pos--;
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];
		memory_copy(tmp_arr, data, pos);
		memory_copy((tmp_arr + pos), (data + pos + 1), (size - pos));
		delete_data();
		data = tmp_arr;
		size--;
	}

	void erase(T* pos) {
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];
		size_t distance_to_pos = std::distance(data, pos);
		memory_copy(tmp_arr, data, distance_to_pos);
		memory_copy((tmp_arr + distance_to_pos), (data + distance_to_pos + 1), (size - distance_to_pos));
		delete_data();
		data = tmp_arr;
		size--;
	}

	void erase(T* begin, T* end) {
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];
		size_t erase_distance = std::distance(begin, end);
		size_t pos_start_erase = std::distance(data, begin);
		memory_copy(tmp_arr, data, pos_start_erase);
		memory_copy(tmp_arr + pos_start_erase, end, (size - erase_distance));
		delete_data();
		data = tmp_arr;
		size -= erase_distance;
	}

	void reserve(const size_t new_cap) {
		T* tmp_arr = alloc_memory(new_cap);
		new(tmp_arr)T[capacity];

		if (size != 0) {
			memory_copy(tmp_arr, data, size);
		}
		delete_data();
		data = tmp_arr;
	}

	void resize(const size_t new_size) {
		if (new_size < size) {
			if (std::is_constructible<T>::value) {
				for (size_t i{ new_size }; i != size; i++) {
					data[i].~T();
				}
			}
			size = new_size;
		}

		capacity = new_size;
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity]{};
		if (size != 0) {
			memory_copy(tmp_arr, data, size);
		}
		delete_data();
		data = tmp_arr;
		size = new_size;
	}

	void resize(const size_t new_size, const T value) {
		if (new_size < size) {
			if (std::is_constructible<T>::value) {
				for (size_t i{ new_size }; i != size; i++) {
					data[i].~T();
				}
			}
			size = new_size;
		}
		capacity = new_size;
		T* tmp_arr = alloc_memory(capacity);
		new(tmp_arr)T[capacity];

		if (size != 0) {
			memory_copy(tmp_arr, data, size);
		}
		if (new_size > size) {
			for (size_t i{ size }; i != new_size; i++) {
				tmp_arr[i] = value;
			}
		}

		delete_data();
		data = tmp_arr;
		size = new_size;
	}

	void clear() {
		size = 0;
		delete_data();
	}

	T front() {
		return { *data };
	}
	T back() {
		return { *(data + size - 1) };
	}


	void test_analize() noexcept {
		std::cout << "CHECK: Empty? " << empty() << std::endl;
		std::cout << "Capacity: " << capacity << std::endl;
		std::cout << "Size: " << size << std::endl;
		if (size != 0) {
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
	size_t capacity{ 4 };
	T* data{};
	size_t size{};

	void delete_data() {
		if (size != 0) {
			if constexpr (std::is_constructible<T>::value) {
				for (size_t i{}; i != size; i++) {
					data[i].~T();
				}
			}
			std::free(data);
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
		for (int i{}; i != size;i++) {
			std::cout << data[i].first << data[i].second << std::endl;
		}
	}
	void print_arithmetic() {
		for (int i{}; i != size;i++) {
			std::cout << data[i] << std::endl;
		}
	}
};
