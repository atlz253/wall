#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <iostream>

template <typename T>
T random(T from, T to)
{
  static std::default_random_engine generator;
  std::uniform_int_distribution<T> distribution(from, to);
  return distribution(generator);
}

#endif // RANDOM_HPP
