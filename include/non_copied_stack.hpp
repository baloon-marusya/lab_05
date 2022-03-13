// Copyright 2021 Melnikova Maria <dandelion.m@mail.ru>

#ifndef INCLUDE_NON_COPIED_STACK_HPP_
#define INCLUDE_NON_COPIED_STACK_HPP_

#include "element_of_stack.hpp"
#include <utility>

template <typename T>
class non_copied_stack {
 private:
  element_of_stack<T> *up = nullptr;
 public:
  non_copied_stack() = default;//конструктор по умолчанию
  non_copied_stack(const non_copied_stack& stack) = delete;//запрет неявного копирования
  non_copied_stack(non_copied_stack&& stack) noexcept = default;
  auto operator=(const non_copied_stack& stack) = delete;
  auto operator=(non_copied_stack&& stack) noexcept -> non_copied_stack& = default;
  void push (const T& val);
  void push (T&& val);
  T pop();
  const T& head () const;
  ~non_copied_stack();
};

template <typename T>
void non_copied_stack<T>::push(const T& val)
{
  auto *tmp = up;
  up = new element_of_stack<T>{val, tmp};
}

template <typename T>
void non_copied_stack<T>::push(T&& val)
{
  auto *tmp = up;
  up = new element_of_stack<T>{std::forward<T>(val), tmp};
}

template <typename T>
T non_copied_stack<T>::pop()
{
  if (up)
  {
    auto *tmp = up;
    T val = std::move(up -> val);
    up = up -> previous;
    delete tmp;
    return val;
  }
  else
  {
    throw std::exception();
  }
}

template <typename T>
const T& non_copied_stack<T>::head() const
{
  return up -> val;
}

template <typename T>
non_copied_stack<T>::~non_copied_stack()
{
  while (up)
  {
    auto *tmp = up;
    up = up -> previous;
    delete tmp;
  }
}

#endif //INCLUDE_NON_COPIED_STACK_HPP_
