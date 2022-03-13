// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_ELEMENT_OF_STACK_HPP_
#define INCLUDE_ELEMENT_OF_STACK_HPP_

template <typename T>
struct element_of_stack
{
  T val;
  element_of_stack<T> *previous;
};

#endif // INCLUDE_ELEMENT_OF_STACK_HPP_
