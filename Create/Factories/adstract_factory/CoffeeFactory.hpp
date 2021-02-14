#pragma once
#include "Coffee.hpp"
#include <memory>

using namespace std;

struct CoffeeFactory
{
  virtual ~CoffeeFactory()=default;
  virtual unique_ptr<Coffee> make_coffee() = 0;
};

struct LatteFactory : CoffeeFactory
{
  unique_ptr<Coffee> make_coffee()
  { 
    return make_unique<Latte>(); 
  }
};

struct AmericanoFactory : CoffeeFactory
{
  unique_ptr<Coffee> make_coffee() 
  {
    return make_unique<Americano>(); 
  }
};

struct CaffemochaFactory : CoffeeFactory
{
  unique_ptr<Coffee> make_coffee() 
  {
    return make_unique<Caffemocha>(); 
  }
};