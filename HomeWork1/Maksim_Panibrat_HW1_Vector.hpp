#pragma once

// only for __FUNCTION__ , can be deleted when program will be complited
#include <iostream>

template <typename T>
class Vector {
public:
	Vector() = default;
	Vector(const size_t& size) {
		std::cout << __FUNCTION__ << std::endl;
		capacity = size;
		data = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (data == nullptr) {
			throw std::bad_alloc();
		}
	}
	Vector(const std::initializer_list<T>& list) : Vector(list.size()) {
		std::cout << __FUNCTION__ << std::endl;
		data = new ((T*)std::malloc(list.size() * sizeof(T)))T[list.size()];
		if (data == nullptr) {
			throw std::bad_alloc();
		}
		T* i{data};
		for (auto& element : list) {
			*i = std::move(element);
			i++;
			size++;
		}
	}
	Vector(T* rhs_begin, T* rhs_end) {
		std::cout << __FUNCTION__ << std::endl;
		capacity = std::distance(rhs_begin, rhs_end);
		data = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (data == nullptr) {
			throw std::bad_alloc();
		}
		for (T* d_begin{ data }; rhs_begin != rhs_end; d_begin++, rhs_begin++) {
				*d_begin = *rhs_begin;
				size++;
		}
	}
	Vector(const Vector& rhs) : capacity{ rhs.capacity_() }, size{ rhs.size_() }, data{ new ((T*)std::malloc(capacity * sizeof(T)))T[capacity] } {
		std::cout << __FUNCTION__ << std::endl;
		if constexpr (std::is_arithmetic<T>::value) {
			std::memcpy(&data, &rhs.data, size);
		}
		for (size_t i{}; i != size; i++) {
			data[i] = rhs.data[i];
		}
	}
	 Vector (Vector&& rhs) noexcept : capacity{ rhs.capacity_() }, size{ rhs.size_() }, data{ rhs.data } {
		 std::cout << __FUNCTION__ << std::endl;
		 rhs.data = nullptr;
		 rhs.size = 0;
		 rhs.capacity = 0;
	}
	 ~Vector() {
		 std::cout << __FUNCTION__ << std::endl;
		 if (std::is_constructible<T>::value) {
			 for (size_t i{}; i != size; i++) {
				 data[i].~T();
			 }
		 }
		 std::free(data);
	 }

	Vector& operator=(const Vector& rhs){
		std::cout << __FUNCTION__ << std::endl;
		T* tmp_arr = new ((T*)std::malloc(rhs.capacity_() * sizeof(T)))T[rhs.capacity_()];

		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}
		if constexpr(std::is_arithmetic<T>::value) {
			std::memcpy(&tmp_arr, &rhs.data, rhs.size_());
			return *this;
		}
		for (size_t i{}; i != rhs.size_(); i++) {
			tmp_arr[i] = rhs.data[i];
		}

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		capacity = rhs.capacity_();
		size = rhs.size_();
		data = tmp_arr;
		return *this;
	}

	Vector& operator=(Vector&& rhs) noexcept{
		std::cout << __FUNCTION__ << std::endl;
		capacity = rhs.capacity_();
		size = rhs.size_();
		data = rhs.data;
		rhs.data = nullptr;
		rhs.size = 0;
		rhs.capacity = 0;
		return *this;
	}

	const T& operator[](const size_t& pos) const {
		if (pos > size) {
			throw std::out_of_range ("operator[] out of range");
		}
		return data[pos];
	}
	T& operator[](const size_t& pos) {
		if (pos > size) {
			throw std::out_of_range ("operator[] out of range");
		}
		return data[pos];
	}

	size_t capacity_() const noexcept {
		return capacity;
	}
	size_t size_() const noexcept {
		return size;
	}
	bool empty() const noexcept{
		if (size == 0) {
			return true;
		}
		return false;
	}

	T* begin() {
		if (data == nullptr) {
			throw std::out_of_range ("called begin == nullptr");
		}
		return { data };
	}
	T* end() const{
		if (data == nullptr) {
			throw std::out_of_range ("called end == nullptr");
		}
		return { data + size };
	}

	void push_front(T value) {
		std::cout << __FUNCTION__ << std::endl;
		if ((size + 1) >= capacity) {
			capacity *= 2;
		}
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		tmp_arr[0] = value;
		for (size_t i{}; i != size; i++) {
			tmp_arr[i + 1] = std::move(data[i]);
		}

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size++;
	}

	void push_back(T value) {
		std::cout << __FUNCTION__ << std::endl;
		if ((size + 1) >= capacity) {
			capacity *= 2;
		}
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		for (size_t i{}; i != size;i++) {
			tmp_arr[i] = data[i];
		}
		tmp_arr[size] = value;

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size++;
	}

	template <typename ... Rest>
	void emplace_back(Rest&&... rest) {
		std::cout << __FUNCTION__ << std::endl;
		push_back(T{rest...});
	}
	// universal &

	void insert(size_t pos, T value) {
		std::cout << __FUNCTION__ << std::endl;
		if (pos > capacity) {
			throw std::out_of_range("insert out of range");
		}
		if ((size + 1) >= capacity) {
			capacity *= 2;
		}

		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		size_t i{};
		for (; i != pos; i++) {
			tmp_arr[i] = data[i];
		}
		tmp_arr[pos] = value;
		for (; i != size; i++) {
			tmp_arr[i+1] = data[i];
		}

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size++;
	}

	void erase(size_t pos) {
		if (pos > size) {
			throw std::out_of_range ("pos erase out of range");
		}
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		size_t i{};
		for (; i != pos;i++) {
			tmp_arr[i] = std::move(data[i]);
		}
		for (; i != size;i++) {
			tmp_arr[i] = std::move(data[i+1]);
		}

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size--;
	}

	void erase(T* pos) {
		if (pos > end()) {
			throw std::out_of_range ("*erase out of range");
		}
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

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

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size--;
	}

	void erase(T* begin, T* end) {
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

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

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
		size -= erase_distance;
	}

	void reserve(const size_t& new_cap) {
		std::cout << __FUNCTION__ << std::endl;
		// T* tmp_arr = (T*)std::malloc(new_cap * sizeof(T));
		T* tmp_arr = new ((T*)std::malloc(new_cap * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		if (size == 0) {
			std::free(data);
			data = tmp_arr;
			return;
		}

		if constexpr (std::is_arithmetic<T>::value) {
			std::memcpy(tmp_arr, data, sizeof(T) * size);
		}
		else {
			for (size_t i{}; i != size;i++) {
				tmp_arr[i] = std::move(data[i]);
			}
		}
		
		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
			std::free(data);
		data = tmp_arr;

	}

	void resize(const size_t& new_size) {
		std::cout << __FUNCTION__ << std::endl;
		if (new_size < size) {
			size = new_size;
		}
		capacity = new_size;
		T* tmp_arr = new ((T*)std::malloc(capacity * sizeof(T)))T[capacity];
		if (tmp_arr == nullptr) {
			throw std::bad_alloc();
		}

		if (size == 0) {
			std::free(data);
			data = tmp_arr;
			return;
		}

		if constexpr (std::is_arithmetic<T>::value) {
			std::memcpy(tmp_arr, data, sizeof(T) * size);
		}
		else {
			for (size_t i{}; i != size;i++) {
				tmp_arr[i] = std::move(data[i]);
			}
		}

		if (std::is_constructible<T>::value) {
			for (size_t i{}; i != size; i++) {
				data[i].~T();
			}
		}
		std::free(data);
		data = tmp_arr;
	}

	void clear() {
		size = 0;
		data = nullptr;
	}

	T& front() {
		if (data == nullptr) {
			throw std::out_of_range("front out of range");
		}
		return { *data };
	}
	T& back() {
		if (data == nullptr) {
			throw std::out_of_range("back out of range");
		}
		return { *(data + size - 1) };
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

	void analize() noexcept {
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
};

