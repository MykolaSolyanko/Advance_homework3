#pragma once

using pair = std::pair<bool, const char*>;

template <typename T, class Container>
class Stack_ad {
public:

	pair push(T value) {
		if (vec.size() > vec.capacity()) {
			return { false, "Stack full" };
		}
		vec.push_back(value);
		return { true, "Push success" };
	}
	pair pop() {
		if (vec.size() == 0) {
			return { false, "Stack clear" };
		}
		vec.erase(vec.end());
		return { true, "Pop success" };
	}

	void clear() {
		if (vec.size() == 0) {
			return;
		}
		vec.clear();
	}

	std::pair<bool, T> top() {
		if (vec.size() == 0) {
			return { false, vec.back() };
		}

		return { true, vec.back() };
	}

	template <typename ... Rest>
	void emplace(Rest... rest) {
		vec.push_back(T{ rest... });
	}

	void resize(size_t new_size) {
		vec.resize(new_size);
	}

	const unsigned long long GetSize() {
		return vec.size();
	}
	const unsigned long long GetCapacity() {
		return vec.capacity();
	}
	void analize() {
		vec.test_analize();
	}

private:
	Container vec{};
};
