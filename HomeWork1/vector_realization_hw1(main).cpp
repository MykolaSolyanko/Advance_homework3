#include <iostream>
#include "Vector_Realization.hpp"
#include "Stack_Realiztion.hpp"

int main()
{

	Stack<size_t, Vector<int>> s;

	s.push(2);

	s.analize();

	s.pop();

	s.analize();

	s.top();

	s.empty();

	return 0;

}
