#pragma once
#include "Vector_Realization.hpp"

template<typename T, class Vector>
class Stack
{
  public:

	  Stack() = default;
	  Stack(const size_t size) {};
	  ~Stack() = default;

	  /////////////////methods////////////////////

	  void push(const T & v) //push to the last el
	  {
		  proxy.push_back(v);
	  };

	  void pop() //delete last el
	  {
		  proxy.pop_back();
	  }

	  void top() //shaw last el
	  {
		  proxy.back();
	  }

	  void empty() //clear all stack
	  {
		  proxy.empty();
	  }
	  /////////////////helper////////////////////

	  void analize() 
	  {
		  proxy.analize();
	  }

  private:

	  Vector proxy;

};
