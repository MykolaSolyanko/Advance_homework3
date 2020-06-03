#pragma once

// iostream used only in analize and prints, can be deleted when program will be complited
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(size_t new_size) : capacity{ new_size }, size{ capacity } {
		data = (T*)std::malloc(capacity * sizeof(T));
		if (data == nullptr) {
			throw std::bad_alloc();
		}
		new(data)T[capacity]{};
	}
	Vector(const size_t new_size, T value) : capacity{ new_size }, size{ capacity } {
		data = (T*)std::malloc(capacity * sizeof(T));
		if (data == nullptr) {
			throw std::bad_alloc();
		}
		new(data)T[capacity];

		std::fill_n(data, capacity, value);
	}
	Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			memcpy(data, list.begin(), list.size() * sizeof(T));
		}
		else {
			T* i{ data };
			for (auto& element : list) {
				*i++ = element;
			}
		}
		size = list.size();
	}
	Vector(T* rhs_begin, T* rhs_end) {
		capacity = std::distance(rhs_begin, rhs_end);
		size = capacity;
		data = (T*)std::malloc(capacity * sizeof(T));
		if (data == nullptr) {
			throw std::bad_alloc();
		}
		new(data)T[capacity];

		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			memcpy(data, rhs_begin, capacity * sizeof(T));
		}
		else {
			for (T* d_begin{ data }; rhs_begin != rhs_end; d_begin++, rhs_begin++) {
				*d_begin = *rhs_begin;
			}
		}
	}
	Vector(const Vector& rhs) : Vector(rhs.size) {

		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(data, rhs.data, size * sizeof(T));
		}
		else {
			for (size_t i{}; i < size; i++) {

				// Предупреждение	C6385	
				//  Чтение недопустимых данных из "data":  
				//   доступный для чтения объем равен "capacity*sizeof(T)" байт, однако считать можно только "32" байт
				data[i] = rhs.data[i];
			}
		}
	}
	 Vector (Vector&& rhs) noexcept : capacity{ rhs.capacity }, size{ rhs.size }, data{ rhs.data } {
		 rhs.data = nullptr;
		 rhs.size = 0;
		 rhs.capacity = 0;
	}
	 ~Vector() {
		 delete_data();
	 }

	Vector& operator=(const Vector& rhs){
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity];

		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(tmp_arr, rhs.data, rhs.size*sizeof(T));
		}
		else {
			for (size_t i{}; i != rhs.size; i++) {
				tmp_arr[i] = rhs.data[i];
			}
		}

		delete_data();
		capacity = rhs.capacity;
		size = rhs.size;
		data = tmp_arr;
		return *this;
	}

	Vector& operator=(Vector&& rhs) noexcept{
		capacity = rhs.capacity;
		size = rhs.size;
		data = rhs.data;
		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
		return *this;
	}

	const T& operator[](const size_t pos) const {

		// only for review
		if (pos > size) {
			throw std::out_of_range ("operator[] out of range");
		}
		// only for review

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
	bool empty() const noexcept{
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

	void push_front(T value) {
		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		tmp_arr[0] = value;
		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy((tmp_arr + 1), data, size * sizeof(T));
		}
		else {
			for (size_t i{}; i != size; i++) {
				tmp_arr[i + 1] = std::move(data[i]);
			}
		}

		delete_data();
		data = tmp_arr;
		size++;
	}

	void push_back(T value) {
		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			std::memcpy(tmp_arr, data, size * sizeof(T));
		}
		else {
			for (size_t i{}; i != size;i++) {
				tmp_arr[i] = data[i];
			}
		}
		tmp_arr[size] = value;

		delete_data();
		data = tmp_arr;
		size++;
	}

	template <typename ... Rest>
	void emplace_back(Rest&&... rest) {
		push_back(T{rest...});
	}

	void insert(size_t pos, T value) {
		// cause of pos{0} which == data[0] causes error in erase function
		pos--;

		if (size == capacity) {
			capacity *= 2;
		}
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		size_t i{};
		for (; i != pos; i++) {
			tmp_arr[i] = data[i];
		}
		tmp_arr[pos] = value;
		for (; i != size; i++) {
			tmp_arr[i+1] = data[i];
		}

		delete_data();
		data = tmp_arr;
		size++;
	}

	void erase(size_t pos) {

		// cause of pos{0} which == data[0] causes error: cant identify which function need to be called
		// then pos{1} = data[0], pos{2} = data[1]  
		pos --;

		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
			memcpy(tmp_arr, data, pos*sizeof(T));
			memcpy((tmp_arr + pos), (data + pos + 1), (size - pos)*sizeof(T));
		}
		else {
			size_t i{};
			for (; i != pos;i++) {
				tmp_arr[i] = std::move(data[i]);
			}
			for (; i != size;i++) {
				tmp_arr[i] = std::move(data[i + 1]);
			}
		}
		delete_data();
		data = tmp_arr;
		size--;
	}

	void erase(T* pos) {
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		T* tmp_ptr { tmp_arr };
		T* d_begin{data};
		for (; d_begin != pos; d_begin++, tmp_ptr++) {
			*tmp_ptr = std::move(*d_begin);
		}
		if (d_begin != end()) {
			d_begin++;
			for (T* d_end{ data + size }; d_begin != d_end; d_begin++, tmp_ptr++) {
				*tmp_ptr = std::move(*d_begin);
			}
		}

		delete_data();
		data = tmp_arr;
		size--;
	}

	void erase(T* begin, T* end) {
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		T* tmp_begin{ tmp_arr };
		T* d_begin{ data };
		size_t erase_distance = std::distance(begin, end);

		for (; d_begin != begin;d_begin++, tmp_begin++) {
			*tmp_begin = std::move(*d_begin);
		}
		d_begin += erase_distance;
		for (T* d_end{ data + size };d_begin != d_end; d_begin++, tmp_begin++) {
			*tmp_begin = std::move(*d_begin);
		}

		delete_data();
		data = tmp_arr;
		size -= erase_distance;
	}

	void reserve(const size_t new_cap) {
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		if (size != 0) {
			if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
				std::memcpy(tmp_arr, data, sizeof(T) * size);
			}
			else {
				for (size_t i{}; i != size;i++) {
					tmp_arr[i] = std::move(data[i]);
				}
			}
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
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		if (size != 0) {
			if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
				std::memcpy(tmp_arr, data, sizeof(T) * size);
			}
			else {
				for (size_t i{}; i != size;i++) {
					tmp_arr[i] = data[i];
				}
			}
		}

		if (new_size > size) {
			T tmp_value{};
			for (size_t i{ size }; i != new_size; i++) {
				tmp_arr[i] = tmp_value;
			}
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
		T* tmp_arr = (T*)std::malloc(capacity * sizeof(T));
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		new(tmp_arr)T[capacity]{};

		if (size != 0) {
			if (std::is_trivially_constructible<T>::value || std::is_fundamental<T>::value) {
				std::memcpy(tmp_arr, data, sizeof(T) * size);
			}
			else {
				for (size_t i{}; i != size;i++) {
					tmp_arr[i] = data[i];
				}
			}
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
		data = nullptr;
	}

	T front() {
		return { *data };
	}
	T back() {
		return { *(data + size - 1) };
	}


	void test_analize() noexcept {
		std::cout << "CHECK: Empty? " << empty() << std::endl;
		std::cout << "Capacity: " << capacity <<std::endl;
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
		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
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
