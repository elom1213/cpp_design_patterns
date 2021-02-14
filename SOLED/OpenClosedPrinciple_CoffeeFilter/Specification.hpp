#pragma once
#include "CoffeeType.hpp"

template<typename T> struct AndSpecification;

template<typename T> struct Specification
{
  virtual bool is_satisfied(T*) = 0;

  AndSpecification<T> operator&&(Specification&& other)
  {
    return AndSpecification<T>(*this, other);
  }
};

struct ColorSpecification : public Specification<Coffee>
{
  Color color;
  explicit ColorSpecification(const Color color) :
  color{color} {}
  bool is_satisfied(Coffee* item) override
  {
    return item->color == color;
  }
};

struct SizeSpecification : public Specification<Coffee>
{
  Size size;
  explicit SizeSpecification(const Size size) :
  size{size} {}
  bool is_satisfied(Coffee* item) override
  {
    return item->size == size;
  }
};

struct TemperatureSpecification : public Specification<Coffee>
{
  Temperature temperature;
  explicit TemperatureSpecification(const Temperature temperature) :
  temperature{temperature} {}
  bool is_satisfied(Coffee* item) override
  {
    return item->temperature == temperature;
  }
};

template<typename T> struct AndSpecification : Specification<T>
{
  Specification<T>& first;
  Specification<T>& second;
  
  AndSpecification(Specification<T>& fst, Specification<T>& sec) :
  first{fst}, second{sec} {}
  bool is_satisfied(T* item) override
  {
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};
