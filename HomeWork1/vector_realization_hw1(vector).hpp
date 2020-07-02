#pragma once
#include <iostream>
#include <cstring>
#include "Stack_Realiztion.hpp"

template<typename T>
class Vector 
{
  public:

	  /////////////////constructors////////////////////

	  Vector() = default; //default construcrtor
	  Vector(size_t size) //custom constructor
	  {
		  std::cout << "custom constructor" << std::endl;
		  my_capacity = size;
		  data = new T[size];
	  }
	  Vector(const Vector& v) //copy constructor
	  {
		  std::cout << "copy constructor" << std::endl;
		  my_size = v.my_size;
		  my_capacity = v.my_capacity;
		  data = new T[my_size];
		  for(size_t i = 0; i < my_size; i++) 
		  {
			  data[i] = v.data[i];
		  }
	  }
	  Vector(Vector&& v) //move constructor
	  {
		  std::cout << "move constructor" << std::endl;
		  my_capacity = v.my_capacity;
		  my_size = v.my_size;
		  data = v.data;
	  }
	  T& operator[](size_t pos) //[] operator
	  {
		  std::cout << "[] operator" << std::endl;
		  return data[pos];
	  }
	  Vector& operator=(const Vector & v) //copy operator
	  {
		  std::cout << "copy operator" << std::endl;
		  delete[] data;
		  my_size = v.my_size;
		  my_capacity = v.my_capacity;
		  data = new T[my_size];
		  for(size_t i = 0; i < my_size; i++) 
		  {
			  data[i] = v.data[i];
		  }
		  return *this;
	  }
	  ~Vector() //destructor
	  {
		  std::cout << "destructor" << std::endl;
		  delete[] data;
	  }
	  Vector(const std::initializer_list<T>& list) //initializer list
	  {
		  std::cout << "initializer list" << std::endl;
		  T* i = begin();
		  for(auto& element : list) 
		  {
			  *i = std::move(element);
			  i++;
			  size++;
		  }
	  }
	  Vector(T* begin, T* end) //??????
	  {
		  std::cout << "Vector(T* begin, T* end)" << std::endl;
		  T* copy_1{begin};
		  T* copy_2{end};
		  my_capacity = 0;
		  for (; copy_1 != copy_2; copy_1++) 
		  {
			  my_capacity++;
		  }
		  data = new T[my_capacity];
		  for (T* d_begin{data}; begin != end; d_begin++, begin++)
		  {
			  if(*d_begin != *begin) 
			  {
				  *d_begin = std::move(*begin);
				  my_size++;
			  }
		  }
	  }

	  /////////////////helper////////////////////

	  void print (T value) 
	  {
		  for (int i{0}; i != my_size; i++ )
		  {
			  std::cout << data[i] << std::endl;
		  }
	  }
	  void analize() 
	  {
		  std::cout << "Check capasity" << my_capacity << std::endl;
		  std::cout << "Check to size" << my_size << std::endl;
		  std::cout << "Print vector: \n";
		  print(data[0]);
	  }

	  /////////////////methods////////////////////

	  T& front() //first element
	  {
		  std::cout << "front" << std::endl;
		  return data[0];
	  }
	  T& back() //last element
	  {
		  std::cout << "back" << std::endl;
		  return data[my_size - 1];
	  }
      T* begin() //begin
	  {
		  std::cout << "begin" << std::endl;
		  return data; 
	  }
	  T* end() //end
	  { 
		  std::cout << "end" << std::endl;
		  return data + my_size; 
	  }
	  const size_t capacity() // know capacity
	  {
		  std::cout << "capacity" << std::endl;
		  return my_capacity;
	  }
	  const size_t size() // know size
	  {
		  std::cout << "size" << std::endl;
		  return my_size;
	  }
	  void push_front (const T & v) //push front func
	  {
		  std::cout << "push_front" << std::endl;
		  if((my_size + 1) > my_capacity) 
		  {
			  my_capacity++;
		  }
		  T* array = new T[my_capacity] {};
		  array[0] = v;
		  for (int i{0}; i != size; i++)
		  {
			  array[i + 1] = std::move(data[i]);
		  }
		  data = std::move(array);
		  size++;
	  }
	  void push_back (const T & v) //push back func
	  {
		  std::cout << "push_back" << std::endl;
		  if(my_size >= my_capacity) 
		  {
			  reserve(my_capacity + 5);
		  }
		  data[my_size++] = v;
	  }
	  void pop_back () //delete last element 
	  {
		  std::cout << "pop_back" << std::endl;
		  my_size--;
	  }
	  void insert (size_t pos, T value) //insert into vector
	  {
		  std::cout<< "insert" << std::endl;
		  if((pos + 1) > my_size) 
		  {
			  pos = my_size;
			  my_size++;
			  if(my_size > my_capacity) 
			  {
				  resize(my_size);
			  }
		  }
		  data[pos] = std::move(value);
	  }
	  void resize (size_t size) //resize
	  {
		  std::cout << "resize" << std::endl;
		  reserve(size);
		  my_size = size;
	  }
	  void reserve (size_t new_capacity) //reserve
	  {
		  std::cout << "reserve" << std::endl;
		  if (data == 0) 
		  {
			  my_size = 0;
			  my_capacity = 0;
		  }
		  T* new_data = new T[new_capacity];
		  size_t size_ = new_capacity < my_size ? new_capacity : my_size;
		  for(size_t i = 0; i < size_; i++) 
		  {
			  new_data[i] = data[i];
		  }
		  my_capacity = new_capacity;
		  delete[] data;
		  data = new_data;
	  }
	  void erase (size_t pos) // delete elements by position
	  {
		  std::cout << "erase" << std::endl;
		  if((pos + 1) > my_size) 
		  {
			  pos = my_size;
		  }
		  T* array = new T[my_capacity];

		  size_t i{};
		  for (; i != pos; i++) 
		  {
			  std::cout << i;
			  array[i] = std::move(data[i]);
		  }
		  for (; i != my_size; i++)
		  {
			  std::cout << i;
			  array[i] = std::move(data[i+1]);
		  }
		  data = array;
		  size--;
	  }
	  void empty() //clear all
	  {
		  std::cout << "Empty" << std::endl;
		  my_capacity = 0;
		  my_size = 0;
		  data = 0;
	  }

  private:

	  T* data = 0;
	  size_t my_capacity = 0;
	  size_t my_size = 0;

};
