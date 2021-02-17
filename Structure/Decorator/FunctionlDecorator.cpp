#include <iostream>
#include <functional>
#include <string>

using namespace std;

/**
 * functional decorator can wrap either blocks of code or particular funtions 
 * to allow composition of behavior
*/

// Logger1
struct Logger1
{
  function<void()> fun;
  string name;

  Logger1(const function<void()>& fun, const string& name) :
  fun{fun}, name{name} {}

  void operator()() const
  {
    cout << "function \"" << name << "\" begins" << "\n";
    fun();
    cout << "function \"" << name << "\" end" << "\n\n";
  }
};

// Logger2
template<typename Fun> struct Logger2
{
  Fun fun;
  string name;

  Logger2(const Fun& fun, const string& name) :
  fun{fun}, name{name} {}

  void operator()()
  {
    cout << "function \"" << name << "\" begins" << "\n";
    fun();
    cout << "function \"" << name << "\" end" << "\n\n";
  }
};

// helper function to deducing Logger2's template arguments
template<typename Fun> 
Logger2<Fun> make_logger2(const Fun& fun, const string& name)
{
  return Logger2<Fun>{fun, name};
}

// Logger3
template<typename> struct Logger;
template<typename R, typename ...Args>
struct Logger<R(Args...)>
{
  function<R(Args...)> fun;
  string name;

  Logger(const function<R(Args...)>& fun, const string& name) :
  fun{fun}, name{name} {}

  R operator()(Args ...args)
  {
    cout << "function \"" << name << "\" begins" << "\n";
    R result = fun(args...);
    cout << "function \"" << name << "\" end" << "\n\n";
    return result;
  }
};

// helper function to deducing Logger3's template arguments
template<typename R, typename ...Args>
auto make_logger3(R (*fun)(Args...), const string& name)
{
  return Logger<R(Args...)>{function<R(Args...)>{fun}, name};
}

int add(int x, int y);

int main() {
  Logger1([](){ cout << "Hellow" << endl;}, "HelloFunction")();

  auto logger2 =
      make_logger2([]() { cout << "What up" << endl; }, "WhatUpFunction");
  logger2();

  auto logged3 = make_logger3(add, "AddFunction");
  auto result = logged3(5, 3);
  cout << "result = " << result << endl;
}

int add(int x, int y)
{
  cout << "add function called" << endl;
  return x + y;
}