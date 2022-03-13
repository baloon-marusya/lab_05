// Copyright 2021 Melnikova Maria <dandelion.m@mail.ru>

#ifndef INCLUDE_NON_COPIED_STACK_2_HPP_
#define INCLUDE_NON_COPIED_STACK_2_HPP_

#include "element_of_stack.hpp"
#include <utility>

template <typename T>
class non_copied_stack_2 {
 private:
  element_of_stack<T> *up = nullptr;
 public:
  non_copied_stack_2() = default;
  non_copied_stack_2(const non_copied_stack_2& stack) = delete;
  non_copied_stack_2(non_copied_stack_2&& stack) noexcept = default;
  auto operator=(const non_copied_stack_2& stack) = delete;
  auto operator=(non_copied_stack_2&& stack) noexcept
      -> non_copied_stack_2& = default;
  template <typename ... Args>
  void push_emplace(Args&& ... val);
  void push(T&& val);
  T pop();
  const T& head() const;
  ~non_copied_stack_2();
};

template <typename T>
template <typename ... Args>
void non_copied_stack_2<T>::push_emplace(Args&& ... val)
{
  auto *tmp = up;
  up = new element_of_stack<T>{{std::forward<Args>(val) ... }, tmp};
}

template <typename T>
void non_copied_stack_2<T>::push(T&& val)
{
  auto *tmp = up;
  up = new element_of_stack<T>{std::forward<T>(val), tmp};
}

template <typename T>
T non_copied_stack_2<T>::pop()
{
  if (up)
  {
    auto *tmp = up;
    T val = std::move(up -> val);
    up = up -> previous;
    delete tmp;
    return val;
  }else{
    throw std::exception();
  }
}

template <typename T>
const T& non_copied_stack_2<T>::head() const
{
  return up -> val;
}

template <typename T>
non_copied_stack_2<T>::~non_copied_stack_2()
{
  while (up)
  {
    auto *tmp = up;
    up = up -> previous;
    delete tmp;
  }
}

#endif  // INCLUDE_NON_COPIED_STACK_2_HPP_
